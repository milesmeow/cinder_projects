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
	void setup();
	void update();
	void draw();
	
	// PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	float				mCameraDistance;
	Vec3f				mEye, mCenter, mUp;
	
	ParticleController	mParticleController;
	
	bool				mCentralGravity;
};

void TutorialApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void TutorialApp::setup()
{	

	mCentralGravity = false;
    
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
	if( mCentralGravity ) mParticleController.pullToCenter( mCenter );
	mParticleController.update();
}

void TutorialApp::draw()
{	
	gl::clear( Color( 0, 0, 0.01f ), true );
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	// DRAW PARTICLES
	glColor4f( ColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
	mParticleController.draw();
	
	// DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}

CINDER_APP_BASIC( TutorialApp, RendererGl )
