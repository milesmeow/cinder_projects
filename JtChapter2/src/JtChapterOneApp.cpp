#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "ParticleController.h"


#define TOTAL_PARTICLES 4800
#define RESOLUTION 10


using namespace ci;
using namespace ci::app;
using namespace std;

class JtChapterOneApp : public AppBasic {

    public:
        void prepareSettings( Settings *settings );
        void setup();
        void mouseDown( MouseEvent event );	
        void update();
        void draw();
        ParticleController myPController;

    
    Channel32f mChannel;
    gl::Texture	mTexture;

};

void JtChapterOneApp::prepareSettings( Settings *settings) {
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}


void JtChapterOneApp::setup()
{
    mChannel = Channel32f( loadImage( loadResource( "jasmine.jpg" )));
    mTexture = mChannel;
                          
    myPController = ParticleController( RESOLUTION );
    
}

void JtChapterOneApp::mouseDown( MouseEvent event )
{
}

void JtChapterOneApp::update()
{
    if( ! mChannel ) return;
    myPController.update( mChannel );
}

void JtChapterOneApp::draw()
{
    //float gray = sin( getElapsedSeconds() ) * 0.5f + 0.5f;
    //gl::clear( Color( gray, gray, gray ), true);

    myPController.draw();
}


CINDER_APP_BASIC( JtChapterOneApp, RendererGl )
