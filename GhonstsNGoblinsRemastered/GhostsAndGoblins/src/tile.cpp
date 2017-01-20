#include "tile.h"

tile::tile(float height, float width, float posX, float posY)
{
    sf::Vector2f temp;
    temp.x = height;
    temp.y = width;
    rect.setSize(temp);
    moveEntity(posX,posY);
    ID.push_back("tile");

    getTexture("./Textures/Error.jpg");
    rect.setTexture(&texture.back());

    kill = false;
}

tile::~tile()
{
    //dtor
}

sf::RectangleShape& tile::draw()
{
    return rect;
}
