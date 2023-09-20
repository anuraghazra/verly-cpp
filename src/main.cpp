#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "constants.hpp"
#include "mouse.hpp"
#include "behaviours/attraction.hpp"
#include "renderer.hpp"

class MyRenderer : public VerlyRenderer {
public:	
	void drawPoint(const Particle& point) const {
		int radius = 10;
		DrawRectangle(point.pos->x - radius / 2, point.pos->y - radius / 2, radius, radius, PARTICLE_COLOR);
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

int main() {
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	auto myRenderer = MyRenderer();
	Verly verly = Verly();

	verly.setRenderer(myRenderer);

	Mouse mouse = Mouse();
	// auto box = Verly::createBox(100, 100, 100, 100);
	auto cloth = Verly::createCloth(200, 100, 10, 5, 100, 1);
	// auto rope = Verly::createRope(200, 30, 50, 30, true);
	// auto hexagon = Verly::createHexagon(300, 300, 32, 100, 13, 7);

	// verly.addEntity(box);
	// box.createPoint(100, 100);
	verly.addEntity(cloth);
	// verly.addEntity(rope);
	// verly.addEntity(hexagon);

	raylib::Vector2 m = raylib::Vector2{0, 0};
	// auto mouseBehaviour = AttractionBehaviour(m);
	// auto mouseBehaviourEvade = AttractionBehaviour(m);
	// mouseBehaviour.setRadius(1200);
	// mouseBehaviour.setStrength(10);
	// mouseBehaviourEvade.setRadius(200);
	// mouseBehaviourEvade.setStrength(-9);

	while (!WindowShouldClose()) {
		mouse.update(verly);
		m.x = GetMousePosition().x;
		m.y = GetMousePosition().y;

		// mouseBehaviour.resolve(box.points.at(1));
		// mouseBehaviourEvade.resolve(box.points.at(1));
	
		verly.update();
	
		ClearBackground(Color{ 245, 245, 245, 255 });
		DrawFPS(100, 100);
		
		verly.draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}