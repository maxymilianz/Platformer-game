// GameLikeOri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classes.h"
#include "Settings.h"
#include "Sound.h"
#include "Initializations.h"
#include "Updates.h"
#include "BestResultsOperations.h"

void end() {
	window.close();
}

void pause() {
	paused = 1;
	window.setMouseCursorVisible(1);
	menu.setPlayingOffset(milliseconds(500));
	menuMusic();
}

void resume() {
	paused = 0, inMenu = 0;
	window.setMouseCursorVisible(0);
	game.setPlayingOffset(milliseconds(500));
	gameMusic();
	loading = 0;
}

void move(char v) {
	if ((posX >= 0 && v < 0) || (posX <= resX / 2 && v > 0))
		posX += v;
	else if (posX <= resX - 84 && bgX + v + resX >= bgResX && v > 0) {
		posX += v;
		if (chestOrPortal.rect == 1)
			updateChestOrPortal();
	}
	else if (bgX + v >= 0 && bgX + v + resX <= bgResX) {
		bgX += v / 2;
		chestOrPortal.posX -= v;
		eOpenText.move(-v, 0);
		eEnterText.move(-v, 0);

		grassX -= v;
		if (grassX <= -256 || grassX >= 0)
			grassX = -128;

		//for (char i = 0; i < nrOfFloors; i++)
			//floors[i].posX -= v;

		for (char i = 0; i < nrOfEnemies; i++)
			enemies[i].posX -= v;
	}

	movement++;
	if (movement > 9)
		movement = 0;

	if (movement > 5)
		currentCharacterRect = 6 - 2 * aimDirX;
	else
		currentCharacterRect = 7 - 2 * aimDirX;
}

void jump() {
	posY += accelerationY;
	accelerationY++;
	speedX += 2;

	if (posY >= groundY[currentGroundY])
		jumped = 0, posY = groundY[currentGroundY];

	currentCharacterRect = 3 - aimDirX;
}

void changeWeapon(char n) {
	currentWeapon += n;
	while (currentWeapon >= nrOfWeapons)
		currentWeapon -= nrOfWeapons;
	while (currentWeapon < 0)
		currentWeapon += nrOfWeapons;
}

void die() {
	currentCharacterRect = 11 - aimDirX, currentGroundY = 2;
}

void gotHit(char dmg) {
	playerHurtPlay();
	health -= dmg;
	if (health <= 0)
		die(), accelerationY = -16;
}

void collision(char dmg, char enemy) {
	playerHurtPlay();
	health -= dmg;
	attacked = 1;
	accelerationY = -16;
	angle = -30;
	aimDirX = posX + 48 < enemies[enemy].posX + 45 ? 0 : 1;
	currentCharacterRect = 1 - aimDirX;
	if (health <= 0)
		die();
}

void fall() {
	posX += speedX * (aimDirX ? 1 : -1);
	posY += accelerationY;
	accelerationY++;
	if (posY >= groundY[currentGroundY])
		posY = groundY[currentGroundY], attacked = 0;
}

void checkForCollision() {
	for (char i = 0; i < 127; i++) {
		for (char j = 0; j < nrOfEnemies; j++) {
			if (enemies[j].health > 0 && bullets[i].rect != 1 && bullets[i].visible && bullets[i].type < 3 &&
				IntRect(bullets[i].posX + 7, bullets[i].posY + 9, 20, 14).intersects(IntRect(enemies[j].posX, enemies[j].posY, 90, 84))) {
				bullets[i].hit();
				enemyHurtPlay(enemies[j].type);
				explosion(bullets[i].power, bullets[i].posX, bullets[i].posY);
				enemies[j].gotHit(bullets[i].power);
			}
		}

		if (health > 0 && bullets[i].rect != 1 && bullets[i].visible &&
			IntRect(bullets[i].posX + 7, bullets[i].posY + 9, 20, 14).intersects(IntRect(posX + 18, posY + 18, 54, 72))) {
			bullets[i].hit();
			explosion(bullets[i].power, bullets[i].posX, bullets[i].posY);
			gotHit(bullets[i].power);
		}
	}

	for (char i = 0; i < nrOfEnemies; i++) {
		if (health > 0 && enemies[i].health > 0 &&
			IntRect(posX + 18, posY + 18, 54, 72).intersects(IntRect(enemies[i].posX, enemies[i].posY, 90, 84))) {
			collision(enemies[i].power, i);
		}
	}

	/*for (char i = 0; i < nrOfFloors; i++) {
		if (posX + 18 <= floors[i].posX + floors[i].amount * floorTextures[level].getSize().x / 4 && posX + 72 >= floors[i].posX && posY + 72 <= floors[i].posY)
			currentGroundY = 1;
		else if (posX + 18 <= floors[i].posX + floors[i].amount * floorTextures[level].getSize().x / 4 && posX + 72 >= floors[i].posX && posY + 6 <= floors[i].posY + 21)
			accelerationY *= -1, posY = floors[i].posY + 15;
		else if (posX + 18 <= floors[i].posX + floors[i].amount * floorTextures[level].getSize().x / 4 && posX + 72 >= floors[i].posX && posY + 6 <= floors[i].posY && posY + 72 >= floors[i].posY + 21)
			posX = floors[i].posX + floors[i].amount * floorTextures[level].getSize().x / 4 - 18;
		else if (posX + 72 >= floors[i].posX && posX + 18 <= floors[i].posX + floors[i].amount * floorTextures[level].getSize().x / 4 && posY + 6 <= floors[i].posY && posY + 72 >= floors[i].posY + 21)
			posX = floors[i].posX - 72;
	}*/

	openOrEnter = 0;
	if (IntRect(posX + 18, posY + 18, 54, 72).intersects(IntRect(chestOrPortal.posX - 20, chestOrPortal.posY, 120, 120)))
		openOrEnter = 1;
}

void aim() {
	angle = atan2(mousePos.x - (posX + 56), mousePos.y - (posY + 64)) / M_PI * 180;

	if (angle < 0) {
		aimDirX = 0;
		currentWeaponRect = 2;
	}
	else
		aimDirX = 1;
}

void defense() {
	defensed = 1;
}

void fallBeyondMap() {
	if (posY < groundY[currentGroundY])
		posY += accelerationY, accelerationY++;
	else
		pause(), died = 1;
}

void newGame() {
	if (loading == 1) {
		speedX = initSpeedX, accelerationY = 16, health = 100, stamina = 100;
		currentBg++;
		if (currentBg == 19)
			currentBg = 0;
		posX = 128, posY = 382, bgX = 0, bgY, bgResX = bgTextures[currentBg].getSize().x, bgResY = resY, grassX = -128;

		initializeChestOrPortal();
		//initializeFloors();
		initializeEnemies();

		resume();
	}
	else
		loading = 1;
}

void newWeapon() {
	nrOfWeapons++;
	weaponUnlocked = 1;
}

void moveBg(char v) {
	if (!bgDirX)
		v *= -1;

	if (bgX + v >= 0 && bgX + v + resX <= bgResX)
		bgX += v / 2;
	else
		bgDirX = !bgDirX;
}

void continueGame() {
	if (loading == -1) {
		loading = 1;
		newGame();
	}
	else
		loading = -1;
}

void newLevel() {
	level++, levelPassed = 1, free(enemies);
}

void reset() {
	level = 0, nrOfWeapons = 1;
}

void checkEvents() {
	Event event;

	if (!paused) {
		updateEnemies();
		updateBullets();
		updateExplosions();
		if (chestOrPortal.rect != 1)
			updateChestOrPortal();
		if (temperature > 1)
			temperature -= 2;
		else if (temperature == 1)
			temperature = 0;

		if (health > 0) {
			if (aimDirX)
				currentCharacterRect = 8;
			else
				currentCharacterRect = 9;
			currentGroundY = 0;
			currentWeaponRect = 0;
			checkForCollision();

			if (attacked)
				fall();
			else {
				if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))		// movement
					move(-speedX);
				else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
					move(speedX);

				speedX = initSpeedX;

				if (jumped)
					jump();
				else if (posY != groundY[currentGroundY])
					accelerationY = 0, jumped = 1, jump();

				mousePos = Mouse::getPosition(window);		// aim
				aim();
				if (Keyboard::isKeyPressed(Keyboard::LControl))		// shoot from keyboard
					shoot(-1);
				else if (Mouse::isButtonPressed(Mouse::Left))		// mouse action
					shoot(-1);
				else if (Mouse::isButtonPressed(Mouse::Right))
					defense();

				if (Keyboard::isKeyPressed(Keyboard::Space) && posY == groundY[currentGroundY])		// jump
					accelerationY = -16, jumped = 1;
			}
		}
		else
			fallBeyondMap();
	}
	else
		moveBg(2);

	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)		// close
			window.close();

		if (!paused) {
			if (health > 0) {
				if (event.type == Event::MouseWheelScrolled)		// choose weapon
					changeWeapon(event.mouseWheelScroll.delta);
				else if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up)
						changeWeapon(-1);
					else if (event.key.code == Keyboard::Down)
						changeWeapon(1);
					else if (event.key.code == Keyboard::Escape)
						pause();
					else if (event.key.code == Keyboard::E && openOrEnter) {
						if (!typeOfExit)
							openChestPlay(), pause(), newWeapon();
						else
							enterPortalPlay(), pause(), newLevel();
					}
				}
				else if (event.type == Event::LostFocus)
					pause();
			}
		}
		else if (bestResults) {
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				bestResults = 0;
		}
		else if (toExit) {
			if (event.type == Event::KeyPressed)
				free(enemies), window.close();
		}
		else if (weaponUnlocked) {
			if (event.type == Event::KeyPressed)
				weaponUnlocked = 0, newLevel();
		}
		else if (levelPassed) {
			if (event.type == Event::KeyPressed) {
				levelPassed = 0;

				if (level < 18)
					newGame();
				else
					gameFinished = 1;
			}
		}
		else if (gameFinished) {
			if (event.type == Event::KeyPressed)
				gameFinished = 0, getName = checkPosition(level), moveResults();
		}
		else if (getName < 5) {
			if (event.type == Event::KeyPressed && event.key.code >= 0 && event.key.code <= 35)
				enterName(event.key.code);
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				scores[getName] = level, getName = 5, inMenu = 1;
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace)
				delete1Char();
		}
		else if (died) {
			if (event.type == Event::KeyPressed)
				died = 0, getName = checkPosition(level), moveResults();
		}
		else if (!inMenu) {
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape || event.type == Event::MouseButtonPressed &&
				event.mouseButton.button == Mouse::Left && IntRect(350, 165, 500, 100).contains(Mouse::getPosition(window)))
				resume();
			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left &&
				IntRect(400, 465, 400, 100).contains(Mouse::getPosition(window)))
				toExit = 1;
		}
		else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			if (IntRect(320, 15, 416, 100).contains(Mouse::getPosition(window)))
				reset(), newGame();
			else if (IntRect(180, 165, 680, 100).contains(Mouse::getPosition(window)))
				continueGame();
			else if (IntRect(200, 315, 640, 100).contains(Mouse::getPosition(window)))
				bestResults = 1;
			else if (IntRect(400, 465, 400, 100).contains(Mouse::getPosition(window)))
				toExit = 1;
		}
	}

	if (loading == 1)
		newGame();
	else if (loading == -1)
		continueGame();
}

int main()
{
	window.setFramerateLimit(60);

	initializeSounds();
	initializeImgs();
	initializeChestOrPortal();
	initializeExplosions();
	initializeTextures();
	initializeTexts();
	initializeRects();

	menu.setPlayingOffset(milliseconds(500));
	menuMusic();

	while (window.isOpen()) {
		checkEvents();
		window.clear();

		{		// updates------------------------------------------------------------------------------------------------------------------------------------------
			if (!paused) {
				Sprite bgSprite;
				Sprite grassSprites[10];
				Sprite floorSprites[20];
				Sprite chestSprite;
				Sprite enemySprites[maxNrOfEnemies];
				Sprite characterSprite;
				Sprite weaponSprite;
				Sprite bulletSprites[maxNrOfBullets];
				Sprite explosionSprites[maxNrOfExplosions];
				Sprite healthBallSprites[maxNrOfEnemies][maxNrOfHealthBalls];
				Sprite viewfinderSprite;

				bgSprite.setTexture(bgTextures[currentBg]);		// bg
				bgResX = bgTextures[currentBg].getSize().x;
				bgY = bgTextures[currentBg].getSize().y - bgResY;
				bgSprite.setTextureRect(IntRect(bgX, bgY, bgResX, bgResY));
				window.draw(bgSprite);

				if (typeOfExit) {		// portal
					chestSprite.setTexture(portalTexture);
					chestSprite.setTextureRect(portalRects[chestOrPortal.rect]);
					chestSprite.setOrigin(Vector2f(31, 30));
					chestSprite.scale(chestOrPortal.scale, chestOrPortal.scale);
					chestSprite.rotate(chestOrPortal.angle);
					chestSprite.setPosition(chestOrPortal.posX, chestOrPortal.posY);
					window.draw(chestSprite);
				}

				grassSprites[0].setTexture(grassTextures[currentGrass]);		// grass
				grassSprites[0].scale(Vector2f(0.25f, 0.25f));
				grassSprites[0].setPosition(Vector2f(grassX, resY - grassTextures[currentGrass].getSize().y / 4));
				window.draw(grassSprites[0]);

				for (char i = 1; i < 10; i++) {
					grassSprites[i] = grassSprites[i - 1];
					grassSprites[i].move(Vector2f(grassTextures[currentGrass].getSize().x / 4, 0));
					window.draw(grassSprites[i]);
				}

				/*for (char j = 0; j < nrOfFloors; j++) {		// floors
					floorSprites[10 * j].setTexture(floorTextures[level]);
					floorSprites[10 * j].scale(Vector2f(0.25f, 0.25f));
					floorSprites[10 * j].setPosition(Vector2f(floors[j].posX, 360));
					window.draw(floorSprites[0]);

					for (char i = 1; i < floors[j].amount; i++) {
						floorSprites[i] = floorSprites[i - 1];
						floorSprites[i].move(Vector2f(64, 0));
						window.draw(floorSprites[i]);
					}
				}*/

				if (!typeOfExit) {		// chestOrPortal
					chestSprite.setTexture(chestTexture);
					chestSprite.setTextureRect(chestRects[chestOrPortal.rect]);
					chestSprite.scale(Vector2f(1.5f, 1.5f));
					chestSprite.setPosition(chestOrPortal.posX, chestOrPortal.posY);
					window.draw(chestSprite);
				}

				for (char i = 0; i < nrOfEnemies; i++) {		// enemies
					char type = enemies[i].type;
					enemySprites[i].setTexture(enemyTextures[type]);
					enemySprites[i].setTextureRect(enemyRects[type][enemies[i].rect]);
					enemySprites[i].scale(Vector2f(1.5f, 1.5f));
					enemySprites[i].setPosition(enemies[i].posX, enemies[i].posY);
					window.draw(enemySprites[i]);
				}

				characterSprite.setTexture(characterTextures[currentCharacter]);		// character
				characterSprite.setTextureRect(characterRects[currentCharacter][currentCharacterRect]);
				characterSprite.scale(Vector2f(3.f, 3.f));
				characterSprite.setPosition(Vector2f(posX, posY));
				window.draw(characterSprite);

				weaponSprite.setTexture(weaponTexture);		// weapon
				weaponSprite.setPosition(Vector2f(posX + 56, posY + 64));
				weaponSprite.setOrigin(16, weaponTexture.getSize().y / 2);
				weaponSprite.setTextureRect(weaponRects[currentWeaponRect]);
				weaponSprite.setRotation(-angle + 90);
				window.draw(weaponSprite);

				for (char i = 0; i < maxNrOfBullets; i++) {		// bullets
					if (bullets[i].visible) {
						char type = bullets[i].type % 3;
						bulletSprites[i].setTexture(bulletTextures[type]);
						bulletSprites[i].setTextureRect(bulletRects[type][bullets[i].rect]);
						bulletSprites[i].setOrigin(16, 16);
						bulletSprites[i].setPosition(bullets[i].posX, bullets[i].posY);
						bulletSprites[i].setRotation(bullets[i].angle);
						window.draw(bulletSprites[i]);
					}
				}

				for (char i = 0; i < maxNrOfExplosions; i++) {		// explosions
					if (explosions[i].rect != 1) {
						explosionSprites[i].setTexture(explosionTextures[explosions[i].string]);
						explosionSprites[i].scale(Vector2f(0.5f, 0.5f));
						explosionSprites[i].setPosition(explosions[i].posX, explosions[i].posY);
						window.draw(explosionSprites[i]);
					}
				}

				char i;		// healthBalls

				for (i = 0; i < health / 10; i++) {
					healthBallSprites[0][i].setTexture(healthBallTexture);
					healthBallSprites[0][i].setTextureRect(healthBallRects[0]);
					healthBallSprites[0][i].scale(3, 3);
					healthBallSprites[0][i].setPosition(24 + 48 * i, 24);
					window.draw(healthBallSprites[0][i]);
				}

				for (short j = 0; j < nrOfEnemies; j++) {
					for (char k = 0; k < enemies[j].health; k++) {
						healthBallSprites[j + 1][k].setTexture(healthBallTexture);
						healthBallSprites[j + 1][k].setTextureRect(healthBallRects[0]);
						healthBallSprites[j + 1][k].setPosition(enemies[j].posX + 45 - 9 * enemies[j].health + 18 * k, enemies[j].posY - 20);
						window.draw(healthBallSprites[j + 1][k]);
					}
				}

				/*if (openOrEnter) {		// open / enter text
					if (!typeOfExit) {
						eOpenText.setFillColor(Color(255, 0, 0, 255));
						window.draw(eOpenText);
					}
					else {
						eEnterText.setFillColor(Color(255, 0, 0, 255));
						window.draw(eEnterText);
					}
				}*/

				temperatureText.setFillColor(Color(255, 0, 0, temperature));		// temperatureText
				window.draw(temperatureText);

				viewfinderSprite.setTexture(viewfinderTexture);		// viewfinder
				viewfinderSprite.scale(Vector2f(0.08f, 0.08f));
				viewfinderSprite.setPosition(mousePos.x - 29, mousePos.y - 29);
				window.draw(viewfinderSprite);
			}
			else {
				if (!weaponUnlocked && !levelPassed && !gameFinished && !died) {
					Sprite bluredBgSprite;		// bg
					bluredBgSprite.setTexture(bluredBgTextures[currentBg]);
					bgResX = bluredBgTextures[currentBg].getSize().x;
					bluredBgSprite.setTextureRect(IntRect(bgX, bgY, bgResX, bgResY));
					window.draw(bluredBgSprite);


					if (loading != 0) {
						//window.draw(loadingRect);
						window.draw(loadingText);
					}
					else if (toExit) {
						Sprite creditsSprite;		// credits
						creditsSprite.setTexture(creditsTexture);
						window.draw(creditsSprite);
					}
					else if (bestResults) {
						Text bestResultsText2 = bestResultsText;
						bestResultsText2.move(0, -300);
						window.draw(bestResultsText2);

						char nrOfBestResults = nrOfScores();
						Text namesText[5];
						Text scoresText[5];

						for (char i = 0; i < nrOfBestResults; i++) {
							namesText[i].setFont(font);
							namesText[i].setString(names[i]);
							namesText[i].setCharacterSize(52);
							namesText[i].setPosition(resX / 3 - length(i), 150 + 76 * i);
							window.draw(namesText[i]);
						}

						for (char i = 0; i < nrOfBestResults; i++) {
							scoresText[i].setFont(font);
							scoresText[i].setString(std::to_string(scores[i]));
							scoresText[i].setCharacterSize(52);
							scoresText[i].setPosition(2 * resX / 3, 150 + 76 * i);
							window.draw(scoresText[i]);
						}
					}
					else if (inMenu) {
						//window.draw(newGameRect);
						window.draw(newGameText);
						//window.draw(continueGameRect);
						window.draw(continueGameText);
						//window.draw(bestResultRect);
						window.draw(bestResultsText);
						//window.draw(exitRect);
						window.draw(exitText);
					}
					else if (getName < 5) {
						window.draw(enterNameText);

						Text name;
						name.setFont(font);
						name.setString(names[getName]);
						name.setCharacterSize(52);
						name.setPosition(resX / 2 - length() / 3 * 52, 350);
						window.draw(name);
					}
					else {
						//window.draw(resumeRect);
						window.draw(resumeText);
						//window.draw(menuRect);
						//window.draw(menuText);
						//window.draw(exitRect);
						window.draw(exitText);
					}
				}
				else {
					if (weaponUnlocked) {
						Sprite newWeaponSprite;
						newWeaponSprite.setTexture(newWeaponTexture);
						window.draw(newWeaponSprite);
					}
					else if (levelPassed) {
						Sprite newLevelSprite;
						newLevelSprite.setTexture(newLevelTexture);
						window.draw(newLevelSprite);
					}
					else if (gameFinished) {
						Sprite finishSprite;
						finishSprite.setTexture(finishTexture);
						window.draw(finishSprite);
					}
					else {
						Sprite diedSprite;
						diedSprite.setTexture(diedTexture);
						window.draw(diedSprite);
					}
				}
			}
		}

		window.display();
	}

	return 0;
}