#include "raylib.h"

int main() {
  // Initialization

  // screen
  const int screenWidth = 800;
  const int screenHeight = 450;

  // Text
  const int fontSize = 20;
  const char *text =
      "Hello the text is perfectly centered, but the rectangle not ...";
  int textWidth;

  // Rectangle
  int rectangleWidth = 50;
  int rectangleHeight = 150;
  int rectanglePositionX = 0;
  int rectanglePositionY = 0;

  // Ball
  int ballRadius = 25;
  int ballPositionX = screenWidth / 2 - ballRadius;
  int ballPositionY = screenHeight / 2 - ballRadius;

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, screenWidth / 2 - textWidth / 2,
             screenHeight / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    DrawRectangle(rectanglePositionX, rectanglePositionY, rectangleWidth,
                  rectangleHeight, BLACK);
    rectanglePositionY = rectanglePositionY + 1;
    if (rectanglePositionY > screenHeight) {
      rectanglePositionY = 0;
    }

    // NOTE: for collision usage I should use DrawRectangleRec() instead of
    // DrawRectangle(). CheckCollisionRecs() return true if a collision occurs
    DrawRectangle(ballPositionX, ballPositionY, 2 * ballRadius, 2 * ballRadius,
                  RED);

    EndDrawing();
  }

  return 0;
}
