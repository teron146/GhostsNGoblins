#include "SplashScreenState.h"

SplashScreenState::SplashScreenState()
{
    entityVector.push_back(new backGround(800, 800, 0, 0));
    stateSwitch = false;
    c1.restart();


}

SplashScreenState::~SplashScreenState()
{
    //dtor
}

void SplashScreenState::processEvents(sf::RenderWindow &window, sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyPressed(sf::Keyboard::Space))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
    }
}

void SplashScreenState::process(sf::RenderWindow &window)
{

}

void SplashScreenState::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < entityVector.size(); i++)
        window.draw(entityVector.at(i)->draw());
}

//Does nothing in SplashScreenState
void SplashScreenState::pause()
{

}
