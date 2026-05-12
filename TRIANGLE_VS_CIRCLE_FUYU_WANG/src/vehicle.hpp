#pragma once
#include "ofMain.h"

class Vehicle {
public:
    Vehicle();
    Vehicle(float x, float y);

    virtual void update(ofVec2f mouse);
    virtual void draw();

    void applyForce(ofVec2f force);
    void seek(ofVec2f target);

    ofVec2f getPosition() const;
    ofVec2f getVelocity() const;
    float getRadius() const;
    void setPosition(ofVec2f p);

protected:
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float maxSpeed;
    float maxForce;
    float r;
};
