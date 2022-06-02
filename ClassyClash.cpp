#include "raylib.h"
#include "raymath.h"
#include "external/glfw/include/GLFW/glfw3.h"

static const Vector2 windowDimensions{384, 384};
static const char* window_title = "Classy Clasher";
static const Color backgroundColor = BLACK;

int main()
{
    InitWindow(windowDimensions.x, windowDimensions.y, window_title);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("Resources/nature_tileset/WorldMap.png");
    Vector2 mapPos {0.0f, 0.0f};
    float speed{4};

    Texture2D knight = LoadTexture("Resources/characters/knight_idle_spritesheet.png");
    Vector2 knightPos
    {
        ((float)windowDimensions.x/2.0f) - (4.0f * (0.5f * (float)knight.width / 6.0f)),
        ((float)windowDimensions.y/2.0f) - (4.0f * (0.5f * (float)knight.height)) 
    };
    Rectangle knightDest 
    {
        knightPos.x,
        knightPos.y,
        (float)knight.width/6.0f*4.0f,
        (float)knight.height*4.0f
    };
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(backgroundColor);
            
            Vector2 direction {0.0, 0.0};
            if (IsKeyDown(KEY_A)) direction.x -= 1.0;
            if (IsKeyDown(KEY_D)) direction.x += 1.0;
            if (IsKeyDown(KEY_W)) direction.y -= 1.0;
            if (IsKeyDown(KEY_S)) direction.y += 1.0;
            if(Vector2Length(direction) != 0.0)
            {
                direction = Vector2Scale(Vector2Normalize(direction), speed);
                mapPos = Vector2Subtract(mapPos, direction);
            }
            DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);
            Rectangle knightSouce 
            {
                0.0f,
                0.0f,
                (float)knight.width/6.0f,
                (float)knight.height
            };
            DrawTexturePro(knight, knightSouce, knightDest, Vector2{}, 0.0f, WHITE);
        EndDrawing();
        glFinish();
    }
    UnloadTexture(map);
    UnloadTexture(knight);
    CloseWindow();
    return 0;
}