#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class Player : public Entity
{
    public:
        Player(std::vector<sf::Sprite*>&);
        ~Player();
        void crouch();
        sf::Sprite& draw();
        sf::Sound& sound();
    private:
        bool crouching;
};

#endif // PLAYER_H
