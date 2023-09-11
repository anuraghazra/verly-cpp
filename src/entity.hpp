#pragma once
#include "particle.hpp"
#include "stick.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Entity {
public:
  Entity();

  int iterations;

  std::vector<std::shared_ptr<Particle>> points;
  std::vector<std::shared_ptr<Stick>> sticks;

  void addPoint(std::shared_ptr<Particle> point);
  void addStick(std::shared_ptr<Stick> stick);
  void update();
  void draw();
  void drawPointIndices();
};