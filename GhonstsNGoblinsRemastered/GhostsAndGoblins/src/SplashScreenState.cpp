#include "SplashScreenState.h"

SplashScreenState::SplashScreenState()
{
    BaseState::folder = "SplashScreen";
    BaseState::files.load(folder, " ");
    BaseState::keyList.push_back(sf::Keyboard::Space);
    BaseState::keyList.push_back(sf::Keyboard::Escape);
    BaseState::files.getMusic(0)->play();
    BaseState::files.getMusic(0)->setLoop(true);

}

SplashScreenState::~SplashScreenState()
{
    //dtor
}

//Work in progress
//Dependencies not yet created
void SplashScreenState::processEvents(sf::RenderWindow &window, sf::Event event)
{

}

void SplashScreenState::draw(sf::RenderWindow &window)
{
    window.draw(*BaseState::files.getSprites(0)->at(0));
}

//Does nothing in SplashScreenState
void SplashScreenState::pause()
{

}
