#include "raylib.h"

int main() {
  // Initialization

  const int screenWidth = 800;
  const int screenHeight = 450;
  const int fontSize = 20;
  const char *text = "Hello this is not perfectly centered ...";
  int textWidth;

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, screenWidth / 2 - textWidth / 2,
             screenHeight / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    EndDrawing();
  }

  return 0;
}
