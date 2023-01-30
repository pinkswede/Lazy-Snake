#include "Entities.h"
#include <vector>
#include "Resources.h"

// storing all main variables and functions
class Level
{
	public:
	std::vector <Entity> Snakes{};

    Vector2i SnakePos[200]{};



	Entity Food;

	int Square_Size = 40;
	int framecounter = 0;

	bool allow_move = true;

	int index = 0;
	int countertail = 1;
	int score = 0;
	bool gameover = false;
	bool addtail = false;

	void movement();
	void spawnsnake();
	void spawnfood();
	void Spawntail(Vector2i pos);
	bool checkcollision(Vector2i posA, int widthA, int heightA, Vector2i posB, int widthB, int heightB);
	void collider();

	void ResetGame();

	void render();
	void update();
};
