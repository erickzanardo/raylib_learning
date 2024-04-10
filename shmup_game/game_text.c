#ifndef GAME_TEXT
#define GAME_TEXT

#include "consts.h"
#include "game_sprite.c"
#include "raylib.h"

Vector2 screenCenter;

int getStringSize (char* s) {
    char* t; // first copy the pointer to not change the original
    int size = 0;

    for (t = s; *t != '\0'; t++) {
        size++;
    }

    return size;
}

void LoadGameFont()
{
  screenCenter = (Vector2){gameWidth / 2.f, gameHeight / 2.f};
}

void DrawGameText(
  char* text,
  Vector2 position,
  bool light
)
{
  int stringSize = getStringSize(text);
  int width = stringSize * 8;

  // Dark start at 64
  // Light start at 80

  Vector2 size = (Vector2){width, 8};
  Rectangle rect[stringSize];
  for (int i = 0; i < stringSize; i++) {
    int y = light ? 80 : 64;
    int letterIndex = text[i] - 65;

    if (letterIndex > 13) {
      letterIndex -= 13;
      y += 8;
    }
    rect[i] = (Rectangle){letterIndex * 8, y, 8, 8};
  }

  for (int i = 0; i < stringSize; i++) {
    DrawTextureRec(
      sprites,
      rect[i],
      (Vector2){position.x + i * 8, position.y},
      WHITE
    );
  }
}
#endif
