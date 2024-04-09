#ifndef SIMPLE_2D_ANIMATION_H
#define SIMPLE_2D_ANIMATION_H

#include "raylib.h"

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
  bool loop);

void UpdateSimple2DAnimation(Simple2DAnimation* animation);

void DrawSimple2DAnimation(Simple2DAnimation animation, Texture2D texture);

#endif
