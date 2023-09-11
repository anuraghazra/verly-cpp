#pragma once
#include <memory>
#include "particle.hpp"
#include "verly.hpp"

class Mouse {
public:
  Mouse();

  Vector2 mouse;
  std::shared_ptr<Particle> dragPoint;
  void update(const Verly& verly);

private:
  void draw();
  void findNearestPoint(const Verly& verly);
};