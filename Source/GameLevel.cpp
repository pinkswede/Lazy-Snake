#include "GameLevel.h"
#include "myMath.h"

// function to spawn snake
void Level::spawnsnake()
{
    Entity SnakeHead;

    SnakeHead.position = {(GetRenderWidth() / Square_Size),GetRenderHeight()/Square_Size};
    SnakeHead.direction = { 0,Square_Size};
    SnakeHead.speed = 1.f;
    SnakeHead.size = { Square_Size,Square_Size };

    Snakes.push_back(SnakeHead);
}

// function to spawn food
void Level::spawnfood()
{
    Food.position = { (GetRandomValue(0,(GetRenderWidth() - 40))),(GetRandomValue(0,(GetRenderHeight() - 40))) };
    Food.direction = { 0,0 };
    Food.speed = 0;
    Food.size = { 30,30 };
  
}

// function to spawn tail
void Level::Spawntail(Vector2i pos)
{
    Entity tail;
    
    tail.position = pos;
    tail.direction = {0,0};
    tail.speed = 3;
    tail.size = { 30,30 };

    Snakes.push_back(tail);
    
}

// function to check collision
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

// This function I made So i can handle all the collision in game and output of those collision events
void Level::collider()
{
    // This function is for collision of the food with snake head
    if (checkcollision(Snakes[0].position, Snakes[0].size.x, Snakes[0].size.x, Food.position, Food.size.x, Food.size.y))
    {
        score += 50;

        Spawntail(Snakes[countertail - 1].position);   // It spawns tail by taking the current position of the snakehead
        countertail += 1;

        PlaySoundMulti(ResourceManager::sounds.EatFood);

        spawnfood();                         // Spawn Food

       
    }


    // this function checks the collision of head with part of body
    for (int b = 2; b < countertail; b++)
    {

        if (Snakes[0].position.x == Snakes[b].position.x && Snakes[0].position.y == Snakes[b].position.y)
        {
            PlaySoundMulti(ResourceManager::sounds.death);
            gameover = true;
        }
    }
   
}


// this function I made to handle the movement for the head but as well as the rest of the body of the snake
void Level::movement()
{
    // This part handles the movement direction and changes it with specific key clicks
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

    // This for loop updates the position in snakepos array through the vector of snakes
    for (int i = 0; i < countertail; i++)
    {
        SnakePos[i] = Snakes[i].position;
    }

    // Here I made a framecounter which runs each frame So I can delay the update of position of the snake movement and the snake body won't overlap each other while spawning

    framecounter++;

    if (SnakePos != 0)
    {
        if (framecounter% 10 == 0)
        {
            for (int i = 0; i < countertail; i++)
            {
                if (i == 0)      // for the head
                {
                    Snakes[i].position += Snakes[i].direction * (int)Snakes[i].speed;
                    allow_move = true;
                }
                else        // Rest of the body
                {
                    Snakes[i].position = SnakePos[i - 1];

                }
            }
        }
    }

   
    // This part of the code i made So I can keep checking if it goes out of window which is like virtual wall and it dies
   

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


// Render part of the code drawn everything of the game screen
void Level::render()
{
    DrawText(TextFormat("Score:%i",score), (GetRenderWidth() / 2) - 50, 15, 30, BLUE);
   
    // Food
    DrawTexture(ResourceManager::textures.Food, Food.position.x + 5, Food.position.y + 5, WHITE);

    if (Snakes.size() > 0)
    {
        for (int i = 0; i < countertail; i++)
        {
            // This is bit messy but here i draw different texture as per the direction of the snake movement for better aesthetics
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
            else         // This code is for the rest of the body of snake
            {
              
                DrawTexture(ResourceManager::textures.SnakeBody, Snakes[i].position.x + 5, Snakes[i].position.y + 5, WHITE);
            }
        }
    }
}


// I made a rest game So whenever i want to play game again i can call this function and game will start with everything fresh and from zero
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

// Update function , Here I call all the function which needs to run every frame and i call this function in game loop of main.cpp
void Level::update()
{
    // This for loop i made So at the start of the game it put vector2i position value {0,0} and i will update them as game will run further
    int size = sizeof(SnakePos) / sizeof(SnakePos[0]);
    for (int i = 0; i < size; i++)
    {
        SnakePos[i] = Vector2i{ 0,0 };
    }
    collider();
    movement();

    render();
}