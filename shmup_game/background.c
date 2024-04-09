#include "raylib.h"
float backgroundOffset = 0;
const float backgroundSpeed = 40.0f;

Texture2D LoadBackgroundTexture() {
    Image backgroundImage = LoadImage("assets/background.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    return backgroundTexture;
}

void UpdateBackground(float gameHeight)
{
    backgroundOffset += backgroundSpeed * GetFrameTime();
    if (backgroundOffset >= gameHeight) {
        backgroundOffset = 0;
    }
}

void DrawBackground(Texture2D backgroundTexture)
{
    DrawTexture(backgroundTexture, 0, backgroundOffset, WHITE);
    DrawTexture(backgroundTexture, 0, backgroundOffset - backgroundTexture.height, WHITE);
}

