#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;
class Box
{
public:
	Box(int xSize, int ySize);
	~Box();
	int getLength();
	int getHeight();
	void setPosition(double, double);
	sf::Vector2f getPosition();
	void setNewSize(int, int);
	sf::Sprite* getShape();
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f);
	void setSkin(string, int, int, int, int);
private:
	sf::Sprite theBox;
	sf::Vector2f velocity;
	sf::Color boxColor;
	sf::Vector2f boxSize;
	sf::Vector2f boxPosition;
	sf::Texture boxTexture;
};