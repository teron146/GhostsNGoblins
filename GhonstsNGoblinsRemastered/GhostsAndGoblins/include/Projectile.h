#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Entity.h>


class Projectile : public Entity
{
    public:
        Projectile(std::string, sf::Vector2f, bool);
        ~Projectile();
        bool killProjectile();
        sf::RectangleShape& draw();
    private:
        bool direction;
        int frameCount;
};

#endif // PROJECTILE_H
