#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include<vector>
#include<SFML/Graphics.hpp>

class InputManager
{
    public:
        InputManager();
        ~InputManager();
        void update(sf::Event);
        bool keyPressed(sf::Keyboard::Key);
        bool keyPressed(std::vector< sf::Keyboard::Key >&);
        bool keyReleased(sf::Keyboard::Key);
        bool keyReleased(std::vector< sf::Keyboard::Key >&);
        bool keyDown(sf::Keyboard::Key);
        bool keyDown(std::vector< sf::Keyboard::Key >&);

    private:
        sf::Event event_m;
};

#endif // INPUTMANAGER_H
