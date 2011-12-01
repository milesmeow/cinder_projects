#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class JtChapterOneApp : public AppBasic {
    gl::Texture myImage;
    ParticleController myPController;

public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    

};

void JtChapterOneApp::prepareSettings( Settings *settings) {
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}


void JtChapterOneApp::setup()
{
    myImage = gl::Texture( loadImage( loadResource( "jasmine.jpg" ) ) );
    //myPController.addParticles( 250 );
    
}

void JtChapterOneApp::mouseDown( MouseEvent event )
{
    myPController.addParticles( 100 );
}

void JtChapterOneApp::update()
{
    myPController.update();
}

void JtChapterOneApp::draw()
{
    float gray = sin( getElapsedSeconds() ) * 0.5f + 0.5f;
    gl::clear( Color( gray, gray, gray ), true);
    gl::draw( myImage, getWindowBounds() );
    myPController.draw();
}


CINDER_APP_BASIC( JtChapterOneApp, RendererGl )
