//
//  SvvimScene.h
//  SvvimCommercial
//
//  Created by Matthew Owen on 8/6/13.
//
//

#pragma once
#ifndef _SvvimScene_h
#define _SvvimScene_h

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Fbo.h"
#include "cinder/qtime/QuickTime.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SvvimScene {
public:
  SvvimScene() {
  };
  SvvimScene(App *app) : mAlpha(0.f), mBeta(0.f), mGamma(0.f) { }
  virtual void update() { }
  virtual void draw() {
    gl::color(1.f, 1.f, 1.f);
    gl::drawSolidRect(Rectf(0., 0., 30., 30.));
  }
  virtual void start() {};
  virtual void stop() {};
  virtual void setup() {};
  virtual void cleanup() {};
  void setParam(std::string key, float val) {
    mParams[key] = val;
  }
  
  void setAlpha (float a = 0.f) { mAlpha = a; }
  void setBeta (float b = 0.f) { mBeta = b; }
  void setGamma (float c = 0.f) { mGamma = c; }
  
protected:
  App * mParentAppRef;
  bool mIsLoaded;
  float mAlpha, mBeta, mGamma;
  std::map <std::string, float> mParams;
};

#endif
