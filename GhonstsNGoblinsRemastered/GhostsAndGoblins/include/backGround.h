#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Entity.h>


class backGround : public Entity
{
    public:
        backGround(float, float, std::vector<sf::Sprite*>&);
        ~backGround();
        sf::Sprite& draw();
        sf::Sound& sound();
    private:
};

#endif // BACKGROUND_H
