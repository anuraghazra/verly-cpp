#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
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
	auto box = Verly::createBox(100, 100, 100, 100);
	auto cloth = Verly::createCloth(500, 100, 700, 300, 20, 1);
	// auto rope = Verly::createRope(200, 30, 10, 30, true);
	// auto heaxgon = Verly::createHexagon(800, 300, 12, 100, 3, 8);

	verly.addEntity(std::move(box));
	verly.addEntity(std::move(cloth));
	// verly.addEntity(rope);
	// verly.addEntity(heaxgon);

	// auto e1 = Entity();
	// auto p1 = Particle{150, 500};
	// auto p2 = Particle{100, 600};
	// e1.addPoint(std::move(p1));
	// e1.addPoint(std::move(p2));
	// auto s1 = Stick((e1.points.at(0)), (e1.points.at(1)));
	// e1.addStick(std::move(s1));

	while (!WindowShouldClose()) {
		verly.update();
		mouse.update(verly);

		BeginDrawing();
		ClearBackground(Color{ 245, 245, 245, 255 });
		DrawFPS(100, 100);
		DrawText(std::string("Points: " + std::to_string(verly.entities.at(0).points.size())).c_str(), 10, 50, 15, GRAY);
		DrawText(std::string("Sticks: " + std::to_string(verly.entities.at(0).sticks.size())).c_str(), 10, 70, 15, GRAY);
		// e1.draw();
		verly.draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}