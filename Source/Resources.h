#include "raylib.h"

// organising sounds
struct Sounds
{
	Sound EatFood;
	Sound death;
	Sound Win;
};

// organising textures
struct Textures
{
	Texture2D  SnakeHeadRight;
	Texture2D  SnakeHeadLeft;
	Texture2D  SnakeHeadUp;
	Texture2D  SnakeHeadDown;
	Texture2D  Food;

	Texture2D SnakeBody;
};

// Resource manager
struct ResourceManager
{
	static Textures textures;
	static Sounds sounds;

	static void LoadResources();
	static void UnloadResources();
};