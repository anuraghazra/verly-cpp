#include "renderer.hpp"
#include "../particle.hpp"
#include "../stick.hpp"

void VerlyRenderer::drawPoints(const std::vector<Particle>& points) const {
  for (int i = 0; i < points.size(); i++)  {
    this->drawPoint(points.at(i));
  }
}

void VerlyRenderer::drawSticks(const std::vector<Stick>& sticks) const {
  for (int i = 0; i < sticks.size(); i++)  {
    this->drawStick(sticks.at(i));
  }
}

void VerlyRenderer::drawPoint(const Particle& point) const {
	DrawCircle(point.pos->x, point.pos->y, point.radius, *point.color);
}

void VerlyRenderer::drawStick(const Stick& stick) const {
	DrawLine(
		stick.startPoint->pos->x,
		stick.startPoint->pos->y,
		stick.endPoint->pos->x,
		stick.endPoint->pos->y,
		stick.color
	);
}