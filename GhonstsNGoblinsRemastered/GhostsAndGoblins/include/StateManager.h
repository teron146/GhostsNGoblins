#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "BaseState.h"

class StateManager
{
    public:
        StateManager();

        //Processes events for the state currently at the top of the stack.
        void processEvents(sf::RenderWindow &, sf::Event);
        //calls on the state at the top of the stack to draw
        void draw(sf::RenderWindow &);
        //Allows you to add a BaseState onto the top of the stack of BaseStates
        void push_State(BaseState *);
        void pop_State();
        //Allows you to pop a BaseState off the top of the stack of BaseStates

        //This vector of BaseStates will allow the programmer to switch between states while maintaining other states.
        //For example if I was in the GameState and paused in order to go to the menu then I could simply push_back() a MenuState then when I unpause
        //I can pop_back() that menu state and continue where I left off in the GameState
        std::vector< BaseState* > states;

        ~StateManager();

    private:

};

        //This vector of BaseStates will allow the programmer to switch between states while maintaining other states.
        //For example if I was in the GameState and paused in order to go to the menu then I could simply push_back() a MenuState then when I unpause
        //I can pop_back() that menu state and continue where I left off in the GameState
       // std::vector< BaseState* > states;

#endif // STATEMANAGER_H
