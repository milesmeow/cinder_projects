//
//  ParticleController.h
//  JtChapterOne
//
//  Created by James Tu on 11/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Particle.h"
#include "cinder/Channel.h"
#include <list>

class ParticleController {
public:
    ParticleController();
	ParticleController( int res );
	void update( const ci::Channel32f &channel, const ci::Surface32f &surface, const ci::Vec2i &mouseLoc );
	void draw();
	void addParticles( int xi, int yi, int res );
	void removeParticles( int amt );
	
	std::list<Particle>	mParticles;
    
    int mXRes, mYRes;
};
