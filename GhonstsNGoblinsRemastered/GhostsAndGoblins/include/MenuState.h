#ifndef MENUSTATE_H
#define MENUSTATE_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MenuState
{
    public:
        MenuState();
        void processEvents(sf::RenderWindow &, sf::Event);
        ~MenuState();

    protected:

    private:
};

#endif // MENUSTATE_H
