#include "raylib.h"
#include "engine/simple_2d_animation.h"
#include "background.c"
#include "explosions.c"
#include "player.c"
#include "shots.c"
#include "enemies.c"
#include "consts.h"
#include <stdio.h>

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Ray shooter");

    Image shipImage = LoadImage("assets/ship.png");
    Texture2D shipTexture = LoadTextureFromImage(shipImage);

    Simple2DAnimation ship = CreateSimple2DAnimation(
        (Vector2){100, 100},
        (Vector2){48, 48},
        (Vector2){192, 48},
        0.2,
        4,
        true
    );

    InitializeEnemies();
    InitializeExplosions();
    InitializeShots();
    Texture2D explosionTexture = LoadExplosionTexture();

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture2D renderTexture = LoadRenderTexture(gameWidth, gameHeight);

    Texture2D backgroundTexture = LoadBackgroundTexture();

    Image shotImage = LoadImage("assets/shot.png");
    Texture2D shotTexture = LoadTextureFromImage(shotImage);

    Image enemyImage = LoadImage("assets/enemy.png");
    Texture2D enemyTexture = LoadTextureFromImage(enemyImage);

    while (!WindowShouldClose())
    {
        BeginTextureMode(renderTexture);
            ClearBackground(BLACK);

            UpdateBackground(gameHeight);
            DrawBackground(backgroundTexture);


            ControlPlayer(&ship);
            UpdateSimple2DAnimation(&ship);
            DrawSimple2DAnimation(ship, shipTexture);

            UpdateShots(shotTexture);

            // Handle explosions
            UpdateExplosions(explosionTexture);


            UpdateEnemies(enemyTexture);
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
