
#include <raylib-cpp.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "../constants.hpp"
#include "../verly.hpp"
#include "../entity.hpp"
#include "../mouse.hpp"
#include "../behaviours/attraction.hpp"
#include "../renderer/debug_renderer.hpp"

int particleFluidScreen() {
	const int screenHeight = 2160;
	const int screenWidth = 3840;
	// SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);
	raylib::Window window(screenWidth, screenHeight, "Verly window");

  auto myRenderer = VerlyRenderer();
  Mouse mouse = Mouse();
  Verly verly = Verly();

  verly.setRenderer(myRenderer);

  // entities
  auto particles = new Entity();
  int particleCount = 2000;
  for (int i = 0; i < particleCount; i++) {
    auto p = particles->createPoint(GetRandomValue(100, screenWidth), GetRandomValue(100, screenHeight));
    p->friction = 0.99;
    p->radius = 20;
  }
  verly.addEntity(*particles);

  // behaviours
  std::vector<AttractionBehaviour> behaviours = {};
  auto globalAttractor = AttractionBehaviour(mouse.mouse);
  auto globalEvader = AttractionBehaviour(mouse.mouse);
  globalAttractor.setRadius(700);
  globalAttractor.setStrength(8);
  globalEvader.setRadius(600);
  globalEvader.setStrength(-4);

  for (int i = 0; i < particleCount; i++) {
    auto behaviour = AttractionBehaviour(*verly.entities.at(0)->points.at(i).pos);
    behaviour.strength = -3;
    behaviour.radius = 100;
    behaviours.push_back(std::move(behaviour));
  }

  while (!WindowShouldClose()) {
    mouse.update(verly);
    verly.update();

    // add circular motion to mouse
    mouse.mouse.SetX(mouse.mouse.GetX() + cos(GetTime()) * 10);
    particles->gravity->SetY(sin(GetTime()) * 0.15);
    particles->gravity->SetX(cos(GetTime()) * 0.15);

    verly.resolveBehaviour(globalEvader);
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      verly.resolveBehaviour(globalAttractor);
    }
    
    for (int i = 0; i < verly.entities.at(0)->points.size(); i++) {
      auto p = &verly.entities.at(0)->points.at(i);
      // color based on velocity
      auto vel = p->pos->Subtract(*p->oldPos);
      vel *= p->friction;
      auto speed = vel.Length();
      p->color->r = Clamp(speed*200, 0, 255);
      p->color->g = Clamp(speed*10, 0, 255);
      p->setRadius(Clamp(speed*2, 10, 40));
      for (int j = 0; j < behaviours.size(); j++) {
        behaviours[j].resolve(p);
      }
    }

    DrawRectangle(0, 0, screenWidth, screenHeight, Color{ 9, 9, 120, 150 });
    // ClearBackground(Color{ 9, 9, 120, 255 });
    DrawFPS(100, 100);
    
    verly.draw();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}