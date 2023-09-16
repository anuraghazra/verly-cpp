#include <raylib-cpp.hpp>
#include "constants.hpp"
#include "mouse.hpp"
#include "verly.hpp"

Mouse::Mouse() {
  this->dragPoint = nullptr;
  this->hoveredEntity = nullptr;
  this->mouse = GetMousePosition();
}

void Mouse::update(Verly& verly) {
  this->mouse = GetMousePosition();

  if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
    this->findNearestPoint(verly);
  }

  // on mouse down pin
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    if (this->dragPoint != nullptr) {
      *this->dragPoint->pinned = true;
      *this->dragPoint->color = PARTICLE_HOVER_COLOR;
      this->dragPoint->pos->x = mouse.x;
      this->dragPoint->pos->y = mouse.y;
    }
  } 

  // on mouse up unpin
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    if (this->dragPoint != nullptr) {
      *this->dragPoint->pinned = false;
      *this->dragPoint->color = PARTICLE_COLOR;
      this->dragPoint->oldPos->x = this->dragPoint->pos->x;
      this->dragPoint->oldPos->y = this->dragPoint->pos->y;
      this->dragPoint = nullptr;
    }
  }

  this->draw();
}

void Mouse::draw() {
  if (this->dragPoint == nullptr) return;

  DrawRing(
    *this->dragPoint->pos,
    this->dragPoint->radius + 2, 
    this->dragPoint->radius + 6,
    0,
    360,
    0,
    GRAY
  );
}

void Mouse::findNearestPoint(const Verly& verly) {
  int d = 10;
  this->dragPoint = nullptr;
  for (int k = 0; k < verly.entities.size(); k++) {
    for (int i = 0; i < verly.entities[k].points.size(); i++) {
      auto entity = &verly.entities[k];
      auto point = &(entity->points.at(i));
      int dist = point->pos->Distance(this->mouse);
      if (dist < d) {
        this->dragPoint = point;
        this->hoveredEntity = (Entity*)entity;
      }
    }
  }
}