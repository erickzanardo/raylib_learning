#ifndef TITLE
#define TITLE
#include "engine/simple_2d_animation.h"
#include "raylib.h"
#include "background.c"
#include "game_state.c"
#include "player.c"
#include "consts.h"

Texture2D bannerTexture;
Vector2 bannerPosition = {0, 0};

void LoadTitle()
{
  Image bannerImage = LoadImage("assets/title/banner.png");
  bannerTexture = LoadTextureFromImage(bannerImage);

  bannerPosition.x = gameWidth / 2.f - bannerTexture.width / 2.f;
  bannerPosition.y = (gameHeight / 2.f - bannerTexture.height / 2.f) - 20;
}

void RunTitle()
{
  UpdateBackground();
  DrawBackground();
  DrawTexture(bannerTexture, bannerPosition.x, bannerPosition.y, WHITE);
  if (IsKeyPressed(KEY_ENTER))
  {
    InitPlayer();
    game_state = GAME;
  }
}

#endif
