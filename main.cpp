#include <iostream>
#include <raylib.h>

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
  }
};

using namespace std;

Player player;

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

  // Main Loop
  while (!WindowShouldClose()) {

    // Updating
    player.updatePaddle();

    BeginDrawing();

    // Drawing
    ClearBackground(BLACK);
    player.drawPaddle();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
