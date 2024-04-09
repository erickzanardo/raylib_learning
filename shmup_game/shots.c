#ifndef SHOTS
#define SHOTS
 #include "raylib.h"

const float shotSpeed = 200.0f;
const float shotTextureSize = 16;

Vector2 shots[100] = {};

void InitializeShots()
{
  for (int i = 0; i < 100; i++) {
   shots[i] = (Vector2){ -1, -1 };
  }
}

void UpdateShots(Texture2D shotTexture) {
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
}

void SetShotAt(Vector2 position, Vector2 targetSize) {
  for (int i = 0; i < 100; i++) {
    Vector2* shot = &shots[i];
    if (shot->x == -1 && shot->y == -1) {
      shot->x = position.x + targetSize.x / 2 - shotTextureSize / 2;
      shot->y = position.y - shotTextureSize;
      break;
    }
  }
}
#endif
