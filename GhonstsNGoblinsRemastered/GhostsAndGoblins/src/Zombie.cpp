#include "Zombie.h"

Zombie::Zombie(float posX, float posY)
{
    sf::Vector2f temp;
    temp.x = 100;
    temp.y = 150;
    rect.setSize(temp);
    rect.setPosition(posX, posY);
    ID.push_back("zombie");
    ID.push_back("enemy");

}

Zombie::~Zombie()
{
}

Zombie::Spawn(sf::Vector2f playerPos)
{
    //If the player is within 300 units right or left
    // of the zombie spawn
    if( abs(playerPos.y - rect.getPosition().y) < 200
       && abs(playerPos.x - rect.getPosition().x) < 300 )
        spawned = true;
}

Zombie::movement(sf::Vector2f playerPos)
{
    if(spawned == true)
    {

    }
}
