#pragma once
#include "ofMain.h"

class Enemy {
public:
    Enemy(ofVec2f startPos);
    void update(ofVec2f playerPos);
    void draw();
    ofVec2f getPosition() const;
    float getRadius() const;

private:
    ofVec2f position;
    ofVec2f velocity;
    float speed;
    float radius;
};
