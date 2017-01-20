#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class Player : public Entity
{
    public:
        Player(float posX, float posY);
        ~Player();
        void crouch();
        void run(bool right = true);
        void jump(bool = false);
        void idle();
        sf::RectangleShape& draw();
        sf::Sound& sound();
    private:
        bool crouching;
        int jumper;
};

#endif // PLAYER_H
