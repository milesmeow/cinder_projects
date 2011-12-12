#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "ParticleController.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

#define NUM_INITIAL_PARTICLES 250
#define NUM_PARTICLES_TO_SPAWN 15

using namespace ci;
using namespace ci::app;

class TutorialApp : public AppBasic {
 public:
	void prepareSettings( Settings *settings );
	void keyDown( KeyEvent event );
	void setup();
	void update();
	void draw();
	
	// PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	Vec3f				mEye, mCenter, mUp;
	float				mCameraDistance;
	
	ParticleController	mParticleController;
	float				mZoneRadius;
	
	bool				mCentralGravity;
	bool				mFlatten;
};

void TutorialApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void TutorialApp::setup()
{	

	mCentralGravity = false;
    mFlatten = false;
	mZoneRadius		= 30.0f;
    
    //define the camera
    mCameraDistance = 500.0f;
    mEye    = Vec3f( 0.0f, 0.0f, mCameraDistance ); //position of the camera
    mCenter = Vec3f::zero(); //the location in 3D space that the camera points at
    mUp     = Vec3f::yAxis(); //the camera's up direction

    // Takes four parameters:
    // (1) foV : the smaller the number the tighter the fustrum (usually between 60.0 and 90.0)
    // (2) aspect ratio of the application window
    // (3) near clipping plane
    // (4) far clipping plane
    mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f ); 
    
    
    // Initialize the Params object
    mParams = params::InterfaceGl( "Flocking", Vec2i( 225, 200 ) );
    // We tell Params that we want it control the mSceneRotation variable...during runtime!
    // It expects the addr in memory of the variable...that's what & is.
    // So, it will include an arc-ball in the scene.
    mParams.addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
    mParams.addSeparator();
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "Center Gravity", &mCentralGravity, "keyIncr=g" );
	mParams.addParam( "Flatten", &mFlatten, "keyIncr=f" );
	mParams.addSeparator();
	mParams.addParam( "Zone Radius", &mZoneRadius, "min=10.0 max=100.0 step=1.0 keyIncr=z keyDecr=Z" );    
    
    // CREATE PARTICLE CONTROLLER
	mParticleController.addParticles( NUM_INITIAL_PARTICLES );

    
}

void TutorialApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'p' ){
		mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN );
	}
}

void TutorialApp::update()
{

    // Stop repulsing for now.
	//mParticleController.repulseParticles();

    // UPDATE CAMERA
	mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCam.lookAt( mEye, mCenter, mUp );
	gl::setMatrices( mCam );
	gl::rotate( mSceneRotation );
	
	// UPDATE PARTICLE CONTROLLER
    mParticleController.applyForce( mZoneRadius );    
	if( mCentralGravity ) mParticleController.pullToCenter( mCenter );
    
	mParticleController.update( mFlatten );
}

void TutorialApp::draw()
{	
	gl::clear( Color( 0, 0, 0 ), true );
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	// DRAW PARTICLES
	mParticleController.draw();
	
	// DRAW ZONE DIAGRAM
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::setMatricesWindow( getWindowSize() );
	gl::pushModelView();
        gl::translate( Vec3f( 117.0f, getWindowHeight() - 117.0f, 0.0f ) );
        
        gl::color( ColorA( 0.25f, 0.25f, 1.0f, 1.0f ) );
        gl::drawSolidCircle( Vec2f::zero(), mZoneRadius );
        
        gl::color( ColorA( 1.0f, 1.0f, 1.0f, 0.25f ) );
        gl::drawStrokedCircle( Vec2f::zero(), 100.0f );
	gl::popModelView();
	
	// DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}

CINDER_APP_BASIC( TutorialApp, RendererGl )
