#include "constants.hpp"
#include "stick.hpp"
#include <memory>

Stick::Stick(const std::shared_ptr<Particle>& p1, const std::shared_ptr<Particle>& p2) {
	this->startPoint = p1;
	this->endPoint = p2;
	this->length = this->startPoint->pos.Distance((this->endPoint)->pos);
	this->stiffness = 0.97;
	this->color = STICK_COLOR;
}

// shared_from_this cannot be called inside constructor since the weakpointer won't be created at that time
// This makes the API of creating Sticks weird, need to figure out a better option
void Stick::Init() {
	this->startPoint->sticks.push_back(shared_from_this());
	this->endPoint->sticks.push_back(shared_from_this());
}

void Stick::update() {
	// caching particle from shared pointer because 
	// calling -> is somehow slower and than .get()
	// and doing so multiple times is even slower, saw ~15% improvement when profiling 
	auto p1 = this->endPoint.get();
	auto p2 = this->startPoint.get();
	auto dx = p1->pos.x - p2->pos.x;
	auto dy = p1->pos.y - p2->pos.y;
	auto dist = sqrt(dx * dx + dy * dy);
	auto diff = (this->length - dist) / dist * this->stiffness;

	auto offsetx = dx * diff * 0.5;
	auto offsety = dy * diff * 0.5;

	// calculate mass
	auto m1 = p2->mass + p1->mass;
	auto m2 = p2->mass / m1;
	m1 = p1->mass / m1;

	if (!p2->pinned) {
		p2->pos.x -= offsetx * m1;
		p2->pos.y -= offsety * m1;
	}
	if (!p1->pinned) {
		p1->pos.x += offsetx * m2;
		p1->pos.y += offsety * m2;
	}
}

void Stick::draw() {
	DrawLineV(this->startPoint.get()->pos, this->endPoint->pos, this->color);
}