#include "entity.hpp"
#include "particle.hpp"
#include "verly.hpp"
#include <cmath>
#include <algorithm>
#include "instrumentor.hpp"

Verly::Verly() {
  this->entities = {};
}

void Verly::addEntity(Entity entity) {
  this->entities.push_back(entity);
}

#if 0
void Verly::removePoint(std::shared_ptr<Particle> point, std::shared_ptr<Entity> hoveredEntity) {
	// find which entity this point belongs to

	// do the rest
  for (int i = 0; i < point->sticks.size(); i++) {
    auto s = point->sticks.at(i);
    auto idx = std::find(hoveredEntity->sticks.begin(), hoveredEntity->sticks.end(), s);
		if (idx != hoveredEntity->sticks.end()) {
	    hoveredEntity->sticks.erase(idx);
		}
  }
  auto idx = std::find(hoveredEntity->points.begin(), hoveredEntity->points.end(), point);
	if (idx != hoveredEntity->points.end()) {
		hoveredEntity->points.erase(idx);
	}
}
#endif

void Verly::update() {
  for (int i = 0; i < this->entities.size(); i++) {
    this->entities[i].update();
  }
}

void Verly::draw() {
  for (int i = 0; i < this->entities.size(); i++) {
    this->entities[i].draw();
  }
}

void Verly::removePoint(const Particle* point, Entity* hoveredEntity) {
	// remove the sticks from point
	for (int i = hoveredEntity->sticks.size() - 1; i >= 0; i--) {
		auto stick = hoveredEntity->sticks.at(i);
		if (stick.startPoint->pos == point->pos) {
			hoveredEntity->sticks.erase(hoveredEntity->sticks.begin() + i);
		}
		if (stick.endPoint->pos == point->pos) {
			hoveredEntity->sticks.erase(hoveredEntity->sticks.begin() + i);
		}
	}

	// remove the point from the entity
	for (int i = hoveredEntity->points.size(); i >=0; i--) {
		if (&hoveredEntity->points[i] == point) {
			hoveredEntity->points.erase(hoveredEntity->points.begin()+i);
		}
	}
}

#if 0


std::shared_ptr<Entity> Verly::createRope(int x, int y, int segments, int gap, bool pin) {
	auto rope = std::make_shared<Entity>();

	for (int i = 0; i < segments; i++) {
		auto p1 = std::make_shared<Particle>(x + i * gap, y);
		rope->addPoint(p1);
	}

	for (int i = 0; i < segments - 1; i++) {
		auto joint1 = std::make_shared<Stick>(rope->points.at(i), rope->points.at((i + 1) % segments));
		rope->addStick(joint1);
	}

	if (pin == true) {
		rope->points.at(0)->pinned = true;
	}

	return rope;
}

std::shared_ptr<Entity> Verly::createHexagon(int x, int y, int segments, int radius, int stride1, int stride2) {
	auto hexagon = std::make_shared<Entity>();
	float stride = (2 * PI) / segments;

	// points
	for (int i = 0; i < segments; ++i) {
		float theta = i * stride;
		auto p = std::make_shared<Particle>(x + cos(theta) * radius, y + sin(theta) * radius);
		hexagon->addPoint(p);
	}

	auto center = std::make_shared<Particle>(x, y);
	hexagon->addPoint(center);

	// sticks
	for (int i = 0; i < segments; ++i) {
		auto stick1 = std::make_shared<Stick>(hexagon->points.at(i), hexagon->points.at((i + stride1) % segments));
		auto stick2 = std::make_shared<Stick>(hexagon->points.at(i), center);
		auto stick3 = std::make_shared<Stick>(hexagon->points.at(i), hexagon->points.at((i + stride2) % segments));
		hexagon->addStick(stick1);
		hexagon->addStick(stick2);
		hexagon->addStick(stick3);
	}

	return hexagon;
}

#endif

Entity Verly::createBox(int x, int y, int w, int h) {
	auto box = new Entity();
	
	box->createPoint(x, y);
	box->createPoint(x + w, y);
	box->createPoint(x + w, y + h);
	box->createPoint(x, y + h);
	box->createStick(0, 1);
	box->createStick(1, 2);
	box->createStick(2, 3);
	box->createStick(3, 0);
	box->createStick(3, 1);
	
  return *box;
}

Entity Verly::createCloth(int posx, int posy, int w, int h, int segments, int pinOffset) {
	auto cloth = new Entity();

	int xStride = w / segments;
	int yStride = h / segments;

	for (int y = 0; y < segments; ++y) {
		for (int x = 0; x < segments; ++x) {
			int px = posx + x * xStride - w / 2 + xStride / 2;
			int py = posy + y * yStride - h / 2 + yStride / 2;
			cloth->addPoint(std::move(Particle(px, py)));
		}
	}

	for (int y = 0; y < segments; ++y) {
		for (int x = 0; x < segments; ++x) {
			if (x > 0) {
				auto stickX = Stick(cloth->points.at(y * segments + x), cloth->points.at(y * segments + x - 1));
				cloth->addStick(std::move(stickX));
			}
			if (y > 0) {
				auto stickY = Stick(cloth->points.at(y * segments + x), cloth->points.at((y - 1) * segments + x));
				cloth->addStick(std::move(stickY));
			}
		}
	}

	// pin points at segmented intervals 
	for (int x = 0; x < segments; ++x) {
		if (x % pinOffset == 0) {
			*cloth->points.at(x).pinned = true;
		}
	}

	return *cloth;
}