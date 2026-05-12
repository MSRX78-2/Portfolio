#pragma once
#include "ofMain.h"

enum class BulletType {
	Regular,
	Arc45
};

class Bullet {
public:
	Bullet(ofVec2f startPos, ofVec2f direction, BulletType type);
	void update();
	void draw();
	bool isOffscreen() const;
	bool hitsEnemy(ofVec2f enemyPos, float enemyRadius) const;
	ofVec2f getPosition() const;
	float getRadius() const;
	BulletType getType() const;

private:
	ofVec2f position;
	ofVec2f velocity;
	BulletType type;
	float radius;
	float angle;
	float growSpeed;
	float maxRadius;
};
