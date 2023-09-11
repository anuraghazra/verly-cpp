#pragma once
#include <vector>
#include "entity.hpp"

class Verly {
public:
  Verly();
  std::vector<std::shared_ptr<Entity>> entities;

  static std::shared_ptr<Entity> createBox(int x, int y, int w, int h);
  void update();
  void draw();
  void addEntity(std::shared_ptr<Entity> entity);
};