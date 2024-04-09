#ifndef SHOTS
#define SHOTS
#include "engine/simple_2d_animation.h"
#include "raylib.h"

const float shotSpeed = 200.0f;

Texture2D shotTexture;

void LoadShotTexture() {
  Image shotImage = LoadImage("assets/bullets/kinetic.png");
  shotTexture = LoadTextureFromImage(shotImage);
}

Simple2DAnimation shots[100] = {};

void InitializeShots()
{
  for (int i = 0; i < 100; i++) {
    shots[i] = CreateSimple2DAnimation(
        (Vector2){-1, -1},
        (Vector2){16, 16},
        (Vector2){64, 16},
        0.1,
        4,
        true
    );
  }
}

void ResetShot(Simple2DAnimation* shot)
{
  shot->position.x = -1;
  shot->position.y = -1;
}

void UpdateShots() {
  for (int i = 0; i < 100; i++) {
    Simple2DAnimation* shot = &shots[i];
    if (shot->position.x != -1 && shot->position.y != -1) {
      UpdateSimple2DAnimation(shot);
      if (shot->position.y + shot->size.y < 0) {
        ResetShot(shot);
      } else {
        DrawSimple2DAnimation(*shot, shotTexture);
      }
      shot->position.y -= shotSpeed * GetFrameTime();
    }
  }
}

void SetShotAt(Vector2 position, Vector2 targetSize) {
  for (int i = 0; i < 100; i++) {
    Simple2DAnimation* shot = &shots[i];
    if (shot->position.x == -1 && shot->position.y == -1) {
      shot->position.x = position.x + targetSize.x / 2 - shot->size.x / 2;
      shot->position.y = position.y - shot->size.y;
      break;
    }
  }
}
#endif
