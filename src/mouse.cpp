#include <raylib-cpp.hpp>
#include "mouse.hpp"
#include "verly.hpp"

Mouse::Mouse() {
  this->dragPoint = nullptr;  
  this->mouse = GetMousePosition();
}

void Mouse::update(const Verly& verly) {
  this->mouse = GetMousePosition();

  if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    this->findNearestPoint(verly);
  } else {
    if (this->dragPoint != nullptr) {
      this->dragPoint->color = BLUE;
      this->dragPoint->pinned = true;
      this->dragPoint->pos.x = mouse.x;
      this->dragPoint->pos.y = mouse.y;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    this->dragPoint->color = RED;
    this->dragPoint->pinned = false;
    this->dragPoint = nullptr;
  }
}

void Mouse::findNearestPoint(const Verly& verly) {
  int d = 20;
  for (int k = 0; k < verly.entities.size(); k++) {
    for (int i = 0; i < verly.entities[k]->points.size(); i++) {
      auto entity = verly.entities.at(k);
      int dist = entity->points.at(i)->pos.Distance(this->mouse);
      if (dist < d) {
        auto e = verly.entities.at(k);
        std::cout << e->points.at(i)->pos.x << "\n";
        this->dragPoint = e->points.at(i);
      }
    }
  }
}