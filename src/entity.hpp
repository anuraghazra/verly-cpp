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

  void addPoint(Particle point);
  void addStick(Stick stick);
  void update();
  void draw();
  void drawPointIndices();
};