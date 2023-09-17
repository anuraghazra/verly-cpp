#pragma once
#include <memory>
#include "particle.hpp"
#include "entity.hpp"
#include "verly.hpp"

class Mouse {
public:
  Mouse();

  Vector2 mouse;
  const Particle* dragPoint;
  Entity* hoveredEntity;
  void update(Verly& verly);

private:
  void draw();
  void findNearestPoint(const Verly& verly);
};