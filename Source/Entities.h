#include"raylib.h"
#include"myMath.h"

class Entity
{
public:
    float speed{};
    Vector2i direction;
    Vector2i position;
    Vector2i size = {0,0};
};