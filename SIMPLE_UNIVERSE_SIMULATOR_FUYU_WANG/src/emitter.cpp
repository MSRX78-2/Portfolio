//
//  emitter.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.
//

#include "emitter.hpp"

// ============================================================
// CONSTRUCTOR
// ============================================================

Emitter::Emitter() {
	// Vectors are empty by default
}

// ============================================================
// SETUP - Create particles of all types
// ============================================================

void Emitter::setup(int numParticles) {
	// Clear all vectors
	circles.clear();
	octagons.clear();
	triangles.clear();
	hexagons.clear();
	
	// Divide particles equally among 4 types
	int perType = numParticles / 4;
	
	// Create all particle types in one loop
	// Each iteration creates one of each type
	for (int i = 0; i < perType; i++) {
		
		CircleParticle c;
		c.setup(ofRandom(100, 450), ofRandom(TWO_PI));
		circles.push_back(c);
		
		OctagonParticle o;
		o.setup(ofRandom(100, 450), ofRandom(TWO_PI));
		octagons.push_back(o);
		
		TriangleParticle t;
		t.setup(ofRandom(100, 450), ofRandom(TWO_PI));
		triangles.push_back(t);
		
		HexagonParticle h;
		h.setup(ofRandom(100, 450), ofRandom(TWO_PI));
		hexagons.push_back(h);
	}
}

// ============================================================
// APPLY ATTRACTOR - Apply force to all particle types
// ============================================================

void Emitter::applyAttractor(Attractor& attractor) {
	for (int i = 0; i < circles.size(); i++) {
		ofVec3f force = attractor.attract(circles[i]);
		circles[i].applyForce(force);
	}
	for (int i = 0; i < octagons.size(); i++) {
		ofVec3f force = attractor.attract(octagons[i]);
		octagons[i].applyForce(force);
	}
	for (int i = 0; i < triangles.size(); ++i) {
		ofVec3f force = attractor.attract(triangles[i]);
		triangles[i].applyForce(force);
	}
	for (int i = 0; i < hexagons.size(); ++i) {
		ofVec3f force = attractor.attract(hexagons[i]);
		hexagons[i].applyForce(force);
	}
}

// ============================================================
// RUN - Update and display all particles
// ============================================================

void Emitter::run(float pullStrength, float pushStrength) {
	for (int i = circles.size() - 1; i >= 0; i--) {
		circles[i].update(pullStrength, pushStrength);
		circles[i].display();
		
		if (circles[i].isDead()) {
			circles[i].respawn();
		}
	}
	
	for (int i = octagons.size() - 1; i >= 0; i--) {
		octagons[i].update(pullStrength, pushStrength);
		octagons[i].display();
		
		if (octagons[i].isDead()) {
			octagons[i].respawn();
		}
	}
	
	for (int i = triangles.size() - 1; i >= 0; --i){
		triangles[i].update(pullStrength, pushStrength);
		triangles[i].display();
		
		if (triangles[i].isDead()) {
			triangles[i].respawn();
		}
	}
	
	for (int i = hexagons.size() - 1; i >= 0; --i){
		hexagons[i].update(pullStrength, pushStrength);
		hexagons[i].display();
		
		if (hexagons[i].isDead()) {
			hexagons[i].respawn();
		}
	}
}

// ============================================================
// GET TOTAL COUNT
// ============================================================

int Emitter::getTotalCount() {
	return circles.size()+ octagons.size() + triangles.size() + hexagons.size();
}
