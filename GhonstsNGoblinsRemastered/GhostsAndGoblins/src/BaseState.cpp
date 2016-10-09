#include "BaseState.h"

BaseState::BaseState()
{
    fileLocation = "empty";
}

void BaseState::pause()
{
}

void BaseState::processEvents(sf::RenderWindow &window, sf::Event event)
{
}

void BaseState::draw(sf::RenderWindow &window)
{
}

void BaseState::load()
{
}

void BaseState::unload()
{
}

BaseState::~BaseState()
{
    //dtor
}
