#pragma once
#include "Monster.h"
#include "Player.h"
#include "PowerUp.h"
#include "Ladder.h"
#include "Droppable.h"
#include "SFML\Audio.hpp"

using namespace std;
using namespace sf;
class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	void gameLogic(Clock, Event::EventType, Keyboard::Key, vector<PowerUp*>*,
		vector<Monster*>*,vector<Box*>*,vector<Ladder*>*,sf::View*, vector<PowerUp*>*,vector<Music*>*);
	void constantLogic(vector<Monster*>*,vector<PowerUp*>*,vector<Box*>*,vector<Ladder*>,
		sf::View* view, float, vector<Text*>*, vector<Droppable*>*, vector<PowerUp*>*,float);
	void manageDrops(vector<Droppable*>*);
	void checkBoxCollision(vector<Monster*>*, vector<PowerUp*>*, vector<Box*>,vector<Ladder*>, vector<PowerUp*>*);
	void checkIfHit(vector<Monster*>*, vector<PowerUp*>*, vector<Text*>*, vector<Droppable*>*, vector<PowerUp*>*);
	void loadMap(vector<Image*>*, vector<Box*>*, vector<Ladder*>*,double);
	void loadMonsters(double, vector<Monster*>*);
	void checkDroppables(vector<Monster*>*, vector<Droppable*>*);
	bool checkLadders(Monster*, vector<Ladder*>,Keyboard::Key,Event::EventType);
	void animation(Monster*);
	void gravity(std::vector<Monster*>*,vector<PowerUp*>*);
	void applyVelocity(vector<Monster*>*,vector<PowerUp*>*,sf::View*,vector<PowerUp*>*,vector<Box*>*);
	double getScreenHeight();
	void setScreenHeight(double);
	double getScreenWidth();
	void setScreenWidth(double);
	bool onTop(sf::FloatRect&, sf::FloatRect&);
	bool inBox(sf::FloatRect&, sf::FloatRect&);
	void createMonsters(vector<Monster*>*,vector<PowerUp*>*);
	void monstersAttack(vector<Monster*>*,vector<PowerUp*>*);
	void addLives(int);
	int getLifeCounter();
	void nextLevel();
	int getLevel();
	void loadLevel();
	void loseLife();
	void playerDeath(vector<Monster*>*, vector<PowerUp*>*, vector<Text*>*, vector<Droppable*>*,vector<PowerUp*>*);
private:
	double screenHeight, screenWidth;
	bool paused = false;
	float viewLeft;
	float viewTop;
	Player player1;
	float dt;
	Clock animationClock;
	Clock fireTime;
	int lifeCounter = 3;
	int level = 0;
};

