#include "raylib.h"

int main() {
  // Initialization

  const int screenWidth = 800;
  const int screenHeight = 450;
  const int fontSize = 20;
  const char *text =
      "Hello the text is perfectly centered, but the rectangle not ...";
  int textWidth;
  int rectanglePosY = 0;

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, screenWidth / 2 - textWidth / 2,
             screenHeight / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    DrawRectangle(screenWidth / 2, rectanglePosY, 50, 50, BLACK);
    rectanglePosY = rectanglePosY + 1;
    if (rectanglePosY > screenHeight) {
      rectanglePosY = 0;
    }

    EndDrawing();
  }

  return 0;
}
