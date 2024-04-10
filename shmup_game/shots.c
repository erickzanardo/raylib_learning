#ifndef SHOTS
#define SHOTS
#include "engine/simple_2d_animation.h"
#include "raylib.h"
#include "game_sprite.c"

enum ShotType {
  PLAYER_SHOT,
  ENEMY_SHOT,
};

typedef struct Shot {
  Vector2 position;
  Vector2 size;
  Rectangle rect;
  bool used;
} Shot;

const float shotSpeed = 200.0f;

Shot shots[100] = {};

void InitializeShots()
{
  for (int i = 0; i < 100; i++) {
    shots[i] = (Shot){
        (Vector2){-1, -1},
        (Vector2){8, 8},
        (Rectangle){0, 0, 8, 8},
        false,
    };
  }
}

void ResetShot(Shot* shot)
{
  shot->used = false;
}

void UpdateShots() {
  for (int i = 0; i < 100; i++) {
    Shot* shot = &shots[i];
    if (shot->used) {
      if (shot->position.y + shot->size.y < 0) {
        ResetShot(shot);
      } else {
        DrawTextureRec(sprites, shot->rect, shot->position, WHITE);
      }
      shot->position.y -= shotSpeed * GetFrameTime();
    }
  }
}

void SetShotAt(Vector2 position, Vector2 targetSize, enum ShotType type) {
  for (int i = 0; i < 100; i++) {
    Shot* shot = &shots[i];
    if (!shot->used) {
      shot->used = true;

      Rectangle rect;

      if (type == PLAYER_SHOT) {
        rect = (Rectangle){0, 56, 8, 8};
      } else {
        rect = (Rectangle){0, 48, 8, 8};
      }

      shot->position.x = position.x + targetSize.x / 2 - shot->size.x / 2;
      shot->position.y = position.y - shot->size.y;
      shot->rect = rect;
      break;
    }
  }
}
#endif
