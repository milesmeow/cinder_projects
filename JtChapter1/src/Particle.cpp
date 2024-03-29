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
	mRadius	= 3.0f;
}

void Particle::update()
{
	mLoc += mDir * mVel;
}

void Particle::draw()
{
	gl::drawSolidCircle( mLoc, mRadius );
}
