#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseState.h>
#include "Player.h"
#include "Zombie.h"
#include "Projectile.h"
#include "tile.h"


class GameState : public BaseState
{
    public:
        GameState(std::string  = "Level_1");
        ~GameState();
        void pause();
        void processEvents(sf::RenderWindow &, sf::Event);
        void process(sf::RenderWindow &);
        void draw(sf::RenderWindow &);
    private:
        sf::Vector2f playerPOS;
        std::vector<Entity *> killList;
        void Cleanup();
        void collide(Entity&);
        void PlayerMovement(Entity&);
        void Zombies(Entity&);
        void PlayerEvents(Entity&, sf::Event &);
        void gravity(Entity&);
        sf::View camera;
};

#endif // GAMESTATE_H
