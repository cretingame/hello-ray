#include "raylib.h"

int main() {
  // Initialization

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Hello this is not perfectly centered ...", screenWidth/2, screenHeight/2, 20, LIGHTGRAY);

    EndDrawing();
  }

  return 0;
}
