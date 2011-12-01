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
using std::list;


ParticleController::ParticleController()
{
}

ParticleController::ParticleController( int res )
{
    
    mXRes = app::getWindowWidth()/res;
    mYRes = app::getWindowHeight()/res;
    
    for( int y=0; y<mYRes; y++ ){
        for( int x=0; x<mXRes; x++ ){ 
            addParticles( x, y, res );
        }
    }
}

void ParticleController::update( const Channel32f &channel, const ci::Surface32f &surface, const Vec2i &mouseLoc )
{
    
    Channel32f rChan = surface.getChannelRed();
    Channel32f gChan = surface.getChannelGreen();
    Channel32f bChan = surface.getChannelBlue();    
    
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->update( channel, rChan, gChan, bChan, mouseLoc );
	}
}

void ParticleController::draw()
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}
}

void ParticleController::addParticles( int xi, int yi, int res )
{
	float x = ( xi + 0.5f ) * (float)res;
	float y = ( yi + 0.5f ) * (float)res;        

	mParticles.push_back( Particle( Vec2f( x, y ) ) );

}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}