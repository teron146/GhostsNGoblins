#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::Entity(sf::Time t1, float scaleX, float scaleY, std::vector<sf::Sprite*> &spriteSet)
{
    sprites = spriteSet;
    sprites.back()->scale(scaleX, scaleY);
    eventTime = t1;
    kill = false;
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

sf::Vector2<float> Entity::get_Velocity()
{
    return velocity_m;
}

sf::Sprite& Entity::draw()
{
    if(clock.getElapsedTime().asSeconds() > eventTime.asSeconds())
    {
    int timeDifference = clock.getElapsedTime().asSeconds() - eventTime.asSeconds();
        sf::Color alpha(255,255,255,255 - (timeDifference * 20));
        sprites.back()->setColor(alpha);
    }

    if(clock.getElapsedTime().asSeconds() - eventTime.asSeconds() > sf::seconds(5).asSeconds() )
        kill = true;
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



