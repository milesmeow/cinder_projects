#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Ball.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BouncyApp : public AppBasic {
  public:
    void prepareSettings( Settings *setting );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Ball mBall;
};

void BouncyApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize( 800.0f, 600.0f );
    settings->setFrameRate( 60.0f );
}

void BouncyApp::setup()
{
    float rndX = Rand::randFloat()*800.0f;
    float rndY = Rand::randFloat()*600.0f;    
    mBall = Ball( Vec2f( rndX, rndY ), Rand::randVec2f() * 10.0f);
}

void BouncyApp::mouseDown( MouseEvent event )
{
}

void BouncyApp::update()
{
    mBall.update();
}

void BouncyApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    mBall.draw();
}


CINDER_APP_BASIC( BouncyApp, RendererGl )
