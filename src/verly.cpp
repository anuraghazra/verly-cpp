#include "entity.hpp"
#include "particle.hpp"
#include "verly.hpp"
#include "constants.hpp"
#include <cmath>
#include <algorithm>
#include "instrumentor.hpp"

Verly::Verly() {
  this->entities = {};
	this->iterations = VERLY_ITERATIONS;
}

void Verly::addEntity(Entity &entity) {
  this->entities.push_back(&entity);
}

void Verly::setIterations(int count) {
	this->iterations = count;
}

void Verly::update() {
  for (int i = 0; i < this->entities.size(); i++) {
    this->entities[i]->update(this->iterations);
  }
}

void Verly::draw() {
  for (int i = 0; i < this->entities.size(); i++) {
    this->entities[i]->draw();
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

Entity Verly::createBox(int x, int y, int w, int h) {
	auto box = Entity();
	
	box.createPoint(x, y);
	box.createPoint(x + w, y);
	box.createPoint(x + w, y + h);
	box.createPoint(x, y + h);
	box.createStick(0, 1);
	box.createStick(1, 2);
	box.createStick(2, 3);
	box.createStick(3, 0);
	box.createStick(3, 1);
	
  return box;
}

Entity Verly::createRope(int x, int y, int segments, int gap, bool pin) {
	auto rope = Entity();

	for (int i = 0; i < segments; i++) {
		rope.createPoint(x + i * gap, y);
	}

	for (int i = 0; i < segments - 1; i++) {
		rope.createStick(i, (i + 1) % segments);
	}

	if (pin == true) {
		*rope.points.at(0).pinned = true;
	}

	return rope;
}

Entity Verly::createHexagon(int x, int y, int segments, int radius, int stride1, int stride2) {
	auto hexagon = Entity();
	float stride = (2 * PI) / segments;

	// points
	for (int i = 0; i < segments; ++i) {
		float theta = i * stride;
		hexagon.createPoint(x + cos(theta) * radius, y + sin(theta) * radius);
	}

	auto center = hexagon.createPoint(x, y);

	// sticks
	for (int i = 0; i < segments; ++i) {
		hexagon.createStick(i, (i + stride1) % segments);
		hexagon.createStick(i, (i + stride2) % segments);
		// Connect from center to all the segments
		hexagon.addStick(std::move(Stick(*center, hexagon.points.at(i))));
	}

	return hexagon;
}

Entity Verly::createCloth(int posx, int posy, int gapx, int gapy, int segments, int pinOffset) {
	auto cloth = Entity();

	for (int y = 0; y < segments; ++y) {
		for (int x = 0; x < segments; ++x) {
			int px = posx + (x * gapx);
			int py = posy + (y * gapy);
			cloth.createPoint(px, py);
		}
	}

	for (int y = 0; y < segments; ++y) {
		for (int x = 0; x < segments; ++x) {
			if (x > 0) {
				cloth.createStick(y * segments + x, y * segments + x - 1);
			}
			if (y > 0) {
				cloth.createStick(y * segments + x, (y - 1) * segments + x);
			}
		}
	}

	// pin points at segmented intervals 
	for (int x = 0; x < segments; ++x) {
		if (x % pinOffset == 0) {
			*cloth.points.at(x).pinned = true;
		}
	}

	return cloth;
}