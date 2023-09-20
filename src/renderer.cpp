#include "renderer.hpp"
#include "particle.hpp"
#include "stick.hpp"

void VerlyRenderer::drawPoint(const Particle& point) const {
  unsigned char vel = Clamp(point.pos->Distance(*point.oldPos) * 50, 0, 255);
	DrawCircle(point.pos->x, point.pos->y, point.radius, Color{(unsigned char)(vel/20), vel, 155, 255});
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