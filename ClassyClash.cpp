#include "raylib.h"
#include "raymath.h"
#include "external/glfw/include/GLFW/glfw3.h"
#include "Character.h"
#include "Prop.h"

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
        
        
        // for(auto prop : props)
        // {
        //     prop.Render(player.GetworldPos());
        // }
        for (int i=0; i<2; i++)
        {
            props[i].Render(player.GetworldPos());
        }

        player.tick(GetFrameTime());
        if( player.GetworldPos().x < 0.f ||
            player.GetworldPos().y < 0.f ||
            player.GetworldPos().x + windowDimensions.x > map.width * mapScale ||
            player.GetworldPos().y + windowDimensions.y > map.height * mapScale)
            {
                player.UndoMovement();
            }

        for (int i=0; i<2; i++)
        {
            //props[i].Render(player.GetworldPos());
            bool collision = CheckCollisionRecs(player.GetCollisionRec(), props[i].GetCollisionRec(player.GetworldPos()));
            if(collision)
            {
                player.UndoMovement();
            }
        }
        
        EndDrawing();
        glFinish();
    }
    UnloadTexture(map);
    player.~Character();
    for(auto prop : props) prop.~Prop();
    CloseWindow();
    return 0;
}