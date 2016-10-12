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

bool InputManager::keyPressed(sf::Keyboard::Key key)
{
    if(event_m.key.code == key && sf::Event::KeyPressed)
        return true;
    else
        return false;
}

bool InputManager::keyPressed(std::vector< sf::Keyboard::Key > &keys)
{
    for(int key = 0; key < keys.size(); key++)
    {
        if(event_m.key.code == keys.at(key) && sf::Event::KeyPressed)
            return true;
        else
            return false;
    }
}

bool InputManager::keyReleased(sf::Keyboard::Key key)
{
    if(event_m.key.code == key && sf::Event::KeyReleased)
        return true;
    else
        return false;
}

bool InputManager::keyReleased(std::vector< sf::Keyboard::Key >& keys)
{
    for(int key = 0; key < keys.size(); key++)
    {
        if(event_m.key.code == keys.at(key) && sf::Event::KeyReleased)
            return true;
        else
            return false;
    }
}

bool InputManager::keyDown(sf::Keyboard::Key key)
{
    if(event_m.key.code == key)
        return true;
    else
        return false;
}

bool InputManager::keyDown(std::vector< sf::Keyboard::Key >& keys)
{
    for(int key = 0; key < keys.size(); key++)
    {
        if(event_m.key.code == keys.at(key))
            return true;
        else
            return false;
    }
}

