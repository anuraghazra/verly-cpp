#pragma once
#include "renderer.hpp"
#include "particle.hpp"
#include "stick.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Entity {
public:
  Entity();
  ~Entity() {
    this->sticks.clear();
    this->points.clear();
  }

  std::vector<Particle> points;
  std::vector<Stick> sticks;
  raylib::Vector2* gravity;

  Particle* createPoint(int x, int y);
  Particle* addPoint(Particle point);
  Stick* createStick(int from, int to);
  Stick* addStick(Stick stick);
  void update(int iterations);
  void draw(VerlyRenderer& renderer);
  void drawPointIndices();
};