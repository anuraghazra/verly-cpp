#include <raylib-cpp.hpp>
#include "scenes/particle-fluid.cpp"
#include "scenes/basic.cpp"

int main() {
	SetTargetFPS(120);

	// basicScene();
	particleFluidScreen();

	return 0;
}
