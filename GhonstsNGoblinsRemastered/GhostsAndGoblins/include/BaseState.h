#ifndef BASESTATE_H
#define BASESTATE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "FileManager.h"


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
        //Draws all objects to the window
        virtual void draw(sf::RenderWindow &);
        //Deletes everything that the fileManager has loaded
        void unload();




    protected:
        //Contains the address of a text file that includes all the files needed for the state.
        //This string is passed to the FileManager which goes to the text file and grabs all the files
        //that the text file asks for.
        //If the GameState calls on the FileManager it also needs to include a number for the level it needs to load.
        std::string folder;

        //Handles all the input that is detected in the Game class and returns which keys were pressed to the state

        //Note:
        //Commented out because currently not created
        //InputManager input;

        //List of keys that the state is looking for input from
        std::vector< sf::Keyboard::Key > keyList;

        //The FileManager loads all the files the state needs and stores them then returns the files when the class needs
        //them.
        FileManager files;




};


#endif // BASESTATE_H
