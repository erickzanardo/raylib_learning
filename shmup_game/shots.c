#ifndef SHOTS
#define SHOTS
 #include "raylib.h"

const float shotSpeed = 200.0f;
const float shotTextureSize = 16;

Texture2D shotTexture;

void LoadShotTexture() {
    Image shotImage = LoadImage("assets/shot.png");
    shotTexture = LoadTextureFromImage(shotImage);
}

Vector2 shots[100] = {};

void InitializeShots()
{
  for (int i = 0; i < 100; i++) {
   shots[i] = (Vector2){ -1, -1 };
  }
}

void ResetShot(Vector2* shot)
{
  shot->x = -1;
  shot->y = -1;
}

void UpdateShots() {
  for (int i = 0; i < 100; i++) {
    Vector2* shot = &shots[i];
    if (shot->x != -1 && shot->y != -1) {
      shot->y -= shotSpeed * GetFrameTime();
      if (shot->y + shotTextureSize < 0) {
        ResetShot(shot);
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
