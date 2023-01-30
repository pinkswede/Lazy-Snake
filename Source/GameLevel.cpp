#include "GameLevel.h"
#include "myMath.h"

void Level::spawnsnake()
{
    Entity SnakeHead;

    SnakeHead.position = {(GetRenderWidth() / Square_Size),GetRenderHeight()/Square_Size};
    SnakeHead.direction = { 0,Square_Size};
    SnakeHead.speed = 1.f;
    SnakeHead.size = { Square_Size,Square_Size };

    Snakes.push_back(SnakeHead);
}

void Level::spawnfood()
{
    Food.position = { (GetRandomValue(0,(GetRenderWidth() - 40))),(GetRandomValue(0,(GetRenderHeight() - 40))) };
    Food.direction = { 0,0 };
    Food.speed = 0;
    Food.size = { 30,30 };
  
}

void Level::Spawntail(Vector2i pos)
{
    Entity tail;
    
    tail.position = pos;
    tail.direction = {0,0};
    tail.speed = 3;
    tail.size = { 30,30 };

    Snakes.push_back(tail);
    
}


bool Level::checkcollision(Vector2i posA, int widthA, int heightA, Vector2i posB, int widthB, int heightB)
{
    if (posA.x <= posB.x + widthB && posA.x + widthA >= posB.x
        && posA.y <= posB.y + heightB && posA.y + heightA >= posB.y)
    {
        return true;
    }
    else
        return false;
}

//ERROR: when collides goes out of script

void Level::collider()
{
    if (checkcollision(Snakes[0].position, Snakes[0].size.x, Snakes[0].size.x, Food.position, Food.size.x, Food.size.y))
    {
        score += 50;

        Spawntail(Snakes[countertail - 1].position);
        countertail += 1;

        PlaySoundMulti(ResourceManager::sounds.EatFood);

        spawnfood();

       
    }

    for (int b = 2; b < countertail; b++)
    {

        if (Snakes[0].position.x == Snakes[b].position.x && Snakes[0].position.y == Snakes[b].position.y)
        {
            PlaySoundMulti(ResourceManager::sounds.death);
            gameover = true;
        }
    }
   
}

// ERROR

void Level::movement()
{
    if (IsKeyPressed(KEY_UP) && Snakes[0].direction.x != 0 && allow_move)
    {
        Snakes[0].direction = { 0, -(Square_Size)};
        allow_move = false;
    }
    if (IsKeyPressed(KEY_DOWN) && Snakes[0].direction.x != 0 && allow_move)
    {
        Snakes[0].direction = { 0, Square_Size };
        allow_move = false;
    }
    if (IsKeyPressed(KEY_LEFT) && Snakes[0].direction.y != 0 && allow_move)
    {
        Snakes[0].direction = { -(Square_Size), 0};
        allow_move = false;
    }
    if (IsKeyPressed(KEY_RIGHT) && Snakes[0].direction.y != 0 && allow_move)
    {
        Snakes[0].direction = { Square_Size, 0 };
        allow_move = false;
    }

    for (int i = 0; i < countertail; i++)
    {
        SnakePos[i] = Snakes[i].position;
    }

    framecounter++;

    if (SnakePos != 0)
    {
        if (framecounter% 10 == 0)
        {
            for (int i = 0; i < countertail; i++)
            {
                if (i == 0)
                {
                    Snakes[i].position += Snakes[i].direction * (int)Snakes[i].speed;
                    allow_move = true;
                }
                else
                {
                    Snakes[i].position = SnakePos[i - 1];

                }
            }
        }
    }

   
    
   

    if (Snakes[0].position.x > GetRenderWidth() - Square_Size || Snakes[0].position.x <= 0)
    {
        PlaySoundMulti(ResourceManager::sounds.death);
        gameover = true;
    }
    if (Snakes[0].position.y > GetRenderHeight() - Square_Size || Snakes[0].position.y <= 0)
    {
        PlaySoundMulti(ResourceManager::sounds.death);
        gameover = true;
    }
   
}

void Level::render()
{
    DrawText(TextFormat("Score:%i",score), (GetRenderWidth() / 2) - 50, 15, 30, BLUE);
   
    // Food
    DrawRectangle(Food.position.x+ 5, Food.position.y + 5, Food.size.x, Food.size.y, RED);
    DrawTexture(ResourceManager::textures.Food, Food.position.x + 5, Food.position.y + 5, WHITE);

    if (Snakes.size() > 0)
    {
        for (int i = 0; i < countertail; i++)
        {
            if (i == 0)
            {
                if (Snakes[0].direction.y == -(Square_Size))
                {
                    DrawTexture(ResourceManager::textures.SnakeHeadUp, Snakes[0].position.x, Snakes[0].position.y, WHITE);
                }
                if (Snakes[0].direction.y == Square_Size)
                {
                    DrawTexture(ResourceManager::textures.SnakeHeadDown, Snakes[0].position.x, Snakes[0].position.y, WHITE);
                }
                if (Snakes[0].direction.x == Square_Size)
                {
                    DrawTexture(ResourceManager::textures.SnakeHeadRight, Snakes[0].position.x, Snakes[0].position.y, WHITE);
                }
                if (Snakes[0].direction.x == -Square_Size)
                {
                    DrawTexture(ResourceManager::textures.SnakeHeadLeft, Snakes[0].position.x, Snakes[0].position.y, WHITE);
                }
            }
            else
            {
                DrawRectangle(Snakes[i].position.x +5 , Snakes[i].position.y + 5, Snakes[i].size.x, Snakes[i].size.y, DARKGREEN);
                DrawTexture(ResourceManager::textures.SnakeBody, Snakes[i].position.x + 5, Snakes[i].position.y + 5, WHITE);
            }
        }
    }
}

void Level::ResetGame()
{
    Snakes.clear();
    SnakePos[0];
    countertail = 1;
    score = 0;
    framecounter = 0;
    gameover = false;
    
    spawnsnake();
    spawnfood();
}

void Level::update()
{
    int size = sizeof(SnakePos) / sizeof(SnakePos[0]);
    for (int i = 0; i < size; i++)
    {
        SnakePos[i] = Vector2i{ 0,0 };
    }
    collider();
    movement();

    render();
}