#include "Ladder.h"

Ladder::Ladder(float posX , float posY)
{
    sf::Vector2f temp;
    temp.x = 75;
    temp.y = 100;
    rect.setSize(temp);
    moveEntity(posX,posY);
    ID.push_back("ladder");
    getTexture("./Textures/Ladder.png");
    rect.setTexture(&texture.back());
}

Ladder::~Ladder()
{
}

sf::RectangleShape& Ladder::draw()
{
    return rect;
}
