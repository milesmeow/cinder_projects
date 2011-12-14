#pragma once
#include "Particle.h"
#include <list>

class ParticleController {
public:
	ParticleController();
	void pullToCenter( const ci::Vec3f &center );
	void applyForce( float zoneRadiusSqrd, float thresh );
    void update( bool flatten );
	void draw();
	void addParticles( int amt );
	
	std::list<Particle>	mParticles;
    
    
    
};