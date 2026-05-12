//
//  hexagonparticle.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by 王俯瑜 on 3/24/26.
//

#include "hexagonparticle.hpp"

HexagonParticle::HexagonParticle(){
	sides = 6;
}

void HexagonParticle::setup(float orbitRadius, float startAngle) {
	Particle::setup(orbitRadius, startAngle);
	
	sides = 6;
	
	mass = 0.6;
	
	particleColor = ofColor(150, 200, 255);
}

void HexagonParticle::update(float pullStrength, float pushStrength) {
		r -= pullStrength * 2.0;
		r += pushStrength * 0.3;
		
		theta += angularVelocity;
		
		lifespan -= 1.0;
		
		updatePositionFromPolar();
}

void HexagonParticle::display(){
	Particle::display();
}

void HexagonParticle::respawn(){
	Particle::respawn();
	sides = 6;
}
