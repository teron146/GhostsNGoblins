#include "stdafx.h"
#include "PowerUp.h"
#include <time.h>

PowerUp::PowerUp(int type)
{
	name = "Misc.png";
	int height = 30, width = 25;
	double scaleX = 4, scaleY = 4; 
	setPowerType(type);
	getSkin()->scale(scaleX, scaleY);
	getSkin()->setOrigin(sf::Vector2f(1, height));
	if (type == 3)
	{
		getSkin()->setOrigin(sf::Vector2f(width / 2, height));
	}

	sf::Vector2f origin = getSkin()->getOrigin();
}


PowerUp::~PowerUp()
{
}


//set the skin (image) of the power up
//precondition: put in a texture and the area to crop
//postcondition: none
void PowerUp::setSkin(string textureName, int xStart, int yStart, int xSize, int ySize)
{
	if (!texture.loadFromFile(textureName, sf::IntRect(xStart, yStart, xSize, ySize))){ cout << "Failed to load texture for powerup." << endl; }
	skin.setTexture(texture);
}

//return the skin of the power up
//precondition: none
//postcondition: return a sprite
sf::Sprite* PowerUp::getSkin()
{
	return &skin;
}


//set the type of power for this power up
//precondition: put in an int (indicating power type)
//postcondition: none
void PowerUp::setPowerType(int type)
{
	enum weapon
	{
		armor = 0 ,flame = 1, axe, spear, dagger, shield,plant
	};
	switch(type)
	{ 
	case armor:
		break;
	case flame:
		setSkin(name, 38, 42, 14, 12);
		break;
	case axe:
		setSkin(name, 55, 42, 15, 12);
		break;
	case spear:
		setSkin(name, 72, 40, 16, 16);
		getSkin()->rotate(45);//To account for rotation in sprite sheet
		break;
	case dagger:
		setSkin(name, 89, 48, 16, 7);
		break;
	case shield:
		setSkin(name, 111, 41, 12, 16);
		break;
	case plant:
		setSkin(name, 149, 22, 8, 8);
		break;
	}
	powerType = type;
}


//return the type of power for this power up
//precondition: none
//postcondition: return the power type (int)
int PowerUp::getPowerType()
{
	return powerType;
}


//return the position on the screen of the power up
//precondition: none
//postcondition: return the position (vector2f)
sf::Vector2f* PowerUp::getPosition()
{
	return &powerPosition;
}


//set the position on the screen of the power up
//precondition: put in the position of the power up (vector2f)
//postcondition: none
void PowerUp::setPosition(sf::Vector2f* position)
{
	powerPosition = *position;
	skin.setPosition(powerPosition);
	return;
}


//set the velocity of the power up
//precondition: put in the velocity of the power up (double)
//postcondition: none
void PowerUp::changeVelocity(sf::Vector2f velocity)
{
	powerVelocity += velocity;
}


//return the velocity of the power up
//precondition: none
//postcondition: return the velocity of the power up (vector2f)
sf::Vector2f PowerUp::getVelocity()
{
	return powerVelocity;
}