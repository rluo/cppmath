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

  Vector2 ballSpeed = {4.0f, -3.0f};

  const float ballRadius = 20.0f;

  // every second, the speed along y axis should be increased by the following
  const float gravityAcceleration = 0.4f;

  while (!WindowShouldClose()) {
    ballSpeed.y = ballSpeed.y + gravityAcceleration;
    // 1 second passed  1/FPS passed, new ball location
    ballLocation.x = ballLocation.x + ballSpeed.x;
    ballLocation.y = ballLocation.y + ballSpeed.y;

    // check if hitting the wall
    // if ball outside the x axis walls: left wall and right wall
    // higt left wall
    if (ballLocation.x - ballRadius <= boundingWalls.x ||
        ballLocation.x + ballRadius >= boundingWalls.x + boundingWalls.width) {
      ballSpeed.x = -1 * ballSpeed.x;
    }
    // top/bottom
    if (ballLocation.y - ballRadius <= boundingWalls.y ||
        ballLocation.y + ballRadius >= boundingWalls.y + boundingWalls.height) {
      ballSpeed.y = -1 * ballSpeed.y;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw walls
    DrawRectangleLinesEx(boundingWalls, 5, BLUE);

    // draw ball
    DrawCircleV(ballLocation, ballRadius, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}