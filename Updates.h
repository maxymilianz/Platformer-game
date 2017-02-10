#pragma once

#include "ExplosionAndShoot.h"

void updateChestOrPortal() {
	chestAndPortalIter++;
	if (!typeOfExit) {
		if (chestAndPortalIter == 2)
			chestOrPortal.rect = 2, chestOrPortal.posY -= 5;
		else if (chestAndPortalIter == 4)
			chestOrPortal.rect = 3, chestOrPortal.posY -= 5;
		else if (chestAndPortalIter == 6)
			chestOrPortal.rect = 4, chestOrPortal.posY -= 4;
		else if (chestAndPortalIter == 8)
			chestOrPortal.rect = 5, chestOrPortal.posY -= 4;
		else if (chestAndPortalIter == 10)
			chestOrPortal.rect = 6, chestOrPortal.posY -= 4;
		else if (chestAndPortalIter > 10)
			chestAndPortalIter = 10;
	}
	else {
		chestOrPortal.rect = 0;
		chestOrPortal.angle += 3;
		if (chestOrPortal.scale < 2)
			chestOrPortal.scale += 0.10;
	}
}

void updateEnemies() {
	enemiesMovement++;
	if (enemiesMovement == 40)
		enemiesMovement = 0;

	for (char i = 0; i < nrOfEnemies; i++) {
		if (enemies[i].rect != 24) {
			if (enemies[i].posX + 45 > posX + 48)
				enemies[i].dirX = 0;
			else
				enemies[i].dirX = 1;

			if (enemies[i].health <= 0)
				enemies[i].die();
			else if (enemies[i].hitIter) {
				if (enemies[i].hitIter == 20)
					enemies[i].hitIter = 0;
				else
					enemies[i].hitIter++;

				enemies[i].rect = enemies[i].dirX ? 19 : 18;
			}
			else if (abs(enemies[i].posX + 45 - posX + 48) > 400 && abs(enemies[i].posX + 45 - posX + 48) < 1000) {
				if (!enemies[i].dirX) {
					enemies[i].rect = enemiesMovement / 5 + 10;
					enemies[i].posX -= enemies[i].speedX;
				}
				else {
					enemies[i].rect = enemiesMovement / 5 + 2;
					enemies[i].posX += enemies[i].speedX;
				}
			}
			else {
				if (!enemies[i].dirX) {
					enemies[i].rect = 21;
					shoot(i);
				}
				else {
					enemies[i].rect = 20;
					shoot(i);
				}
			}
		}
	}
}

void updateBullets() {
	for (char i = 0; i < 127; i++) {
		if (bullets[i].rect != 1) {
			bullets[i].posX += bulletSpeed * bullets[i].speedY;
			bullets[i].posY += bulletSpeed * bullets[i].speedX;

			if (bullets[i].posY > resY - grassTextures[0].getSize().y / 4)
				bullets[i].hit(), explosion(bullets[i].power, bullets[i].posX, bullets[i].posY);
			else if (bullets[i].posX > resX || bullets[i].posX < -32 || bullets[i].posY < -32)
				bullets[i].hit();
			/*else {
				for (char j = 0; j < nrOfFloors; j++) {
					if (IntRect(bullets[i].posX + 7, bullets[i].posY + 9, 20, 14).intersects(IntRect(floors[0].posX, floors[0].posY + 8, floors[0].amount * floorTextures[level].getSize().x / 4,
						floorTextures[level].getSize().y / 4))) {
						bullets[i].hit();
						explosion(bullets[i].power, bullets[i].posX, bullets[i].posY);
					}
				}
			}*/

			if (!bullets[i].type && bullets[i].visible && bullets[i].rect != 5) {
				if (bullets[i].iter == 5) {
					bullets[i].iter = 0;
					if (!bullets[i].rect)
						bullets[i].rect = 2;
					else if (bullets[i].rect == 2)
						bullets[i].rect = 3;
					else if (bullets[i].rect == 3)
						bullets[i].rect = 4;
					else
						bullets[i].rect = 5;
				}
				else
					bullets[i].iter++;
			}
			else if (bullets[i].type == 1) {
				if (bullets[i].iter == 5) {
					bullets[i].iter = 0;
					if (!bullets[i].rect)
						bullets[i].rect = 2;
					else if (bullets[i].rect == 2)
						bullets[i].rect = 3;
					else if (bullets[i].rect == 3)
						bullets[i].rect = 4;
					else
						bullets[i].rect = 0;
				}
				else
					bullets[i].iter++;
			}
			else if (bullets[i].type == 2) {
				if (bullets[i].iter == 5) {
					if (!bullets[i].rect)
						bullets[i].rect = 2;
					else
						bullets[i].rect = 0;
					bullets[i].iter = 0;
				}
				else
					bullets[i].iter++;
			}
		}
	}
}

void updateExplosions() {
	for (char i = 0; i < maxNrOfExplosions; i++) {
		if (explosions[i].rect != 1) {
			if (explosions[i].string == 16)
				explosions[i].rect = 1;
			explosions[i].string++;
		}
	}
}
