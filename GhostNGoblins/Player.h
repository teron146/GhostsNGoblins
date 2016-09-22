#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Monster.h"

using namespace std;
class Player : public Monster
{
public:
	Player();
	void setHighScore(double);
	~Player();
private:
};
