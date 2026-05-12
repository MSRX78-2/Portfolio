#include "vehicle.hpp"

Vehicle::Vehicle() {
    position = ofVec2f(0, 0);
    velocity = ofVec2f(0, 0);
    acceleration = ofVec2f(0, 0);
    maxSpeed = 4.0f;
    maxForce = 0.15f;
    r = 14.0f;
}

Vehicle::Vehicle(float x, float y) {
    position = ofVec2f(x, y);
    velocity = ofVec2f(0, 0);
    acceleration = ofVec2f(0, 0);
    maxSpeed = 4.0f;
    maxForce = 0.15f;
    r = 14.0f;
}

void Vehicle::applyForce(ofVec2f force) {
    acceleration += force;
}

void Vehicle::seek(ofVec2f target) {
    ofVec2f desired = target - position;
    if (desired.length() > 0.01f) {
        desired.normalize();
        desired *= maxSpeed;
        ofVec2f steer = desired - velocity;
        steer.limit(maxForce);
        applyForce(steer);
    }
}

void Vehicle::update(ofVec2f mouse) {
    seek(mouse);
    velocity += acceleration;
    velocity.limit(maxSpeed);
    position += velocity;
    acceleration *= 0;
}

void Vehicle::draw() {
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofRotateRad(atan2(velocity.y, velocity.x));

    ofSetColor(ofColor::fromHex(0xFFF808));
    ofFill();
    ofBeginShape();
    ofVertex( r * 2.0f,  0);
    ofVertex(-r * 1.5f, -r);
    ofVertex(-r * 1.5f,  r);
    ofEndShape(true);

    ofNoFill();
    ofSetColor(255, 120);
    ofSetLineWidth(2);
    ofBeginShape();
    ofVertex( r * 2.0f,  0);
    ofVertex(-r * 1.5f, -r);
    ofVertex(-r * 1.5f,  r);
    ofEndShape(true);
    ofPopMatrix();
}

ofVec2f Vehicle::getPosition() const { return position; }
ofVec2f Vehicle::getVelocity() const { return velocity; }
float Vehicle::getRadius() const { return r * 1.5f; }
void Vehicle::setPosition(ofVec2f p) { position = p; }
