#include "raylib.h"
#include <stdio.h>

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 960;

    const int gameWidth = 256;
    const int gameHeight = 240;

    const float shipTextureSize = 48;
    const float shipSpeed = 120.0f;

    const float backgroundSpeed = 40.0f;
    const float backgroundHeight = 240;

    const float shotSpeed = 200.0f;
    const float shotTextureSize = 16;

    const float enemySpeed = 40.0f;
    const float enemyTextureSize = 16;

    float enemySpawnTimer = 0;

    Vector2 shots[100] = {};
    for (int i = 0; i < 100; i++) {
      shots[i] = (Vector2){ -1, -1 };
    }

    Vector2 enemies[100] = {};
    for (int i = 0; i < 100; i++) {
      enemies[i] = (Vector2){ -1, -1 };
    }

    float backgroundOffset = 0;

    InitWindow(screenWidth, screenHeight, "Ray shooter");

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture2D renderTexture = LoadRenderTexture(gameWidth, gameHeight);

    Image shipImage = LoadImage("assets/ship.png");
    Texture2D shipTexture = LoadTextureFromImage(shipImage);

    Image backgroundImage = LoadImage("assets/background.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);

    Image shotImage = LoadImage("assets/shot.png");
    Texture2D shotTexture = LoadTextureFromImage(shotImage);

    Image enemyImage = LoadImage("assets/enemy.png");
    Texture2D enemyTexture = LoadTextureFromImage(enemyImage);

    Vector2 shipPosition = { 100, 100 };

    while (!WindowShouldClose())
    {
        BeginTextureMode(renderTexture);
            ClearBackground(BLACK);

            DrawTexture(backgroundTexture, 0, backgroundOffset, WHITE);
            DrawTexture(backgroundTexture, 0, backgroundOffset - backgroundHeight, WHITE);
            backgroundOffset += backgroundSpeed * GetFrameTime();
            if (backgroundOffset >= backgroundHeight) {
              backgroundOffset = 0;
            }

            if (IsKeyDown(KEY_A)) {
              shipPosition.x -= shipSpeed * GetFrameTime();
            } else if (IsKeyDown(KEY_D)) {
              shipPosition.x += shipSpeed * GetFrameTime();
            }

            if (IsKeyDown(KEY_W)) {
              shipPosition.y -= shipSpeed * GetFrameTime();
            } else if (IsKeyDown(KEY_S)) {
              shipPosition.y += shipSpeed * GetFrameTime();
            }

            // Don't allow the ship to go off the screen
            if (shipPosition.x < 0) {
              shipPosition.x = 0;
            } else if (shipPosition.x > gameWidth - shipTextureSize) {
              shipPosition.x = gameWidth - shipTextureSize;
            }

            if (shipPosition.y < 0) {
              shipPosition.y = 0;
            } else if (shipPosition.y > gameHeight - shipTextureSize) {
              shipPosition.y = gameHeight - shipTextureSize;
            }

            if (IsKeyPressed(KEY_SPACE)) {
              for (int i = 0; i < 100; i++) {
                Vector2* shot = &shots[i];
                if (shot->x == -1 && shot->y == -1) {
                  shot->x = shipPosition.x + shipTextureSize / 2 - shotTextureSize / 2;
                  shot->y = shipPosition.y - shotTextureSize;
                  break;
                }
              }
            }

            DrawTexture(shipTexture, shipPosition.x, shipPosition.y, WHITE);

            for (int i = 0; i < 100; i++) {
              Vector2* shot = &shots[i];
              if (shot->x != -1 && shot->y != -1) {
                shot->y -= shotSpeed * GetFrameTime();
                if (shot->y + shotTextureSize < 0) {
                  shot->y = -1;
                  shot->x = -1;
                } else {
                  DrawTexture(shotTexture, shot->x, shot->y, WHITE);
                }
              }
            }

            enemySpawnTimer += GetFrameTime();
            if (enemySpawnTimer > 1) {
              enemySpawnTimer = 0;
              for (int i = 0; i < 100; i++) {
                Vector2* enemy = &enemies[i];
                if (enemy->x == -1 && enemy->y == -1) {
                  enemy->x = GetRandomValue(0, gameWidth - enemyTextureSize);
                  enemy->y = -enemyTextureSize;
                  break;
                }
              }
            }

            for (int i = 0; i < 100; i++) {
              Vector2* enemy = &enemies[i];
              if (enemy->x != -1 && enemy->y != -1) {
                enemy->y += enemySpeed * GetFrameTime();
                if (enemy->y > gameHeight) {
                  enemy->y = -1;
                  enemy->x = -1;
                } else {
                  Rectangle enemyRect = (Rectangle){enemy->x, enemy->y, enemyTextureSize, enemyTextureSize};
                  bool hit = false;
                  for (int j = 0; j < 100; j++) {
                    Vector2* shot = &shots[j];
                    if (shot->x != -1 && shot->y != -1) {
                      Rectangle shotRect = (Rectangle){shot->x, shot->y, shotTextureSize, shotTextureSize};
                      if (CheckCollisionRecs(enemyRect, shotRect)) {
                        enemy->x = -1;
                        enemy->y = -1;
                        shot->x = -1;
                        shot->y = -1;

                        hit = true;
                        break;
                      }
                    }
                  }
                  if (!hit) {
                    DrawTexture(enemyTexture, enemy->x, enemy->y, WHITE);
                  }
                }
              }
            }
        EndTextureMode();


        BeginDrawing();
          DrawTexturePro(
              renderTexture.texture,
              (Rectangle){ 0, 0, renderTexture.texture.width, -renderTexture.texture.height},
              (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() },
              (Vector2){ 0, 0 },
              0,
              WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
