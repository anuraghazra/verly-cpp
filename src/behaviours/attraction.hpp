#pragma once
#include <raylib-cpp.hpp>
#include "../particle.hpp"

class AttractionBehaviour {
public:
  AttractionBehaviour(raylib::Vector2& attractor);

  raylib::Vector2* attractor;
  int radius;
  float strength;

  void resolve(Particle* to);
};