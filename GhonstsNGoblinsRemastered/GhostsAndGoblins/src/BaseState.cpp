#include "BaseState.h"

BaseState::BaseState()
{
    folder = "empty";
}

void BaseState::pause()
{
}

void BaseState::processEvents(sf::RenderWindow &window, sf::Event event)
{
}

void BaseState::process(sf::RenderWindow &window)
{
}

void BaseState::draw(sf::RenderWindow &window)
{
}

void BaseState::unload()
{
    files.unload();
}

bool BaseState::switchTrue()
{
    if(stateSwitch)
        return true;
    else
        return false;
}

std::string BaseState::nextState()
{
    return nextStateS;
}

BaseState::~BaseState()
{
    //dtor
}
