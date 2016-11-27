#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

sf::Vector2<float> Entity::get_Position(std::string i)
{
    if(i == "current")
        return position_m;
    else
        return oldPosition_m;
}

void Entity::moveEntity(sf::Vector2<float> velocity)
{
    if(!(velocity.x == 0))
            oldPosition_m.x = position_m.x;
    if(!(velocity.y == 0))
            oldPosition_m.y = position_m.y;

    position_m += velocity;
    velocity_m = velocity;
    sprites.at(currentSprite)->setPosition(position_m);
}

void Entity::moveEntity(float x, float y)
{
    if(!(x == 0))
            oldPosition_m.x = position_m.x;
    if(!(y == 0))
            oldPosition_m.y = position_m.y;
    position_m.x += x;
    position_m.y += y;
    velocity_m.x = x;
    velocity_m.y = y;
    sprites.at(currentSprite)->setPosition(position_m);
}

sf::FloatRect Entity::getBoundingBox(std::string i)
{
    if(i == "current")
        return sprites.at(currentSprite)->getGlobalBounds();
    else
    {
        sprites.at(currentSprite)->setPosition(oldPosition_m);
        sf::FloatRect temp = sprites.at(currentSprite)->getGlobalBounds();
        sprites.at(currentSprite)->setPosition(position_m);
        return temp;
    }
}

sf::Vector2<float> Entity::get_Velocity()
{
    return velocity_m;
}

sf::Sprite& Entity::draw()
{
    return *sprites.back();
}

sf::Sound& Entity::sound()
{
    return *sounds.back();
}

bool Entity::isKill()
{
    return kill;
}

std::vector<std::string> Entity::getID()
{
    return ID;
}



