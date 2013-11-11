//
//  CinderHelperFunctions.h
//  RainbowCrush
//
//  Created by Matthew Owen on 7/27/13.
//
//

#ifndef RainbowCrush_CinderHelperFunctions_h
#define RainbowCrush_CinderHelperFunctions_h

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"


/**
 *
 */
using namespace ci;
using namespace ci::app;
using namespace std;

namespace svvim { namespace ci {

Rectf getCenteredRect(gl::Texture texture, Area containerArea) {
  Rectf bounds = texture.getBounds();
  return bounds.getCenteredFit(containerArea, true);
}
/**
 */
Rectf getCoveringRect(Rectf bounds, Area containerArea) {
  float scale;
  bounds = bounds.getCenteredFit(containerArea, true);
  
  int container_h = containerArea.getHeight(),
  container_w = containerArea.getWidth(),
  bounds_h = bounds.getHeight(),
  bounds_w = bounds.getWidth();
  
  if (abs(container_h - bounds_h) > abs(container_w - bounds_w))
    scale = (float) container_h/bounds_h;
  else
    scale = (float) container_w/bounds_w;
  
  bounds.scaleCentered(scale + .05);
  
  return bounds;
}

/**
 *
 */
Rectf getCoveringRect(gl::Texture texture, Area containerArea) {
  float scale;
  Rectf bounds = texture.getBounds();
  bounds = bounds.getCenteredFit(containerArea, true);
  
  int container_h = containerArea.getHeight(),
  container_w = containerArea.getWidth(),
  texture_h = bounds.getHeight(),
  texture_w = bounds.getWidth();
  
  if (abs(container_h - texture_h) > abs(container_w - texture_w))
    scale = (float) container_h/texture_h;
  else
    scale = (float) container_w/texture_w;
  
  bounds.scaleCentered(scale + .05);
  
  return bounds;
}

// Close Namespace
}}

// Aliases
namespace svv = svvim;

#endif