#include <iostream>
#include <raylib.h>
#include <constants.h>
#include <cstdlib>
#include <string>

float p1_x = 0, p1_y = SCREEN_HEIGHT / 2 - 50;
float p2_x = SCREEN_WIDTH-20, p2_y = SCREEN_HEIGHT / 2 - 50;

float b_dx, b_dy;
float b_x = SCREEN_WIDTH /  2 - 10;
float b_y = SCREEN_HEIGHT / 2 - 10;

int player_1_score = 0, player_2_score = 0;

int main()
{
    std::cout<<"Hello World";

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong!");
    SetTargetFPS(60);

    // Init Players
    Rectangle p1 = {0, 0, 20, 100};
    Rectangle p2 = {SCREEN_WIDTH - 20, 0, 20, 100};

    b_dx = GetRandomValue(0,1) == 1 ? 100 : -100;
    b_dy = GetRandomValue(-50,50);

    while(!WindowShouldClose())
    {
        if(IsKeyDown(KEY_UP))
        {
            p2_y -= 100 * GetFrameTime();

            // std::cout<<"P1"<<p1.y<<" ";
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            p2_y += 100 * GetFrameTime();
        }

        if(IsKeyDown(KEY_W))
        {
            p1_y -= 100 * GetFrameTime();
        }
        else if(IsKeyDown(KEY_S))
        {
            p1_y += 100 * GetFrameTime();
        }

        b_x += b_dx * GetFrameTime();
        b_y += b_dy * GetFrameTime();

        // Collision Check Paddles
        if(b_x < p1_x + 20 && b_y > p1_y && b_y < p1_y + 100)
        {
            b_dx = -b_dx * 1.2;
            b_dy = -GetRandomValue(10,150);
        }
        else if(b_x > p2_x - 20 && b_y > p2_y && b_y < p2_y + 100)
        {
            b_dx = -b_dx * 1.2;
            b_dy = GetRandomValue(100,150);
        }

        // Check Collision Up/Down Walls

        if(b_y < 0)
        {
            b_dy = -b_dy;
        }
        else if(b_y+20 > SCREEN_HEIGHT)
        {
            b_dy = -b_dy;
        }

        // Check Win Condition
        if(b_x < 0 && (b_y < p1_y || b_y > p1_y + 100))
        {
            std::cout<<"OUT";
            player_1_score++;
            b_x = SCREEN_WIDTH /  2 - 10;
            b_y = SCREEN_HEIGHT / 2 - 10;
            b_dx = 100;
            b_dy = GetRandomValue(-50,50);

        }
        else if(b_x > SCREEN_WIDTH + 20 && (b_y < p2_y || b_y > p2_y + 100))
        {
            player_2_score++;
            b_x = SCREEN_WIDTH /  2 - 10;
            b_y = SCREEN_HEIGHT / 2 - 10;
            b_dx = -100;
            b_dy = GetRandomValue(-50,50);
        }

        BeginDrawing();
        Vector2 v = {1.0f,9.0f};
        ClearBackground(BLACK);
        DrawText(std::to_string(GetFPS()).c_str(),0,0,20,WHITE);
        DrawText("Pong", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, WHITE);
        DrawText(std::to_string(player_1_score).c_str(), SCREEN_WIDTH - 100, SCREEN_HEIGHT / 2, 30, WHITE);
        DrawText(std::to_string(player_2_score).c_str(), 100, SCREEN_HEIGHT / 2, 30, WHITE);
        DrawLine(0, 1, SCREEN_WIDTH, 1,WHITE);
        DrawLine(0, SCREEN_HEIGHT-1, SCREEN_WIDTH, SCREEN_HEIGHT-1,WHITE);

        // DrawRectangleRec(p1, BEIGE);
        // DrawRectangleRec(p2, BEIGE);
        DrawRectangle(b_x,b_y, 20, 20, BLUE);
        DrawRectangle(p1_x, p1_y, 20, 100, BEIGE);
        DrawRectangle(p2_x, p2_y, 20, 100, BEIGE);


        EndDrawing();
    }

    CloseWindow();    

    return 0;
}