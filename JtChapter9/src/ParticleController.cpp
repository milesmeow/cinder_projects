#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{
}

void ParticleController::pullToCenter( const ci::Vec3f &center )
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ) {
		p->pullToCenter( center );
	}
}

void ParticleController::applyForce( float zoneRadiusSqrd, float lowThresh, float highThresh )
{
	for( list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1 ){
        
		list<Particle>::iterator p2 = p1;
		for( ++p2; p2 != mParticles.end(); ++p2 ) {
			Vec3f dir = p1->mPos - p2->mPos;
			float distSqrd = dir.lengthSquared();
            
			if( distSqrd <= zoneRadiusSqrd ){
                
                float percent = distSqrd/zoneRadiusSqrd;
                
                if( percent < lowThresh ) { // SEPARATION
                
                    float F = ( zoneRadiusSqrd/distSqrd - 1.0f ) * 0.01f;
                    dir.normalize();
                    dir *= F;
                    
                    p1->mAcc += dir;
                    p2->mAcc -= dir;
                
                }
                else if( percent < highThresh ) { // if it's within the higher threshold limits, ALIGN
                    float threshDelta = highThresh - lowThresh;
                    float adjustedPercent = ( percent - lowThresh )/threshDelta;
                    float F = ( 0.5f - cos( adjustedPercent * M_PI * 2.0f ) * 0.5f + 0.5f ) * 0.01f;
                    p1->mAcc += p2->mVel.normalized() * F;
                    p2->mAcc += p1->mVel.normalized() * F;
                }
                else { // ... else ATTRACT
                    float threshDelta = 1.0f - lowThresh;
                    float adjustedPercent = ( percent - lowThresh )/threshDelta;
                    float F = ( 1.0 - ( cos( adjustedPercent * M_PI*2.0f ) * -0.5f + 0.5f ) ) * 0.04f;
					dir = dir.normalized() * F;
					p1->mAcc -= dir;
					p2->mAcc += dir;
                }                
                
			}
		}
	}
}

void ParticleController::update( bool flatten )
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ) {
		p->update( flatten );
	}
}

void ParticleController::draw()
{
	gl::color( ColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}
	
	glBegin( GL_LINES );
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->drawTail();
	}
	glEnd();
}

void ParticleController::addParticles( int amt )
{
	for( int i=0; i<amt; i++ ) {
        Vec3f pos = Rand::randVec3f() * Rand::randFloat( 50.0f, 250.0f );
		Vec3f vel = Rand::randVec3f() * 2.0f;
        
		mParticles.push_back( Particle( pos, vel ) );
	}
}


