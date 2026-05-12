#pragma once
#include "ofMain.h"

class Pickup {
public:
    Pickup(ofVec2f p);
    void draw();
    ofVec2f getPosition() const;
    float getSize() const;

private:
    ofVec2f position;
    float size;
};
