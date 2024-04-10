#ifndef GAME_SPRITE
#define GAME_SPRITE
#include "raylib.h"

Texture2D sprites;

void LoadGameSprite()
{
  Image spritesImage = LoadImage("assets/sprites.png");
  sprites = LoadTextureFromImage(spritesImage);
}

#endif

