#pragma once
#include "SFML\Graphics.hpp"
#include "GameLogic.h"
class App
{
public:
	App();
	~App();
	void setUpdateRate(int);
	int getUpdateRate();
	bool isRunning();
	void gameLoop();
private:
	sf::Clock timer;
	void quit(int);
	bool running;
	int refreshRate = 30;
	GameLogic gameLogic;
};