#include "raylib.h"
#include "engine/simple_2d_animation.h"
#include "background.c"
#include "explosions.c"
#include "player.c"
#include "shots.c"
#include "enemies.c"
#include "consts.h"
#include "game_state.c"
#include "title.c"
#include <stdio.h>

void RenderGame()
{
  UpdateBackground();
  DrawBackground();

  ControlPlayer(&ship);
  UpdateSimple2DAnimation(&ship);
  DrawSimple2DAnimation(ship, shipTexture);

  UpdateShots();

  UpdateExplosions();


  UpdateEnemies();
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Ray shooter");

    InitializeEnemies();
    InitializeExplosions();
    InitializeShots();

    LoadPlayer();
    LoadTitle();
    LoadBackgroundTexture();
    LoadExplosionTexture();
    LoadShotTexture();
    LoadEnemyTexture();

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture2D renderTexture = LoadRenderTexture(gameWidth, gameHeight);

    while (!WindowShouldClose())
    {
        BeginTextureMode(renderTexture);
            ClearBackground(BLACK);
            if (game_state == GAME)
            {
              RenderGame();
            }
            else
            {
              RunTitle();
            }
        EndTextureMode();


        BeginDrawing();
          DrawTexturePro(
              renderTexture.texture,
              (Rectangle){ 0, 0, renderTexture.texture.width, -renderTexture.texture.height},
              (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() },
              (Vector2){ 0, 0 },
              0,
              WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
