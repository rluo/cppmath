#include "raylib.h"

int main() {
  // make window
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Social bouncing ball");

  SetTargetFPS(60);

  // create walls : (x = 50, y = 50)
  Rectangle boundingWalls = {50, 50, screenWidth - 100, screenHeight - 100};

  // create ball location speed (x, y)
  Vector2 ballLocation = {boundingWalls.x + boundingWalls.width / 2,
                          boundingWalls.y + boundingWalls.height / 4};

  Vector2 ballSpeed = {30.0f, -30.0f};

  const float ballRadius = 10.0f;

  // every second, the speed along y axis should be increased by the following
  const float gravityAcceleration = 0.0f;

  // create a paddle, rectagle size
  const float paddleWidth = 75;
  const float paddleHeight = 20;
  // create ball location speed (x, y)
  Vector2 paddleLocation = {screenWidth / 2 - paddleWidth / 2,
                            screenHeight - 100};
  float centerPaddleLocationX = paddleLocation.x + paddleWidth / 2;

  const float paddleSpeed = 50.0f;

  int score = 0;
  bool gameOver = false;

  while (!WindowShouldClose()) {
    // ! means not
    if (!gameOver) {
      ballSpeed.y = ballSpeed.y + gravityAcceleration;
      // 1 second passed  1/FPS passed, new ball location
      ballLocation.x = ballLocation.x + ballSpeed.x;
      ballLocation.y = ballLocation.y + ballSpeed.y;

      // check if hitting the wall
      // if ball outside the x axis walls: left wall and right wall
      // higt left wall
      if (ballLocation.x - ballRadius <= boundingWalls.x ||
          ballLocation.x + ballRadius >=
              boundingWalls.x + boundingWalls.width) {
        ballSpeed.x = -1 * ballSpeed.x;
      }
      // top/bottom
      if (ballLocation.y - ballRadius <= boundingWalls.y) {
        ballSpeed.y = -1 * ballSpeed.y;  // flip speed
      }

      // math for checking if ball hits the paddle
      // y axis, center of ball's location y + radiu =  paddle's y location
      // x axis, center of ball's location x >  paddle position.x
      if (ballLocation.y + ballRadius >= paddleLocation.y &&
          ballLocation.x >= paddleLocation.x &&
          ballLocation.x <= paddleLocation.x + paddleWidth) {
        score = score + 1;
        ballSpeed.y = -1 * ballSpeed.y;
      }

      // move paddle left, postion x value should be bigger than the left wall
      // (left boundary)
      // if (IsKeyDown(KEY_LEFT) && paddleLocation.x >= boundingWalls.x) {
      //   // move paddle left, substract x axis value
      //   paddleLocation.x = paddleLocation.x - paddleSpeed;
      // }

      // // move paddle right
      // if (IsKeyDown(KEY_RIGHT) && paddleLocation.x + paddleWidth <=
      //                                 boundingWalls.x + boundingWalls.width)
      //                                 {
      //   // move paddle left, substract x axis value
      //   paddleLocation.x = paddleLocation.x + paddleSpeed;
      // }

      centerPaddleLocationX = paddleLocation.x + paddleWidth / 2;

      // robot move paddle to the right
      if (ballLocation.x > paddleLocation.x + paddleWidth / 2 &&
          paddleLocation.x + paddleWidth <=
              boundingWalls.x + boundingWalls.width) {
        // move paddle left, substract x axis value
        paddleLocation.x = paddleLocation.x + paddleSpeed;
      }

      // move to the left
      if (ballLocation.x < paddleLocation.x + paddleWidth / 2 &&
          paddleLocation.x >= boundingWalls.x) {
        // move paddle left, substract x axis value
        paddleLocation.x = paddleLocation.x - paddleSpeed;
      }

      // game over if ball y location > screenHeight
      if (ballLocation.y - ballRadius > screenHeight) {
        gameOver = true;
      }
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw walls
    DrawRectangleLinesEx(boundingWalls, 5, BLUE);

    // draw ball
    DrawCircleV(ballLocation, ballRadius, RED);

    // draw paddle
    DrawRectangleV(paddleLocation, {paddleWidth, paddleHeight}, ORANGE);

    // display the score
    DrawText(TextFormat("Score: %d", score), 20, 20, 20, PURPLE);

    // display game over
    if (gameOver) {
      DrawText("GAME OVER", screenWidth / 2 - 140, screenHeight / 2, 40, RED);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}