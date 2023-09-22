#pragma once
#include "stick.hpp"
#include "particle.hpp"
#include "renderer/renderer.hpp"
#include <memory>

class Stick {
public:
	Stick(Particle& p1, Particle& p2);
	Color color;
	// void Init();

	Particle* startPoint;
	Particle* endPoint;
	float stiffness;
	float length;

	void update();
	void draw(VerlyRenderer& renderer);
};