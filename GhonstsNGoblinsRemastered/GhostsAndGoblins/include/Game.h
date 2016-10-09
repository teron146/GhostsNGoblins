#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "SplashScreenState.h"

//This class runs the game loop.
class Game
{
    public:
        //Default constructor for game. Sets the FPS to 60 and the screen dimensions to 800x800.
        Game();
        //Initializes the FPS, screen height, and width of the game window
        Game(int, int, int);
        ~Game();
        //Runs the game loop which runs every game process
        //The game loop has a fixed time step based on FPS_m
        void loop();

    private:
        int FPS_m;
        sf::RenderWindow window;
        sf::Vector2<int> screenDimensions;
        StateManager stateManager;

};

#endif // GAME_H
