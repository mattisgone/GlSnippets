#pragma once

#include <iostream>
#include "cinder/Rand.h"

using namespace cinder;

class Particle {
public:
  // Constructor
  Particle(Vec3f loc) {
    mAcc = Vec3f(0.f, 0.f, 0.f);
    mVel = Vec3f(0.f, 0.f, 0.f);
    mLoc = loc;
    mDecay = 0.000003f;
    mMinSpeed = 1.f;
    mMaxSpeed = 3.f;
    
    mRadius = 30.f;
    mColor = Color(1., 1., 1.);
    //    mBornOn = app:getElapsedTime();
  }
  // Update position
  void update() {
    pullToPoint(Vec3f(0., 0., 0.));
    
    mVel += mAcc;
    
    if (mVel.lengthSquared() > mMaxSpeed) {
      mVel.normalize();
      mVel *= mMaxSpeed;
    }
    else if (mVel.lengthSquared() < mMinSpeed) {
      mVel.normalize();
      mVel *= mMinSpeed;
    }
    
    mLoc += mVel;
    mMass = pow(mRadius, 2) * 0.0005f;
    //  mVel *= mDecay;
  }
  // Draw particle
  void draw() {
    gl::color(mColor);
    //gl::drawCube(mLoc, Vec3f(mRadius, mRadius, mRadius));
    Vec3f tail = mVel.normalized();
    gl::drawVector(mLoc, mLoc - tail, 15.f, 7.f);
  }
  /**
   * Whether the Particle should be considered dead
   */
  bool isDead() const {
    // return app::getElapsedTime() - mBornOn > 5.;
    return false;
  }
  // D.
  void pullToPoint(const Vec3f &point) {
    Vec3f dirToCenter = mLoc - point;
    float pullStrength = 1.f;
    mVel -= dirToCenter.normalized() * pullStrength ;
  }
public:
  cinder::Vec3f mLoc, mVel, mAcc;
  float mDecay, mMass, mRadius, mMinSpeed, mMaxSpeed;
  Color mColor;
  double mBornOn;
};