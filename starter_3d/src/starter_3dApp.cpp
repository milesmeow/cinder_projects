#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class starter_3dApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings );    
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    // PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	float				mCameraDistance;
	Vec3f				mEye, mCenter, mUp;
    
};


void starter_3dApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void starter_3dApp::setup()
{
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
    
    
    // Initialize the Params object...and examples of parameter control
    // (1) Title
    // (2) Size
    // (3) Color, optional.
    mParams = params::InterfaceGl( "Flocking", Vec2i( 225, 200 ), Color(0.0f, 1.0f, 0.0f) );
    
    // We tell Params that we want it control the mSceneRotation variable...during runtime!
    // It expects the addr in memory of the variable...that's what & is.
    // So, it will include an arc-ball in the scene.
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" );
    
}

void starter_3dApp::mouseDown( MouseEvent event )
{
}

void starter_3dApp::update()
{
    // UPDATE CAMERA
	mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCam.lookAt( mEye, mCenter, mUp );
	gl::setMatrices( mCam );
	gl::rotate( mSceneRotation );
	
}

void starter_3dApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::enableDepthRead();
	gl::enableDepthWrite();
		
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f ), 20.0f, 16 );
    
	// DRAW PARAMS WINDOW
	params::InterfaceGl::draw();    
}


CINDER_APP_BASIC( starter_3dApp, RendererGl )
