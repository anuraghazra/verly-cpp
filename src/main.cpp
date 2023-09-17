#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "mouse.hpp"

int main() {
	const int screenWidth = 1280;
	const int screenHeight = 800;

	// SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	Verly verly = Verly();
	Mouse mouse = Mouse();

	auto box = Verly::createBox(100, 100, 100, 100);
	auto cloth = Verly::createCloth(200, 100, 10, 10, 50, 1);
	auto rope = Verly::createRope(200, 30, 50, 30, true);
	auto heaxgon = Verly::createHexagon(800, 300, 12, 100, 3, 8);

	verly.addEntity(std::move(box));
	verly.addEntity(std::move(cloth));
	verly.addEntity(std::move(rope));
	verly.addEntity(std::move(heaxgon));

	while (!WindowShouldClose()) {
		mouse.update(verly);
		verly.update();

		ClearBackground(Color{ 245, 245, 245, 255 });
		DrawFPS(100, 100);
		
		verly.draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}