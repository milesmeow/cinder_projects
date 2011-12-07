#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Perlin.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "ParticleController.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

#define RESOLUTION 10
#define NUM_PARTICLES_TO_SPAWN 15

#include <sstream>
using std::stringstream;

using namespace ci;
using namespace ci::app;

class TutorialApp : public AppBasic {
 public:
	void prepareSettings( Settings *settings );
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void setup();
	void update();
	void draw();
	
	Perlin mPerlin;

	Channel32f mChannel;
	gl::Texture	mTexture;
	
	Vec2i mMouseLoc;
	Vec2f mMouseVel;
	bool mIsPressed;
	
	ParticleController mParticleController;
	
	bool mDrawParticles;
	bool mDrawImage;
	bool mSaveFrames;
	bool mCentralGravity;
	bool mAllowPerlin;
	
	int mSaveFrameCount;
    
    CameraPersp mCam;
    Vec3f mEye;
    Vec3f mCenter;
    Vec3f mUp;
    
    params::InterfaceGl mParams;
    Quatf mSceneRotation;
    float mCameraDistance;
};

void TutorialApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void TutorialApp::setup()
{	
	mPerlin = Perlin();
	
	Url url( "http://libcinder.org/media/tutorial/paris.jpg" );
	mChannel = Channel32f( loadImage( loadUrl( url ) ) );
	mTexture = mChannel;

	mMouseLoc = Vec2i( 0, 0 );
	mMouseVel = Vec2f::zero();
	
	mDrawParticles	= true;
	mDrawImage		= false;
	mIsPressed		= false;
	mCentralGravity = false;
	mAllowPerlin	= false;
	mSaveFrames		= false;
	mSaveFrameCount = 0;
    
    // Takes four parameters:
    // (1) foV : the smaller the number the tighter the fustrum (usually between 60.0 and 90.0)
    // (2) aspect ratio of the application window
    // (3) near clipping plane
    // (4) far clipping plane
    mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f ); 
    
    //define the camera
    mCameraDistance = 500.0f;
    mEye    = Vec3f( 0.0f, 0.0f, mCameraDistance ); //position of the camera
    mCenter = Vec3f::zero(); //the location in 3D space that the camera points at
    mUp     = Vec3f::yAxis(); //the camera's up direction
    
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    
    // Initialize the Params object
    mParams = params::InterfaceGl( "Flocking", Vec2i( 225, 200 ) );
    // We tell Params that we want it control the mSceneRotation variable...during runtime!
    // It expects the addr in memory of the variable...that's what & is.
    // So, it will include an arc-ball in the scene.
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" );
}


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
	mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void TutorialApp::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void TutorialApp::keyDown( KeyEvent event )
{
	if( event.getChar() == '1' ){
		mDrawImage = ! mDrawImage;
	} else if( event.getChar() == '2' ){
		mDrawParticles = ! mDrawParticles;
	}
	
	if( event.getChar() == 's' ){
		mSaveFrames = ! mSaveFrames;
	} else if( event.getChar() == 'g' ){
		mCentralGravity = ! mCentralGravity;
	} else if( event.getChar() == 'p' ){
		mAllowPerlin = ! mAllowPerlin;
	}
}


void TutorialApp::update()
{
	if( ! mChannel ) return;
	
	if( mIsPressed )
		mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN, mMouseLoc, mMouseVel );
	
    // Stop repulsing for now.
	//mParticleController.repulseParticles();
	
	if( mCentralGravity )
		mParticleController.pullToCenter();
		
	if( mAllowPerlin )
		mParticleController.applyPerlin( mPerlin );
		
	mParticleController.update( mChannel, mMouseLoc );
}

void TutorialApp::draw()
{	
	gl::clear( Color( 0, 0, 0 ), true );
	
	if( mDrawImage ){
		mTexture.enableAndBind();
		gl::draw( mTexture, getWindowBounds() );
	}
	
	if( mDrawParticles ){
		glDisable( GL_TEXTURE_2D );
		mParticleController.draw();
	}
	
	if( mSaveFrames ){
		writeImage( getHomeDirectory() + "image_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
	}
}

CINDER_APP_BASIC( TutorialApp, RendererGl )
