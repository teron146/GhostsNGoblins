#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class FileManager
{
    public:
        FileManager();
        ~FileManager();
        //Goes to a folder based on the first string and grabs the data their
        //If being called on from the GameState the second string is required to input the level
        void load( std::string, std::string);
        //Deletes anything inside the vectors then
        //Pops back every vector until its size is 0
        void unload();
        //returns a music pointer from the desired index
        sf::Music* getMusic(int);

    private:
        //Handles loading music for load
        //Requires the exact address of the file from the text file called addresses in every folder
        void loadMusic(std::string);
        //reads in files
        std::ifstream ifs;
        //Music contains all the music for a state. It is not multi-dimensional because only the state will need a music vector.
        std::vector< sf::Music* > musicVector;
};

#endif // FILEMANAGER_H
