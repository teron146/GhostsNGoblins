#pragma once
#include <iostream>
#include <string>
#include "SFML\Graphics.hpp"
#include "PowerUp.h"

using namespace std;
class Monster
{
public:
	Monster();
	~Monster();
	void setName(string);
	string getName();
	float getLastTimer();
	void setLastTimer(float);
	void setSkin(string, int, int, int, int);
	sf::Sprite* getSkin();
	bool isGrounded();
	void setGrounded(bool);
	int getChaseDirection();
	void setChaseDirection(int);
	void setFlipped(bool);
	sf::Clock animationClock;
	sf::Clock* getMonsterTimer();
	double getHighScore();
	void addToHighScore(double);
	void setDroppable(int);
	int hasDroppable();
	int getFireCount();
	void setFireCount(int);

	int currentAction;
	void move(int, int);
	void jump(double);
	void duck();
	void stand();
	PowerUp* createPowerUp();
	sf::Vector2f attack(PowerUp*);
	bool checkArmor();
	void changeArmor(bool);
	sf::Vector2f getMonsterVelocity();
	void changeVelocity(sf::Vector2f);
	void setYVelocity(float);
	void setXVelocity(float);
	void monsterDirection();
	void setPowerUp(int);
	PowerUp* getPowerUp();
	bool isDucked();
	void setDucked(bool);
	bool isFlipped();
	void setPowerUpType(int);
	int getMonsterPowerUpType();
	void animation(int,float, sf::Clock);
	
	void animations(int);
	sf::Clock deadTime;
	int monsterarmor = 0;
protected:
	string name;
private:
	int powerUpType=3;
	bool ducked = false;
	bool armor = true;
	
	sf::Clock monsterTimer;
	sf::Texture texture;
	sf::Sprite skin;
	bool flipped = false;
	sf::Vector2f monsterPosition;
	sf::Vector2f monsterVelocity;
	PowerUp* powerup;
	float lastTimer=0;
	bool grounded=false;
	int chaseDirection = 0;
	double highScore = 0;
	int fireCounter = 0;
	int droppable = 0;// 0 =no 1= armor 2 = powerup1,3 = powerup2...6=powerup5
};

