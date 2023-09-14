#include "constants.hpp"
#include "entity.hpp"
#include "particle.hpp"
#include "stick.hpp"
#include <memory>
#include <algorithm>
#include <execution>
#include "instrumentor.hpp"

Entity::Entity() {
  this->points = {};
  this->sticks = {};
  this->iterations = VERLY_ITERATIONS;
}

// void Entity::addPoint(std::unique_ptr<Particle>& point) {
//   this->points.push_back(point);
// }

// void Entity::addStick(std::unique_ptr<Stick>& stick) {
//   // TODO: fix
//   stick->Init();
//   this->sticks.push_back(stick);
// }

void Entity::update() {
  for (int m = 0; m < this->points.size(); m++)  {
    this->points[m].get()->update();
  }

  for (int i = 0; i < this->iterations; i++) {
    for (int j = 0; j < this->sticks.size(); j++)  {
      this->sticks[j].get()->update();
    }
    for (int k = 0; k < this->points.size(); k++)  {
      this->points[k].get()->constrain();
    }
  }
}

void Entity::draw() {
  // for (int i = 0; i < this->points.size(); i++)  {
  //   this->points.at(i)->draw();
  // }
  for (int k = 0; k < this->sticks.size(); k++)  {
    this->sticks[k]->draw();
  }
  // this->drawPointIndices();
}

void Entity::drawPointIndices() {
  for (int i = 0; i < this->points.size(); i++) {
    auto point = this->points;
    auto index = std::to_string(i).c_str();
    DrawText(index, point[i]->pos.x + 12, point[i]->pos.y - 12, 20, GRAY);
  };
}