#include "backGround.h"

backGround::backGround(float scaleX, float scaleY)
{
    getTexture("./Textures/error.jpg");
    rect.scale(scaleX, scaleY);
    kill = false;
}

backGround::~backGround()
{
    //dtor
}

sf::RectangleShape& backGround::draw()
{
    return rect;
}

sf::Sound& backGround::sound()
{
    return *sounds.back();
}
