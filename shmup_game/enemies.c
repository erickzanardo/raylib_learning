#ifndef ENEMIES
#define ENEMIES
#include "consts.h"
#include "engine/simple_2d_animation.h"
#include "raylib.h"
#include "explosions.c"
#include "shots.c"

enum EnemyType {
 THUG_A,
 THUG_B,
 THUG_C
};

typedef struct Enemy {
  Vector2 position;
  Vector2 size;
  enum EnemyType type;
  Rectangle rect;
  Simple2DAnimation thrusterAnimation;
  bool used;
} Enemy;

const float enemySpeed = 40.0f;

Enemy enemies[100] = {};
float enemySpawnTimer = 0;

void InitializeEnemies()
{
  for (int i = 0; i < 100; i++) {
    enemies[i] = (Enemy){
      (Vector2){-1, -1},
      (Vector2){8, 8},
      THUG_A,
      (Rectangle){0, 0, 8, 8},
      CreateSimple2DAnimation(
        (Vector2){0, 0},
        (Vector2){0, 0},
        (Vector2){8, 8},
        0.1,
        4,
        true
      ),
      false
    };
  }

}

void ResetEnemy(Enemy* enemy)
{
  enemy->used = false;
}

Rectangle RectangleFromEnemyType(enum EnemyType type)
{
  switch (type) {
    case THUG_A:
      return (Rectangle){0, 8, 8, 8};
    case THUG_B:
      return (Rectangle){8, 8, 8, 8};
    case THUG_C:
      return (Rectangle){16, 8, 8, 8};
  }
}

void UpdateEnemies()
{
  enemySpawnTimer += GetFrameTime();
  if (enemySpawnTimer > 1) {
    enemySpawnTimer = 0;

    for (int i = 0; i < 100; i++) {
      Enemy* enemy = &enemies[i];
      if (!enemy->used) {
        enemy->position.x = GetRandomValue(0, gameWidth - enemy->size.x);
        enemy->position.y = -enemy->size.y;
        enemy->type = (enum EnemyType)GetRandomValue(0, 2);
        enemy->rect = RectangleFromEnemyType(enemy->type);
        enemy->used = true;
        break;
      }
    }
  }
  for (int i = 0; i < 100; i++) {
    Enemy* enemy = &enemies[i];
    if (enemy->used) {
      enemy->position.y += enemySpeed * GetFrameTime();
      if (enemy->position.y > gameHeight) {
        ResetEnemy(enemy);
      } else {
        Rectangle enemyRect = (Rectangle){
          enemy->position.x,
          enemy->position.y,
          enemy->size.y,
          enemy->size.y
        };
        bool hit = false;
        for (int j = 0; j < 100; j++) {
          Shot* shot = &shots[j];
          if (shot->position.x != -1 && shot->position.y != -1) {
            Rectangle shotRect = (Rectangle){
              shot->position.x,
              shot->position.y,
              shot->size.x,
              shot->size.y
            };
            if (CheckCollisionRecs(enemyRect, shotRect)) {

              SetExplosionAt(
                enemy->position,
                enemy->size,
                ENEMY_EXPLOSION
              );

              ResetEnemy(enemy);
              ResetShot(shot);

              hit = true;
              break;
            }
          }
        }
        if (!hit) {
          UpdateSimple2DAnimation(&enemy->thrusterAnimation);
          enemy->thrusterAnimation.position.x = enemy->position.x + enemy->size.x / 2 - enemy->thrusterAnimation.size.x / 2;
          enemy->thrusterAnimation.position.y = enemy->position.y - enemy->thrusterAnimation.size.y;
          DrawSimple2DAnimation(enemy->thrusterAnimation, sprites);
          DrawTextureRec(sprites, enemy->rect, enemy->position, WHITE);
        }
      }
    }
  }
}

#endif
