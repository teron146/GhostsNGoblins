#include "stdafx.h"
#include "App.h"
#include "GameState.h"
#include "GameLogic.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window\VideoMode.hpp"
#include <vector>
#include <iostream>
using namespace std;

App::App()
{
}


App::~App()
{
}


//Quits the current app/Deletes running App
//Precondition:An exit code
//Postcondition:none
int quit(int exitCode)
{
	return exitCode;
}


//Sets the rate for the screen refresh
//Precondition:The new refresh rate
//Postcondition:none
void App::setUpdateRate(int refreshTemp)
{
	refreshRate = refreshTemp; 
}


//Returns the current Update Rate
//Precondition:none
//Postcondition:The current refresh rate
int App::getUpdateRate()
{
	return refreshRate;
}


//Returns true/false of wheter the app is running
//Precondition:none
//Postcondition:Bool of whether the app is running
bool App::isRunning()
{
	return running;
}


//Initiates the game loop
//Precondition:none
//Postcondition:none
void App::gameLoop()
{
	srand(time(NULL));
	double screenWidth, screenHeight;
	// Display the list of all the video modes available for fullscreen
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];
		std::cout << "Mode #" << i << ": "
			<< mode.width << "x" << mode.height << " - "
			<< mode.bitsPerPixel << " bpp" << std::endl;
	}

	// Create a window with the same pixel depth as the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window1(sf::VideoMode(modes.at(0).width-15, modes.at(0).height-75, desktop.bitsPerPixel), "Ghost N Goblins");
	window1.setPosition(sf::Vector2i(0, 0));
	screenWidth = modes.at(0).width-15;
	screenHeight = modes.at(0).height-75;

	window1.setFramerateLimit(getUpdateRate());//Set FPS rate
	gameLogic.setScreenHeight(screenHeight);
	gameLogic.setScreenWidth(screenWidth);
	GameState theGameState(timer,false,screenWidth,screenHeight,&window1);

	//GameLoop
	while (window1.isOpen() && theGameState.getGameOver() == 0)
	{
		theGameState.handleEvents(&window1, gameLogic);
		theGameState.draw(&window1);
	}
	window1.close();

}