#pragma once
#include <vector>
#include "../particle.hpp"
#include "../stick.hpp"

class VerlyRenderer {
public:
	VerlyRenderer() = default;
	virtual void drawPoint(const Particle& point) const;
	virtual void drawStick(const Stick& stick) const;
	virtual void drawPoints(const std::vector<Particle>& points) const;
	virtual void drawSticks(const std::vector<Stick>& sticks) const;
};
