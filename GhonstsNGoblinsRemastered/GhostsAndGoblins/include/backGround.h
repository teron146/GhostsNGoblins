#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Entity.h>

class backGround : public Entity
{
    public:
        backGround(float, float, float = 0, float = 0);
        ~backGround();
        sf::RectangleShape& draw();
        sf::Sound& sound();
    private:
};

#endif // BACKGROUND_H
