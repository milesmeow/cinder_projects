//
//  Ball.cpp
//  Bouncy
//
//  Created by James Tu on 12/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Ball.h"

using namespace ci;
using namespace ci::app; //needed for console()
using namespace std; //needed for std::endl

Ball::Ball()
{    
}

Ball::Ball ( ci::Vec2f loc, ci::Vec2f vel ) {
    mLoc = loc;
    mVel = vel;
}


void Ball::update() {
    mLoc += mVel;
    if (mLoc.x > 800.0f || mLoc.x < 0.0f ) {
        mVel.x *= -1;
    }
    if (mLoc.y > 600.0f || mLoc.y < 0.0f ) {
        mVel.y *= -1;
    }
    //console() << mLoc << std::endl;
}

void Ball::draw() {
    gl::drawStrokedCircle( mLoc, 10.0f );
}
