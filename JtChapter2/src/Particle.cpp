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

Particle::Particle()
{
}

Particle::Particle( Vec2f loc )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();
	mVel	= Rand::randFloat( 5.0f );
	//mRadius	= Rand::randFloat( 1.0f, 5.0f );
	//mRadius	= cos( mLoc.y * 0.1f ) + sin( mLoc.x * 0.1f ) + 2.0f;
    //mRadius = ( sin( mLoc.y * mLoc.x ) + 1.0f ) * 2.0f;
    mScale = 6.0f;
}

void Particle::update( const Channel32f &channel )
{
	//mLoc += mDir * mVel;
    float gray = channel.getValue( mLoc );
    mColor = Color( gray, gray, gray );
    mRadius = channel.getValue( mLoc ) * mScale;
    //mRadius = 3.0f;
}

void Particle::draw()
{
    gl::color( mColor );
	gl::drawSolidCircle( mLoc, mRadius );
}
