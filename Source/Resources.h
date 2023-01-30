#include "raylib.h"

struct Sounds
{
	Sound EatFood;
	Sound death;
	Sound Win;
};

struct Textures
{
	Texture2D  SnakeHeadRight;
	Texture2D  SnakeHeadLeft;
	Texture2D  SnakeHeadUp;
	Texture2D  SnakeHeadDown;
	Texture2D  Food;

	Texture2D SnakeBody;
};

struct ResourceManager
{
	static Textures textures;
	static Sounds sounds;

	static void LoadResources();
	static void UnloadResources();
};