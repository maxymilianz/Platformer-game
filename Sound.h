#pragma once

#include <SFML/Audio.hpp>
#include "Settings.h"

using namespace sf;

void initializeSounds() {
	clickSound.loadFromFile("sounds/click.wav");
	enemyHurtSound[0].loadFromFile("sounds/enemyHurt1.wav");
	enemyHurtSound[1].loadFromFile("sounds/enemyHurt2.wav");
	enemyHurtSound[2].loadFromFile("sounds/enemyHurt3.wav");
	enterPortalSound.loadFromFile("sounds/enterPortal.wav");
	gunSound[0].loadFromFile("sounds/gun1.wav");
	gunSound[1].loadFromFile("sounds/gun2.wav");
	gunSound[2].loadFromFile("sounds/gun3.wav");
	openChestSound.loadFromFile("sounds/openChest.wav");
	playerHurtSound.loadFromFile("sounds/playerHurt.wav");
	explosionSound.loadFromFile("sounds/explosion.wav");

	click.setBuffer(clickSound);
	enemyHurt[0].setBuffer(enemyHurtSound[0]), enemyHurt[0].setVolume(50);
	enemyHurt[1].setBuffer(enemyHurtSound[1]), enemyHurt[1].setVolume(50);
	enemyHurt[2].setBuffer(enemyHurtSound[2]), enemyHurt[2].setVolume(50);
	enterPortal.setBuffer(enterPortalSound);
	gun[0].setBuffer(gunSound[0]), gun[0].setVolume(10);
	gun[1].setBuffer(gunSound[1]), gun[1].setVolume(10);
	gun[2].setBuffer(gunSound[2]), gun[2].setVolume(10);
	openChest.setBuffer(openChestSound);
	playerHurt.setBuffer(playerHurtSound);
}

void menuMusic() {
	game.stop();
	menu.openFromFile("sounds/menu.wav");
	menu.setLoop(true);
	menu.play();
}

void gameMusic() {
	menu.stop();
	game.openFromFile("sounds/Platformer2.wav");
	game.setLoop(true);
	game.play();
}

void enemyHurtPlay(char type) {
	enemyHurt[type].play();
}

void gunPlay(char type) {
	gun[type].play();
}

void clickPlay() {
	click.play();
}

void enterPortalPlay() {
	enterPortal.play();
}

void openChestPlay() {
	openChest.play();
}

void playerHurtPlay() {
	playerHurt.setPlayingOffset(milliseconds(500));
	playerHurt.play();
}

void explosionPlay() {
	explosion2Play.play();
}