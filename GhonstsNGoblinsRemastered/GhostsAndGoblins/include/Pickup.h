#ifndef PICKUP_H
#define PICKUP_H

#include <Entity.h>


class Pickup : public Entity
{
    public:
        Pickup(float posX, float posY, std::string);
        ~Pickup();
        sf::RectangleShape& draw();
        std::string getType();
    private:
        std::string type;
};

#endif // PICKUP_H
