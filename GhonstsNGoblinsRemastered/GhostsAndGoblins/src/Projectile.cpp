#include "Projectile.h"

Projectile::Projectile(std::string projectileChoice, sf::Vector2f location, bool facing)
{
    direction = facing;
    sf::Vector2f temp;
    temp.x = 30;
    temp.y = 30;
    rect.setSize(temp);
    if(projectileChoice == "Dagger")
    {
        getTexture("./Textures/Dagger.png");

        rect.setTexture(&texture.at(0));
    }
    if(direction)
        moveEntity(location.x + 20, location.y + 30);
    else
    {
        moveEntity(location.x , location.y + 30);
        rect.setScale(-1, 1);
    }
    ID.push_back("moves");
    ID.push_back("projectile");

}

Projectile::~Projectile()
{
    //dtor
}

sf::RectangleShape& Projectile::draw()
{
    if(direction)
        moveEntity(15, 0);
    else
        moveEntity(-15, 0);
    frameCount++;
    return rect;
}

bool Projectile::killProjectile()
{
    if(frameCount >= 30)
        return true;
    return false;
}
