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
	mVel	= Rand::randFloat( 5.0f );
	//mRadius	= Rand::randFloat( 1.0f, 5.0f );
	//mRadius	= cos( mLoc.y * 0.1f ) + sin( mLoc.x * 0.1f ) + 2.0f;
    //mRadius = ( sin( mLoc.y * mLoc.x ) + 1.0f ) * 2.0f;
    mScale = 6.0f;
}

void Particle::update( const Channel32f &channel,  const ci::Channel32f &rChan, const ci::Channel32f &gChan, const ci::Channel32f &bChan, const ci::Vec2i &mouseLoc )
{
	
    //calculate the vector that points from the particl to the mouse.
    mDirToCursor = mouseLoc - mLoc;
    mDirToCursor.safeNormalize(); //normalize it so it gives us a unit vector.
    
    
    Vec2f newLoc = mLoc + mDirToCursor * 100.f;
    newLoc.x = constrain( newLoc.x, 0.0f, channel.getWidth() - 1.0f );
    newLoc.y = constrain( newLoc.y, 0.0f, channel.getHeight() - 1.0f );
    
    
    
    //mRadius = channel.getValue( mLoc ) * mScale;
    mRadius = channel.getValue( newLoc ) * mScale;
    
    Vec2i mLoci = (Vec2i) mLoc;
        
    r = rChan.getValue( newLoc );
    g = gChan.getValue( newLoc );
    b = bChan.getValue( newLoc );    
    
    //console() << r << ", " << g << ", " << b << std::endl;
    //console() << channel.getValue(mLoc) << std::endl;
    //console() << "hello" << std::endl;
    
}

void Particle::draw()
{
    //gl::color( Color( 1.0f, 1.0f, 1.0f ));
    gl::color( Color( r, g, b));    
    
    /*
    float arrowLength = 15.0f;
    Vec3f p1( mLoc, 0.0f );
    Vec3f p2( mLoc + mDirToCursor, 0.0f);
    float headLength = 6.0f;
    float headRadius = 3.0f;
    gl::drawVector( p1, p2, headLength, headRadius );
    */
     
//    Rectf rect( mLoc.x, mLoc.y, mLoc.x + mRadius, mLoc.y + mRadius );
//	gl::drawSolidRect( rect );
  
    gl::drawSolidCircle( mLoc + mDirToCursor * 0.2f, mRadius);
}
