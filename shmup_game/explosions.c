#ifndef EXPLOSIONS
#define EXPLOSIONS
#include "engine/simple_2d_animation.c"

Simple2DAnimation explosions[100] = {};

Texture2D LoadExplosionTexture()
{
  Image explosionImage = LoadImage("assets/purple_explosion.png");
  Texture2D explosionTexture = LoadTextureFromImage(explosionImage);
  return explosionTexture;
}

void InitializeExplosions()
{
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
}


void UpdateExplosions(Texture2D explosionTexture)
{
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
}

void SetExplosionAt(Vector2 position, Vector2 targetSize)
{
   for (int j = 0; j < 100; j++) {
     Simple2DAnimation* explosion = &explosions[j];
     if (explosion->position.x == -1 && explosion->position.y == -1) {
       explosion->position.x = position.x + targetSize.x / 2 - explosion->size.x / 2;
       explosion->position.y = position.y + targetSize.y / 2 - explosion->size.y / 2;
       break;
     }
   }
}
#endif
