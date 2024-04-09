#include "raylib.h"
#include "engine/simple_2d_animation.h"
#include "background.c"
#include "explosions.c"
#include <stdio.h>

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 960;

    const int gameWidth = 256;
    const int gameHeight = 240;

    InitWindow(screenWidth, screenHeight, "Ray shooter");

    Image shipImage = LoadImage("assets/ship.png");
    Texture2D shipTexture = LoadTextureFromImage(shipImage);

    Simple2DAnimation ship = CreateSimple2DAnimation(
        (Vector2){100, 100},
        (Vector2){48, 48},
        (Vector2){192, 48},
        0.2,
        4,
        true
    );
    const float shipSpeed = 120.0f;

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

    Texture2D explosionTexture = LoadExplosionTexture();

    Simple2DAnimation explosions[100] = {};
    for (int i = 0; i < 100; i++) {
      explosions[i] = CreateSimple2DAnimation(
          (Vector2){-1, -1},
          (Vector2){32, 32},
          (Vector2){192, 32},
          0.06,
          6,
          false
      );
    }

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture2D renderTexture = LoadRenderTexture(gameWidth, gameHeight);

    Texture2D backgroundTexture = LoadBackgroundTexture();

    Image shotImage = LoadImage("assets/shot.png");
    Texture2D shotTexture = LoadTextureFromImage(shotImage);

    Image enemyImage = LoadImage("assets/enemy.png");
    Texture2D enemyTexture = LoadTextureFromImage(enemyImage);

    while (!WindowShouldClose())
    {
        BeginTextureMode(renderTexture);
            ClearBackground(BLACK);

            UpdateBackground(gameHeight);
            DrawBackground(backgroundTexture);

            if (IsKeyDown(KEY_A)) {
              ship.position.x -= shipSpeed * GetFrameTime();
            } else if (IsKeyDown(KEY_D)) {
              ship.position.x += shipSpeed * GetFrameTime();
            }

            if (IsKeyDown(KEY_W)) {
              ship.position.y -= shipSpeed * GetFrameTime();
            } else if (IsKeyDown(KEY_S)) {
              ship.position.y += shipSpeed * GetFrameTime();
            }

            // Don't allow the ship to go off the screen
            if (ship.position.x < 0) {
              ship.position.x = 0;
            } else if (ship.position.x > gameWidth - ship.size.x) {
              ship.position.x = gameWidth - ship.size.x;
            }

            if (ship.position.y < 0) {
              ship.position.y = 0;
            } else if (ship.position.y > gameHeight - ship.size.y) {
              ship.position.y = gameHeight - ship.size.y;
            }

            if (IsKeyPressed(KEY_SPACE)) {
              for (int i = 0; i < 100; i++) {
                Vector2* shot = &shots[i];
                if (shot->x == -1 && shot->y == -1) {
                  shot->x = ship.position.x + ship.size.x / 2 - shotTextureSize / 2;
                  shot->y = ship.position.y - shotTextureSize;
                  break;
                }
              }
            }

            UpdateSimple2DAnimation(&ship);
            DrawSimple2DAnimation(ship, shipTexture);

            // Handle explosions
            for (int i = 0; i < 100; i++) {
              Simple2DAnimation* explosion = &explosions[i];
              if (explosion->position.x != -1 && explosion->position.y != -1) {
                UpdateSimple2DAnimation(explosion);
                DrawSimple2DAnimation(*explosion, explosionTexture);

                if (explosion->finished) {
                  explosion->position.x = -1;
                  explosion->position.y = -1;
                  explosion->finished = false;
                }
              }
            }

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

                        for (int j = 0; j < 100; j++) {
                          Simple2DAnimation* explosion = &explosions[j];
                          if (explosion->position.x == -1 && explosion->position.y == -1) {
                            explosion->position.x = enemy->x + enemyTextureSize / 2 - explosion->size.x / 2;
                            explosion->position.y = enemy->y + enemyTextureSize / 2 - explosion->size.y / 2;
                            break;
                          }
                        }
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
