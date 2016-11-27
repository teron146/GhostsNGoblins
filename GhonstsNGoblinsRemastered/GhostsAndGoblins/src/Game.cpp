#include "Game.h"


Game::Game()
{
    FPS_m = 60;
    screenDimensions.x = 800;
    screenDimensions.y = 800;
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Ghosts N' Goblins");
    window.setFramerateLimit(FPS_m);
    stateManager.push_State(new SplashScreenState);
}

Game::Game(int FPS = 60, int screenHeight = 800, int screenWidth = 800)
{
    FPS_m = FPS;
    screenDimensions.x = screenHeight;
    screenDimensions.y = screenWidth;
    window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Ghosts N' Goblins");
    //window.setFramerateLimit(FPS_m);
}

Game::~Game()
{
    //dtor
}

void Game::loop()
{

    while(window.isOpen())
    {
        //Checks for any events that occur while the window is open
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            stateManager.processEvents(window, event);
        }
        stateManager.process(window);
        window.clear();
        stateManager.draw(window);
        window.display();
    }
}







