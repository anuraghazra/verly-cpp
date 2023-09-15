#include "constants.hpp"
#include "stick.hpp"
#include <memory>

Stick::Stick(Particle& p1, Particle& p2): startPoint(&p1), endPoint(&p2) {
	// this->startPoint = *p1;
	// this->endPoint = *p2;
	this->length = this->startPoint->pos->Distance(*this->endPoint->pos);
	this->stiffness = 0.97;
	this->color = STICK_COLOR;
}

void Stick::update() {
	auto dx = this->endPoint->pos->x - this->startPoint->pos->x;
	auto dy = this->endPoint->pos->y - this->startPoint->pos->y;
	auto dist = sqrt(dx * dx + dy * dy);
	auto diff = (this->length - dist) / dist * this->stiffness;

	auto offsetx = dx * diff * 0.5;
	auto offsety = dy * diff * 0.5;

	// calculate mass
	auto m1 = this->startPoint->mass + this->endPoint->mass;
	auto m2 = this->startPoint->mass / m1;
	m1 = this->endPoint->mass / m1;

	if (!this->startPoint->pinned) {
		this->startPoint->pos->x -= offsetx * m1;
		this->startPoint->pos->y -= offsety * m1;
	}
	if (!this->endPoint->pinned) {
		this->endPoint->pos->x += offsetx * m2;
		this->endPoint->pos->y += offsety * m2;
	}
}

void Stick::draw() {
	DrawLine(
		this->startPoint->pos->x,
		this->startPoint->pos->y,
		this->endPoint->pos->x,
		this->endPoint->pos->y,
		this->color
	);
}