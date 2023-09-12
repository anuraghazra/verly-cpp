#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "mouse.hpp"

int main() {
	const int screenWidth = 1200;
	const int screenHeight = 700;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	Verly verly = Verly();
	Mouse mouse = Mouse();
	auto box = Verly::createBox(100, 100, 100, 100);
	auto rope = Verly::createRope(200, 30, 10, 30, true);
	auto cloth = Verly::createCloth(500, 100, 400, 400, 20, 2);

	verly.addEntity(box);
	verly.addEntity(rope);
	verly.addEntity(cloth);

	while (!WindowShouldClose()) {
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