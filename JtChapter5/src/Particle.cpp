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

    //	mLoc	= loc;
//	mDir	= Rand::randVec2f();
//
//    mScale = 6.0f;
//    
//    mAge = 0;
//    mLifespan = Rand::randInt( 50, 200 );
//    mIsDead = false;
//    mDecay = 0.9999f;
//    mRadiusDest	= 3.0f;
//    
//    mVel = vel;
//    mAcc = Vec2f(0.0f, 0.0f);
    
    
    mLoc			= loc;
	mVel			= vel;
	mAcc			= Vec2f::zero();
	
	mDecay			= Rand::randFloat( 0.95f, 0.951f );
	mRadius			= 3.0f + Rand::randFloat( 0.1 );
	mRadiusDest		= 3.0f;
	mMass			= mRadius * mRadius * 0.0001f + 0.01f;
	mScale			= 3.0f;
	mAge			= 0;
	mLifespan		= Rand::randInt( 50, 250 );
	mIsDead			= false;
    
    
    
}

void Particle::update( const Perlin &perlin, const Channel32f &channel,  const Channel32f &rChan, const Channel32f &gChan, const Channel32f &bChan, const Vec2i &mouseLoc )
{
 
    

    
    
    mVel += mAcc;
    
	float maxVel = mRadius + 0.0025f;
	
	float velLength = mVel.lengthSquared() + 0.1f;
	if( velLength > maxVel*maxVel ){
		mVel.normalize();
		mVel *= maxVel;
	}
	
	mLoc += mVel;
	mVel *= mDecay;
	mAcc.set( 0, 0 );
	
	if( mLoc.x >= 0.0f && mLoc.x <= (float)app::getWindowWidth() - 1 &&
       mLoc.y >= 0.0f && mLoc.y <= (float)app::getWindowHeight() - 1 ){
		
		mRadiusDest	= channel.getValue( mLoc ) * mScale + 0.5f;
	} else {
		mRadiusDest = 0.1f;
	}
	
	mRadius -= ( mRadius - mRadiusDest ) * 0.1f;
	mMass		= mRadius * mRadius * 0.0001f + 0.01f;
	
	//Uncomment these lines to enable particles to die over time
	//mAge++;
	//if( mAge > mLifespan ) mIsDead = true;
    
    
    r = rChan.getValue(mLoc);
    g = gChan.getValue(mLoc);
    b = bChan.getValue(mLoc);
    
    
    
}    
    
//void Particle::update( const Perlin &perlin, const Channel32f &channel,  const Channel32f &rChan, const Channel32f &gChan, const Channel32f &bChan, const Vec2i &mouseLoc )
//    {    
//    
//    //Age the particle
//    mAge++;
//    if( mAge > mLifespan ){
//        mIsDead = true;
//    }
//
//    
//    //make the particle shrink as it ages
//    float agePer = 1.0f - (mAge / (float)mLifespan); 
//    mRadius = 3.0f * agePer;
//    
//    
//    /*
//    // get Perlin noise value based on my location and
//	// elapsed seconds and turn this noise value into an angle.
//	float nX = mLoc.x * 0.005f;
//	float nY = mLoc.y * 0.005f;
//	float nZ = app::getElapsedSeconds() * 0.1f;
//	float noise = perlin.fBm( nX, nY, nZ );
//	float angle = noise * 15.0f;
//	Vec2f noiseVector( cos( angle ), sin( angle ) );
//    mVel += noiseVector * 0.2f * ( 1.0f - agePer );
//    */
//    
//    mRadius = channel.getValue( mLoc ) * mScale;    
//    
// 
//    
//    mMass = mRadius * mRadius * 0.005f;
//    
//    mVel += mAcc;
//    mLoc += mVel;
//    mVel *= mDecay;
//    mAcc.set( 0, 0 );
//    
//}















void Particle::draw()
{
    //gl::color( Color( 1.0f, 1.0f, 1.0f ));
    gl::color( Color( r, g, b));    
           
    //gl::drawSolidCircle( mLoc + mDirToCursor * 0.2f, mRadius);
    //gl::drawSolidCircle( mLoc, mRadius);
    gl::drawSolidCircle( mLoc, mRadius );    
}

bool Particle::isDead()
{
    return mIsDead;
}
