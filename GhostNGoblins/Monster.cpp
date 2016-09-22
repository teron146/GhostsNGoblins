#include "stdafx.h"
#include "Monster.h"
#include "PowerUp.h"
#include <SFML/Graphics.hpp>

using namespace std;

Monster::Monster()
{
	setPowerUp(powerUpType);
}


Monster::~Monster()
{
	delete powerup;//Free up the powerup pointer
}


//set the fire count of monster
//Pre condition int
void Monster::setFireCount(int temp)
{
	fireCounter+= temp;
}


//Return the fire count of  the monster
// Post condition :int
int Monster::getFireCount()
{
	return fireCounter;
}


//set the droppable of the monster
//pre condition : int
void Monster::setDroppable(int temp)
{
	droppable = temp;
}


//Return if/what the monster has a droppable powerup
//post condiiton : int
int Monster::hasDroppable()
{
	return droppable;
}

//set the high score of the game
//Precondition: put in a double
//Postcondition: none
void Monster::addToHighScore(double newScore)
{
	highScore += newScore;
	return;
}


//get the high score of the game and return it
//Precondition: none
//Postcondition: return the double of the high score
double Monster::getHighScore()
{
	return highScore;
}


//set the name of the player with the user given string
//Precondition: put in a string
//Postcondition: none
void Monster::setName(string inputName)
{
	name = inputName;
	if (name == "golem")
	{
		monsterarmor = 9;
	}
	else if (name == "flying knight")
	{
		monsterarmor = 0;
	}
	else if (name == "arremer")
	{
		monsterarmor = 3;
	}
	else if (name == "satan")
	{
		monsterarmor = 5;
	}
	else if (name == "unicorn")
	{
		monsterarmor = 10;
	}
	else if (name == "astaroth")
	{
		monsterarmor = 10;
	}
	return;
}


//return the name of the player
//Precondition: none
//Postcondition: return a string of the name
string Monster::getName()
{
	return name;
}


//Get the monster clock
//Postcondition::sf::Clock*
sf::Clock* Monster::getMonsterTimer()
{
	return &monsterTimer;
}


//set the skin of the player 
//Precondition: put in the texture file name, and how you want to crop the image
// (where the x starts, where the y starts, and the x and y size of the rectangle)
//Postcondition: none
void Monster::setSkin(string textureName, int xStart, int yStart, int xSize, int ySize)
{
	if (!texture.loadFromFile(textureName, sf::IntRect(xStart, yStart, xSize, ySize))){ cout << "Failed to load texture for player." << endl; }
	skin.setTexture(texture, true);
	// skin.setTextureRect(sf::IntRect(xStart, yStart, xSize, ySize));
}


//return the skin of the player
//Precondition: none
//Postcondition: return the sprite of the skin
sf::Sprite* Monster::getSkin()
{
	return &skin;
}

//Makes the Player Jump!
void Monster::jump(double height)
{
	//Is Player touching the ground jump
	//cout << monsterVelocity.y << endl;
	if (grounded==true)
	{
		grounded = false;
		changeVelocity(sf::Vector2f(0, -50));
		getSkin()->move(0,-1);
	}
}


//If the monster is grounded
//Postcondition: Bool
bool Monster::isGrounded()
{
	return grounded;
}


//Change whether the monster is grounded
void Monster::setGrounded(bool temp)
{
	grounded = temp;
}


//Makes the Monster Duck!
//Duck
//Duck
//Goose!
void Monster::duck()
{
	ducked = true;
	float x = 20, y = 20;
	getSkin()->setOrigin(x / 2, y);
	
}



//Makes the Monster Stand
void Monster::stand()
{
	ducked = false;
	float x = 20, y = 30;
	getSkin()->setOrigin(x / 2, y);
}


//Sets the chase direction of the monsters
//Precondition int: 0 = not set 1 = left 2 = right
void Monster::setChaseDirection(int  direction)
{
	chaseDirection = direction;
}


//Returns the chase direction of the monster
//Post condition int: 0 = not set 1 = left 2 = right
int Monster::getChaseDirection()
{
	return chaseDirection;
}


//Returns a NEW powerup
//returns type powerup
PowerUp* Monster::createPowerUp()
{
	return new PowerUp(powerUpType);
}

  
//changes the type of powerup for the monster
//takes in an int, representing  type
void Monster::setPowerUpType(int type)
{
	powerUpType = type;
}


//Returns the type of powerup the monster has
//returns type int
int Monster::getMonsterPowerUpType()
{
	return powerUpType;
}


//Makes the Monster Attack!
sf::Vector2f Monster::attack(PowerUp* weapon)
{
	enum weapons
	{
		flame = 1, axe, spear, dagger, shield , plant
	};
	float projectileDirection = 1, x = 10, y = 0;
	if (isFlipped())
	{
		projectileDirection = -1;
		weapon->getSkin()->scale(-1, 1);
		if (weapon->getPowerType()==spear)
			weapon->getSkin()->rotate(-90);
	}
	else
		projectileDirection = 1;

	x *= 3 * projectileDirection;
	switch (weapon->getPowerType())
	{
	case flame:
		y = -30;
		x *= 1.5;
		break;
	case axe:
		y = -24;
		x *= 2.5;
		break;
	case spear:
		break;
	case dagger:
		x *= 2;
		break;
	case shield:
		x *= .5;
		break;
	case plant:
		x /= 3;
		break;
	}
	return sf::Vector2f(x, y);
}



//Returns the monster's powerup
//returns type powerup
PowerUp* Monster::getPowerUp()
{
	return powerup;
}


//Changes the monster's current powerup
//takes in type of powerup
void Monster::setPowerUp(int type)
{
	powerup = new PowerUp(type);
}


//checks for player armor and changes it if needed
bool Monster::checkArmor()
{
	if (armor == true)
	{
		setSkin("Arthur.png", 5, 40, 20, 30);
	}
	else
	{
		setSkin("Arthur.png", 5, 0, 20, 30);
	}
	return armor;
}


//changes the armor on/off 
//needs a bool/ true=armor on
void Monster::changeArmor(bool toggleArmor)
{
	if (toggleArmor == true)
	{
		armor = true;
	}
	if (toggleArmor == false)
	{
		armor = false;
	}
	checkArmor();
}


//Returns the current velocity of the monster
//Postcondition: double float Vector
sf::Vector2f Monster::getMonsterVelocity()
{
	return monsterVelocity;
}


//Sets the current velocity of the monster realative to the last veloicity
//Preconditioin: double float vector
void Monster::changeVelocity(sf::Vector2f temp)
{
	monsterVelocity.x = monsterVelocity.x + temp.x;
	monsterVelocity.y = monsterVelocity.y + temp.y;
}


//sets the current velocity of the monster completely
//Precondition: double float vector
void Monster::setYVelocity(float temp)
{
	monsterVelocity.y = temp;
}


//sets the current x componet of the velocity of the monster completely
//Precondition: double float vector
void Monster::setXVelocity(float temp)
{
	monsterVelocity.x = temp;
}


//Set if the monster is flipped
//pre condition bool
void Monster::setFlipped(bool temp)
{
	flipped = temp;
}


//Checks and if needed Changes the direction the monster is facing
void Monster::monsterDirection()
{
	if (monsterVelocity.x < 0 && flipped == false)
	{
		flipped = true;
		getSkin()->scale(-1.f, 1.f);
	}
	else if (monsterVelocity.x > 0 && flipped == true)
	{
		flipped = false;
		getSkin()->scale(-1.f, 1.f);
	}
}


//Sets monster duck bool to prevent movement and jumping
//Requires a bool
void Monster::setDucked(bool temp)
{
	ducked = temp;
}


//Returns the true/false for monster ducked
//Returns a bool
bool Monster::isDucked()
{
	return ducked;
}


//returns the whether the flipped boolian
//returns a bool
bool Monster::isFlipped()
{
	return flipped;
}


//Returns the value of the last timer
//returns type float
float Monster::getLastTimer()
{
	return lastTimer;
}


//Changes the last timer
//Takes in a float
void Monster::setLastTimer(float temp)
{
	lastTimer = temp;
}