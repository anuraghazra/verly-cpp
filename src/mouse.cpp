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
      this->dragPoint->color = PARTICLE_HOVER_COLOR;
      this->dragPoint->pinned = true;
      this->dragPoint->pos.x = mouse.x;
      this->dragPoint->pos.y = mouse.y;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    if (this->dragPoint != nullptr)  {
      this->dragPoint->color = PARTICLE_COLOR;
      this->dragPoint->oldPos = this->dragPoint->pos;
      this->dragPoint->pinned = false;
      this->dragPoint = nullptr;
    }
  }

  this->draw();
}

void Mouse::draw() {
  if (this->dragPoint == nullptr) return;

  DrawRing(this->dragPoint->pos, this->dragPoint->radius + 2, this->dragPoint->radius + 6, 0, 360, 0, GRAY);
}

void Mouse::findNearestPoint(const Verly& verly) {
  int d = 20;
  this->dragPoint = nullptr;
  for (int k = 0; k < verly.entities.size(); k++) {
    for (int i = 0; i < verly.entities[k]->points.size(); i++) {
      auto entity = verly.entities.at(k);
      int dist = entity->points.at(i)->pos.Distance(this->mouse);
      if (dist < d) {
        auto e = verly.entities.at(k);
        this->dragPoint = e->points.at(i);
        this->hoveredEntity = e;
      }
    }
  }
}