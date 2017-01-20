#include "FileManager.h"

FileManager::FileManager()
{
    //ctor
}

FileManager::~FileManager()
{
    //dtor
}

void FileManager::load(std::string folder, std::string level = " ")
{
    //Creates a base location so entering addresses is more efficient
    std::string baseLocation, item, location;
    if(level != " ")
        baseLocation = "./Files/" + folder + "/" + level + "/";
    else
        baseLocation = "./Files/" + folder + "/";


    //Opens the addresses text file for music. This lists the addresses for every music file
    location = baseLocation + "/Music/addresses.txt";
    ifs.open(location.c_str());
    if(ifs.fail())
        std::cout << "failed to open file at " << baseLocation << "Music/addresses.txt" << std::endl;
    //Reads every line of the file until the end
    while(!ifs.eof())
    {
        ifs >> item;
        //load the music from the address stored in item
        loadMusic(item);
    }
    ifs.close();
}

//Loads music based on an address and pushes it onto music vector
void FileManager::loadMusic(std::string address)
{
    musicVector.push_back( new sf::Music );
    musicVector.back()->openFromFile(address);
}

sf::Music* FileManager::getMusic(int index)
{
    return musicVector.at(index);
}

//Deletes anything inside the vectors then
//Pops back every vector until its size is 0
void FileManager::unload()
{
    //Sets i to the size of the vector then decrements by 1 until 0
    for (int i = musicVector.size() - 1; i >= 0; i--)
        delete musicVector.at(i);
    musicVector.resize(0);
}



