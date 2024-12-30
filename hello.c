#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

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

  // Left Bar
  Rectangle leftBar = {
      .x = 0,
      .y = 0,
      .width = 50,
      .height = 150,
  };

  // Ball
  const int ballRadius = 25;
  // top left postion
  Vector2 ballTopLeftPosition = {
      .x = (float)screenWidth / 2 - ballRadius,
      .y = (float)screenHeight / 2 - ballRadius,
  };
  Rectangle ball = {
      .x = ballTopLeftPosition.x,
      .y = ballTopLeftPosition.y,
      .width = ballRadius * 2,
      .height = ballRadius * 2,
  };

  bool ballInCollision = false;
  Color ballColor = GREEN;
  Vector2 ballDirection = {
      .x = -1,
      .y = -1,
  };
  Vector2 ballDestination;

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, GetScreenWidth() / 2 - textWidth / 2,
             GetScreenHeight() / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    // Left bar
    leftBar.y = leftBar.y + 1;
    if (leftBar.y > GetScreenHeight()) {
      leftBar.y = 0;
    }
    DrawRectangleRec(leftBar, BLACK);

    // Ball
    ballDestination =
        Vector2Add(ballTopLeftPosition, Vector2Scale(ballDirection, 100));

    ballTopLeftPosition =
        Vector2MoveTowards(ballTopLeftPosition, ballDestination, 1.0);
    ball.x = ballTopLeftPosition.x;
    ball.y = ballTopLeftPosition.y;

    ballInCollision = false;

    // Collision with the left bar
    ballInCollision |= CheckCollisionRecs(ball, leftBar);

    // Left screen collision
    ballInCollision |= ball.x <= 0;

    // Right screen collision
    ballInCollision |= ball.x >= screenWidth + 2 * ballRadius;

    // Up screen collision
    ballInCollision |= ball.y <= 0;

    // Down screen collision
    ballInCollision |= ball.y >= screenHeight + 2 * ballRadius;

    if (ballInCollision) {
      ballColor = RED;
      // Vector2Reflect(Vector2 v, Vector2 normal)
    } else {
      ballColor = GREEN;
    }

    DrawRectangleRec(ball, ballColor);

    DrawLineV(ballTopLeftPosition, ballDestination, BLUE);

    EndDrawing();
  }

  return 0;
}
