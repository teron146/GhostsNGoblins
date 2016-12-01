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
        //returns a vector of Sprite pointers from the desired index
        std::vector< sf::Sprite* >* getSprites(int);
        //returns a vector of sound pointers from the desired index
        std::vector< sf::Sound* >* getSounds(int);
        //returns a music pointer from the desired index
        sf::Music* getMusic(int);

        //Beginning revamp of file grabbing
        //Entities themselves will now request needed files
        sf::Texture* getTexture(std::string entity);


    private:
        //Handles loading sprites for load
        //Requires the exact address of the file from the text file called addresses in every sprite folder
        void loadSprites(std::string);
        //Handles loading sounds for load
        //Requires the exact address of the file from the text file called addresses in every sound folder
        void loadSounds(std::string);
        //Handles loading music for load
        //Requires the exact address of the file from the text file called addresses in every folder
        void loadMusic(std::string);
        //reads in files
        std::ifstream ifs;
        //The sprite and sound vectors are multi-dimensional. This is because every entity is going to need sets of sprites and sound. The best way
        //to achieve this is by giving every entity its own vector of sprites or sound. Meaning that several vectors will be required.
        std::vector< std::vector< sf::Sprite* >* > spriteVector;
        std::vector< std::vector< sf::Sound* >* > soundVector;

        //Music contains all the music for a state. It is not multi-dimensional because only the state will need a music vector.
        std::vector< sf::Music* > musicVector;
        std::vector< sf::Texture* > textureVector;
};

#endif // FILEMANAGER_H
