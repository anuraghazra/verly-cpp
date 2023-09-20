#pragma once
#include "particle.hpp"
#include "stick.hpp"

class VerlyRenderer {
public:
	VerlyRenderer() = default;
	virtual void drawPoint(const Particle& point) const;
	virtual void drawStick(const Stick& stick) const;
};
