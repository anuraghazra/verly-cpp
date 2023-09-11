#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "mouse.hpp"

int main() {
	const int screenWidth = 1200;
	const int screenHeight = 450;

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(60);

	Verly verly = Verly();
	Mouse mouse = Mouse();
	auto box = Verly::createBox(100, 100, 100, 100);

	verly.addEntity(box);

	while (!WindowShouldClose()) {
		box->update();
		mouse.update(verly);

		BeginDrawing();
		ClearBackground(Color{ 245, 245, 245, 255 });
		box->draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}