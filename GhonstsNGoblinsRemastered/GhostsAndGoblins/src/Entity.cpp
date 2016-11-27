#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

sf::Vector2<float> Entity::get_Position()
{
    return position_m;
}

void Entity::moveEntity(sf::Vector2<float> velocity)
{
    position_m += velocity;
    velocity_m = velocity;
}

void Entity::moveEntity(float x, float y)
{
    position_m.x += x;
    position_m.y += y;
    velocity_m.x = x;
    velocity_m.y = y;
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



