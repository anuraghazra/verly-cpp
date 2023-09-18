#include <raylib-cpp.hpp>
#include "verly.hpp"
#include "entity.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "mouse.hpp"
#include "behaviours/attraction.hpp"

int main() {
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);

	raylib::Window window(screenWidth, screenHeight, "Verly window");
	SetTargetFPS(120);

	Verly verly = Verly();
	verly.setIterations(50);
	Mouse mouse = Mouse();

	// auto box = Verly::createBox(100, 100, 100, 100);
	// auto cloth = Verly::createCloth(200, 100, 10, 10, 50, 1);
	// auto rope = Verly::createRope(200, 30, 50, 30, true);
	// auto heaxgon = Verly::createHexagon(800, 300, 12, 100, 3, 8);

	// verly.addEntity(std::move(box));
	// verly.addEntity(std::move(cloth));
	// verly.addEntity(std::move(rope));
	// verly.addEntity(std::move(heaxgon));

	auto e = new Entity();
	std::vector<AttractionBehaviour> behaviours = {};
	int particleCount = 2000;
	for (int i = 0; i < particleCount; i++) {
		auto p = e->createPoint(GetRandomValue(100, 1000), GetRandomValue(100, 700));
	}
	
	*e->gravity = Vector2{0, 0.0};
	
	verly.addEntity(std::move(*e));

	for (int i = 0; i < particleCount; i++) {
		auto behaviour1 = AttractionBehaviour(*verly.entities.at(0).points.at(i).pos);
		behaviour1.strength = -4;
		behaviour1.radius = 30;
		behaviours.push_back(std::move(behaviour1));
	}
	// verly.addEntity(std::move(cloth));

	raylib::Vector2 m = raylib::Vector2{0, 0};
	auto mouseBehaviour = AttractionBehaviour(m);
	mouseBehaviour.radius = 200;
	mouseBehaviour.strength = -4;

	while (!WindowShouldClose()) {
		// mouse.update(verly);
		m.x = GetMousePosition().x;
		m.y = GetMousePosition().y;
		verly.update();
	
		for (int i = 0; i < verly.entities.at(0).points.size(); i++) {
			auto p = verly.entities.at(0).points.at(i);
			for (int j = 0; j < behaviours.size(); j++) {
				auto b = behaviours[j];
				b.resolve(&p);
			}
			mouseBehaviour.resolve(&p);
		}
	
		ClearBackground(Color{ 245, 245, 245, 255 });
		DrawFPS(100, 100);
		
		verly.draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}