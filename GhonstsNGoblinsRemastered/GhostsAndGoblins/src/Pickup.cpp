#include "Pickup.h"

Pickup::Pickup(float posX, float posY, std::string type_)
{
    ID.push_back("pickup");
    sf::Vector2f temp;
    temp.x = 60;
    temp.y = 60;
    rect.setSize(temp);
    moveEntity(posX, posY);
    if(type_ == "armor")
    {
        getTexture("./Textures/ArmorPickup.png");
        rect.setTexture(&texture.at(0));
        type = type_;
    }

}

Pickup::~Pickup()
{
    //dtor
}

sf::RectangleShape& Pickup::draw()
{
    return rect;
}

std::string Pickup::getType()
{
    return type;
}
