#include <iostream>
#include <raylib.h>

class Ball {
public:
  float x, y;
  int speed_x, speed_y;
  int radius;

  void drawBall() { DrawCircle(x, y, radius, WHITE); }

  void updateBall() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth() || x - radius <= 0) {
      speed_x *= -1;
    }
  }
};

// Player Paddle
class Player {
public:
  float x, y;
  float width, height;
  int speed;

  void drawPaddle() { DrawRectangle(x, y, width, height, WHITE); }

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

using namespace std;

Player player;
Ball ball;

int main() {
  cout << "Starting Breakout.." << endl;
  const int screen_width = 1280;
  const int screen_height = 720;

  InitWindow(screen_width, screen_height, "Breakout");
  SetTargetFPS(60);

  // Player Paddle
  player.width = 100;
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

  // Main Loop
  while (!WindowShouldClose()) {

    // Updating
    ball.updateBall();
    player.updatePaddle();

    BeginDrawing();

    // Drawing
    ClearBackground(BLACK);
    ball.drawBall();
    player.drawPaddle();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
