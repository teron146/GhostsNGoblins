#include "tile.h"

tile::tile(std::vector<sf::Sprite*> &spriteSet)
{
    ID.push_back("tile");
    sprites = spriteSet;
    kill = false;
    currentSprite = sprites.size() - 1;
}

tile::~tile()
{
    //dtor
}

sf::Sprite& tile::draw()
{
    sprites.at(currentSprite)->setPosition(position_m);
    return *sprites.at(currentSprite);
}
