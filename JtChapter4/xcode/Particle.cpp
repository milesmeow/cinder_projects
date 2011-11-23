//
//  Particle.cpp
//  JtChapterOne
//
//  Created by James Tu on 11/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"


using namespace ci;
using namespace ci::app;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();

    mScale = 6.0f;
    
    mAge = 0;
    mLifeSpan = Rand::randInt( 50, 250 );
    mIsDead = false;
    //mDecay = 0.9999f;
    
    mVel = Rand::randVec2f();
}

void Particle::update( const Channel32f &channel,  const ci::Channel32f &rChan, const ci::Channel32f &gChan, const ci::Channel32f &bChan, const ci::Vec2i &mouseLoc )
{
	    
    mRadius = channel.getValue( mLoc ) * mScale;    
            
    mAge++;
    if( mAge > mLifeSpan ){
        mIsDead = true;
    }
    
    mLoc += mVel;
    //mVel *= mDecay;
}

void Particle::draw()
{
    gl::color( Color( 1.0f, 1.0f, 1.0f ));
    //gl::color( Color( r, g, b));    
           
    //gl::drawSolidCircle( mLoc + mDirToCursor * 0.2f, mRadius);
    //gl::drawSolidCircle( mLoc, mRadius);
    float agePer = 1.0f - (mAge / (float)mLifeSpan); 
    mRadius = 3.0f * agePer;
    gl::drawSolidCircle( mLoc, mRadius );    
}

bool Particle::isDead()
{
    return mIsDead;
}
