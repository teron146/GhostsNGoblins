#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include <SFML/Graphics.hpp>

Player::Player() : Monster()
{
	name = "arthur.png";
	int height = 30, width = 25;
	double scaleX = 4, scaleY = 4; 
	checkArmor();
	getSkin()->scale(scaleX, scaleY);
	getSkin()->setOrigin(sf::Vector2f(width/2,height));	 
	getSkin()->setPosition(0, 0);
	sf::Vector2f origin = getSkin()->getOrigin();

}

Player::~Player()
{
}