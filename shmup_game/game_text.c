#ifndef GAME_TEXT
#define GAME_TEXT

#include "consts.h"
#include "raylib.h"

Font gameFont;
Vector2 screenCenter;

void LoadGameFont()
{
  screenCenter = (Vector2){gameWidth / 2.f, gameHeight / 2.f};
  gameFont = LoadFont(
    "assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf"
  );
}

void DrawGameText(
  const char* text,
  Vector2 position,
  int fontSize, Color color
)
{
  Vector2 size = MeasureTextEx(gameFont, text, fontSize, 1);
  DrawTextEx(gameFont, text, position, fontSize, 1, color);
}

void DrawGameTextCentered(
  const char* text,
  int fontSize,
  Color color
)
{
  Vector2 size = MeasureTextEx(gameFont, text, fontSize, 1);
  Vector2 position = {
    (screenCenter.x - size.x) / 2,
    (screenCenter.y - size.y) / 2
  };
  DrawTextEx(gameFont, text, position, fontSize, 1, color);
}

void DrawGameTextHorizontalCentered(
  const char* text,
  int fontSize,
  int y,
  Color color
)
{
  Vector2 size = MeasureTextEx(gameFont, text, fontSize, 1);
  Vector2 position = {
    screenCenter.x - size.x / 2,
    y
  };
  DrawTextEx(gameFont, text, position, fontSize, 1, color);
}

void DrawGameTextVerticalCentered(
  const char* text,
  int fontSize,
  int x,
  Color color
)
{
  Vector2 size = MeasureTextEx(gameFont, text, fontSize, 1);
  Vector2 position = {
    x,
    (screenCenter.y - size.y) / 2
  };
  DrawTextEx(gameFont, text, position, fontSize, 1, color);
}

#endif
