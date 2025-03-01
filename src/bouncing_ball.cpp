#include "raylib.h"

int main() {
  // Window dimensions
  const int screenWidth = 800;
  const int screenHeight = 600;
  const float gravity = 0.0f;

  InitWindow(screenWidth, screenHeight, "Bouncing Ball in Bounding Box");

  // Define bounding box (inside window margins)
  Rectangle boundingBox = {50, 50, screenWidth - 100, screenHeight - 100};

  // Ball properties
  Vector2 ballPosition = {boundingBox.x + boundingBox.width / 2,
                          boundingBox.y + boundingBox.height / 2};
  Vector2 ballVelocity = {3.0f, 5.0f};  // Initial velocity
  float ballRadius = 10.0f;

  // create paddle
  const float paddleWidth = 100;
  const float paddleHeight = 20;
  Vector2 paddlePosition = {screenWidth / 2 - paddleWidth / 2,
                            screenHeight - 80};
  const float paddleSpeed = 6.0f;
  bool gameOver = false;
  int score = 0;
  bool stopGame = false;

  SetTargetFPS(60);  // Set frame rate

  while (!WindowShouldClose()) {
    if (!gameOver) {
      // Update ball position
      ballPosition.x += ballVelocity.x;
      ballPosition.y += ballVelocity.y;

      // Check for collisions with bounding box walls
      if ((ballPosition.x - ballRadius <= boundingBox.x) ||
          (ballPosition.x + ballRadius >= boundingBox.x + boundingBox.width)) {
        ballVelocity.x *= -1;  // Reverse X direction
      }

      if ((ballPosition.y - ballRadius <= boundingBox.y)) {
        ballVelocity.y *= -1;  // Reverse Y direction
      }

      // check if ball hits paddle
      if (ballPosition.y + ballRadius >= paddlePosition.y &&
          ballPosition.x >= paddlePosition.x &&
          ballPosition.x <= paddlePosition.x + paddleWidth) {
        ballVelocity.y = -1 * ballVelocity.y;
        ballPosition.y =
            paddlePosition.y - ballRadius;  // Prevent ball from getting stuck
        ++score;
      }

      // move paddle
      if (IsKeyDown(KEY_LEFT) && paddlePosition.x > boundingBox.x) {
        paddlePosition.x -= paddleSpeed;
      }
      if (IsKeyDown(KEY_RIGHT) &&
          paddlePosition.x + paddleWidth < boundingBox.x + boundingBox.width) {
        paddlePosition.x += paddleSpeed;
      }

      // Check if ball falls below the bottom wall (game over)
      if (ballPosition.y - ballRadius > screenHeight) {
        gameOver = true;
      }
      ballVelocity.y += gravity;
    }
    // Draw everything
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw bounding box
    DrawRectangleLinesEx(boundingBox, 3, BLACK);
    // draw walls except the bottom wall
    // DrawLine(boundingBox.x, boundingBox.y, boundingBox.x + boundingBox.width,
    //          boundingBox.y, BLUE);
    // DrawLine(boundingBox.x, boundingBox.y, boundingBox.x,
    //          boundingBox.y + boundingBox.height, BLUE);
    // DrawLine(boundingBox.x + boundingBox.width, boundingBox.y,
    //          boundingBox.x + boundingBox.width,
    //          boundingBox.y + boundingBox.height, BLUE);

    // Draw ball
    DrawCircleV(ballPosition, ballRadius, RED);

    // draw paddle
    DrawRectangleV(paddlePosition, {paddleWidth, paddleHeight}, ORANGE);

    // Draw score
    DrawText(TextFormat("Score: %d", score), 20, 20, 20, DARKGRAY);

    if (gameOver) {
      DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2, 30, RED);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
