#include "MenuState.h"

MenuState::MenuState()
{
    entityVector.push_back(new backGround(800,800,0,0));
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
    for(int i = 0; i < entityVector.size(); i++)
        window.draw(entityVector.at(i)->draw());
}
