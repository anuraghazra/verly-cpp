#pragma once
#include "stick.hpp"
#include "particle.hpp"
#include <memory>

class Stick {
public:
	Stick(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);

	std::shared_ptr<Particle> startPoint;
	std::shared_ptr<Particle> endPoint;
	float stiffness;
	float length;

	void update();
	void draw();
};