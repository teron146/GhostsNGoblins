#include "StateManager.h"

StateManager::StateManager()
{
    //ctor
}


StateManager::~StateManager()
{
    //dtor
}

void StateManager::processEvents(sf::RenderWindow &window, sf::Event event)
{
    states.back()->processEvents( window, event );
}

void StateManager::draw(sf::RenderWindow &window)
{
    states.back()->draw( window );
}

void StateManager::push_State( BaseState *newState )
{
    states.push_back(newState);
}

void StateManager::pop_State()
{
   //this->unload();
   states.back()->unload();
    states.pop_back();
}

void StateManager::unload()
{
    states.back()->unload();
}


