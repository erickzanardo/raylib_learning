#include "raylib.h"
#include <stdio.h>

typedef struct Simple2DAnimation {
  Vector2 position;
  Vector2 size;
  float currentFrame;
  float currentTime;
  float frameTime;
  int frames;
  bool finished;
  bool loop;
  Rectangle rect;
} Simple2DAnimation;

Simple2DAnimation CreateSimple2DAnimation(
  Vector2 position,
  Vector2 size,
  Vector2 textureSize,
  float frameTime,
  int frames,
  bool loop)
{
  Simple2DAnimation animation = (Simple2DAnimation){
    position,
    size,
    0,
    0,
    frameTime,
    frames,
    false,
    loop,
    (Rectangle){0, 0, textureSize.x / frames, textureSize.y},
  };
  return animation;
}

void UpdateSimple2DAnimation(Simple2DAnimation* animation)
{
  if (animation->finished) {
    return;
  }
  animation->currentTime += GetFrameTime();
  if (animation->currentTime >= animation->frameTime) {
    animation->currentTime = 0;
    animation->currentFrame++;
    if (animation->currentFrame >= animation->frames) {
      animation->currentFrame = 0;
      if (!animation->loop) {
        animation->finished = true;
      }
    }
    animation->rect.x = animation->currentFrame * animation->size.x;
  }
}

void DrawSimple2DAnimation(Simple2DAnimation animation, Texture2D texture)
{
  DrawTextureRec(texture, animation.rect, animation.position, WHITE);
}


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

    Image explosionImage = LoadImage("assets/purple_explosion.png");
    Texture2D explosionTexture = LoadTextureFromImage(explosionImage);

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

    float backgroundOffset = 0;

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture2D renderTexture = LoadRenderTexture(gameWidth, gameHeight);

    Image backgroundImage = LoadImage("assets/background.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);

    Image shotImage = LoadImage("assets/shot.png");
    Texture2D shotTexture = LoadTextureFromImage(shotImage);

    Image enemyImage = LoadImage("assets/enemy.png");
    Texture2D enemyTexture = LoadTextureFromImage(enemyImage);

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
