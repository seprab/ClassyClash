#include "raylib.h"
#include "raymath.h"
#include "external/glfw/include/GLFW/glfw3.h"

static const Vector2 windowDimensions{384, 384};
static const char* window_title = "Classy Clasher";
static const Color backgroundColor = BLACK;

class Character
{
public:
    Character();
    ~Character();
private:
};

int main()
{
    InitWindow(windowDimensions.x, windowDimensions.y, window_title);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("Resources/nature_tileset/WorldMap.png");
    Vector2 mapPos {0.0f, 0.0f};
    float speed{4};

    Texture2D knightIdle = LoadTexture("Resources/characters/knight_idle_spritesheet.png");
    Texture2D knightRun = LoadTexture("Resources/characters/knight_run_spritesheet.png");
    Vector2 knightPos
    {
        ((float)windowDimensions.x/2.0f) - (4.0f * (0.5f * (float)knightIdle.width / 6.0f)),
        ((float)windowDimensions.y/2.0f) - (4.0f * (0.5f * (float)knightIdle.height)) 
    };
    Rectangle knightDest 
    {
        knightPos.x,
        knightPos.y,
        (float)knightIdle.width/6.0f*4.0f,
        (float)knightIdle.height*4.0f
    };
    float knightRightLeft{1.f};
    float knightRunningTime{};
    int knightFrame{};
    const int knightMaxFrames{6};
    const float knightUpdateTime{1.f/12.f}; //Update the knightIdle 12 times per frame

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(backgroundColor);
            
            Vector2 direction {0.0, 0.0};
            if (IsKeyDown(KEY_A)) direction.x -= 1.0;
            if (IsKeyDown(KEY_D)) direction.x += 1.0;
            if (IsKeyDown(KEY_W)) direction.y -= 1.0;
            if (IsKeyDown(KEY_S)) direction.y += 1.0;
            
            float directionMagnitude = Vector2Length(direction); 
            if(directionMagnitude != 0.0)
            {
                direction = Vector2Scale(Vector2Normalize(direction), speed);
                mapPos = Vector2Subtract(mapPos, direction);
                knightRightLeft = direction.x<0 ? -1.f : 1.f;
            }
            DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);
            knightRunningTime += GetFrameTime();
            if(knightRunningTime>knightUpdateTime)
            {
                knightFrame++;
                knightRunningTime = 0;
                if(knightFrame>knightMaxFrames) knightFrame = 0;
            }
            Rectangle knightSouce 
            {
                knightFrame * knightRightLeft * (float)knightIdle.width/6.0f,
                0.0f,
                knightRightLeft * (float)knightIdle.width/6.0f,
                (float)knightIdle.height
            };
            DrawTexturePro(directionMagnitude ? knightRun : knightIdle, knightSouce, knightDest, Vector2{}, 0.0f, WHITE);
        EndDrawing();
        glFinish();
    }
    UnloadTexture(map);
    UnloadTexture(knightIdle);
    UnloadTexture(knightRun);
    CloseWindow();
    return 0;
}