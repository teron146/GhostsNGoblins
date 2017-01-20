#include "backGround.h"

backGround::backGround(float scaleX, float scaleY, float posX, float posY)
{
    sf::Vector2f temp;
    temp.x = scaleX;
    temp.y = scaleY;
    getTexture("./Textures/error.jpg");
    rect.setSize(temp);
    rect.setPosition(posX, posY);
    rect.setTexture(&texture.at(0));
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
