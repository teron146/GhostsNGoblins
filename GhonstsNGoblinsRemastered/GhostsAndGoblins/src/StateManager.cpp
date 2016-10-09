#include "StateManager.h"

StateManager::StateManager()
{
    //ctor
}


StateManager::~StateManager()
{
    //dtor
}

void StateManager::load()
{
    states.back()->load();
}

void StateManager::unload( )
{
    states.back()->unload();
}

void StateManager::processEvents(sf::RenderWindow &window, sf::Event event)
{
    states.back()->processEvents( window, event );
}

void StateManager::draw(sf::RenderWindow &window)
{
    states.back()->draw( window );
}

void StateManager::push_State( BaseState &newState )
{
    states.push_back(&newState);
}

void StateManager::pop_State()
{
    states.pop_back();
}


