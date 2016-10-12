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

    //Opens the addresses text file for sprites. This lists the addresses for every sprite sheet
    location = baseLocation + "/Sprites/addresses.txt";
    ifs.open(location.c_str());
    if(ifs.fail())
        std::cout << "failed to open file at " << baseLocation << "Sprites/addresses.txt" << std::endl;
    //Reads every line of the file until the end
    while(!ifs.eof())
    {
        ifs >> item;
        std::cout << "Address: "<< item << std::endl;
        //load the sprites from the address stored in item
        loadSprites(item);
    }
    ifs.close();

    //SplashScreen does not have any sounds
    if(folder != "SplashScreen")
    {
        //Opens the addresses text file for sounds. This lists the addresses for every sound
        location = baseLocation + "/Sounds/addresses.txt";
        ifs.open(location.c_str());
        if(ifs.fail())
            std::cout << "failed to open file at " << baseLocation << "Sounds/addresses.txt" << std::endl;
        //Reads every line of the file until the end
        while(!ifs.eof())
        {
            ifs >> item;
            //load the sounds from the address stored in item
            loadSounds(item);
        }
        ifs.close();
    }

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

void FileManager::loadSprites(std::string address)
{
    //This is the size of the rectangles on sprite sheets
    std::vector< sf::Rect<int>* > tempRectangle;

    textureVector.push_back( new sf::Texture );
    textureVector.back()->loadFromFile(address);
    spriteVector.push_back( new std::vector< sf::Sprite* > );
    std::cout << spriteVector.size() << std::endl;
    //All sprites will be 100x100 pixels so the for loop chunks the texture into 100x100 blocks
    std::cout << "texture:" << textureVector.back()->getSize().x / 100 << std::endl;
    for(int i = 1; i <= (textureVector.back()->getSize().x / 100); i++)
    {
        spriteVector.back()->push_back(new sf::Sprite);
        tempRectangle.push_back(new sf::Rect<int>(100 * i - 100, 0, 100, 100));
        spriteVector.back()->back()->setTexture(*textureVector.back());
        spriteVector.back()->back()->setTextureRect(*tempRectangle.back());
        tempRectangle.pop_back();
        std::cout << spriteVector.at(0)->size() << std::endl;
    }

}

//Work In Progress
void FileManager::loadSounds(std::string address)
{
    //sf::SoundBuffer tempBuffer;
    //sf::Sound tempSound;
    //tempBuffer.loadFromFile(address);
    //soundVector.push_back( new std::vector< sf::Sound > );
}

//Loads music based on an address and pushes it onto music vector
void FileManager::loadMusic(std::string address)
{
    musicVector.push_back( new sf::Music );
    musicVector.back()->openFromFile(address);
}

std::vector< sf::Sprite* >* FileManager::getSprites(int index)
{
    return spriteVector.at(index);
}

std::vector< sf::Sound* >* FileManager::getSounds(int index)
{
    return soundVector.at(index);
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

    for (int i = textureVector.size() - 1; i >= 0; i--)
        delete textureVector.at(i);
    textureVector.resize(0);

    for (int i = spriteVector.size() - 1; i >= 0; i--)
    {
        for(int e = spriteVector.back()->size() - 1; e >= 0; e--)
            delete spriteVector.at(i)->at(e);
        delete spriteVector.at(i);
    }
    spriteVector.resize(0);

    for (int i = soundVector.size() - 1; i >= 0; i--)
    {
        for(int e = soundVector.back()->size() - 1; e >= 0; e--)
            delete soundVector.at(i)->at(e);
        delete soundVector.at(i);
    }
    soundVector.resize(0);
}



