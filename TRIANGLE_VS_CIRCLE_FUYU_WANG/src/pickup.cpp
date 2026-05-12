#include "pickup.hpp"

Pickup::Pickup(ofVec2f p) {
    position = p;
    size = 28.0f;
}

void Pickup::draw() {
    ofFill();
    ofSetColor(120, 180, 255, 220);
    ofDrawRectangle(position.x - size / 2, position.y - size / 2, size, size);

    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(2);
    ofDrawRectangle(position.x - size / 2, position.y - size / 2, size, size);
}

ofVec2f Pickup::getPosition() const { return position; }
float Pickup::getSize() const { return size; }
