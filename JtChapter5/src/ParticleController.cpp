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

void ParticleController::update( const Perlin &perlin, const Channel32f &channel, const ci::Surface32f &surface, const Vec2i &mouseLoc )
{
    
    Channel32f rChan = surface.getChannelRed();
    Channel32f gChan = surface.getChannelGreen();
    Channel32f bChan = surface.getChannelBlue();    
        
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ){
        //console() << p->mIsDead << std::endl;
        if( p->isDead() ) {
            p = mParticles.erase( p );
        } else {
            p->update( perlin, channel, rChan, gChan, bChan, mouseLoc );
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


void ParticleController::repulseParticles() {
    for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1) {
        list<Particle>::iterator p2 = p1;
        for( ++p2; p2 != mParticles.end(); ++p2 ) {
            Vec2f dir = p1->mLoc - p2->mLoc;
            
            
            
            float thresh = ( p1->mRadius + p2->mRadius ) * 5.0f;
			if( dir.x > -thresh && dir.x < thresh && dir.y > -thresh && dir.y < thresh ){
                float distSqrd = dir.lengthSquared() * dir.length();
                
                if( distSqrd > 0.0f ) {
                    dir.normalize();
                    float F = 1.0f/distSqrd;
                    
                    p1->mAcc += dir * ( F / p1->mMass );
                    p2->mAcc += dir * ( F / p2->mMass );
                }
            }
            
        }
    }
}

void ParticleController::addParticles( int amt, const Vec2i &mouseLoc, const Vec2f &mouseVel )
{

    for( int i=0; i<amt; i++ ){
        
        //Vec2f loc = mouseLoc + Rand::randVec2f() * 10.0f;
        //Vec2f vel = (mouseVel * 0.25f) + Rand::randVec2f() * Rand::randFloat( 1.0f, 3.0f );
        
        //no change
//        Vec2f loc = mouseLoc;
//        Vec2f vel = mouseVel * 0.0f; //let's try with no vel
        
        Vec2f loc = mouseLoc + Rand::randVec2f() * Rand::randFloat( 5.0f );
		Vec2f velOffset = Rand::randVec2f() * Rand::randFloat( 1.0f, 3.0f );
		Vec2f vel = mouseVel * 5.0f + velOffset;
        
        mParticles.push_back( Particle( loc, vel ) );
    }

}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}