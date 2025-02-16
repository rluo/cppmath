#include "raylib.h"

int main() {
  // Window dimensions
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Bouncing Ball in Bounding Box");

  // Define bounding box (inside window margins)
  Rectangle boundingBox = {50, 50, screenWidth - 100, screenHeight - 100};

  // Ball properties
  Vector2 ballPosition = {boundingBox.x + boundingBox.width / 2,
                          boundingBox.y + boundingBox.height / 2};
  Vector2 ballVelocity = {4.0f, 3.5f};  // Initial velocity
  float ballRadius = 20.0f;

  SetTargetFPS(60);  // Set frame rate

  while (!WindowShouldClose()) {
    // Update ball position
    ballPosition.x += ballVelocity.x;
    ballPosition.y += ballVelocity.y;

    // Check for collisions with bounding box walls
    if ((ballPosition.x - ballRadius <= boundingBox.x) ||
        (ballPosition.x + ballRadius >= boundingBox.x + boundingBox.width)) {
      ballVelocity.x *= -1;  // Reverse X direction
    }

    if ((ballPosition.y - ballRadius <= boundingBox.y) ||
        (ballPosition.y + ballRadius >= boundingBox.y + boundingBox.height)) {
      ballVelocity.y *= -1;  // Reverse Y direction
    }

    // Draw everything
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw bounding box
    DrawRectangleLinesEx(boundingBox, 3, BLACK);

    // Draw ball
    DrawCircleV(ballPosition, ballRadius, RED);

    DrawText("Ball Bouncing in a Bounding Box", 20, 20, 20, DARKGRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
