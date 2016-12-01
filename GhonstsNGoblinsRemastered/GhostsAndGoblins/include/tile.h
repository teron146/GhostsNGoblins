#ifndef TILE_H
#define TILE_H

#include <Entity.h>


class tile : public Entity
{
    public:
        tile(float height = 100, float width = 100, float posX = 0, float posY = 0);
        ~tile();
        sf::RectangleShape& draw();
    protected:

    private:
};

#endif // TILE_H
