#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HelloWorldApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

// This function is not included in the default empty project.
// This runs once at the beginning of your program...before setup();
void HelloWorldApp::prepareSettings( Settings *settings) {
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

// This runs once at the start of the program
void HelloWorldApp::setup()
{

}


void HelloWorldApp::mouseDown( MouseEvent event )
{
    // This allows you to write messages to the console. Useful for simple debugging.
    console() << "Hello World...the mouse was clicked at: " << event.getPos() << std::endl;

}

// An update event happens before each frame is drawn.
void HelloWorldApp::update()
{
}

// This is called to draw the next frame before it is shown to the user
void HelloWorldApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
}


CINDER_APP_BASIC( HelloWorldApp, RendererGl )
