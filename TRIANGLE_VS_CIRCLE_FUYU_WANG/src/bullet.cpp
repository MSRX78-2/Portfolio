#include "bullet.hpp"

Bullet::Bullet(ofVec2f startPos, ofVec2f direction, BulletType bulletType) {
	position = startPos;
	if (direction.length() < 0.01f) {
		direction = ofVec2f(1, 0);
	}
	direction.normalize();
	type = bulletType;

	if (type == BulletType::Regular) {
		velocity = direction * 9.0f;
		radius = 6.0f;
		growSpeed = 0.0f;
		maxRadius = radius;
	} else {
		velocity = direction * 5.5f;
		radius = 18.0f;
		growSpeed = 1.8f;
		maxRadius = 220.0f;
	}

	angle = atan2(direction.y, direction.x);
}

void Bullet::update() {
	position += velocity;

	if (type == BulletType::Arc45) {
		radius += growSpeed;

		if (radius > maxRadius) {
			radius = maxRadius;
		}
	}
}

void Bullet::draw() {
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateRad(angle);

	if (type == BulletType::Regular) {
		// 2D capsule/cylinder-looking bullet
		ofFill();
		ofSetColor(255, 240, 120);
		ofDrawRectangle(-8, -4, 16, 8);
		ofDrawCircle(-8, 0, 4);
		ofDrawCircle(8, 0, 4);
	} else {
		// 45-degree arc bullet that grows while flying
		ofPath arcPath;
		arcPath.setFilled(false);
		arcPath.setStrokeColor(ofColor(120, 220, 255));
		arcPath.setStrokeWidth(6);
		arcPath.arc(0, 0, radius, radius, -22.5f, 22.5f);
		arcPath.draw();
	}

	ofPopMatrix();
}

bool Bullet::hitsEnemy(ofVec2f enemyPos, float enemyRadius) const {
	if (type == BulletType::Regular) {
		return position.distance(enemyPos) < radius + enemyRadius;
	}

	ofVec2f toEnemy = enemyPos - position;
	float distanceToEnemy = toEnemy.length();

	if (distanceToEnemy > radius + enemyRadius) {
		return false;
	}

	float enemyAngle = atan2(toEnemy.y, toEnemy.x);
	float angleDifference = ofAngleDifferenceRadians(angle, enemyAngle);

	return abs(angleDifference) < ofDegToRad(22.5f);
}

bool Bullet::isOffscreen() const {
	return position.x < -60 || position.x > ofGetWidth() + 60 ||
		   position.y < -60 || position.y > ofGetHeight() + 60;
}

ofVec2f Bullet::getPosition() const { return position; }
float Bullet::getRadius() const { return radius; }
BulletType Bullet::getType() const { return type; }
