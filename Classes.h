#pragma once

class Object {
public:
	char rect = 1;		// 1 - IntRect(0, 0, 0, 0)
	short posX, posY;
	float angle, scale;
};

/*class Floor : public Object {
public:
	char amount;
};*/

class NPC : public Object {
public:
	bool dirX = 0;
	char health, power, type, accelerationY = -16, hitIter = 0, shootIter = 0, speedX;

	void gotHit(char dmg) {
		health -= dmg;
		rect = 19;
		hitIter++;
	}

	void die() {
		/*if (posY <= 600) {
			posY += accelerationY;
			rect = dirX ? 19 : 18;
			accelerationY++;
		}
		else*/
			rect = 24;
	}
};

class Bullet : public Object {
public:
	bool visible = 0;		// change to 1 after got out of weapon
	char power, type, iter = 0;
	float speedX, speedY, angleRadians, startX, startY;

	void hit() {
		rect = 1;
		visible = 0;
	}
};

class Explosion : public Object {
public:
	char power, string;
};

class Img {
public:
	char top, bottom, left, right;		// margins
};