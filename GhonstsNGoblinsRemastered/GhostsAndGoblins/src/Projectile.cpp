#include "Projectile.h"

Projectile::Projectile(std::string projectileChoice, sf::Vector2f location)
{
    sf::Vector2f temp;
    temp.x = 30;
    temp.y = 30;
    rect.setSize(temp);
    moveEntity(location.x + 20, location.y + 30);
      if(projectileChoice == "Dagger")
      {

        getTexture("./Textures/Dagger.png");

        rect.setTexture(&texture.at(0));
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
    moveEntity(20, 0);
    frameCount++;
    return rect;
}

bool Projectile::killProjectile()
{
    if(frameCount >= 30)
        return true;
    return false;
}
