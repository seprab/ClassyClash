#include "raylib.h"
#include "raymath.h"
#include "external/glfw/include/GLFW/glfw3.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

static const Vector2 windowDimensions{384, 384};
static const char *window_title = "Classy Clasher";
static const Color backgroundColor = BLACK;

int main()
{
    InitWindow(windowDimensions.x, windowDimensions.y, window_title);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("Resources/nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0f, 0.0f};
    const float mapScale{4.f};
    Character player{windowDimensions.x ,windowDimensions.y};
    Enemy enemies[]
    {
        Enemy{Vector2{}, LoadTexture("Resources/characters/goblin_idle_spritesheet.png"), LoadTexture("Resources/characters/goblin_run_spritesheet.png")},
        Enemy{Vector2{static_cast<float>(map.width), 0.f}, LoadTexture("Resources/characters/slime_idle_spritesheet.png"), LoadTexture("Resources/characters/slime_run_spritesheet.png")},
        Enemy{Vector2{static_cast<float>(map.width), static_cast<float>(map.height)}, LoadTexture("Resources/characters/slime_idle_spritesheet.png"), LoadTexture("Resources/characters/slime_run_spritesheet.png")},
        Enemy{Vector2{0.f, static_cast<float>(map.height)}, LoadTexture("Resources/characters/goblin_idle_spritesheet.png"), LoadTexture("Resources/characters/goblin_run_spritesheet.png")}
    };
    for(auto& enemy : enemies) enemy.SetTarget(&player);
    Prop props[2]
    {
        Prop{LoadTexture("Resources/nature_tileset/Rock.png"), Vector2{350,350}},
        Prop{LoadTexture("Resources/nature_tileset/Log.png"), Vector2{650,650}}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        mapPos = Vector2Scale(player.GetworldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);
        
        for(auto& prop : props) prop.Render(player.GetworldPos());

        if(player.GetAlive())
        {
            std::string playerHealth = "Health: ";
            playerHealth.append(std::to_string(player.GetHealth()), 0, 5);
            DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        else
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            glFinish();
            continue;
        }

        player.Tick(GetFrameTime());
        if( player.GetworldPos().x < 0.f ||
            player.GetworldPos().y < 0.f ||
            player.GetworldPos().x + windowDimensions.x > map.width * mapScale ||
            player.GetworldPos().y + windowDimensions.y > map.height * mapScale)
            {
                player.UndoMovement();
            }

        for(auto& prop : props)
        {
            bool collision = CheckCollisionRecs(player.GetCollisionRec(), prop.GetCollisionRec(player.GetworldPos()));
            if(collision)
            {
                player.UndoMovement();
            }
        }
        for(auto& enemy : enemies) 
        {
            enemy.Tick(GetFrameTime());
            if(IsKeyPressed(KEY_SPACE))
            {
                if (CheckCollisionRecs(enemy.GetCollisionRec(), player.GetSwordCollisionRec()))
                {
                    enemy.SetAlive(false);
                }
            }
        }
        
        EndDrawing();
        glFinish();
    }
    UnloadTexture(map);
    player.~Character();
    for(auto& prop : props) prop.~Prop();
    CloseWindow();
    return 0;
}