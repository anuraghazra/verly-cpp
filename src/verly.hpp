#pragma once
#include <vector>
#include "entity.hpp"
#include "renderer/renderer.hpp"

class Verly {
public:
  Verly();
  VerlyRenderer* renderer;
  std::vector<Entity*> entities;
  std::vector<AttractionBehaviour*> behaviours;
  int iterations;

  static Entity createBox(int x, int y, int w, int h);
  static Entity createRope(int x, int y, int segments, int gap, bool pin);
  static Entity createCloth(int x, int y, int gapx, int gapy, int segments, int pinOffset);
  static Entity createHexagon(int x, int y, int segments, int radius = 50, int stride1 = 1, int stride2 = 5);
  void update();
  void removePoint(const Particle* point, Entity* hoveredEntity);
  void draw();
  void addEntity(Entity& entity);
  void resolveBehaviour(AttractionBehaviour& behaviour);
  void setIterations(int count);
  void setRenderer(VerlyRenderer& renderer);
};