#ifndef ENEMIES
#define ENEMIES
#include "consts.h"
#include "raylib.h"
#include "explosions.c"
#include "shots.c"


const float enemySpeed = 40.0f;
const float enemyTextureSize = 16;

Vector2 enemies[100] = {};
float enemySpawnTimer = 0;

void InitializeEnemies()
{
  for (int i = 0; i < 100; i++) {
    enemies[i] = (Vector2){ -1, -1 };
  }
}

void UpdateEnemies(Texture2D enemyTexture)
{
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
}

#endif
