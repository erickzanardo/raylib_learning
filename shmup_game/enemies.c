#ifndef ENEMIES
#define ENEMIES
#include "consts.h"
#include "engine/simple_2d_animation.h"
#include "raylib.h"
#include "explosions.c"
#include "shots.c"


const float enemySpeed = 40.0f;
const float enemyTextureSize = 16;

Vector2 enemies[100] = {};
float enemySpawnTimer = 0;
Texture2D enemyTexture;

void LoadEnemyTexture()
{
  Image enemyImage = LoadImage("assets/enemy.png");
  enemyTexture = LoadTextureFromImage(enemyImage);
}

void InitializeEnemies()
{
  for (int i = 0; i < 100; i++) {
    enemies[i] = (Vector2){ -1, -1 };
  }
}

void ResetEnemy(Vector2* enemy)
{
  enemy->x = -1;
  enemy->y = -1;
}

void UpdateEnemies()
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
        ResetEnemy(enemy);
      } else {
        Rectangle enemyRect = (Rectangle){enemy->x, enemy->y, enemyTextureSize, enemyTextureSize};
        bool hit = false;
        for (int j = 0; j < 100; j++) {
          Simple2DAnimation* shot = &shots[j];
          if (shot->position.x != -1 && shot->position.y != -1) {
            Rectangle shotRect = (Rectangle){
              shot->position.x,
              shot->position.y,
              shot->size.x,
              shot->size.y
            };
            if (CheckCollisionRecs(enemyRect, shotRect)) {

              SetExplosionAt(
                *enemy,
                (Vector2){enemyTextureSize, enemyTextureSize}
              );

              ResetEnemy(enemy);
              ResetShot(shot);

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
