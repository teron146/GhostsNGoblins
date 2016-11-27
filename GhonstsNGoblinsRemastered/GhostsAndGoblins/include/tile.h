#ifndef TILE_H
#define TILE_H

#include <Entity.h>


class tile : public Entity
{
    public:
        tile(std::vector<sf::Sprite*> &);
        ~tile();
        sf::Sprite& draw();
    protected:

    private:
};

#endif // TILE_H
