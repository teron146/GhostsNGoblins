#include "Zombie.h"

Zombie::Zombie(float posX, float posY)
{
    spawned = false;
    sf::Vector2f temp;
    temp.x = 100;
    temp.y = 150;
    rect.setSize(temp);
    moveEntity(posX, posY);
    ID.push_back("zombie");
    ID.push_back("enemy");
    //ID.push_back("gravity");
    //ID.push_back("moves");
    currentAnimation = 3;
    //File Grabbing
    getTexture("./Textures/Zombie.png");

    //Animation

    //0
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(3,3), 0.3f, 1 ) );
    animations.at(animations.size() - 1)->ID = "Spawning";

    //1
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(3,3), 0.6f, 0, false ) );
    animations.at(animations.size() - 1)->ID = "walking_Right";

    //2
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(3,3), 0.6f, 0 ) );
    animations.at(animations.size() - 1)->ID = "walking_Left";

    //3
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(3,3), 0.6f, 2 ) );
    animations.at(animations.size() - 1)->ID = "hidden";

}

Zombie::~Zombie()
{
}

void Zombie::spawn(sf::Vector2f playerPos)
{
    if(spawned == true)
    {
        //Does Nothing
    }
    //If the player is within 300 units right or left
    // of the zombie spawn
    else if( abs(playerPos.y - get_Position().y) < 200
       && abs(playerPos.x - get_Position().x) < 300 )
    {
        spawned = true;
        //currentAnimation = 1;
       // rect.setTexture(animations.at(currentAnimation)->texture);
    }
}

void Zombie::movement(sf::Vector2f playerPos)
{
    if(spawned == true)
    {
        if(playerPos.x < get_Position().x)
        {
            comingRight = true;
            currentAnimation = 2;
            rect.setTexture(animations.at(currentAnimation)->texture);
            moveEntity(-5, 0);
        }
        else
        {
            comingRight = false;
            currentAnimation = 1;
            rect.setTexture(animations.at(currentAnimation)->texture);
            moveEntity(5, 0);
        }
    }
}

sf::RectangleShape& Zombie::draw()
{
    deltaTime = clock.restart().asSeconds();
    animations.at(currentAnimation)->update(deltaTime);
    rect.setTextureRect(animations.at(currentAnimation)->uvRect);
    return rect;
}

bool Zombie::fromRight()
{
    return comingRight;
}
