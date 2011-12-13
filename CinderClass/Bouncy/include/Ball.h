//
//  Ball.h
//  Bouncy
//
//  Created by James Tu on 12/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

class Ball {
public:
	Ball();
	Ball( ci::Vec2f loc, ci::Vec2f vel );    
	void update();
	void draw();
	
    //float		mRadius;

	ci::Vec2f   mLoc;
	ci::Vec2f   mVel;
};
