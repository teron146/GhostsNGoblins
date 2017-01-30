#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Entity.h>


class Projectile : public Entity
{
    public:
        Projectile(std::string, sf::Vector2f);
        ~Projectile();
        bool killProjectile();
        sf::RectangleShape& draw();
    private:
        int frameCount;
};

#endif // PROJECTILE_H
