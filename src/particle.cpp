#include "constants.hpp"
#include "particle.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

Particle::Particle(float x, float y) {
	this->bounce = 0.99;
	this->friction = 0.97;
	this->groundFriction = 0.98;
	this->mass = 1.0;
	this->radius = 4;
	this->pos = new raylib::Vector2(x, y);
	this->oldPos = new raylib::Vector2(this->pos->x, this->pos->y);
	this->gravity = raylib::Vector2(0, 0.4);
	this->pinned = false;
	this->color = PARTICLE_COLOR;
}

void Particle::update() {
	if (this->pinned) return;

	auto vel = this->pos->Subtract(*this->oldPos);
	vel *= this->friction;

	// TODO: set ground friction

	this->oldPos->x = this->pos->x;
	this->oldPos->y = this->pos->y;

	this->pos->x += vel.x;
	this->pos->y += vel.y;
	this->pos->x += this->gravity.x;
	this->pos->y += this->gravity.y;
}

void Particle::constrain() {
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	if (this->pos->y > screenHeight - this->radius) {
		this->pos->y = screenHeight - this->radius;
	}

	if (this->pos->y < this->radius) {
		this->pos->y = this->radius;
	}

	if (this->pos->x > screenWidth - this->radius) {
		this->pos->x = screenWidth - this->radius;
	}

	if (this->pos->x < this->radius) {
		this->pos->x = this->radius;
	}
}

void Particle::applyForce(raylib::Vector2 force) {
	this->pos->x += force.x;
	this->pos->y += force.y;
}

void Particle::draw() {
	DrawCircle(this->pos->x, this->pos->y, this->radius, this->color);
}
