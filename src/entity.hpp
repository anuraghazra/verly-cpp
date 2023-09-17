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

  std::vector<Particle> points;
  std::vector<Stick> sticks;

  Particle* createPoint(int x, int y);
  Particle* addPoint(Particle point);
  Stick* createStick(int from, int to);
  Stick* addStick(Stick stick);
  void update();
  void draw();
  void drawPointIndices();
};