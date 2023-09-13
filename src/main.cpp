#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "mouse.hpp"

int main() {
	const int screenWidth = 1200;
	const int screenHeight = 500;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	Verly verly = Verly();
	Mouse mouse = Mouse();
	auto box = Verly::createBox(100, 100, 100, 100);
	auto rope = Verly::createRope(200, 30, 10, 30, true);
	auto cloth = Verly::createCloth(500, 100, 500, 300, 40, 3);
	auto heaxgon = Verly::createHexagon(800, 300, 12, 100, 3, 8);

	verly.addEntity(box);
	verly.addEntity(rope);
	verly.addEntity(cloth);
	verly.addEntity(heaxgon);

	while (!WindowShouldClose()) {
  	if (IsKeyDown(KEY_DELETE)) {
			if (mouse.dragPoint != nullptr)  {
				verly.removePoint(mouse.dragPoint, mouse.hoveredEntity);		
			}
		}
		mouse.update(verly);
		verly.update();


		BeginDrawing();
		ClearBackground(Color{ 245, 245, 245, 255 });
		verly.draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}