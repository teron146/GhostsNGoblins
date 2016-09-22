#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;
class PowerUp
{
public:
	PowerUp(int);
	~PowerUp();
	void setSkin(string, int, int, int, int);
	void setPowerType(int);
	int getPowerType();
	sf::Vector2f* getPosition();
	void setPosition(sf::Vector2f*);
	void changeVelocity(sf::Vector2f);
	sf::Vector2f getVelocity();
	sf::Sprite* getSkin();

private:
	string name;
	sf::Texture texture;
	sf::Sprite skin;
	int powerType;
	sf::Vector2f powerPosition;
	sf::Vector2f powerVelocity;

};