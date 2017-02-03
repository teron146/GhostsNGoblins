#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <Entity.h>
#include <Animation.h>
#include <Math.h>

class Zombie : public Entity
{
    public:
        Zombie(float, float);
        ~Zombie();
        //Checks if the player is near the zombie
        //if so come out of the ground and attack
        void spawn(sf::Vector2f);
        void movement(sf::Vector2f);
        sf::RectangleShape& draw();
        bool fromRight();
    private:
        bool spawned;
        sf::Clock spawning;
};

#endif // ZOMBIE_H
