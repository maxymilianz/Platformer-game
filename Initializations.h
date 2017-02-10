#pragma once

void initializeChestOrPortal() {
	if (level < 15)
		typeOfExit = !(level && !(level % 5));
	else
		typeOfExit = 1;

	chestOrPortal.posX = bgResX + 128;
	if (!typeOfExit)
		chestOrPortal.posY = 461;
	else
		chestOrPortal.posY = 440;
	chestOrPortal.rect = 1;
}

void initializeExplosions() {
	explosionStrings[0] = "graphics/explosion/8.png";
	explosionStrings[1] = "graphics/explosion/9.png";
	explosionStrings[2] = "graphics/explosion/10.png";
	explosionStrings[3] = "graphics/explosion/11.png";
	explosionStrings[4] = "graphics/explosion/12.png";
	explosionStrings[5] = "graphics/explosion/13.png";
	explosionStrings[6] = "graphics/explosion/14.png";
	explosionStrings[7] = "graphics/explosion/15.png";
	explosionStrings[8] = "graphics/explosion/16.png";
	explosionStrings[9] = "graphics/explosion/0.png";
	explosionStrings[10] = "graphics/explosion/1.png";
	explosionStrings[11] = "graphics/explosion/2.png";
	explosionStrings[12] = "graphics/explosion/3.png";
	explosionStrings[13] = "graphics/explosion/4.png";
	explosionStrings[14] = "graphics/explosion/5.png";
	explosionStrings[15] = "graphics/explosion/6.png";
}

/*void initializeRectShapes() {
	newGameRect.setSize(Vector2f(450, 100));		// new game
	newGameRect.setOutlineThickness(10);
	newGameRect.setOutlineColor(Color());
	newGameRect.setFillColor(Color(127, 127, 127, 255));

	continueGameRect.setSize(Vector2f(450, 100));		// continue game
	continueGameRect.setOutlineThickness(10);
	continueGameRect.setOutlineColor(Color());
	continueGameRect.setFillColor(Color(127, 127, 127, 255));

	bestResultRect.setSize(Vector2f(600, 100));		// best results
	bestResultRect.setOutlineThickness(10);
	bestResultRect.setOutlineColor(Color());
	bestResultRect.setFillColor(Color(127, 127, 127, 255));

	menuRect.setSize(Vector2f(200, 100));		// menu
	menuRect.setOutlineThickness(10);
	menuRect.setOutlineColor(Color());
	menuRect.setFillColor(Color(127, 127, 127, 255));

	exitRect.setSize(Vector2f(200, 100));		// exit
	exitRect.setOutlineThickness(10);
	exitRect.setOutlineColor(Color());
	exitRect.setFillColor(Color(127, 127, 127, 255));

	resumeRect.setSize(Vector2f(300, 100));		// resume
	resumeRect.setOutlineThickness(10);
	resumeRect.setOutlineColor(Color());
	resumeRect.setFillColor(Color(127, 127, 127, 255));

	loadingRect.setSize(Vector2f(350, 50));		// loading
	loadingRect.setOutlineThickness(10);
	loadingRect.setOutlineColor(Color());
	loadingRect.setFillColor(Color(127, 127, 127, 255));
}*/

void initializeTexts() {
	font.loadFromFile("graphics/ARCADECLASSIC.TTF");

	newGameText.setFont(font);		// new game
	newGameText.setString("NEW GAME");
	newGameText.setCharacterSize(100);
	newGameText.setPosition(320, 15);

	continueGameText.setFont(font);		// continue game
	continueGameText.setString("CONTINUE GAME");
	continueGameText.setCharacterSize(100);
	continueGameText.setPosition(180, 165);

	bestResultsText.setFont(font);		// best results
	bestResultsText.setString("BEST RESULTS");
	bestResultsText.setCharacterSize(100);
	bestResultsText.setPosition(212, 315);

	menuText.setFont(font);		// menu
	menuText.setString("MENU");
	menuText.setCharacterSize(100);
	menuText.setPosition(400, 315);

	exitText.setFont(font);		// exit
	exitText.setString("EXIT");
	exitText.setCharacterSize(100);
	exitText.setPosition(408, 465);

	resumeText.setFont(font);		// resume
	resumeText.setString("RESUME");
	resumeText.setCharacterSize(100);
	resumeText.setPosition(340, 165);

	temperatureText.setFont(font);		// temperature
	temperatureText.setString("TEMPERATURE");
	temperatureText.setCharacterSize(52);
	temperatureText.setPosition(670, 6);

	eOpenText.setFont(font);		// e open
	eOpenText.setString("E OPEN");
	eOpenText.setCharacterSize(32);
	eOpenText.setPosition(chestOrPortal.posX - 20, chestOrPortal.posY - 100);

	eEnterText.setFont(font);		// e enter
	eEnterText.setString("E ENTER");
	eEnterText.setCharacterSize(32);
	eEnterText.setPosition(chestOrPortal.posX - 20, chestOrPortal.posY - 100);

	loadingText.setFont(font);		// loading
	loadingText.setString("LOADING");
	loadingText.setCharacterSize(52);
	loadingText.setPosition(400, 315);

	enterNameText.setFont(font);		// enter name
	enterNameText.setString("ENTER YOUR NAME");
	enterNameText.setCharacterSize(52);
	enterNameText.setPosition(300, 150);
}

void initializeEnemies() {
	time_t tt;
	srand(time(&tt));
	nrOfEnemies = 5 + level / 2;
	enemies = (NPC *)malloc(sizeof *enemies * nrOfEnemies);

	for (char i = 0; i < nrOfEnemies; i++) {
		if (level < 15)
			enemies[i].type = level / 5 + 1;
		else
			enemies[i].type = (rand() % (nrOfEnemyStrings - 1)) + 1;

		enemies[i].rect = 1;

		enemies[i].health = level * 7 / 20 + 1;
		enemies[i].power = level * 7 / 20 + 1;
		enemies[i].speedX = 4 + enemies[i].type;

		enemies[i].posX = (rand() % (bgResX - resX / 2)) + resX / 2;

		if (enemies[i].type == 1)
			enemies[i].posY = 391;
		else if (enemies[i].type == 2)
			enemies[i].posY = 388;
		else
			enemies[i].posY = 376;

		for (char j = 0; j < i; j++) {
			while (enemies[j].posX - enemies[i].posX < 96 && enemies[j].posX - enemies[i].posX > -96)
				enemies[i].posX = (rand() % (bgResX - resX / 2)) + resX / 2;
		}
	}
}

void initializeImgs() {
	enemyImg[0].bottom = 4, enemyImg[0].left = 1, enemyImg[0].right = 2, enemyImg[0].top = 1;
	characterImg[0].bottom = 12, characterImg[0].left = 12, characterImg[0].right = 18, characterImg[0].top = 15;		// after multiplying x3
	bulletImg[0].bottom = 8, bulletImg[0].left = 7, bulletImg[0].right = 5, bulletImg[0].top = 10;
}

void initializeTextures() {
	bool success;

	for (char i = 0; i < nrOfBluredBgStrings; i++) {		// bluredBgs
		success = bluredBgTextures[i].loadFromFile(bluredBgStrings[i]);
		if (!success)
			bluredBgTextures[i].loadFromFile(bluredBgStrings[i]);
		bluredBgTextures[i].setSmooth(true);
	}

	for (char i = 0; i < nrOfBgStrings; i++) {		// bgs
		success = bgTextures[i].loadFromFile(bgStrings[i]);
		if (!success)
			bgTextures[i].loadFromFile(bgStrings[i]);
		bgTextures[i].setSmooth(true);
	}

	for (char i = 0; i < nrOfGrassStrings; i++) {		// grass
		success = grassTextures[i].loadFromFile(grassStrings[i]);
		if (!success)
			grassTextures[i].loadFromFile(grassStrings[i]);
		grassTextures[i].setSmooth(true);
	}

	success = portalTexture.loadFromFile(portalString);		// portal
	if (!success)
		portalTexture.loadFromFile(portalString);

	for (char i = 0; i < nrOfFloorStrings; i++) {		// floors
		success = floorTextures[i].loadFromFile(floorStrings[i]);
		if (!success)
			floorTextures[i].loadFromFile(floorStrings[i]);
		floorTextures[i].setSmooth(true);
	}

	success = chestTexture.loadFromFile(chestString);		// chestOrPortal
	if (!success)
		chestTexture.loadFromFile(chestString);

	for (char i = 0; i < nrOfEnemyStrings; i++) {		// enemies
		success = enemyTextures[i].loadFromFile(enemyStrings[i]);
		if (!success)
			success = enemyTextures[i].loadFromFile(enemyStrings[i]);
	}

	for (char i = 0; i < nrOfCharacterStrings; i++) {		// character
		success = characterTextures[i].loadFromFile(characterStrings[i]);
		if (!success)
			success = characterTextures[i].loadFromFile(characterStrings[i]);
	}

	success = weaponTexture.loadFromFile(weaponString);		// weapon
	if (!success)
		weaponTexture.loadFromFile(weaponString);

	for (char i = 0; i < nrOfBulletStrings; i++) {		// bullets
		success = bulletTextures[i].loadFromFile(bulletStrings[i]);
		if (!success)
			bulletTextures[i].loadFromFile(bulletStrings[i]);
	}

	for (char i = 0; i < nrOfExplosionStrings - 1; i++) {		// explosions
		success = explosionTextures[i].loadFromFile(explosionStrings[i]);
		if (!success)
			explosionTextures[i].loadFromFile(explosionStrings[i]);
		explosionTextures[i].setSmooth(true);
	}

	success = healthBallTexture.loadFromFile(healthBallString);		// healthBall
	if (!success)
		healthBallTexture.loadFromFile(healthBallString);

	success = viewfinderTexture.loadFromFile(viewfinderString);
	if (!success)
		viewfinderTexture.loadFromFile(viewfinderString);
	viewfinderTexture.setSmooth(true);

	success = creditsTexture.loadFromFile(creditsString);		// credits
	if (!success)
		creditsTexture.loadFromFile(creditsString);

	success = newWeaponTexture.loadFromFile(newWeaponString);		// new weapon
	if (!success)
		newWeaponTexture.loadFromFile(newWeaponString);
	newWeaponTexture.setSmooth(true);

	success = newLevelTexture.loadFromFile(newLevelString);		// new level
	if (!success)
		newLevelTexture.loadFromFile(newLevelString);
	newLevelTexture.setSmooth(true);

	success = finishTexture.loadFromFile(finishString);		// finish
	if (!success)
		finishTexture.loadFromFile(finishString);

	success = diedTexture.loadFromFile(diedString);		// died
	if (!success)
		diedTexture.loadFromFile(diedString);
}

void initializeRects() {
	portalRects[0] = IntRect(169, 160, 62, 61);		// portal
	portalRects[1] = IntRect(0, 0, 0, 0);

	chestRects[1] = IntRect(0, 0, 0, 0);		// chest
	chestRects[2] = IntRect(10, 28, 30, 5);
	chestRects[3] = IntRect(58, 23, 32, 10);
	chestRects[4] = IntRect(107, 19, 32, 14);
	chestRects[5] = IntRect(156, 15, 32, 18);
	chestRects[6] = IntRect(205, 11, 32, 22);

	enemyRects[0][0] = IntRect(0, 0, 48, 40);		// enemies
	enemyRects[0][1] = IntRect(48, 0, 48, 40);
	enemyRects[0][2] = IntRect(18, 40, 48, 40);
	enemyRects[0][3] = IntRect(66, 40, 48, 40);
	enemyRects[0][6] = IntRect(0, 0, 0, 0);

	enemyRects[1][0] = IntRect(3, 3, 56, 62);		// standing r
	enemyRects[1][1] = IntRect(59, 3, -56, 62);		// standing l
	enemyRects[1][2] = IntRect(9, 135, 57, 54);		// going r
	enemyRects[1][3] = IntRect(77, 135, 58, 54);
	enemyRects[1][4] = IntRect(142, 134, 61, 55);
	enemyRects[1][5] = IntRect(212, 135, 58, 54);
	enemyRects[1][6] = IntRect(281, 135, 57, 55);
	enemyRects[1][7] = IntRect(348, 135, 57, 55);
	enemyRects[1][8] = IntRect(411, 134, 62, 56);
	enemyRects[1][9] = IntRect(479, 135, 63, 53);
	enemyRects[1][10] = IntRect(65, 135, -57, 54);		// going l
	enemyRects[1][11] = IntRect(134, 135, -58, 54);
	enemyRects[1][12] = IntRect(202, 134, -61, 55);
	enemyRects[1][13] = IntRect(269, 135, -58, 54);
	enemyRects[1][14] = IntRect(337, 135, -57, 55);
	enemyRects[1][15] = IntRect(404, 135, -57, 55);
	enemyRects[1][16] = IntRect(472, 134, -62, 56);
	enemyRects[1][17] = IntRect(541, 135, -63, 53);
	enemyRects[1][18] = IntRect(3, 328, 59, 56);		// attacked r
	enemyRects[1][19] = IntRect(62, 328, -59, 56);		// attacked l
	enemyRects[1][20] = IntRect(82, 618, 59, 58);		// attacking r
	enemyRects[1][21] = IntRect(141, 618, -59, 58);		// attacking l
	enemyRects[1][22] = IntRect(3, 942, 59, 58);		// jumping r
	enemyRects[1][23] = IntRect(62, 942, -59, 58);		// jumping l
	enemyRects[1][24] = IntRect(0, 0, 0, 0);

	enemyRects[2][0] = IntRect(3, 3, 55, 62);		// standing r
	enemyRects[2][1] = IntRect(58, 3, -55, 62);		// standing l
	enemyRects[2][2] = IntRect(12, 135, 52, 54);		// going r
	enemyRects[2][3] = IntRect(78, 135, 53, 54);
	enemyRects[2][4] = IntRect(138, 134, 59, 55);
	enemyRects[2][5] = IntRect(206, 135, 56, 54);
	enemyRects[2][6] = IntRect(277, 135, 50, 55);
	enemyRects[2][7] = IntRect(338, 135, 54, 55);
	enemyRects[2][8] = IntRect(399, 134, 59, 56);
	enemyRects[2][9] = IntRect(465, 135, 60, 53);
	enemyRects[2][10] = IntRect(64, 135, -52, 54);		// going l
	enemyRects[2][11] = IntRect(131, 135, -53, 54);
	enemyRects[2][12] = IntRect(197, 134, -59, 55);
	enemyRects[2][13] = IntRect(262, 135, -56, 54);
	enemyRects[2][14] = IntRect(327, 135, -50, 55);
	enemyRects[2][15] = IntRect(392, 135, -54, 55);
	enemyRects[2][16] = IntRect(458, 134, -59, 56);
	enemyRects[2][17] = IntRect(525, 135, -60, 53);
	enemyRects[2][18] = IntRect(3, 328, 58, 54);		// attacked r
	enemyRects[2][19] = IntRect(61, 328, -58, 54);		// attacked l
	enemyRects[2][20] = IntRect(64, 630, 56, 58);		// attacking r
	enemyRects[2][21] = IntRect(120, 630, -56, 58);		// attacking l
	enemyRects[2][22] = IntRect(3, 808, 54, 63);		// jumping r
	enemyRects[2][23] = IntRect(57, 808, -54, 63);		// jumping l
	enemyRects[2][24] = IntRect(0, 0, 0, 0);

	enemyRects[3][0] = IntRect(3, 3, 63, 68);		// standing r
	enemyRects[3][1] = IntRect(66, 3, -63, 68);		// standing l
	enemyRects[3][2] = IntRect(4, 149, 63, 63);		// going r
	enemyRects[3][3] = IntRect(74, 149, 63, 63);
	enemyRects[3][4] = IntRect(143, 148, 63, 64);
	enemyRects[3][5] = IntRect(211, 149, 63, 63);
	enemyRects[3][6] = IntRect(280, 149, 63, 64);
	enemyRects[3][7] = IntRect(348, 149, 63, 64);
	enemyRects[3][8] = IntRect(417, 148, 63, 65);
	enemyRects[3][9] = IntRect(486, 149, 64, 62);
	enemyRects[3][10] = IntRect(67, 149, -63, 63);		// going l
	enemyRects[3][11] = IntRect(137, 149, -63, 63);
	enemyRects[3][12] = IntRect(206, 148, -63, 64);
	enemyRects[3][13] = IntRect(274, 149, -63, 63);
	enemyRects[3][14] = IntRect(343, 149, -63, 64);
	enemyRects[3][15] = IntRect(411, 149, -63, 64);
	enemyRects[3][16] = IntRect(480, 148, -63, 65);
	enemyRects[3][17] = IntRect(550, 149, -64, 62);
	enemyRects[3][18] = IntRect(3, 367, 61, 64);		// attacked r
	enemyRects[3][19] = IntRect(64, 367, -61, 64);		// attacked l
	enemyRects[3][20] = IntRect(82, 681, 63, 67);		// attacking r
	enemyRects[3][21] = IntRect(145, 681, -63, 67);		// attacking l
	enemyRects[3][22] = IntRect(3, 962, 63, 71);		// jumping r
	enemyRects[3][23] = IntRect(66, 962, -63, 71);		// jumping l
	enemyRects[3][24] = IntRect(0, 0, 0, 0);

	// character
	characterRects[0][0] = IntRect(32, 0, 32, 32);		// attacked rigth
	characterRects[0][1] = IntRect(64, 0, -32, 32);		// attacked left
	characterRects[0][2] = IntRect(264, 0, 32, 32);		// jumping rigth
	characterRects[0][3] = IntRect(296, 0, -32, 32);		// jumping left
	characterRects[0][4] = IntRect(0, 32, 32, 32);		// going right
	characterRects[0][5] = characterRects[0][2];
	characterRects[0][6] = IntRect(32, 32, -32, 32);		// going left
	characterRects[0][7] = characterRects[0][3];
	characterRects[0][8] = IntRect(32, 32, 32, 32);		// standing right
	characterRects[0][9] = IntRect(64, 32, -32, 32);		// standing left
	characterRects[0][10] = IntRect(0, 0, 32, 32);		// dying right
	characterRects[0][11] = IntRect(32, 0, -32, 32);		//dying left

	weaponRects[0] = IntRect(0, 0, 76, 24);		// weapon
	weaponRects[1] = IntRect(76, 0, -76, 24);
	weaponRects[2] = IntRect(0, 24, 76, -24);

	bulletRects[0][0] = IntRect(0, 0, 32, 32);		// bullets
	bulletRects[0][1] = IntRect(0, 0, 0, 0);
	bulletRects[0][2] = IntRect(32, 0, 32, 32);
	bulletRects[0][3] = IntRect(64, 0, 32, 32);
	bulletRects[0][4] = IntRect(96, 0, 32, 32);
	bulletRects[0][5] = IntRect(0, 32, 32, 32);

	bulletRects[1][0] = IntRect(3, 756, 41, 28);
	bulletRects[1][1] = IntRect(0, 0, 0, 0);
	bulletRects[1][2] = IntRect(53, 759, 36, 22);
	bulletRects[1][3] = IntRect(102, 758, 33, 24);
	bulletRects[1][4] = IntRect(145, 757, 38, 26);

	bulletRects[2][0] = IntRect(3, 838, 62, 23);
	bulletRects[2][1] = IntRect(0, 0, 0, 0);
	bulletRects[2][2] = IntRect(78, 838, 53, 23);

	healthBallRects[0] = IntRect(55, 0, 13, 14);		// healthBall
}

/*void initializeFloors() {
	nrOfFloors = currentBg ? 1 : 2;
	time_t tt;
	srand(time(&tt));

	for (char i = 0; i < nrOfFloors; i++) {
		floors[i].posY = 360;
		floors[i].posX = (rand() % (bgResX / 2)) + (i ? bgResX / 2 : 0);
		floors[i].amount = 5 + (rand() % 5);
	}
}*/
