#pragma once
#include "renderer.hpp"
#include "../particle.hpp"
#include "../stick.hpp"

#define RENDER_DEBUG_INDEX_RENDER 0
#define RENDER_POINT_VELOCITY 0

class DebugRenderer : public VerlyRenderer {
public:
	void drawPoints(const std::vector<Particle>& points) const {
		for (int i = 0; i < points.size(); i++) {
      auto point = points.at(i);
			this->drawPoint(point);
      #if RENDER_DEBUG_INDEX_RENDER == 1
        auto index = std::to_string(i).c_str();
        DrawText(index, point.pos->x + 12, point.pos->y - 12, 20, GRAY);
      #endif
    };
	}

  void drawSticks(const std::vector<Stick>& sticks) const {
    for (int i = 0; i < sticks.size(); i++)  {
      this->drawStick(sticks.at(i));
    }
  }

	void drawPoint(const Particle& point) const {
    #if RENDER_POINT_VELOCITY
      unsigned char vel = Clamp(point.pos->Distance(*point.oldPos) * 50, 0, 255);
      DrawCircle(point.pos->x, point.pos->y, point.radius, Color{(unsigned char)(vel/20), vel, 155, 255});
		#else
      int radius = 10;
      DrawRectangle(point.pos->x - radius / 2, point.pos->y - radius / 2, radius, radius, PARTICLE_COLOR);
    #endif
	};

  void drawStick(const Stick& stick) const {
    DrawLine(
      stick.startPoint->pos->x,
      stick.startPoint->pos->y,
      stick.endPoint->pos->x,
      stick.endPoint->pos->y,
      stick.color
    );
  }
};
