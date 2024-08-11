
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

int basicScene() {
	const int screenWidth = 1080;
	const int screenHeight = 720;
	// SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);
	raylib::Window window(screenWidth, screenHeight, "Verly window");

  auto myRenderer = DebugRenderer();
  Mouse mouse = Mouse();
  Verly verly = Verly();

  verly.setRenderer(myRenderer);

  // entities
  auto box = verly.createBox(100, 100, 100, 100);

  verly.addEntity(box);

  while (!WindowShouldClose()) {
    mouse.update(verly);
    verly.update();

    ClearBackground(RAYWHITE);
    DrawFPS(100, 100);
    
    verly.draw();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}