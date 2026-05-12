//
//  hexagonparticle.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by 王俯瑜 on 3/24/26.
//

#ifndef hexagonparticle_hpp
#define hexagonparticle_hpp

#include "particle.hpp"

class HexagonParticle : public Particle {
	
public:
	
	HexagonParticle();
	
	void setup(float orbitRadius, float startAngle) override;
	void update(float pullStrength, float pushStrength) override;
	void display() override;
	void respawn() override;
};

#endif
