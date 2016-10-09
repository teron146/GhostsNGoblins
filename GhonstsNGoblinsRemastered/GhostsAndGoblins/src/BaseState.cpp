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

void BaseState::draw(sf::RenderWindow &window)
{
}

BaseState::~BaseState()
{
    //dtor
}
