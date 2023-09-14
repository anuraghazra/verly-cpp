#pragma once
#include "stick.hpp"
#include "particle.hpp"
#include <memory>

class Stick: public std::enable_shared_from_this<Stick> {
public:
	Stick(const std::shared_ptr<Particle>& p1, const std::shared_ptr<Particle>& p2);
	Color color;
	void Init();

	std::shared_ptr<Particle> startPoint;
	std::shared_ptr<Particle> endPoint;
	float stiffness;
	float length;

	void update();
	void draw();
};