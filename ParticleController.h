#pragma once
#include "Particle.h"
#include <list>

class ParticleController {
public:
  ParticleController();
  void update();
  void draw();
  void addParticle(float x, float y, float z);
  void addParticles(int amt);
  void removeParticles(int amt);
  
  void applyForce(float, float);
private:
  std::list<Particle> mParticles;
};

#include "ParticleController.cpp"