#ifndef EXPLOSIONS
#define EXPLOSIONS
#include "engine/simple_2d_animation.c"
#include "game_sprite.c"

enum ExplosionType {
  PLAYER_EXPLOSION,
  ENEMY_EXPLOSION
};

Simple2DAnimation explosions[100] = {};

void InitializeExplosions()
{
  for (int i = 0; i < 100; i++) {
    explosions[i] = CreateSimple2DAnimation(
        (Vector2){-1, -1},
        (Vector2){0, 32},
        (Vector2){8, 8},
        0.1,
        4,
        false
    );
  }
}

void ResetExplosion(Simple2DAnimation* explosion)
{
  explosion->position.x = -1;
  explosion->position.y = -1;
  explosion->finished = false;
}

void UpdateExplosions()
{
  // Handle explosions
  for (int i = 0; i < 100; i++) {
    Simple2DAnimation* explosion = &explosions[i];
    if (explosion->position.x != -1 && explosion->position.y != -1) {
      UpdateSimple2DAnimation(explosion);
      DrawSimple2DAnimation(*explosion, sprites);

      if (explosion->finished) {
        ResetExplosion(explosion);
      }
    }
  }
}

void SetExplosionAt(Vector2 position, Vector2 targetSize, enum ExplosionType type)
{
   for (int j = 0; j < 100; j++) {
     Simple2DAnimation* explosion = &explosions[j];
     if (explosion->position.x == -1 && explosion->position.y == -1) {
       explosion->position.x = position.x + targetSize.x / 2 - explosion->size.x / 2;
       explosion->position.y = position.y + targetSize.y / 2 - explosion->size.y / 2;

       if (type == PLAYER_EXPLOSION) {
         explosion->rect.y = 40;
       } else {
         explosion->rect.y = 32;
       }
       break;
     }
   }
}
#endif
