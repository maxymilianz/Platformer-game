#pragma once

void explosion(char power, short x, short y) {
	char i;

	for (i = 0; explosions[i].rect != 1; i++);

	explosionPlay();
	explosions[i].posX = x - explosionTextures[0].getSize().x / 2 + bulletTextures[0].getSize().x / 2;
	explosions[i].posY = y - explosionTextures[0].getSize().y + 30 + bulletTextures[0].getSize().y / 2;
	explosions[i].power = 4 * power;
	explosions[i].rect = 0;
	explosions[i].string = 0;
}

void shoot(short who) {		// -1 - character, other - enemies
	if (who == -1) {
		if (temperature < 250) {
			temperature += 5;
			gunPlay(currentWeapon);

			if (shootIter == 5) {
				shootIter = 0;

				char i;
				for (i = 0; bullets[i].rect != 1; i++);

				bullets[i].angle = -angle + 90;
				bullets[i].angleRadians = angle * M_PI / 180;
				bullets[i].speedX = cos(bullets[i].angleRadians);
				bullets[i].speedY = sin(bullets[i].angleRadians);

				bullets[i].posX = posX + 56 - 76 * cos(bullets[i].angleRadians + M_PI / 2);
				bullets[i].posY = posY + 67 + 76 * sin(bullets[i].angleRadians + M_PI / 2);

				bullets[i].power = currentWeapon + 1;
				bullets[i].rect = 0;
				bullets[i].type = currentWeapon;
				bullets[i].visible = 1;
			}
			else
				shootIter++;
		}
	}
	else {
		if (enemies[who].shootIter >= 20) {
			enemies[who].shootIter = 0;

			char i;
			for (i = 0; bullets[i].rect != 1; i++);

			bullets[i].posX = enemies[who].posX + 48 - 40 * cos(bullets[i].angleRadians + M_PI / 2);
			bullets[i].posY = enemies[who].posY + 42 + 40 * sin(bullets[i].angleRadians + M_PI / 2);

			bullets[i].angle = enemies[who].dirX ? 90 : -90;
			bullets[i].angleRadians = bullets[i].angle * M_PI / 180;
			bullets[i].angle *= -1, bullets[i].angle += 90;
			bullets[i].speedX = cos(bullets[i].angleRadians);
			bullets[i].speedY = sin(bullets[i].angleRadians);

			bullets[i].power = enemies[who].power;
			bullets[i].rect = 0;
			bullets[i].type = enemies[who].type + 2;
			bullets[i].visible = 1;
		}
		else
			enemies[who].shootIter++;
	}
}
