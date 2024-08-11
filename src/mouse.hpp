#pragma once
#include <memory>
#include "particle.hpp"
#include "entity.hpp"
#include "verly.hpp"

class Mouse {
public:
  Mouse();

  raylib::Vector2 mouse;
  Particle* dragPoint;
  Entity* hoveredEntity;
  void update(Verly& verly);

private:
  void draw();
  void findNearestPoint(const Verly& verly);
};