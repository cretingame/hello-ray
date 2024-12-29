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
  const int ballRadius = 25;
  Vector2 ballCenterPosition = {
      .x = (float)screenWidth / 2,
      .y = (float)screenHeight / 2,
  };
  Rectangle ball = {
      .x = ballCenterPosition.x - ballRadius,
      .y = ballCenterPosition.y - ballRadius,
      .width = ballRadius * 2,
      .height = ballRadius * 2,
  };
  // INFO: https://fr.wikipedia.org/wiki/Norme_(math%C3%A9matiques)
  Vector2 ballDirection = {
      .x = 100,
      .y = 100,
  };
  Vector2 ballDestination = {
      .x = ballCenterPosition.x + ballDirection.x,
      .y = ballCenterPosition.y + ballDirection.y,
  };

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, screenWidth / 2 - textWidth / 2,
             screenHeight / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    // Left bar
    rectanglePositionY = rectanglePositionY + 1;
    if (rectanglePositionY > screenHeight) {
      rectanglePositionY = 0;
    }
    DrawRectangle(rectanglePositionX, rectanglePositionY, rectangleWidth,
                  rectangleHeight, BLACK);

    // Ball

    ball.x = ballCenterPosition.x - ballRadius;
    ball.y = ballCenterPosition.y - ballRadius;

    DrawRectangleRec(ball, GREEN);

    DrawLineV(ballCenterPosition, ballDestination, BLUE);

    EndDrawing();
  }

  return 0;
}
