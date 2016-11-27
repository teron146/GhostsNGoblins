#include "InputManager.h"

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}

void InputManager::update(sf::Event event)
{
    this->event_m = event;
}

//Checks if the keyPressed event occurred on a specific key
//if pressed return true
bool InputManager::keyPressed(sf::Keyboard::Key key)
{
    if(event_m.type == sf::Event::KeyPressed)
    {
        if(event_m.key.code == key)
            return true;
    }
    return false;

}

//Checks if the keyPressed event occurred on several different keys
//If all keys are pressed return true
bool InputManager::keyPressed(std::vector< sf::Keyboard::Key > &keys)
{
    //This counts how many of the keys were pressed
    int tally = 0;
    for(int key = 0; key < keys.size(); key++)
    {
        if(event_m.type == sf::Event::KeyPressed)
        {
            if(event_m.key.code == keys.at(key))
                ++tally;
        }
    }
    if(tally == keys.size())
        return true;
    else
        return false;
}

//Checks if the keyReleased event occurred on a specific key
//if released return true
bool InputManager::keyReleased(sf::Keyboard::Key key)
{
    if(event_m.type == sf::Event::KeyReleased)
    {
        if(event_m.key.code == key)
            return true;
    }
    return false;


}

//Checks if the keyReleased event occurred on a set of keys
//if all keysReleased return true
bool InputManager::keyReleased(std::vector< sf::Keyboard::Key >& keys)
{
    //checks how many of the keys were released
    int tally;
    for(int key = 0; key < keys.size(); key++)
    {
        if(event_m.type == sf::Event::KeyReleased)
        {
            if(event_m.key.code == keys.at(key))
                ++tally;
        }

    }
    if(tally == keys.size())
        return true;
    else
        return false;
}

//Checks if a specific Keyboard key is current pressed down
//different than keyPressed because it tells if something is happening
//currently and not whether or not it has occurred
//if the key is down return true
bool InputManager::keyDown(sf::Keyboard::Key key)
{
     if(sf::Keyboard::isKeyPressed(key))
            return true;
    return false;
}

//Checks if a set of Keyboard keys are currently being held down
//if the keys are all held down return true
bool InputManager::keyDown(std::vector< sf::Keyboard::Key >& keys)
{
    //checks how many of the keys in the set are currently being held down
    int tally = 0;
    for(int key = 0; key < keys.size(); key++)
    {
        if(sf::Keyboard::isKeyPressed(keys.at(key)))
            ++tally;
    }
    if(tally == keys.size())
        return true;
    else
        return false;
}

