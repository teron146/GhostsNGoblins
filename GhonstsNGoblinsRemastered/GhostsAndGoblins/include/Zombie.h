#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <Entity.h>
#include <Animation.h>
#include <Math.h>

class Zombie
{
    public:
        Zombie(float, float);
        ~Zombie();
        //Checks if the player is near the zombie
        //if so come out of the ground and attack
        spawn(sf::Vector2f);
        movement(sf::Vector2f);
    private:
        bool faceRight;
        bool spawned;
};

#endif // ZOMBIE_H
