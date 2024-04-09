#include "simple_2d_animation.h"

Simple2DAnimation CreateSimple2DAnimation(
  Vector2 position,
  Vector2 size,
  Vector2 textureSize,
  float frameTime,
  int frames,
  bool loop)
{
  Simple2DAnimation animation = (Simple2DAnimation){
    position,
    size,
    0,
    0,
    frameTime,
    frames,
    false,
    loop,
    (Rectangle){0, 0, textureSize.x / frames, textureSize.y},
  };
  return animation;
}

void UpdateSimple2DAnimation(Simple2DAnimation* animation)
{
  if (animation->finished) {
    return;
  }
  animation->currentTime += GetFrameTime();
  if (animation->currentTime >= animation->frameTime) {
    animation->currentTime = 0;
    animation->currentFrame++;
    if (animation->currentFrame >= animation->frames) {
      animation->currentFrame = 0;
      if (!animation->loop) {
        animation->finished = true;
      }
    }
    animation->rect.x = animation->currentFrame * animation->size.x;
  }
}

void DrawSimple2DAnimation(Simple2DAnimation animation, Texture2D texture)
{
  DrawTextureRec(texture, animation.rect, animation.position, WHITE);
}