#include "constants.hpp"
#include "entity.hpp"
#include "particle.hpp"
#include "stick.hpp"
#include <memory>
#include <algorithm>
#include "instrumentor.hpp"

Entity::Entity() {
  this->points = {};
  this->sticks = {};
  this->iterations = VERLY_ITERATIONS;
}

// Helper function to create point
void Entity::createPoint(int x, int y) {
	auto p1 = Particle(x, y);
	this->addPoint(std::move(p1));
}

// Helper function to create stick
void Entity::createStick(int from, int to) {
	auto s1 = Stick(this->points.at(from), this->points.at(to));
	this->addStick(std::move(s1));
}

void Entity::addPoint(Particle point) {
  this->points.push_back(point);
}

void Entity::addStick(Stick stick) {
  this->sticks.push_back(stick);
}

void Entity::update() {
  for (int m = 0; m < this->points.size(); m++)  {
    this->points.at(m).update();
  }

  for (int i = 0; i < this->iterations; i++) {
    for (int j = 0; j < this->sticks.size(); j++)  {
      this->sticks.at(j).update();
    }
    for (int k = 0; k < this->points.size(); k++)  {
      this->points.at(k).constrain();
    }
  }
}

void Entity::draw() {
  for (int i = 0; i < this->points.size(); i++)  {
    this->points[i].draw();
  }
  for (int k = 0; k < this->sticks.size(); k++)  {
    this->sticks[k].draw();
  }
  // this->drawPointIndices();
}

void Entity::drawPointIndices() {
  for (int i = 0; i < this->points.size(); i++) {
    auto point = this->points.at(i);
    auto index = std::to_string(i).c_str();
    DrawText(index, point.pos->x + 12, point.pos->y - 12, 20, GRAY);
  };
}