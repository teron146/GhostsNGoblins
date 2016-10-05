#include "stdafx.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>


Box::Box(int xSize, int ySize)
{
	setNewSize(xSize, ySize);
	theBox.setPosition(boxPosition);
	velocity = sf::Vector2f(0, 0);
}


Box::~Box()
{
}


//Returns the rectangle shape of the box
//Post condition: sf::RectangleShape
sf::Sprite *Box::getShape()
{
	return &theBox;
}


//Returns the Length of the current Box
//Precondition:None
//Post condition:Returns an Int
int Box::getLength()
{
	return boxSize.x;
}


//Returns the Height of the current Box
//Precondition:None
//Post condition: Returns an Int
int Box::getHeight()
{
	return boxSize.y;
}


//Returns the current Position of the Box relative to the top-left
//Precondition: None
//Post condition: Returns a sf::Vector2f 
sf::Vector2f Box::getPosition()
{
	return boxPosition;
}


//Set the new size of the box
//Precondition:Length,Height
//Post condition: None
void Box::setNewSize(int length, int height)
{
	boxSize.x = length;
	boxSize.y = height;
	return;
}


//set the new velocity of the box
//precondition: velocity
//postcondition: none
void Box::setVelocity(sf::Vector2f input)
{
	velocity = input;
	return;
}


//return the velocity of the box
//precondition: none
//postcondition: box velocity
sf::Vector2f Box::getVelocity()
{
	return velocity;
}


//set the new position of the box
//precondition: xPos and yPos
//postcondition: none
void Box::setPosition(double xPos, double yPos)
{
	theBox.setPosition(xPos, yPos);
	return;
}


//set the skin of the box
//precondition: a sprite and some cropping numbers
//postcondition: none
void Box::setSkin(string textureName, int xStart, int yStart, int xSize, int ySize)
{
	boxTexture.loadFromFile(textureName, sf::IntRect(xStart, yStart, xSize, ySize));
	boxTexture.setRepeated(true);
	theBox.setTexture(boxTexture);
	theBox.setTextureRect(sf::IntRect(boxPosition.x / 1, boxPosition.y / 1, boxSize.x, boxSize.y));
}