#include "stdafx.h"
#include "Droppable.h"
#include <iostream>
#include "SFML\Graphics.hpp"

using namespace std;
using namespace sf;
Droppable::Droppable()
{
}


Droppable::~Droppable()
{
}


//returns the time the drop has exsisted
//post condition: sf::Clock
sf::Clock Droppable::getDropTime()
{
	return dropTime;
}


//set the skin of the drop 
//Precondition: put in the texture file name, and how you want to crop the image
// (where the x starts, where the y starts, and the x and y size of the rectangle)
//Postcondition: none
void Droppable::setSkin(string textureName, int xStart, int yStart, int xSize, int ySize)
{
	if (!texture.loadFromFile(textureName, sf::IntRect(xStart, yStart, xSize, ySize))){ cout << "Failed to load texture for player." << endl; }
	skin.setTexture(texture, true);
	// skin.setTextureRect(sf::IntRect(xStart, yStart, xSize, ySize));
}


//return the skin of the drop
//Precondition: none
//Postcondition: return the sprite of the skin
sf::Sprite* Droppable::getSkin()
{
	return &skin;
}


//set the skin of the player 
//Precondition: put in the texture file name, and how you want to crop the image
// (where the x starts, where the y starts, and the x and y size of the rectangle)
void Droppable::setDropType(int temp)
{
	type = temp;
	switch (type)
	{
	case 1:
		setSkin("Misc.png",38, 42, 14, 12);
		break;
	case 2:
		setSkin("Misc.png", 55, 42, 15, 12);
		break;
	case 3:
		setSkin("Misc.png", 72, 40, 16, 16);
		getSkin()->rotate(45);//To account for rotation in sprite sheet
		break;
	case 4:
		setSkin("Misc.png", 89, 48, 16, 7);
		break;
	case 5:
		setSkin("Misc.png", 111, 41, 12, 16);
		break;
	case 6:
		setSkin("Misc.png", 135, 41, 15, 16);
		break;
	}
}


//return the skin of the player
//Postcondition: return the sprite of the skin
int Droppable::getDropType()
{
	return type;
}