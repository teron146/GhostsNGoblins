#include "Ladder.h"

Ladder::Ladder(float height, float width, float posX , float posY)
{
    sf::Vector2f temp;
    temp.x = height;
    temp.y = width;
    rect.setSize(temp);
    moveEntity(posX,posY);
    ID.push_back("ladder");
    getTexture("./Textures/Error.jpg");
    rect.setTexture(&texture.back());
}

Ladder::~Ladder()
{
}

sf::RectangleShape& Ladder::draw()
{
    return rect;
}
