#include <raylib-cpp.hpp>
#include "constants.hpp"
#include "mouse.hpp"
#include "verly.hpp"

Mouse::Mouse() {
  this->dragPoint = nullptr;  
  this->hoveredEntity = nullptr;  
  this->mouse = GetMousePosition();
}

void Mouse::update(const Verly& verly) {
  this->mouse = GetMousePosition();

  if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    this->findNearestPoint(verly);
  } else {
    if (this->dragPoint != nullptr) {
      *this->dragPoint->color = PARTICLE_HOVER_COLOR;
      *this->dragPoint->pinned = true;
      this->dragPoint->pos->x = this->mouse.x;
      this->dragPoint->pos->y = this->mouse.y;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    if (this->dragPoint != nullptr)  {
      *this->dragPoint->color = PARTICLE_COLOR;
      this->dragPoint->oldPos->x = this->dragPoint->pos->x;
      this->dragPoint->oldPos->y = this->dragPoint->pos->y;
      *this->dragPoint->pinned = false;
      this->dragPoint = nullptr;
    }
  }

  this->draw();
}


void Mouse::draw() {
  if (this->dragPoint == nullptr) return;

  DrawRing(*this->dragPoint->pos, this->dragPoint->radius + 2, this->dragPoint->radius + 6, 0, 360, 0, GRAY);
}

void Mouse::findNearestPoint(const Verly& verly) {
  int d = 20;
  this->dragPoint = nullptr;
  for (int k = 0; k < verly.entities.size(); k++) {
    for (int i = 0; i < verly.entities[k].points.size(); i++) {
      auto entity = &verly.entities[k];
      auto point = &(entity->points.at(i));
      int dist = point->pos->Distance(this->mouse);
      if (dist < d) {
        // auto w = (entity->points.at(i));
        // auto w = *point;
        this->dragPoint = point;
        // this->hoveredEntity = entity;
      }
    }
  }
}