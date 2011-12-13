#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
};

void BouncyApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize( 800.0f, 600.0f );
    settings->setFrameRate( 60.0f );
}

void BouncyApp::setup()
{
}

void BouncyApp::mouseDown( MouseEvent event )
{
}

void BouncyApp::update()
{
}

void BouncyApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( BouncyApp, RendererGl )
