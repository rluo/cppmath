#include <random>
#include <string>
#include <vector>

#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int GRID_SIZE = 199;  // Numbers from 2 to 200
const int ROWS = 20;        // Number of rows in the grid
const int COLUMNS = 10;     // Number of columns in the grid

struct Cell {
  Rectangle rect;
  int number;
  Color color;
  bool crossedOut;
};

void HighlightMultiples(std::vector<Cell> &cells, int prime, Color color) {
  for (auto &cell : cells) {
    if (cell.number % prime == 0 && cell.number != prime) {
      cell.color = color;
      cell.crossedOut = true;
    }
  }
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sieve of Eratosthenes");
  SetTargetFPS(60);

  std::vector<Cell> cells;
  float cellWidth = SCREEN_WIDTH / COLUMNS;
  float cellHeight = SCREEN_HEIGHT / ROWS;

  for (int i = 2; i <= 200; ++i) {
    int index = i - 2;
    int row = index / COLUMNS;
    int col = index % COLUMNS;

    Cell cell;
    cell.rect = {col * cellWidth, row * cellHeight, cellWidth, cellHeight};
    cell.number = i;
    cell.color = LIGHTGRAY;
    cell.crossedOut = false;

    cells.push_back(cell);
  }

  std::vector<int> primes;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(50, 255);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (auto &cell : cells) {
      DrawRectangleRec(cell.rect, cell.color);
      DrawRectangleLinesEx(cell.rect, 1, BLACK);

      std::string text = std::to_string(cell.number);
      int textWidth = MeasureText(text.c_str(), 20);
      int textHeight = 20;

      DrawText(text.c_str(), cell.rect.x + (cell.rect.width - textWidth) / 2,
               cell.rect.y + (cell.rect.height - textHeight) / 2, 20, BLACK);

      if (cell.crossedOut) {
        DrawLine(cell.rect.x, cell.rect.y, cell.rect.x + cell.rect.width,
                 cell.rect.y + cell.rect.height, RED);

        DrawLine(cell.rect.x, cell.rect.y + cell.rect.height,
                 cell.rect.x + cell.rect.width, cell.rect.y, RED);
      }
    }

    if (IsKeyPressed(KEY_SPACE)) {
      for (auto &cell : cells) {
        if (!cell.crossedOut && cell.color == LIGHTGRAY) {
          int r = dist(gen);
          int g = dist(gen);
          int b = dist(gen);

          Color randomColor = {r, g, b, 255};
          cell.color = randomColor;
          primes.push_back(cell.number);
          HighlightMultiples(cells, cell.number, randomColor);
          break;
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
