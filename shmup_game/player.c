#include "engine/simple_2d_animation.h"
#include "consts.h"
#include "shots.c"

const float shipSpeed = 120.0f;

void ControlPlayer(Simple2DAnimation* ship) {
  if (IsKeyDown(KEY_A)) {
    ship->position.x -= shipSpeed * GetFrameTime();
  } else if (IsKeyDown(KEY_D)) {
    ship->position.x += shipSpeed * GetFrameTime();
  }

  if (IsKeyDown(KEY_W)) {
    ship->position.y -= shipSpeed * GetFrameTime();
  } else if (IsKeyDown(KEY_S)) {
    ship->position.y += shipSpeed * GetFrameTime();
  }

  // Don't allow the ship to go off the screen
  if (ship->position.x < 0) {
    ship->position.x = 0;
  } else if (ship->position.x > gameWidth - ship->size.x) {
    ship->position.x = gameWidth - ship->size.x;
  }

  if (ship->position.y < 0) {
    ship->position.y = 0;
  } else if (ship->position.y > gameHeight - ship->size.y) {
    ship->position.y = gameHeight - ship->size.y;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    SetShotAt(ship->position, ship->size);
  }
}
