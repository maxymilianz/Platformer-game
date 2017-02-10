#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define M_PI 3.14159265358979323846

#define nrOfBluredBgStrings 19
#define nrOfBgStrings 19
#define nrOfGrassStrings 1
#define nrOfFloorStrings 1
#define nrOfEnemyStrings 4
#define nrOfCharacterStrings 1
#define nrOfWeaponStrings 2
#define nrOfBulletStrings 3
#define nrOfExplosionStrings 17

#define maxNrOfEnemies 32
#define maxNrOfBullets 127
#define maxNrOfExplosions 100
#define maxNrOfHealthBalls 100

#define nrOfRects 25

using namespace sf;

bool paused = 1, attacked = 0, defensed = 0, aimDirX = 1, jumped = 0, typeOfExit, inMenu = 1, bgDirX = 1, bestResults = 0, openOrEnter = 0, weaponUnlocked = 0,
levelPassed = 0, gameFinished = 0, died = 0;		// typeOfExit: 0 - chest, 1 - portal
char initSpeedX = 8, speedX = initSpeedX, accelerationY = 16, health = 100, stamina = 100, difficulty = 10, bulletSpeed = 20, level = 0, toExit = 0, getName = 5,
currentBg = 0, currentGrass = 0, currentCharacter = 0, currentWeapon = 0, currentGroundY = 0,
nrOfEnemies, nrOfWeapons = 1, //nrOfFloors,
enemiesMovement = 0, movement = 0, shootIter = 0, chestAndPortalIter = 0,
currentEnemyRect = 0, currentCharacterRect = 0, currentWeaponRect = 0;
unsigned char temperature = 0;
short resX = 1024, resY = 600, posX = 128, posY = 382, bgX = 0, bgY, bgResX = 2311, bgResY = resY, grassX = -128, grassY, loading = 0;		// loading: 1 - new, -1 - con
float angle;

char scores[5] = { 0 };
char names[5][16] = { 0 };

short groundY[3] = { 382, 270, 600 };		// 2 - when died

char *bluredBgStrings[nrOfBluredBgStrings] = { "graphics/bgs/cave1B.jpg", "graphics/bgs/desert1B.jpg", "graphics/bgs/desert2B.jpg", "graphics/bgs/forest1B.jpg",
"graphics/bgs/forest2B.jpg", "graphics/bgs/forest3B.jpg", /*"graphics/bgs/forest4B.jpg", */"graphics/bgs/forest5B.jpg", "graphics/bgs/forest6B.jpg",
"graphics/bgs/forest7B.jpg", "graphics/bgs/ice1B.jpg", "graphics/bgs/lake1B.jpg", "graphics/bgs/mountains1B.jpg", "graphics/bgs/mountains2B.jpg",
"graphics/bgs/mountains3B.jpg", "graphics/bgs/mountains4B.jpg", "graphics/bgs/night1B.jpg", "graphics/bgs/river1B.jpg",
"graphics/bgs/rocks1B.jpg", /*"graphics/bgs/sculpture1B.jpg", */"graphics/bgs/tree1B.jpg" };
char *bgStrings[nrOfBgStrings] = { "graphics/bgs/cave1.jpg", "graphics/bgs/desert1.jpg", "graphics/bgs/desert2.jpg", "graphics/bgs/forest1.jpg",
"graphics/bgs/forest2.jpg", "graphics/bgs/forest3.jpg", /*"graphics/bgs/forest4.jpg", */"graphics/bgs/forest5.jpg", "graphics/bgs/forest6.jpg",
"graphics/bgs/forest7.jpg", "graphics/bgs/ice1.jpg", "graphics/bgs/lake1.jpg", "graphics/bgs/mountains1.jpg", "graphics/bgs/mountains2.jpg",
"graphics/bgs/mountains3.jpg", "graphics/bgs/mountains4.jpg", "graphics/bgs/night1.jpg", "graphics/bgs/river1.jpg",
"graphics/bgs/rocks1.jpg", /*"graphics/bgs/sculpture1.jpg", */"graphics/bgs/tree1.jpg" };
char *portalString = "graphics/portalT.png";
char *grassStrings[nrOfGrassStrings] = { "graphics/dirtAndGrass.jpg" };
char *floorStrings[nrOfFloorStrings] = { "graphics/floor1.jpg" };
char *chestString = "graphics/chest.png";
char *enemyStrings[nrOfEnemyStrings] = { "graphics/enemies/enemyBird1.png", "graphics/enemies/enemy1.png", "graphics/enemies/enemy2.png", "graphics/enemies/enemy3.png" };
char *characterStrings[nrOfCharacterStrings] = { "graphics/character.png" };
char *weaponString = "graphics/gun.png";
char *bulletStrings[nrOfBulletStrings] = { "graphics/missile1.png", "graphics/enemies/enemy2.png", "graphics/enemies/enemy3.png" };
char *explosionStrings[nrOfExplosionStrings];
char *healthBallString = "graphics/healthBall.png";
char *viewfinderString = "graphics/viewfinder.png";
char *creditsString = "graphics/credits.png";
char *newWeaponString = "graphics/treasureTR.png";
char *newLevelString = "graphics/heavenR.png";
char *finishString = "graphics/finish.png";
char *diedString = "graphics/death.png";

RenderWindow window(VideoMode(resX, resY), "Game like Ori");

SoundBuffer clickSound;
SoundBuffer enemyHurtSound[3];
SoundBuffer enterPortalSound;
SoundBuffer gunSound[3];
SoundBuffer openChestSound;
SoundBuffer playerHurtSound;
SoundBuffer explosionSound;

Sound click;
Sound enemyHurt[3];
Sound enterPortal;
Sound gun[3];
Sound openChest;
Sound playerHurt;
Sound explosion2Play;

Music menu, game;

Vector2i mousePos;

//Floor floors[2];
Object chestOrPortal;
NPC *enemies;
Bullet bullets[maxNrOfBullets];
Explosion explosions[maxNrOfExplosions];

Texture bluredBgTextures[nrOfBluredBgStrings];
Texture bgTextures[nrOfBgStrings];
Texture portalTexture;
Texture grassTextures[nrOfGrassStrings];
Texture floorTextures[nrOfFloorStrings];
Texture chestTexture;
Texture enemyTextures[nrOfEnemyStrings];
Texture characterTextures[nrOfCharacterStrings];
Texture weaponTexture;
Texture bulletTextures[nrOfBulletStrings];
Texture explosionTextures[nrOfExplosionStrings];
Texture healthBallTexture;
Texture viewfinderTexture;
Texture creditsTexture;
Texture newWeaponTexture;
Texture newLevelTexture;
Texture finishTexture;
Texture diedTexture;

Font font;
Text temperatureText, newGameText, continueGameText, bestResultsText, menuText, exitText, resumeText, eOpenText, eEnterText, loadingText, enterNameText;
//RectangleShape newGameRect, continueGameRect, bestResultRect, menuRect, exitRect, resumeRect, loadingRect;

Img enemyImg[nrOfEnemyStrings];
Img characterImg[nrOfCharacterStrings];
Img bulletImg[nrOfBulletStrings];

IntRect portalRects[nrOfRects];
IntRect chestRects[nrOfRects];
IntRect enemyRects[nrOfEnemyStrings][nrOfRects];
IntRect characterRects[nrOfCharacterStrings][nrOfRects];
IntRect weaponRects[nrOfRects];
IntRect bulletRects[nrOfBulletStrings][nrOfRects];
IntRect healthBallRects[nrOfRects];