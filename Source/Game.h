#include"GameLevel.h"

enum struct GameScreen
{
	TITLE = 0,
	GAMESCREEN,
	WINSCREEN,
	GAMEOVER,
};

struct GameManager
{
	GameScreen CurrentScreen{};
	Level levelref;
};
