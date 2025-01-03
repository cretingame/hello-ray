#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>
#include <time.h>

typedef struct {
  char *name;
  float speed;
  Rectangle rectangle;
  Color color;
  Vector2 direction;
} Ball;

typedef struct {
  char *name;
  float speed;
  float upLimit;
  float downLimit;
  Rectangle rectangle;
  // TODO: enum for paddle direction
  bool direction;
} Paddle;

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
  Rectangle leftRacket = {
      .x = 0,
      .y = (float)GetRandomValue(0, screenHeight - 150),
      .width = 50,
      .height = 150,
  };
  float leftRacketDirection = 1;

  Rectangle rightRacket = {
      .x = (float)screenWidth - 50,
      .y = (float)GetRandomValue(0, screenHeight - 150),
      .width = 50,
      .height = 150,
  };
  float rightRacketDirection = 1;

  // Ball
  const float ballRadius = 25.0;
  const float ballSpeed = 1.0;
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
    leftRacket.y = leftRacket.y + leftRacketDirection;
    if (leftRacket.y >= GetScreenHeight() - 150 - 3 * ballRadius) {
      leftRacketDirection = -1;
    }
    if (leftRacket.y <= 3 * ballRadius) {
      leftRacketDirection = 1;
    }
    DrawRectangleRec(leftRacket, BLACK);

    // Right racket
    rightRacket.y = rightRacket.y + rightRacketDirection;
    if (rightRacket.y >= GetScreenHeight() - 150 - 3 * ballRadius) {
      rightRacketDirection = -1;
    }
    if (rightRacket.y <= 3 * ballRadius) {
      rightRacketDirection = 1;
    }
    DrawRectangleRec(rightRacket, BLACK);

    // Ball
    ballInCollision = false;

    // Collision with the left racket
    if (CheckCollisionRecs(ball, leftRacket)) {
      ballInCollision = true;
      // FIXME: Top and bottom collision
      collision = GetCollisionRec(ball, leftRacket);

      if (collision.width > collision.height) {
        if (ball.y > leftRacket.y) {
          ballReflection.x = 0;
          ballReflection.y = 1;
          TraceLog(LOG_DEBUG, "Left racket collision on the top");
        } else {
          ballReflection.x = 0;
          ballReflection.y = 1;
          TraceLog(LOG_DEBUG, "Left racket collision on the bottom");
        }
      } else {
        ballReflection.x = 1;
        ballReflection.y = 0;
        TraceLog(LOG_DEBUG, "Left racket collision on the right");
      }
    } else if (CheckCollisionRecs(
                   ball, rightRacket)) { // Collision with the right racket
      ballInCollision = true;
      ballReflection.x = 1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Right racket collision");
      // FIXME: Top and bottom collision
      collision = GetCollisionRec(ball, rightRacket);
      if (collision.width > collision.height) {
        if (ball.y > rightRacket.y) {
          ballReflection.x = 0;
          ballReflection.y = 1;
          TraceLog(LOG_DEBUG, "Right racket collision on the top");
        } else {
          ballReflection.x = 0;
          ballReflection.y = 1;
          TraceLog(LOG_DEBUG, "Right racket collision on the bottom");
        }
      } else {
        ballReflection.x = 1;
        ballReflection.y = 0;
        TraceLog(LOG_DEBUG, "Right racket collision on the right");
      }
    } else if (ball.x <= 0) { // Left screen collision
      ballInCollision = true;
      ballReflection.x = 1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Left screen collision");
    } else if (ball.x >=
               screenWidth - 2 * ballRadius) { // Right screen collision
      ballInCollision = true;
      ballReflection.x = 1;
      ballReflection.y = 0;
      TraceLog(LOG_DEBUG, "Right screen collision");
    } else if (ball.y <= 0) { // Top screen collision
      ballInCollision = true;
      ballReflection.x = 0;
      ballReflection.y = 1;
      TraceLog(LOG_DEBUG, "Top screen collision");
    } else if (ball.y >=
               screenHeight - 2 * ballRadius) { // Bottom screen collision
      ballInCollision = true;
      ballReflection.x = 0;
      ballReflection.y = 1;
      TraceLog(LOG_DEBUG, "Bottom screen collision");
      TraceLog(LOG_DEBUG, "ball.x = %f ball.y = %f", ball.x, ball.y);
    } else {
      ballInCollision = false;
    }

    if (ballInCollision) {
      ballColor = RED;
      // ballDirection = Vector2Reflect(ballDirection, ballReflection);
      DrawRectangleRec(collision, BLUE);
    } else {
      ballColor = GREEN;
    }

    ballDestination = Vector2Add(ballTopLeftPosition,
                                 Vector2Scale(ballDirection, 100 * ballSpeed));

    ballTopLeftPosition =
        Vector2MoveTowards(ballTopLeftPosition, ballDestination, ballSpeed);
    ball.x = ballTopLeftPosition.x;
    ball.y = ballTopLeftPosition.y;

    DrawRectangleRec(ball, ballColor);
    DrawLineV(ballTopLeftPosition, ballDestination, BLUE);

    EndDrawing();
  }

  return 0;
}

Ball updateBall(Ball ball, Paddle paddleList[]) {
  Paddle *paddlePtr = paddleList;
  while (paddlePtr != NULL) {
    // TODO: check for collision with each paddle
    if (CheckCollisionRecs(ball.rectangle, paddlePtr->rectangle)) {
      TraceLog(LOG_DEBUG, "collision: %s -> %s", ball.name, paddlePtr->name);
      // TODO: move ball in case of collsion with a paddle
      return ball;
    }
    paddlePtr++;
  }

  // TODO: collision with screen borders

  // TODO: usual ball move

  // TODO: update ball
  return ball;
}

void drawBall(Ball ball) { DrawRectangleRec(ball.rectangle, ball.color); }

Paddle updatePaddle(Paddle paddle) {
  if (paddle.rectangle.y >= paddle.upLimit) {
    paddle.direction = false;
  }

  if (paddle.rectangle.y <= paddle.downLimit) {
    paddle.direction = true;
  }

  if (paddle.direction == true) {
    // Moving up
    paddle.rectangle.y = paddle.rectangle.y - paddle.speed;
  } else {
    // Moving Down
    paddle.rectangle.y = paddle.rectangle.y + paddle.speed;
  }

  return paddle;
}

void drawPaddle(Paddle paddle) { DrawRectangleRec(paddle.rectangle, BLACK); }
