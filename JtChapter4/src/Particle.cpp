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

Particle::Particle( Vec2f loc, Vec2f vel )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();

    mScale = 6.0f;
    
    mAge = 0;
    mLifeSpan = Rand::randInt( 50, 200 );
    mIsDead = false;
    //mDecay = 0.9999f;
    
    mVel = vel;
}

void Particle::update( const Perlin &perlin, const Channel32f &channel,  const Channel32f &rChan, const Channel32f &gChan, const Channel32f &bChan, const Vec2i &mouseLoc )
{
   
    
    mAge++;
    if( mAge > mLifeSpan ){
        mIsDead = true;
    }

    //make the particle shrink as it ages
    float agePer = 1.0f - (mAge / (float)mLifeSpan); 
    mRadius = 3.0f * agePer;
    
    // get Perlin noise value based on my location and
	// elapsed seconds and turn this noise value into an angle.
	float nX = mLoc.x * 0.005f;
	float nY = mLoc.y * 0.005f;
	float nZ = app::getElapsedSeconds() * 0.1f;
	float noise = perlin.fBm( nX, nY, nZ );
	float angle = noise * 15.0f;
	Vec2f noiseVector( cos( angle ), sin( angle ) );
    
    
    //mRadius = channel.getValue( mLoc ) * mScale;    
    
    mVel += noiseVector * 0.2f * ( 1.0f - agePer );
    mLoc += mVel;
    //mVel *= mDecay;
    
    
}

void Particle::draw()
{
    gl::color( Color( 1.0f, 1.0f, 1.0f ));
    //gl::color( Color( r, g, b));    
           
    //gl::drawSolidCircle( mLoc + mDirToCursor * 0.2f, mRadius);
    //gl::drawSolidCircle( mLoc, mRadius);
    gl::drawSolidCircle( mLoc, mRadius );    
}

bool Particle::isDead()
{
    return mIsDead;
}
