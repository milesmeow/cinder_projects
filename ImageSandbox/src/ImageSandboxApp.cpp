#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageSandboxApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void mouseUp( MouseEvent event );	
	void mouseMove( MouseEvent event );	    
	void update();
	void draw();
    

    gl::Texture mTexture;
    Surface     mSurface;
    bool        isMouseDown;
    Area        mouseArea;
    
};


void ImageSandboxApp::prepareSettings( Settings *settings) {
    settings->setWindowSize( 720, 540 ); //( 1024, 768 );
    settings->setFrameRate( 60.0f );
}

/*
void ImageSandboxApp::setup()
{
    //Textures represent a block of bitmap data loaded into the GPU memory
    mTexture = loadImage( loadResource( "jasmine.jpg" ));
}
*/

void ImageSandboxApp::setup()
{
    //Surfaces represent a block of bitmap data loaded into the CPU memory
    //Use Surfaces if you need to manipulate the bitmap data...such as filtering, replacing
    //sections of bitmaps, or tweaking values of pixels.
    
    mSurface = loadImage( loadResource( "jasmine.jpg" )); //720x540 
    isMouseDown = false;
}


void ImageSandboxApp::mouseDown( MouseEvent event )
{
    isMouseDown = true;
    Vec2i tMouseLoc = event.getPos();
    mouseArea = ci::Area( tMouseLoc.x-50, tMouseLoc.y-50, tMouseLoc.x+50, tMouseLoc.y+50 );
}

void ImageSandboxApp::mouseUp( MouseEvent event )
{
    isMouseDown = false;
}

void ImageSandboxApp::mouseMove( MouseEvent event )
{
    Vec2i tMouseLoc = event.getPos();
    mouseArea = ci::Area( tMouseLoc.x-50, tMouseLoc.y-50, tMouseLoc.x+50, tMouseLoc.y+50 );
}

//void ImageSandboxApp::update()
//{
//    //inverts the image
//    Area area( 0, 0, 500, 500 );
//    
//    Surface::Iter iter = mSurface.getIter( area );
//    while( iter.line() ) {
//        while( iter.pixel() ) {
//            iter.r() = 255 - iter.r();
//            iter.g() = 255 - iter.g();
//            iter.b() = 255 - iter.b();            
//        }
//    }
//    
//}

void ImageSandboxApp::update()
{
    
    
    if ( isMouseDown ) {
        //blurs the image
        //mouseArea = ci::Area( 100, 100, 200, 200 );
        
        Surface origSurface = mSurface.clone();
        Surface::Iter origIter = origSurface.getIter( mouseArea );
        
        Surface::Iter iter = mSurface.getIter( mouseArea );
        while( iter.line() && origIter.line() ) {
            while( iter.pixel() && origIter.pixel() ) {
                iter.r() = ( ( origIter.r() + origIter.r(1,0) + origIter.r(-1,0) + origIter.r(0,1) + origIter.r(0,-1) ) )/5;
                iter.g() = ( ( origIter.g() + origIter.g(1,0) + origIter.g(-1,0) + origIter.g(0,1) + origIter.g(0,-1) ) )/5;
                iter.b() = ( ( origIter.b() + origIter.b(1,0) + origIter.b(-1,0) + origIter.b(0,1) + origIter.b(0,-1) ) )/5;            
            }
        }
    }
}



void ImageSandboxApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    //gl::draw( mTexture );
    
    gl::draw( mSurface );
}


CINDER_APP_BASIC( ImageSandboxApp, RendererGl )
