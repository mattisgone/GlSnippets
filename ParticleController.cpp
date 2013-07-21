//
//  ParticleController.cpp
//  swim
//
//  Created by Matthew Owen on 7/1/13.
//
//

#include "ParticleController.h"
#include <list>

/**
 *
 */
ParticleController::ParticleController() {
  mParticles = std::list<Particle> ();
}
/**
 *
 */
void ParticleController::addParticle(float x, float y, float z) {
  mParticles.push_back(Particle(Vec3f(x, y, z)));
}
/**
 *
 */
void ParticleController::applyForce(float zoneRadiusSquared = 60.f, float thresh = 1.f) {
  // Iterate through list of particles
  for (std::list<Particle>::iterator p = mParticles.begin(); p!= mParticles.end(); ++p) {
    // Copy iterator
    std::list<Particle>::iterator q = p;
    
    // This loop goes through every corresponding pair of vectors (once)
    for (++q; q != mParticles.end(); ++q) {
      //
      Vec3f dir = p->mLoc - q->mLoc;
      float d = dir.lengthSquared();
      
      // Move to the next pair
      float percent = d/zoneRadiusSquared;
      
      // If in the repulsion zone
      if (percent < thresh) {
        float F = ( thresh/percent - 1.0f ) * 0.000001f;
        dir = dir.normalized() * F;
        p->mAcc += dir;
        q->mAcc -= dir;
      }
      else {
        float threshDelta = 1.0f - thresh;
        float adjustedPercent = ( percent - thresh )/threshDelta;
        float F = ( 1.0 - ( cos( adjustedPercent * M_PI*2.0f ) * -0.5f + 0.5f ) ) * 0.04f;
        dir = dir.normalized() * F;
        p->mAcc -= dir;
        q->mAcc += dir;
      }
    }
  }
}
/**
 *
 */
void ParticleController::removeParticles(int amt) {
  for (int k = 0; k < amt; k++)
    mParticles.pop_back();
}
void ParticleController::update() {
  // Repulse
  applyForce(50.f);
  
  for (std::list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p)
    p->update();
}
/**
 *
 */
void ParticleController::draw() {
  for (std::list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p)
    p->draw();
}