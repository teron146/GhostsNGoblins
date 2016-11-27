#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseState.h>


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
        bool collide(Entity&);
        sf::Vector2<float> cameraPosition;
        void handlePlayer(Entity&);
        void gravity(Entity&);
};

#endif // GAMESTATE_H
