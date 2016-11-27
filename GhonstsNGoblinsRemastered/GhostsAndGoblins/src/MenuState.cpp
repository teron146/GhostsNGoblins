#include "MenuState.h"

MenuState::MenuState()
{
    files.load("Menu", " ");
    stateSwitch = false;

}

MenuState::~MenuState()
{
    //dtor
}

void MenuState::pause()
{
}

void MenuState::processEvents(sf::RenderWindow &window, sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "GameState";
    }

}

void MenuState::process(sf::RenderWindow &window)
{
}

void MenuState::draw(sf::RenderWindow &window)
{

}
