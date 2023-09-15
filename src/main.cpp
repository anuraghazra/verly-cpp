#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "mouse.hpp"
#include "instrumentor.hpp"

int main() {
	const int screenWidth = 1200;
	const int screenHeight = 700;

	// SetConfigFlags();

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	Verly verly = Verly();
	Mouse mouse = Mouse();
	// auto box = Verly::createBox(100, 100, 100, 100);
	// auto rope = Verly::createRope(200, 30, 10, 30, true);
	auto cloth = Verly::createCloth(500, 100, 500, 300, 100, 1);
	// auto heaxgon = Verly::createHexagon(800, 300, 12, 100, 3, 8);

	// verly.addEntity(box);
	// verly.addEntity(rope);
	verly.addEntity(std::move(cloth));
	// verly.addEntity(heaxgon);

	// auto e1 = Entity();
	// auto p1 = Particle{150, 500};
	// auto p2 = Particle{100, 600};
	// e1.addPoint(std::move(p1));
	// e1.addPoint(std::move(p2));
	// auto s1 = Stick((e1.points.at(0)), (e1.points.at(1)));
	// e1.addStick(std::move(s1));

	while (!WindowShouldClose()) {
  	// if (IsKeyDown(KEY_DELETE)) {
		// 	if (mouse.dragPoint != nullptr)  {
		// 		verly.removePoint(mouse.dragPoint, mouse.hoveredEntity);		
		// 	}
		// }
		// mouse.update(verly);
		verly.update();
		// e1.update();

		BeginDrawing();
		ClearBackground(Color{ 245, 245, 245, 255 });
		DrawFPS(100, 100);
		// e1.draw();
		verly.draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}