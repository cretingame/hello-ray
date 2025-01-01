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

  // Left Racket
  Rectangle lefRacket = {
      .x = 0,
      .y = (float)GetRandomValue(0, screenHeight - 150),
      .width = 50,
      .height = 150,
  };
  int leftRacketDirection = 1;

  Rectangle rightRacket = {
      .x = (float)screenWidth - 50,
      .y = (float)GetRandomValue(0, screenHeight - 150),
      .width = 50,
      .height = 150,
  };
  int rightRacketDirection = 1;

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
  Vector2 ballReflection;

  Rectangle collision;

  SetTraceLogLevel(LOG_ALL);

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, GetScreenWidth() / 2 - textWidth / 2,
             GetScreenHeight() / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    // Left Racket
    lefRacket.y = lefRacket.y + leftRacketDirection;
    if (lefRacket.y >= GetScreenHeight() - 150) {
      leftRacketDirection = -1;
    }
    if (lefRacket.y <= 0) {
      leftRacketDirection = 1;
    }
    DrawRectangleRec(lefRacket, BLACK);

    // Right racket
    rightRacket.y = rightRacket.y + rightRacketDirection;
    if (rightRacket.y >= GetScreenHeight() - 150) {
      rightRacketDirection = -1;
    }
    if (rightRacket.y <= 0) {
      rightRacketDirection = 1;
    }
    DrawRectangleRec(rightRacket, BLACK);

    // Ball
    ballDestination =
        Vector2Add(ballTopLeftPosition, Vector2Scale(ballDirection, 100));

    ballTopLeftPosition =
        Vector2MoveTowards(ballTopLeftPosition, ballDestination, 1.0);
    ball.x = ballTopLeftPosition.x;
    ball.y = ballTopLeftPosition.y;

    ballInCollision = false;

    // Collision with the left racket
    if (CheckCollisionRecs(ball, lefRacket)) {
      ballInCollision = true;
      ballReflection.x = 1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Left racket collision");
      // FIXME: Top and bottom collision
      collision = GetCollisionRec(ball, lefRacket);
      // NOTE: I will use collision CheckCollisionLines() to detect where the
      // collsion commes from. Then I sould plan the collision priority order.
      // Either I use an "else if" statement or I will place the collision with
      // the weakest priority first and the strongest last.
    }

    if (CheckCollisionRecs(ball, rightRacket)) {
      ballInCollision = true;
      ballReflection.x = -1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Right racket collision");
      // FIXME: Top and bottom collision
      collision = GetCollisionRec(ball, rightRacket);
    }

    // Left screen collision
    if (ball.x <= 0) {
      ballInCollision = true;
      ballReflection.x = 1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Left screen collision");
    }

    // Right screen collision
    if (ball.x >= screenWidth - 2 * ballRadius) {
      ballInCollision = true;
      ballReflection.x = -1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Right screen collision");
    }

    // Top screen collision
    ballInCollision |= ball.y <= 0;
    if (ball.y <= 0) {
      ballInCollision = true;
      ballReflection.x = 0;
      ballReflection.y = -1;
      TraceLog(LOG_DEBUG, "Top screen collision");
    }

    // Bottom screen collision
    if (ball.y >= screenHeight - 2 * ballRadius) {
      ballInCollision = true;
      ballReflection.x = 0;
      ballReflection.y = 1;
      TraceLog(LOG_DEBUG, "Bottom screen collision");
    }

    DrawRectangleRec(ball, ballColor);

    if (ballInCollision) {
      ballColor = RED;
      ballDirection = Vector2Reflect(ballDirection, ballReflection);
      DrawRectangleRec(collision, BLUE);
    } else {
      ballColor = GREEN;
    }

    DrawLineV(ballTopLeftPosition, ballDestination, BLUE);

    EndDrawing();
  }

  return 0;
}
