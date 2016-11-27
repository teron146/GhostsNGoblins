#include "backGround.h"

backGround::backGround(float scaleX, float scaleY, std::vector<sf::Sprite*> &spriteSet)
{
    sprites = spriteSet;
    sprites.back()->scale(scaleX, scaleY);
    kill = false;
}

backGround::~backGround()
{
    //dtor
}

sf::Sprite& backGround::draw()
{
    return *sprites.back();
}

sf::Sound& backGround::sound()
{
    return *sounds.back();
}
