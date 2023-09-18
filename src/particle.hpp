#pragma once
#include <raylib-cpp.hpp>
#include <iostream>
#include <memory>

class Stick;

class Particle {
public:
	Particle(float x, float y, raylib::Vector2* gravity);

	raylib::Vector2* pos;
	raylib::Vector2* oldPos;
	raylib::Vector2* gravity;
	raylib::Color* color;
	bool* pinned;
	float mass;
	float bounce;
	float friction;
	float groundFriction;
	int radius;

	void applyForce(raylib::Vector2 force);
	void update();
	void draw();
	void constrain();
};

