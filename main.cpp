#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

/* GLOBAL VARIABLES */
int player_score = 0;
int player_life = 5;
bool gameOver = false;
bool gameWon = false;

/* Bricks */
// Define numbers of Rows and Columns of bricks
const int NUM_ROWS = 6;
const int NUM_COLS = 22;

// Define bricks dimensions
const int BRICK_WIDTH = 50;
const int BRICK_HEIGHT = 20;

vector<Rectangle> bricks;

class Ball {
public:
  float x, y;
  int speed_x, speed_y;
  int radius;

  void drawBall() { DrawCircle(x, y, radius, WHITE); }

  void updateBall() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight()) {
      player_score++;
      resetBall();
    }
    if (y <= 0) {
      speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth() || x - radius <= 0) {
      speed_x *= -1;
    }
  }

  void resetBall() {
    y = GetScreenHeight() / 2;
    player_life--;
  }
};

// Player Paddle
class Player {
public:
  float x, y;
  float width, height;
  int speed;

  void drawPaddle() { DrawRectangle(x, y, width, height, RED); }

  void updatePaddle() {
    if (IsKeyDown(KEY_A)) {
      x -= speed;
    }
    if (IsKeyDown(KEY_D)) {
      x += speed;
    }
    // stops paddle from leaving to the side of the screen
    if (x <= 0) {
      x = 0;
    }
    if (x >= GetScreenWidth()) {
      x = GetScreenWidth() - width;
    }
  }
};

void InitBricks() {
  bricks.clear();

  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      // Create rectangle object and set it's properties
      Rectangle brick = {static_cast<float>(j * (BRICK_WIDTH + 5) + 40),
                         static_cast<float>(i * (BRICK_HEIGHT + 5) + 40),
                         BRICK_WIDTH, BRICK_HEIGHT};

      bricks.push_back(brick);
    }
  }
}

void drawBricks() {
  for (const auto &brick : bricks) {
    DrawRectangleRec(brick, RED);
  }
}

Player player;
Ball ball;

int main() {
  cout << "Starting Breakout.." << endl;
  const int screen_width = 1280;
  const int screen_height = 720;

  InitWindow(screen_width, screen_height, "Breakout");
  SetTargetFPS(60);

  // Player Paddle
  player.width = 125;
  player.height = 15;
  player.x = screen_height - player.height - 10;
  player.y = screen_width / 2 - player.width / 2;
  player.speed = 8;

  // Ball
  ball.radius = 12;
  ball.x = screen_width / 2;
  ball.y = screen_height / 2;
  ball.speed_x = 5;
  ball.speed_y = 5;

  // Bricks
  InitBricks();

  // Main Loop
  while (!WindowShouldClose()) {

    // Updating
    ball.updateBall();
    player.updatePaddle();

    // Check for Collisions

    // Player
    if (CheckCollisionCircleRec(
            Vector2{ball.x, ball.y}, ball.radius,
            Rectangle{player.x, player.y, player.width, player.height})) {
      ball.speed_y *= -1;
    }

    BeginDrawing();

    /* Drawing */
    ClearBackground(BLACK);
    ball.drawBall();
    player.drawPaddle();
    drawBricks();

    /* GUI TEXT */

    // Player Life Text
    DrawText(TextFormat("Lives: %i", player_life), 3 * screen_width / 4 - 20,
             700, 25, WHITE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
