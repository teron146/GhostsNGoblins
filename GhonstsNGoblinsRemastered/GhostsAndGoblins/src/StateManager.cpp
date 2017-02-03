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
    if(states.back()->switchTrue())
    {
        if(states.back()->nextState() == "SplashScreenState")
        {
            this->pop_State();
            this->push_State(new SplashScreenState);
        }
        else if(states.back()->nextState() == "MenuState")
        {
            this->pop_State();
            this->push_State(new MenuState);
        }
        else if(states.back()->nextState() == "GameState")
        {
            this->pop_State();
            this->push_State(new GameState);
        }
    }
}

void StateManager::process(sf::RenderWindow &window)
{
    states.back()->process(window);
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
   delete states.back();
}

void StateManager::unload()
{
    states.back()->unload();
}


