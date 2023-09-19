#pragma once
#include <raylib-cpp.hpp>
#include "../particle.hpp"

class AttractionBehaviour {
public:
  AttractionBehaviour(raylib::Vector2& attractor);

  raylib::Vector2* attractor;
  int radius;
  float strength;

  /**
   * Toxiclib like behaviours API
   * https://github.com/hapticdata/toxiclibsjs
   */
  void resolve(Particle& to);
  void setRadius(int radius);
  /**
   * Sets the strength of the behaviour, setting to negative values will repel instead of attract
   */
  void setStrength(float value);
};