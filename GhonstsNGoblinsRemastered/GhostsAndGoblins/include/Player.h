#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <Math.h>


class Player : public Entity
{
    public:
        Player(float posX, float posY);
        ~Player();
        void crouch();
        void run(bool right = true);
        void jump(bool = false);
        void idle();
        void toss(bool = true);
        void changeDirection(bool);
        void climb(bool = true);
        sf::RectangleShape& draw();
        sf::Sound& sound();

    private:
        int jumper, tossing;
};

#endif // PLAYER_H
