#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>
#include <time.h>

typedef struct {
  const char *name;
  float speed;
  Rectangle rectangle;
  Color color;
  Vector2 direction;
} Ball;

typedef struct {
  const char *name;
  float speed;
  float upLimit;
  float downLimit;
  Rectangle rectangle;
  // TODO: enum for paddle direction
  bool direction;
} Paddle;

Ball updateBall(Ball ball, Paddle paddleList[]) {
  Paddle *paddlePtr = paddleList;
  ball.color = GREEN;
  while (paddlePtr->name != NULL) {
    if (CheckCollisionRecs(ball.rectangle, paddlePtr->rectangle)) {
      ball.color = RED;
      TraceLog(LOG_DEBUG, "collision: %s -> %s", ball.name, paddlePtr->name);
      // Paddle left collision
      if (ball.rectangle.x < paddlePtr->rectangle.x) {
        if (ball.direction.x > 0) {
          ball.direction.x = -ball.direction.x;
        }
        TraceLog(LOG_DEBUG, "right collision: %s -> %s", ball.name,
                 paddlePtr->name);
      }

      // Paddle right collision
      else if (ball.rectangle.x > paddlePtr->rectangle.x) {
        if (ball.direction.x < 0) {
          ball.direction.x = -ball.direction.x;
        }
        TraceLog(LOG_DEBUG, "left collision: %s -> %s", ball.name,
                 paddlePtr->name);
      }

      // Paddle top collision
      else if (ball.rectangle.y < paddlePtr->rectangle.y) {
        if (ball.direction.y > 0) {
          ball.direction.y = -ball.direction.y;
        }
        TraceLog(LOG_DEBUG, "top collision: %s -> %s", ball.name,
                 paddlePtr->name);
      }

      // Paddle bottom collision
      else if (ball.rectangle.y > paddlePtr->rectangle.y) {
        if (ball.direction.y < 0) {
          ball.direction.y = -ball.direction.y;
        }
        TraceLog(LOG_DEBUG, "bottom collision: %s -> %s", ball.name,
                 paddlePtr->name);
      }
    }
    paddlePtr++;
  }

  // Right screen collision
  if (ball.rectangle.x <= 0) {
    ball.color = RED;
    if (ball.direction.x < 0) {
      ball.direction.x = -ball.direction.x;
    }
    TraceLog(LOG_DEBUG, "collision: %s -> left screen", ball.name);
  }

  // Left screen collision
  if (ball.rectangle.x >= GetScreenWidth() - ball.rectangle.width) {
    ball.color = RED;
    if (ball.direction.x > 0) {
      ball.direction.x = -ball.direction.x;
    }
    TraceLog(LOG_DEBUG, "collision: %s -> right screen", ball.name);
  }

  // Top screen collision
  if (ball.rectangle.y <= 0) {
    ball.color = RED;
    if (ball.direction.y < 0) {
      ball.direction.y = -ball.direction.y;
    }
    TraceLog(LOG_DEBUG, "collision: %s -> top screen", ball.name);
  }

  // Botoom screen collision
  if (ball.rectangle.y >= GetScreenHeight() - ball.rectangle.height) {
    ball.color = RED;
    if (ball.direction.y > 0) {
      ball.direction.y = -ball.direction.y;
    }
    TraceLog(LOG_DEBUG, "collision: %s -> bottom screen", ball.name);
  }

  Vector2 currentPosition;
  currentPosition.x = ball.rectangle.x;
  currentPosition.y = ball.rectangle.y;

  Vector2 target = Vector2Add(currentPosition,
                              Vector2Scale(ball.direction, 100 * ball.speed));

  target = Vector2MoveTowards(currentPosition, target, ball.speed);
  ball.rectangle.x = target.x;
  ball.rectangle.y = target.y;

  return ball;
}

void drawBall(Ball ball) { DrawRectangleRec(ball.rectangle, ball.color); }

Paddle updatePaddle(Paddle paddle) {
  if (paddle.rectangle.y <= paddle.upLimit) {
    paddle.direction = false;
  }

  if (paddle.rectangle.y >= paddle.downLimit) {
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

  const float paddleWidth = 50;
  const float paddleHeight = 150;

  // Left paddle
  Paddle leftPaddle = {
      .rectangle =
          {
              .x = 0.0,
              .y = (float)GetRandomValue(0, screenHeight - paddleHeight),
              .width = paddleWidth,
              .height = paddleHeight,

          },
  };

  Paddle paddleList[] = {
      // Left paddle
      {
          .name = "leftPaddle",
          .speed = 1.0,
          .upLimit = paddleWidth,
          .downLimit = screenHeight - paddleHeight,
          .rectangle =
              {
                  .x = 0.0,
                  .y = (float)GetRandomValue(0, screenHeight - paddleHeight),
                  .width = paddleWidth,
                  .height = paddleHeight,

              },
          .direction = true,
      },
      // Right paddle
      {
          .name = "rightPaddle",
          .speed = 1.0,
          .upLimit = 50.0,
          .downLimit = screenHeight - 150,
          .rectangle =
              {
                  .x = (float)screenWidth - 50,
                  .y = (float)GetRandomValue(0, screenHeight - 150),
                  .width = paddleWidth,
                  .height = paddleHeight,

              },
          .direction = true,
      },

      // Ballast
      {
          .name = NULL,
      },
  };

  const float ballRadius = 25.0;
  Ball ball = {
      .name = "ball",
      .speed = 1.0,
      .rectangle =
          {
              .x = (float)screenWidth / 2 - ballRadius,
              .y = (float)screenHeight / 2 - ballRadius,
              .width = ballRadius * 2,
              .height = ballRadius * 2,
          },
      .color = GREEN,
      .direction =
          {
              .x = -1,
              .y = -1,
          },

  };

  SetTraceLogLevel(LOG_ALL);

  InitWindow(screenWidth, screenHeight, "basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    Paddle *paddlePtr = paddleList;
    while (paddlePtr->name != NULL) {
      *paddlePtr = updatePaddle(*paddlePtr);
      paddlePtr++;
    }
    ball = updateBall(ball, paddleList);

    // Drawing
    BeginDrawing();

    textWidth = MeasureText(text, fontSize);

    ClearBackground(RAYWHITE);

    DrawText(text, GetScreenWidth() / 2 - textWidth / 2,
             GetScreenHeight() / 2 - fontSize / 2, fontSize, LIGHTGRAY);

    paddlePtr = paddleList;
    while (paddlePtr->name != NULL) {
      drawPaddle(*paddlePtr);
      paddlePtr++;
    }
    drawBall(ball);

    EndDrawing();
  }

  return 0;
}
