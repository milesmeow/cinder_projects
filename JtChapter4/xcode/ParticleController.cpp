//
//  ParticleController.cpp
//  JtChapterOne
//
//  Created by James Tu on 11/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using std::list;


ParticleController::ParticleController()
{
}

ParticleController::ParticleController( int res )
{
    
    mXRes = app::getWindowWidth()/res;
    mYRes = app::getWindowHeight()/res;
    
}

void ParticleController::update( const Channel32f &channel, const ci::Surface32f &surface, const Vec2i &mouseLoc )
{
    
    Channel32f rChan = surface.getChannelRed();
    Channel32f gChan = surface.getChannelGreen();
    Channel32f bChan = surface.getChannelBlue();    
    
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ){
        //console() << p->mIsDead << std::endl;
        if( p->isDead() ) {
            p = mParticles.erase( p );
        } else {
            p->update( channel, rChan, gChan, bChan, mouseLoc );
            ++p;
        }
    }
}

void ParticleController::draw()
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}
}

void ParticleController::addParticles( int amt, const Vec2i &mouseLoc )
{

    for( int i=0; i<amt; i++ ){
        Vec2i randVec = Rand::randVec2f() * 10.0f;
        mParticles.push_back( Particle( mouseLoc + randVec ) );
    }

}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}