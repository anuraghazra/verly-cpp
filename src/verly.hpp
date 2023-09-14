#pragma once
#include <vector>
#include "entity.hpp"

class Verly {
public:
  Verly();
  std::vector<std::shared_ptr<Entity>> entities;

  static std::shared_ptr<Entity> createBox(int x, int y, int w, int h);
  // static std::shared_ptr<Entity> createRope(int x, int y, int segments, int gap, bool pin);
  static std::shared_ptr<Entity> createCloth(int x, int y, int w, int h, int segments, int pinOffset);
  // static std::shared_ptr<Entity> createHexagon(int x, int y, int segments, int radius = 50, int stride1 = 1, int stride2 = 5);
  void update();
  void removePoint(std::shared_ptr<Particle> point, std::shared_ptr<Entity> hoveredEntity);
  void draw();
  void addEntity(std::shared_ptr<Entity> entity);
};