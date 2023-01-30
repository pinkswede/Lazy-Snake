#include "Resources.h"

// I called these because i made them static
Textures ResourceManager::textures;
Sounds ResourceManager::sounds;

// Loading textures and sounds
void ResourceManager::LoadResources()
{
	textures.SnakeHeadUp = LoadTexture("./Resources/Textures/snakeheadup.png");
	textures.SnakeHeadLeft = LoadTexture("./Resources/Textures/snakeheadleft.png");
	textures.SnakeHeadRight = LoadTexture("./Resources/Textures/snakeheadright.png");
	textures.SnakeHeadDown = LoadTexture("./Resources/Textures/snakeheaddown.png");
	textures.SnakeBody = LoadTexture("./Resources/Textures/snakebody.png");
	textures.Food = LoadTexture("./Resources/Textures/food.png");

	sounds.EatFood = LoadSound("./Resources/Sounds/EatingSound.wav");
	sounds.death = LoadSound("./Resources/Sounds/Death.wav");
	sounds.Win = LoadSound("./Resources/Sounds/Win.wav");
}

// unloading textures and sounds
void ResourceManager::UnloadResources()
{
	UnloadTexture(textures.SnakeHeadUp);
	UnloadTexture(textures.SnakeHeadDown);
	UnloadTexture(textures.SnakeHeadLeft);
	UnloadTexture(textures.SnakeHeadRight);
	UnloadTexture(textures.SnakeBody);
	UnloadTexture(textures.Food);

	UnloadSound(sounds.EatFood);
	UnloadSound(sounds.death);
	UnloadSound(sounds.Win);
}