#include "entity.hpp"
#include "particle.hpp"
#include "verly.hpp"

Verly::Verly() {
  this->entities = {};
}

void Verly::addEntity(std::shared_ptr<Entity> entity) {
  this->entities.push_back(entity);
}

void Verly::update() {
  for (int i = 0; i < this->entities.size(); i++) {
    this->entities.at(i)->update();
  }
}

void Verly::draw() {
  for (int i = 0; i < this->entities.size(); i++) {
    this->entities.at(i)->draw();
  }
}

std::shared_ptr<Entity> Verly::createBox(int x, int y, int w, int h) {
	auto box = std::make_shared<Entity>();
	
	auto p1 = std::make_shared<Particle>(x, y);
	auto p2 = std::make_shared<Particle>(x + w, y);
	auto p3 = std::make_shared<Particle>(x + w, y + h);
	auto p4 = std::make_shared<Particle>(x, y + h);

	auto joint1 = std::make_shared<Stick>(p1, p2);
	auto joint2 = std::make_shared<Stick>(p2, p3);
	auto joint3 = std::make_shared<Stick>(p3, p4);
	auto joint4 = std::make_shared<Stick>(p4, p1);
	auto joint5 = std::make_shared<Stick>(p4, p2);
	box->addPoint(p1);
	box->addPoint(p2);
	box->addPoint(p3);
	box->addPoint(p4);
	box->addStick(joint1);
	box->addStick(joint2);
	box->addStick(joint3);
	box->addStick(joint4);
	box->addStick(joint5);
	
  return box;
}