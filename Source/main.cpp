#include "Game.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();

    GameManager game;

    ResourceManager::LoadResources();       // I load all the resources here before game starts

    game.CurrentScreen = GameScreen::TITLE;

    // I spawn the snake and the food before the game window starts because i want snake and food to be there and food will update as it gets eaten
    game.levelref.spawnsnake();
    game.levelref.spawnfood();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch(game.CurrentScreen)
        {
        case(GameScreen::TITLE):
        {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Lazy Snake", screenWidth/2 - 160, screenHeight/2 - 200, 60, GREEN);

            DrawText("Press 'X' to start Game", screenWidth/2 - 220, screenHeight/2, 40, ORANGE);

            EndDrawing();
            if (IsKeyPressed(KEY_X))
            {
                game.CurrentScreen = GameScreen::GAMESCREEN;
            }

        }
        break;

        case(GameScreen::GAMESCREEN):
        {
            BeginDrawing();
            ClearBackground(ORANGE);


            game.levelref.update();

            EndDrawing();

            // these functions checks different condition happens in game and change screens 
            if(game.levelref.score == 8000)
            {
                game.CurrentScreen = GameScreen::WINSCREEN;
            }
            if (game.levelref.gameover == true)
            {
                game.CurrentScreen = GameScreen::GAMEOVER;
            }
            if (IsKeyPressed(KEY_R))
            {
                game.levelref.ResetGame();
            }
        }
        break;

        case(GameScreen::WINSCREEN):
        {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawText("YAY! YOU WON", screenWidth / 2 - 180, screenHeight / 2 - 200, 60, YELLOW);

            DrawText(TextFormat("Score: %i", game.levelref.score), screenWidth / 2 - 125, screenHeight / 2 - 80, 60, BLUE);

            DrawText("Press 'SPACE' for TITLE Screen", screenWidth / 2 - 280, screenHeight / 2 + 40, 35, GREEN);

            if (IsKeyPressed(KEY_SPACE))
            {
                game.CurrentScreen = GameScreen::TITLE;
                game.levelref.ResetGame();
            }
        }
        break;

        case(GameScreen::GAMEOVER):
        {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawText("GAME OVER!", screenWidth / 2 - 180, screenHeight / 2 - 200, 60, YELLOW);

            DrawText(TextFormat("Score: %i", game.levelref.score), screenWidth / 2 - 125, screenHeight / 2 - 80, 60, BLUE);

            DrawText("Press 'SPACE' for TITLE Screen", screenWidth / 2 - 280, screenHeight / 2 + 40 , 35, GREEN);

            if (IsKeyPressed(KEY_SPACE))
            {
                game.CurrentScreen = GameScreen::TITLE;
                game.levelref.ResetGame();
            }

            

            EndDrawing();
        }
        break;
        }
       
    }

    // I unload everything here So I don't leak memory
    ResourceManager::UnloadResources();

    CloseAudioDevice();

    // De-Initialization
    CloseWindow();

    return 0;
}