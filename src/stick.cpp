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
	double coef = 0.5;
	auto dx = this->endPoint->pos->x - this->startPoint->pos->x;
	auto dy = this->endPoint->pos->y - this->startPoint->pos->y;
	auto dist = dx * dx + dy * dy;
	auto diff = ((this->length*this->length - dist) / dist) * this->stiffness * coef;
	auto offsetx = dx * diff * coef;
	auto offsety = dy * diff * coef;

	// calculate mass
	// auto m1 = this->startPoint->mass + this->endPoint->mass;
	// auto m2 = this->startPoint->mass / m1;
	// m1 = this->endPoint->mass / m1;

	if (!*this->startPoint->pinned) {
		this->startPoint->pos->x -= offsetx;
		this->startPoint->pos->y -= offsety;
	}
	if (!*this->endPoint->pinned) {
		this->endPoint->pos->x += offsetx;
		this->endPoint->pos->y += offsety;
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