#ifndef BASESTATE_H
#define BASESTATE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "FileManager.h"
#include "Entity.h"
#include "InputManager.h"
#include "backGround.h"


class BaseState
{
    public:
        BaseState();
        ~BaseState();
        //Allows states to stop and switch between each other.
        //Planned to be use to stop GameState and switch to MenuState.
        virtual void pause();
        //Processes keyboard events, handles Entities, DynamicEnvironment,
        //StaticEnvironment, and collisionDetection for every state
        virtual void processEvents(sf::RenderWindow &, sf::Event);
        //Processes game logic not dependent on events
        virtual void process(sf::RenderWindow &);
        //Draws all objects to the window
        virtual void draw(sf::RenderWindow &);
        //Deletes everything that the fileManager has loaded
        bool switchTrue();
        std::string nextState();
        void unload();

    protected:
        bool stateSwitch;
        std::string nextStateS;
        //Contains the address of a text file that includes all the files needed for the state.
        //This string is passed to the FileManager which goes to the text file and grabs all the files
        //that the text file asks for.
        //If the GameState calls on the FileManager it also needs to include a number for the level it needs to load.
        std::string folder;
        //Handles all the input that is detected in the Game class and returns which keys were pressed to the state
        InputManager inputManager;
        std::vector< Entity* > entityVector;



        //The FileManager loads all the files the state needs and stores them then returns the files when the class needs
        //them.
        FileManager files;




};


#endif // BASESTATE_H
