#ifndef LADDER_H
#define LADDER_H

#include <Entity.h>


class Ladder : public Entity
{
    public:
        Ladder(float posX = 0, float posY = 0);
        ~Ladder();
        sf::RectangleShape& draw();

    protected:

    private:
};

#endif // LADDER_H
