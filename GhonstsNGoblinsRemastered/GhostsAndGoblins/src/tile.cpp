#include "tile.h"

tile::tile(float height, float width, float posX, float posY)
{
    sf::Vector2f temp;
    temp.x = height;
    temp.y = width;
    rect.setSize(temp);
    moveEntity(posX,posY);
    ID.push_back("tile");

    if(height < 5000)
        getTexture("./Textures/Grass.png");
    else
        getTexture("./Textures/longGrass.png");
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
