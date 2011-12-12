#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "ParticleController.h"


#define TOTAL_PARTICLES 19200
#define RESOLUTION 5


using namespace ci;
using namespace ci::app;
using namespace std;

//Basic Tutorial JTChapter3 (aka Hello Chapter 3)

class JtChapterOneApp : public AppBasic {

    public:
        void prepareSettings( Settings *settings );
        void setup();
    
        void mouseDown( MouseEvent event );	
        void mouseMove( MouseEvent event );
        void mouseDrag( MouseEvent event );
    
        void keyDown( KeyEvent event );
        
        void update();
        void draw();
        ParticleController myPController;

    
    Channel32f mChannel;
    gl::Texture	mTexture;
    
    Surface32f mSurface;
    
    bool mRenderImage;
    bool mRenderParticles;
    
    Vec2i mMouseLoc;

};

void JtChapterOneApp::prepareSettings( Settings *settings) {
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

//I'm trying to get at the color data!
void JtChapterOneApp::setup()
{
    mRenderImage = false;
    mRenderParticles = true;
    
    
    mSurface = loadImage( loadResource( "jasmine.jpg" )); //initializes and loads the image, so we have access to RGB
    mChannel = Channel32f( loadImage( loadResource( "jasmine.jpg" )));
    mTexture = gl::Texture( mSurface );
        
    myPController = ParticleController( RESOLUTION );
    
}

/*
void JtChapterOneApp::setup()
{
    mRenderImage = false;
    mRenderParticles = true;
    
    mChannel = Channel32f( loadImage( loadResource( "jasmine.jpg" )));
    mTexture = mChannel;
    
    
    myPController = ParticleController( RESOLUTION );
    
}
*/

void JtChapterOneApp::mouseDown( MouseEvent event )
{
}

void JtChapterOneApp::mouseMove( MouseEvent event )
{
    mMouseLoc = event.getPos();
}

void JtChapterOneApp::mouseDrag( MouseEvent event )
{
    mouseMove( event );
}

void JtChapterOneApp::keyDown( KeyEvent event )
{
    
    console() << event.getChar() << std::endl;
    
    if( event.getChar() == '1' ){
        mRenderImage = !mRenderImage;
    } else if( event.getChar() == '2' ){
        mRenderParticles = !mRenderParticles;
    }
}

void JtChapterOneApp::update()
{
    if( ! mChannel ) return;
    myPController.update( mChannel, mSurface, mMouseLoc );
}

void JtChapterOneApp::draw()
{
    //float gray = sin( getElapsedSeconds() ) * 0.5f + 0.5f;
    gl::clear( Color( 0, 0, 0 ), true);

    if ( mRenderImage ){
        mTexture.enableAndBind();
        gl::draw( mTexture, getWindowBounds() );
    }
    
    if( mRenderParticles ){
        myPController.draw();
    }
}


CINDER_APP_BASIC( JtChapterOneApp, RendererGl )
