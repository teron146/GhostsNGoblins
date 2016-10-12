#include "SplashScreenState.h"

SplashScreenState::SplashScreenState()
{
    BaseState::folder = "SplashScreen";
    BaseState::files.load(folder, " ");
    entityVector.push_back(new Entity(sf::seconds(3), 8, 8, *files.getSprites(0)));
    BaseState::files.getMusic(0)->play();
    BaseState::files.getMusic(0)->setLoop(true);
    stateSwitch = false;
    c1.restart();


}

SplashScreenState::~SplashScreenState()
{
    //dtor
}

//Work in progress
//Dependencies not yet created
void SplashScreenState::processEvents(sf::RenderWindow &window, sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyPressed(sf::Keyboard::Space) || c1.getElapsedTime().asSeconds() >= sf::seconds(10).asSeconds())
    {
        stateSwitch = true;
        nextStateS = "SplashScreenState";
    }
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
