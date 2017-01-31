#ifndef LADDER_H
#define LADDER_H

#include <Entity.h>


class Ladder : public Entity
{
    public:
        Ladder(float height = 100, float width = 100, float posX = 0, float posY = 0);
        ~Ladder();
        sf::RectangleShape& draw();

    protected:

    private:
};

#endif // LADDER_H
