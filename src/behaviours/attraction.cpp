#include <raylib-cpp.hpp>
#include "attraction.hpp"

raylib::Vector2 normalizeTo(raylib::Vector2 vec, float len) {
  auto mag = vec.Length();
  if (mag > 0) {
    mag = len / mag;
    auto newVec = vec.Multiply(Vector2{mag, mag});
    vec.x = newVec.x;
    vec.y = newVec.y;
  }
  return vec;
}

AttractionBehaviour::AttractionBehaviour(raylib::Vector2& attractor) {
  this->attractor = &attractor;
  this->radius = 100;
  this->strength = 1;
}

void AttractionBehaviour::setRadius(int radius) {
  this->radius = radius;
}

void AttractionBehaviour::setStrength(float value) {
  this->strength = value;
}

void AttractionBehaviour::resolve(Particle& to) {
  auto delta = this->attractor->Subtract(*to.pos);
  auto dist = delta.LengthSqr();

  auto magR = this->radius * this->radius;
  if (dist < magR) {
    auto f = normalizeTo(delta, 1 - (dist / magR)).Scale(this->strength);
    to.applyForce(f);
  }
}