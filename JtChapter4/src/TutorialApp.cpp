#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "ParticleController.h"

#define NUM_PARTICLES_TO_SPAWN 25
#define RESOLUTION 5


using namespace ci;
using namespace ci::app;
using namespace std;

class TutorialApp : public AppBasic {
    
public:
    void prepareSettings( Settings *settings );
    void setup();
    
    void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );	
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
    
    bool mIsPressed;
    
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

void TutorialApp::prepareSettings( Settings *settings) {
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

//I'm trying to get at the color data!
void TutorialApp::setup()
{
    mRenderImage = false;
    mRenderParticles = true;
    mIsPressed = false;
    
    mSurface = loadImage( loadResource( "jasmine.jpg" )); //initializes and loads the image, so we have access to RGB
    mChannel = Channel32f( loadImage( loadResource( "jasmine.jpg" )));
    mTexture = gl::Texture( mSurface );
    
    myPController = ParticleController( RESOLUTION );
    
}

/*
 void TutorialApp::setup()
 {
 mRenderImage = false;
 mRenderParticles = true;
 
 mChannel = Channel32f( loadImage( loadResource( "jasmine.jpg" )));
 mTexture = mChannel;
 
 
 myPController = ParticleController( RESOLUTION );
 
 }
 */

void TutorialApp::mouseDown( MouseEvent event )
{
    mIsPressed = true;
}

void TutorialApp::mouseUp( MouseEvent event )
{
    mIsPressed = false;
}


void TutorialApp::mouseMove( MouseEvent event )
{
    mMouseLoc = event.getPos();
}

void TutorialApp::mouseDrag( MouseEvent event )
{
    mouseMove( event );
}

void TutorialApp::keyDown( KeyEvent event )
{
    
    console() << event.getChar() << std::endl;
    
    if( event.getChar() == '1' ){
        mRenderImage = !mRenderImage;
    } else if( event.getChar() == '2' ){
        mRenderParticles = !mRenderParticles;
    }
}

void TutorialApp::update()
{
    
    
    if( ! mChannel ) return;
    myPController.update( mChannel, mSurface, mMouseLoc );
    
    if( mIsPressed ){
        myPController.addParticles( 5, mMouseLoc );
    }
    
}

void TutorialApp::draw()
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


CINDER_APP_BASIC( TutorialApp, RendererGl )
