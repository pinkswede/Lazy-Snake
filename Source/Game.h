#include"GameLevel.h"

// declaration of the different screens
enum struct GameScreen
{
	TITLE = 0,
	GAMESCREEN,
	WINSCREEN,
	GAMEOVER,
};

//game manager which handles the game
struct GameManager
{
	GameScreen CurrentScreen{};
	Level levelref;
};
