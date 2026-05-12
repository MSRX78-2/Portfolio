#pragma once
#include "ofMain.h"
#include "vehicle.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "pickup.hpp"
#include <vector>

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void mousePressed(int x, int y, int button) override;

private:
    Vehicle player;
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    vector<Pickup> pickups;

    int kills;
    int maxEnemyCount;
    int arcAmmo;
    bool gameOver;

    float lastEnemySpawnTime;
    float enemySpawnInterval;
    float lastPickupSpawnTime;
    float pickupSpawnInterval;

    void resetGame();
    void spawnEnemy();
    void spawnPickups();
    ofVec2f randomOutsidePosition();
    ofVec2f aimDirection() const;
    bool circleHit(ofVec2f a, float ar, ofVec2f b, float br) const;
};
