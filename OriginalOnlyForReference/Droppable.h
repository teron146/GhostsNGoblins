#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;
class Droppable
{
public:
	Droppable();
	~Droppable();
	void setSkin(string, int, int, int, int);
	sf::Sprite* getSkin();
	void setDropType(int);
	int getDropType();
	sf::Clock getDropTime();
private:
	Sprite skin;
	sf::Texture texture;
	sf::Clock dropTime;
	int type=0;
};

