#include "tile.h"

tile::tile(float height, float width, float posX, float posY)
{
    rect.setScale(height, width);
    moveEntity(posX,posY);
    ID.push_back("tile");

    getTexture("./Textures/Error.jpg");
    rect.setTexture(texture.back());

    kill = false;
    currentSprite = sprites.size() - 1;
}

tile::~tile()
{
    //dtor
}

sf::RectangleShape& tile::draw()
{
    return *rect;
}
