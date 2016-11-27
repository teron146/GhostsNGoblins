#ifndef MENUSTATE_H
#define MENUSTATE_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BaseState.h"

class MenuState : public BaseState
{
    public:
        MenuState();
        ~MenuState();
        void pause();
        void processEvents(sf::RenderWindow &, sf::Event);
        void process(sf::RenderWindow &);
        void draw(sf::RenderWindow &);

    protected:

    private:
};

#endif // MENUSTATE_H
