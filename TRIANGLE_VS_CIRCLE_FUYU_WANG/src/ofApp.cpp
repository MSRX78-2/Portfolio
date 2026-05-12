#include "ofApp.h"

void ofApp::setup() {
	ofSetFrameRate(60);
	resetGame();
}

void ofApp::resetGame() {
	ofBackground(0);
	player = Vehicle(ofGetWidth() / 2, ofGetHeight() / 2);

	enemies.clear();
	bullets.clear();
	pickups.clear();

	kills = 0;
	arcAmmo = 0;
	gameOver = false;

	maxEnemyCount = (int)ofRandom(8, 18); // random maximum enemy number
	lastEnemySpawnTime = ofGetElapsedTimef();
	enemySpawnInterval = 0.7f;

	lastPickupSpawnTime = ofGetElapsedTimef();
	pickupSpawnInterval = 3.5f;
}

void ofApp::update() {
	if (gameOver) return;

	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	player.update(mouse);

	float now = ofGetElapsedTimef();

	// Spawn enemies from outside the screen, but never exceed maxEnemyCount.
	if (now - lastEnemySpawnTime > enemySpawnInterval && enemies.size() < maxEnemyCount) {
		spawnEnemy();
		lastEnemySpawnTime = now;
	}

	// Every 20 seconds, spawn 1 to 3 square pickups.
	if (now - lastPickupSpawnTime > pickupSpawnInterval) {
		spawnPickups();
		lastPickupSpawnTime = now;
	}

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].update(player.getPosition());
	}

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].update();
	}

	// Bullet-enemy collision. Reverse loops make erase safer.
	for (int i = bullets.size() - 1; i >= 0; i--) {
		bool bulletRemoved = false;

		for (int j = enemies.size() - 1; j >= 0; j--) {
			if (bullets[i].hitsEnemy(enemies[j].getPosition(), enemies[j].getRadius())) {
				enemies.erase(enemies.begin() + j);
				kills++;

				// Regular bullets disappear after hitting one enemy.
				// Arc bullets stay alive and can kill multiple enemies until they leave the screen.
				if (bullets[i].getType() == BulletType::Regular) {
					bullets.erase(bullets.begin() + i);
					bulletRemoved = true;
					break;
				}
			}
		}

		if (bulletRemoved) continue;

		if (bullets[i].isOffscreen()) {
			bullets.erase(bullets.begin() + i);
		}
	}

	// Player-pickup collision: square gives one arc bullet ammo.
	for (int i = pickups.size() - 1; i >= 0; i--) {
		float hitRadius = pickups[i].getSize() * 0.7f;
		if (circleHit(player.getPosition(), player.getRadius(), pickups[i].getPosition(), hitRadius)) {
			pickups.erase(pickups.begin() + i);
			arcAmmo++;
		}
	}

	// Enemy-player collision: game over.
	for (int i = 0; i < enemies.size(); i++) {
		if (circleHit(player.getPosition(), player.getRadius(), enemies[i].getPosition(), enemies[i].getRadius())) {
			gameOver = true;
			break;
		}
	}
}

void ofApp::draw() {
	ofSetColor(0, 40);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	for (int i = 0; i < pickups.size(); i++) pickups[i].draw();
	for (int i = 0; i < bullets.size(); i++) bullets[i].draw();
	for (int i = 0; i < enemies.size(); i++) enemies[i].draw();
	player.draw();

	ofSetColor(255);
	ofDrawBitmapString("Kills: " + ofToString(kills), 15, 24);
	ofDrawBitmapString("Max Enemies: " + ofToString(maxEnemyCount), 15, 42);
	ofDrawBitmapString("Current Enemies: " + ofToString(enemies.size()), 15, 60);
	ofDrawBitmapString("Arc Ammo: " + ofToString(arcAmmo), 15, 78);
	ofDrawBitmapString("Left Click: regular bullet | Right Click: 45-degree arc bullet | R: restart", 15, 96);

	if (gameOver) {
		ofSetColor(0, 180);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		ofSetColor(255, 80, 80);
		ofDrawBitmapString("GAME OVER", ofGetWidth() / 2 - 45, ofGetHeight() / 2);
		ofSetColor(255);
		ofDrawBitmapString("Kills: " + ofToString(kills), ofGetWidth() / 2 - 35, ofGetHeight() / 2 + 24);
		ofDrawBitmapString("Press R to restart", ofGetWidth() / 2 - 60, ofGetHeight() / 2 + 48);
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	if (gameOver) return;

	ofVec2f dir = aimDirection();
	ofVec2f start = player.getPosition() + dir * 28.0f;

	if (button == 0) {
		bullets.push_back(Bullet(start, dir, BulletType::Regular));
	}
	if (button == 2 && arcAmmo > 0) {
		bullets.push_back(Bullet(start, dir, BulletType::Arc45));
		arcAmmo--;
	}
}

void ofApp::keyPressed(int key) {
	if (key == 'r' || key == 'R') {
		resetGame();
	}
}

void ofApp::spawnEnemy() {
	enemies.push_back(Enemy(randomOutsidePosition()));
}

void ofApp::spawnPickups() {
	int amount = (int)ofRandom(1, 4); // 1, 2, or 3
	for (int i = 0; i < amount; i++) {
		ofVec2f p(ofRandom(40, ofGetWidth() - 40), ofRandom(40, ofGetHeight() - 40));
		pickups.push_back(Pickup(p));
	}
}

ofVec2f ofApp::randomOutsidePosition() {
	int side = (int)ofRandom(4);
	float margin = 50.0f;

	if (side == 0) return ofVec2f(ofRandom(ofGetWidth()), -margin);                 // top
	if (side == 1) return ofVec2f(ofGetWidth() + margin, ofRandom(ofGetHeight()));  // right
	if (side == 2) return ofVec2f(ofRandom(ofGetWidth()), ofGetHeight() + margin);  // bottom
	return ofVec2f(-margin, ofRandom(ofGetHeight()));                               // left
}

ofVec2f ofApp::aimDirection() const {
	ofVec2f dir(ofGetMouseX(), ofGetMouseY());
	dir -= player.getPosition();

	if (dir.length() < 0.01f) {
		dir = player.getVelocity();
	}
	if (dir.length() < 0.01f) {
		dir = ofVec2f(1, 0);
	}
	dir.normalize();
	return dir;
}

bool ofApp::circleHit(ofVec2f a, float ar, ofVec2f b, float br) const {
	return a.distance(b) < ar + br;
}
