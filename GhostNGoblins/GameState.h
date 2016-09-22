#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "GameLogic.h"
#include "Player.h"
#include "Monster.h"
#include "Box.h"
#include "Ladder.h"
#include "Droppable.h"


class GameState
{
public:
	GameState(sf::Clock, bool, double, double,sf::RenderWindow*);
	~GameState();
	void pause(sf::Event, sf::RenderWindow*);
	void handleEvents(sf::RenderWindow*, GameLogic&);
	void GameOver(int);
	void draw(sf::RenderWindow*);
	int isGameOver(GameLogic*,sf::RenderWindow*);
	void setUpText(Text*, int, string,Font*);
	void loadMap();
	bool getPaused();
	void openingSequence(sf::RenderWindow*);
	void gamewon(sf::RenderWindow*);
	void setPaused(bool);
	void logo(sf::RenderWindow*);
	bool getGameOver();
	void restart(sf::RenderWindow*);
private:
	Player player1;
	Player player2;
	bool isPaused;
	std::vector<Text*> texts;
	std::vector<Monster*> monsters;
	std::vector<PowerUp*> powerups;
	std::vector<PowerUp*> monsterPowerups;
	std::vector<Box*> boxes;
	std::vector<Ladder*> ladders;
	std::vector<Droppable*> droppables;
	std::vector<Image*> images;
	std::vector<Music*> musics;
	sf::Music music;
	sf::View* view;
	sf::View* view1;
	sf::Event theEvent;
	sf::Clock pausetimer;
	sf::Clock timer;
	sf::Clock gameTimer;
	sf::Text* ptr;
	int highscore=0;
	int gameOver=0;
	int lifeCounter=4;
	float viewLeft;
	float viewTop;
	float pausedTime=0;
	double screenHeight;
	double screenWidth;
};