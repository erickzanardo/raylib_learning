#ifndef PLAYER
#define PLAYER
#include "engine/simple_2d_animation.h"
#include "consts.h"
#include "shots.c"
#include "game_state.c"
#include "game_sprite.c"

Vector2 shipPosition = {100, 100};
Vector2 shipSize = {8, 8};
Rectangle shipRect;
Simple2DAnimation thrusterAnimation;

const float shipSpeed = 120.0f;
void InitPlayer()
{
  shipPosition = (Vector2){
    gameWidth / 2.f - shipSize.x / 2,
    gameHeight - 32
  };

  if (shipModel == 0)
  {
    shipRect = (Rectangle){0, 16, 8, 8};
  }
  else
  {
    shipRect = (Rectangle){8, 16, 8, 8};
  }

  thrusterAnimation = CreateSimple2DAnimation(
    (Vector2){0, 0},
    (Vector2){0, 24},
    (Vector2){8, 8},
    0.1,
    4,
    true
  );
}

void RenderPlayer()
{
  DrawTextureRec(sprites, shipRect, shipPosition, WHITE);
  DrawSimple2DAnimation(thrusterAnimation, sprites);
}

void ControlPlayer() {
  if (IsKeyDown(KEY_A)) {
    shipPosition.x -= shipSpeed * GetFrameTime();
  } else if (IsKeyDown(KEY_D)) {
    shipPosition.x += shipSpeed * GetFrameTime();
  }

  if (IsKeyDown(KEY_W)) {
    shipPosition.y -= shipSpeed * GetFrameTime();
  } else if (IsKeyDown(KEY_S)) {
    shipPosition.y += shipSpeed * GetFrameTime();
  }

  // Don't allow the ship to go off the screen
  if (shipPosition.x < 0) {
    shipPosition.x = 0;
  } else if (shipPosition.x > gameWidth - shipSize.x) {
    shipPosition.x = gameWidth - shipSize.x;
  }

  if (shipPosition.y < 0) {
    shipPosition.y = 0;
  } else if (shipPosition.y > gameHeight - shipSize.y) {
    shipPosition.y = gameHeight - shipSize.y;
  }

  UpdateSimple2DAnimation(&thrusterAnimation);

  thrusterAnimation.position.x = shipPosition.x + shipSize.x / 2 - thrusterAnimation.size.x / 2;
  thrusterAnimation.position.y = shipPosition.y + shipSize.y;

  if (IsKeyPressed(KEY_SPACE)) {
    SetShotAt(shipPosition, shipSize, PLAYER_SHOT);
  }
}
#endif
