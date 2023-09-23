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
#include "renderer/debug_renderer.hpp"

int main() {
	const int screenWidth = 1200;
	const int screenHeight = 700;

	// SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	auto myRenderer = DebugRenderer();
	Verly verly = Verly();

	verly.setRenderer(myRenderer);

	Mouse mouse = Mouse();
	auto box = Verly::createBox(100, 100, 100, 100);
	auto cloth = Verly::createCloth(200, 100, 10, 5, 30, 1);
	auto rope = Verly::createRope(200, 30, 50, 30, true);
	auto hexagon = Verly::createHexagon(300, 300, 32, 100, 13, 7);

	verly.addEntity(box);
	box.createPoint(100, 100);
	verly.addEntity(cloth);
	verly.addEntity(rope);
	verly.addEntity(hexagon);

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