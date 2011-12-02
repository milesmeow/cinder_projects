//
//  Particle.h
//  JtChapterOne
//
//  Created by James Tu on 11/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "cinder/Channel.h"
#include "cinder/Surface.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/perlin.h"
#include <vector>

class Particle {
public:
	Particle();
	Particle( ci::Vec2f, ci::Vec2f );
	void update( const ci::Perlin &perlin, const ci::Channel32f &channel, const ci::Channel32f &rChan, const ci::Channel32f &gChan, const ci::Channel32f &bChan, const ci::Vec2i &mouseLoc );
	void draw();
    bool isDead();
	
	ci::Vec2f	mLoc;
	ci::Vec2f	mDir;
    ci::Vec2f   mVel;
	
	float		mRadius;
    float		mScale;
    
    float r;
    float g;
    float b;      
    
    ci::Color   mColor;
    
    ci::Vec2f   mDirToCursor;
    
    int mAge;
    int mLifeSpan;
    bool mIsDead;
    float mDecay;
    

};
