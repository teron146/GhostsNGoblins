#ifndef SPLASHSCREENSTATE_H
#define SPLASHSCREENSTATE_H

#include <BaseState.h>


class SplashScreenState : public BaseState
{
    public:
        //Constructor initializes file directory, keyList, and loads
        SplashScreenState();
        ~SplashScreenState();
        //pause does Nothing in splash screen
        void pause();
        //Checks if any key is pressed. If a key is pressed go to menu state
        void processEvents(sf::RenderWindow &, sf::Event);
        //Draws the background for the splash screen
        void draw(sf::RenderWindow &);

    private:
};

#endif // SPLASHSCREENSTATE_H
