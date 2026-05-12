#include "enemy.hpp"

Enemy::Enemy(ofVec2f startPos) {
    position = startPos;
    velocity = ofVec2f(0, 0);
    speed = ofRandom(1.2f, 2.4f);
    radius = ofRandom(14.0f, 24.0f);
}

void Enemy::update(ofVec2f playerPos) {
    ofVec2f dir = playerPos - position;
    if (dir.length() > 0.01f) {
        dir.normalize();
    }
    velocity = dir * speed;
    position += velocity;
}

void Enemy::draw() {
    ofFill();
    ofSetColor(255, 60, 80, 220);
    ofDrawCircle(position.x, position.y, radius);

    ofNoFill();
    ofSetColor(255, 180);
    ofSetLineWidth(2);
    ofDrawCircle(position.x, position.y, radius);
}

ofVec2f Enemy::getPosition() const { return position; }
float Enemy::getRadius() const { return radius; }
