#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseState.h>
#include "Player.h"
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
        void collide(Entity&);
        sf::Vector2<float> cameraPosition;
        void PlayerMovement(Entity&);
        void PlayerEvents(Entity&, sf::Event &);
        void gravity(Entity&);
};

#endif // GAMESTATE_H
