#include "raylib.h"
#include "engine/simple_2d_animation.h"
#include "background.c"
#include "explosions.c"
#include "player.c"
#include "shots.c"
#include "consts.h"
#include <stdio.h>

int main(void)
{

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

    const float enemySpeed = 40.0f;
    const float enemyTextureSize = 16;

    float enemySpawnTimer = 0;

    Vector2 enemies[100] = {};
    for (int i = 0; i < 100; i++) {
      enemies[i] = (Vector2){ -1, -1 };
    }

    InitializeExplosions();
    InitializeShots();
    Texture2D explosionTexture = LoadExplosionTexture();

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


            ControlPlayer(&ship);
            UpdateSimple2DAnimation(&ship);
            DrawSimple2DAnimation(ship, shipTexture);

            UpdateShots(shotTexture);

            // Handle explosions
            UpdateExplosions(explosionTexture);


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

                        SetExplosionAt(
                          *enemy,
                          (Vector2){enemyTextureSize, enemyTextureSize}
                        );

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
