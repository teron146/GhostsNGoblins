#include "stdafx.h"
#include "GameState.h"
#include "GameLogic.h"
#include "App.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\Window\VideoMode.hpp"
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
GameState::GameState(sf::Clock clock, bool multiplayer,double width, double height,sf::RenderWindow* window)
{
	screenWidth = width;
	screenHeight = height;
	//Initialize player1
	monsters.push_back(&player1);
	monsters.at(0)->getSkin()->setPosition(0, screenHeight);

	//Other Stuff
	string line;
	std::ifstream fs;
	fs.open("highscores.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	if (fs.is_open())
	{
		while (getline(fs, line))
		{
			int score= stoi(line);
			if (highscore < score)
			{
				highscore = score;
			}
		}
		fs.close();
	}
	else cout << "unable to open file" << endl;
	//logo(window);
	openingSequence(window);
	loadMap();
	if (!music.openFromFile("Music/background.ogg"))
	{
		cout << "failed to load music" << endl;
	}
	else
	{
		musics.push_back(&music);
		musics.at(0)->play();
	}
	
}


//displays logo
//Precondition sf::RenderWindow*
void GameState::logo(sf::RenderWindow* window)
{
	sf::Font font;
	font.loadFromFile("Fonts/Berry Rotunda.ttf");
	sf::Text A("A", font);
	A.setCharacterSize(30);
	A.setStyle(sf::Text::Bold);
	A.setFillColor(sf::Color::White);
	A.setOrigin(A.getGlobalBounds().width / 2, A.getGlobalBounds().height);
	A.setPosition(viewLeft + screenWidth / 2, viewTop + 150);
	sf::Text text2("3 Weeks Late", font);
	text2.setCharacterSize(60);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color::White);
	text2.setOrigin(text2.getGlobalBounds().width / 2, text2.getGlobalBounds().height);
	text2.setPosition(viewLeft + screenWidth / 2, viewTop + 250);
	sf::Text text4("Production", font);
	text4.setCharacterSize(30);
	text4.setStyle(sf::Text::Bold);
	text4.setFillColor(sf::Color::White);
	text4.setOrigin(text4.getGlobalBounds().width / 2, text4.getGlobalBounds().height);
	text4.setPosition(viewLeft + screenWidth / 2, viewTop + 350);
	window->draw(text2);
	window->draw(text4);
	window->draw(A);
	window->display();
	Sleep(3000);
	window->clear();
}


//restarts everything!
void GameState::restart(sf::RenderWindow* window)
{
	//Do stuff
	for (int i = 1; i < monsters.size(); i++)
	{
		//Delete all monsters minus plalyer
		Monster *ptr = monsters.at(i);
		monsters.erase(monsters.begin() + i);
		delete ptr;
		monsters.shrink_to_fit();
	}

	//Delete Powerups
	for (int a = 0; a < powerups.size(); a++)
	{
		//Destroy Powerup
		PowerUp *ptr = powerups.at(a);
		powerups.erase(powerups.begin() + a);
		delete ptr;
		powerups.shrink_to_fit();
	}


	//Delete Drops
	for (int a = 0; a < droppables.size(); a++)
	{
		//Destroy drops
		Droppable *ptr = droppables.at(a);
		droppables.erase(droppables.begin() + a);
		delete ptr;
		droppables.shrink_to_fit();
	}
	//Reset player position
	monsters.at(0)->getSkin()->setPosition(-900, screenHeight);
	monsters.at(0)->changeArmor(true);
	monsters.at(0)->addToHighScore(-monsters.at(0)->getHighScore());
	monsters.at(0)->setPowerUpType(3);
	monsters.at(0)->changeVelocity(-monsters.at(0)->getMonsterVelocity());
	pausetimer.restart();
	gameTimer.restart();
	highscore = 0;
	gameOver = 0;
	lifeCounter = 4;
	pausedTime = 0;
}


//starts off the game 
//Pre condition sf::RenderWindow*
void GameState::openingSequence(sf::RenderWindow* window)
{
	sf::Event event;
	window->clear();
	Sleep(200);
	do
	{	
		while (window->pollEvent(event))
		{
			// Declare and load a font
			sf::Sprite image;
			sf::Texture texture;
			texture.loadFromFile("title.png");
			image.setTexture(texture);
			image.setOrigin(image.getGlobalBounds().width / 2, image.getGlobalBounds().height);
			image.setPosition(screenWidth / 2, screenHeight / 2 - 100);
			image.scale(2, 2);
			sf::Font font;
			font.loadFromFile("Fonts/upheavtt.ttf");
			// Create a text
			sf::Text text("LITE", font);
			text.setCharacterSize(90);
			text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height);
			text.setStyle(sf::Text::Bold);
			text.setFillColor(sf::Color(82, 30, 51));
			text.setPosition(screenWidth / 2, screenHeight / 2 - 100);
			sf::Text player1("1 Player", font);
			player1.setCharacterSize(90);
			player1.setOrigin(player1.getGlobalBounds().width / 2, player1.getGlobalBounds().height);
			player1.setStyle(sf::Text::Bold);
			player1.setFillColor(sf::Color::White);
			player1.setPosition(screenWidth / 2, screenHeight / 2 + 200);
			sf::Text enter("Press Enter", font);
			enter.setCharacterSize(90);
			enter.setOrigin(enter.getGlobalBounds().width / 2, enter.getGlobalBounds().height);
			enter.setStyle(sf::Text::Bold);
			enter.setFillColor(sf::Color(82, 30, 51));
			enter.setPosition(screenWidth / 2, screenHeight / 2 + 300);
			string highscorestring = "High Score: " + to_string(highscore);
			sf::Text highscore(highscorestring, font);
			highscore.setCharacterSize(90);
			highscore.setOrigin(highscore.getGlobalBounds().width / 2, highscore.getGlobalBounds().height);
			highscore.setStyle(sf::Text::Bold);
			highscore.setFillColor(sf::Color(229, 193, 0));
			highscore.setPosition(screenWidth / 2, 50);
			// Draw it
			window->draw(enter);
			window->draw(player1);
			window->draw(image);
			window->draw(text);
			window->draw(highscore);
			window->display();
		}
	} while (event.key.code != sf::Keyboard::Return);
}


//Load Map
void GameState::loadMap()
{
	GameLogic temp;
	temp.loadMap(&images, &boxes, &ladders,screenHeight);
	temp.loadMonsters(screenHeight, &monsters);
}


GameState::~GameState()
{
}



//Returns if the game is paused
//Precondition: none
//Postcondition: bool
bool GameState::getPaused()
{
	return isPaused;
}


//Paused the game
//Precondition: whether the game is paused or not
//Postcondition:not
void GameState::setPaused(bool temp)
{
	isPaused = temp;
}


//If the game is won does this thingy
//Pre condition sf::RenderWindow*
void GameState::gamewon(sf::RenderWindow* window)
{
	window->clear();
	
	// Declare and load a font
	sf::Font font;
	font.loadFromFile("Fonts/Berry Rotunda.ttf");
	// Create a text
	sf::Text text("Congratulations!", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height);
	text.setPosition(viewLeft + screenWidth / 2, viewTop + 100);
	sf::Text text2("You have restored", font);
	text2.setCharacterSize(30);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color::White);
	text2.setOrigin(text2.getGlobalBounds().width / 2, text2.getGlobalBounds().height);
	text2.setPosition(viewLeft + screenWidth / 2, viewTop +200);
	sf::Text text4("Peace to the kingdom!", font);
	text4.setCharacterSize(30);
	text4.setStyle(sf::Text::Bold);
	text4.setFillColor(sf::Color::White);
	text4.setOrigin(text4.getGlobalBounds().width / 2, text4.getGlobalBounds().height);
	text4.setPosition(viewLeft + screenWidth / 2, viewTop + 300);
	sf::Text text3("Thank you.", font);
	text3.setCharacterSize(30);
	text3.setStyle(sf::Text::Bold);
	text3.setFillColor(sf::Color::White);
	text3.setOrigin(text3.getGlobalBounds().width / 2, text3.getGlobalBounds().height);
	text3.setPosition(viewLeft + screenWidth / 2,viewTop + 400);
	sf::Sprite image;
	sf::Texture texture;
	texture.loadFromFile("end.png");
	image.setTexture(texture);
	image.setOrigin(image.getGlobalBounds().width / 2, image.getGlobalBounds().height);
	image.setPosition(viewLeft + screenWidth / 2, viewTop + screenHeight - 50);
	image.scale(2, 2);
	window->draw(text2);
	window->draw(text3);
	window->draw(text4);
	window->draw(text);
	window->draw(image);
	window->display();
	Sleep(3000);
	window->clear();
	string gameover;
	gameover = "Game Over " + to_string(monsters.at(0)->getHighScore());
	setUpText(&text, 2, gameover, &font);
	window->draw(text);
	Sleep(3000);
}


//Pauses the clock and game
//Precondition:sf::Event , sf::RenderWindow*
//Postconditon:none
void GameState::pause(sf::Event event, sf::RenderWindow *window)
{
	pausetimer.restart();
	while (getPaused())
	{
		Sleep(1000);
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					setPaused(false);
					pausedTime = pausetimer.getElapsedTime().asSeconds();
				}
			}
		}	
	}
	return;
}


//Handeles new events
//Precondition:Takes in a new event and the window
//Postconditon:none
void GameState::handleEvents(sf::RenderWindow *window, GameLogic &theGameLogic)
{
	enum  	Status {
		Stopped,
		Paused,
		Playing
	};

	sf::Event event;
	isGameOver(&theGameLogic,window);
	if (music.getStatus() != Playing)
	{
		music.play();
	}

	theGameLogic.constantLogic(&monsters,&powerups,&boxes, ladders, view1,viewLeft,&texts,&droppables,&monsterPowerups,viewTop);
		while (window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Declare and load a font
					sf::Font font;
					font.loadFromFile("Fonts/Berry Rotunda.ttf");
					// Create a text
					sf::Text text("Paused", font);
					text.setCharacterSize(30);
					text.setStyle(sf::Text::Bold);
					text.setFillColor(sf::Color::White);
					text.setPosition(viewLeft, monsters.at(0)->getSkin()->getPosition().y - 400);
					// Draw it
					window->draw(text);
					window->display();
					setPaused(true);
					pause(event, window);
				}
				theGameLogic.gameLogic(timer, event.type, event.key.code, &powerups, &monsters,
					&boxes, &ladders, view1, & monsterPowerups,&musics);
			}
			if (event.type == sf::Event::KeyReleased)
			{
				theGameLogic.gameLogic(timer, event.type, event.key.code, &powerups, &monsters,
					&boxes,&ladders,view1, &monsterPowerups, &musics);
			}
		}	
		if (monsters.at(0)->getHighScore() > 2000)
		{
			gamewon(window);
			lifeCounter = 0;
			gameOver = 1;
			isGameOver(&theGameLogic, window);
			theGameLogic.addLives(3);
			return;
		}
}


//Goes to the game logic and asks if gameover
//precondition game logic
//post condition ing
int GameState::isGameOver(GameLogic* theGameLogic,sf::RenderWindow* window)
{
	Event event;
	sf::Font font;
	sf::Text text;
	string words;
	
	if (lifeCounter != theGameLogic->getLifeCounter() && gameOver != 1)
	{
		if (monsters.at(0)->deadTime.getElapsedTime().asSeconds() > 1 || lifeCounter == 4)
		{
			lifeCounter = theGameLogic->getLifeCounter();
			window->clear();
			font.loadFromFile("Fonts/Berry Rotunda.ttf");
			text.setFont(font);
			words = "  Lives: " + to_string(theGameLogic->getLifeCounter());
			words += "  ";
			text.setString(words);
			text.setCharacterSize(72);
			text.setStyle(sf::Text::Bold);
			text.setFillColor(sf::Color::White);
			text.setPosition(viewLeft + screenWidth / 2, viewTop + 300);
			text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height);
			window->draw(text);
			window->display();
			Sleep(1000);
			window->clear();
			if (lifeCounter < 3)
			{
				theGameLogic->playerDeath(&monsters, &powerups, &texts, &droppables,&monsterPowerups);
				theGameLogic->loadMonsters(screenHeight, &monsters);
			}
			gameTimer.restart();
		}

	}
	else if (gameTimer.getElapsedTime().asSeconds()-pausetimer.getElapsedTime().asSeconds() > 120)
	{
		lifeCounter--;
		pausetimer.restart();
		theGameLogic->loseLife();
		window->clear();
		font.loadFromFile("Fonts/Berry Rotunda.ttf");
		text.setFont(font);
		words = "  Lives: " + to_string(theGameLogic->getLifeCounter());
		words += "  ";
		text.setString(words);
		text.setCharacterSize(72);
		text.setStyle(sf::Text::Bold);
		text.setFillColor(sf::Color::White);
		text.setPosition(viewLeft + screenWidth / 2, viewTop + 300);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height);
		window->draw(text);
		window->display();
		Sleep(1000);
		window->clear();
		gameTimer.restart();
		theGameLogic->playerDeath(&monsters, &powerups, &texts,&droppables,&monsterPowerups);
		theGameLogic->loadMonsters(screenHeight,&monsters);
	}
	if (lifeCounter > 0)
	{
		gameOver = 0;
		
		return gameOver;
	}
	else
	{
		gameOver = 1;
		bool newHighScore = false;
		int toInt = monsters.at(0)->getHighScore();
		string line;
		std::fstream fs;
		fs.open("highscores.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		if (highscore < monsters.at(0)->getHighScore())
		{
			std::ofstream ofs;
			ofs.open("highscores.txt", std::ofstream::out | std::ofstream::trunc);
			ofs.close();
			fs << to_string(toInt) << endl;
		}
		fs.close();
	}
	return gameOver;
}


//Setup the text look
//Precondition Text* int->indicates which text style to use
void GameState::setUpText(sf::Text* text, int type,string words, sf::Font* font)
{
	sf::FloatRect textBox;
	font->loadFromFile("Fonts/Berry Rotunda.ttf");

	switch (type)
	{
	case 1://score
		text->setFont(*font);
		text->setString(words);
		text->setCharacterSize(24);
		text->setStyle(sf::Text::Bold);
		text->setFillColor(sf::Color::White);
		text->setPosition(viewLeft + 10, viewTop + 10);

		break;
	case 2://GameOver
		text->setFont(*font);
		text->setString(words);
		text->setCharacterSize(72);
		text->setStyle(sf::Text::Bold);
		text->setFillColor(sf::Color::White);
		textBox = text->getGlobalBounds();
		text->setOrigin(textBox.left + textBox.width / 2, textBox.top + textBox.height);
		text->setPosition(viewLeft + screenWidth / 2, viewTop + screenHeight / 2);
		break;
	case 3://Time
		text->setFont(*font);
		text->setString(words);
		text->setCharacterSize(24);
		text->setStyle(sf::Text::Bold);
		text->setFillColor(sf::Color::White);
		text->setPosition(viewLeft + 10, viewTop + 40);
		break;
	case 4://enter
		text->setFont(*font);
		text->setString(words);
		text->setCharacterSize(24);
		text->setStyle(sf::Text::Bold);
		text->setFillColor(sf::Color::White);
		textBox = text->getGlobalBounds();
		text->setOrigin(textBox.left + textBox.width / 2, textBox.top + textBox.height);
		text->setPosition(viewLeft + screenWidth/2, viewTop + screenHeight / 2 -200);

		break;
	case 5://quit
		text->setFont(*font);
		text->setString(words);
		text->setCharacterSize(24);
		text->setStyle(sf::Text::Bold);
		text->setFillColor(sf::Color::White);
		textBox = text->getGlobalBounds();
		text->setOrigin(textBox.left + textBox.width / 2, textBox.top + textBox.height);
		text->setPosition(viewLeft + screenWidth/2, viewTop + screenHeight /2 + 200);

		break;
	}
}


//Returns game over
//post condition: bool
bool GameState::getGameOver()
{
	return gameOver;
}

//Draws the current gamestate
//Precondition:the window and a vector of pointers of sprites
//Postconditon:none
void GameState::draw(sf::RenderWindow *window)
{
	Monster* player = monsters.at(0);
	sf::Font font;
	sf::Text text,highscore,gameTime,playAgain,enter,quit;
	string words, gameover, time;
	float xStart, yStart;
	int makeHighScoreWhole, timeSec=120, timeMin=0;
	xStart = player->getSkin()->getPosition().x - screenWidth / 2;
	yStart = player->getSkin()->getPosition().y - screenHeight / 2;
	viewLeft = xStart;
	viewTop = yStart;
	sf::View view1(sf::FloatRect(xStart, yStart, screenWidth, screenHeight));
	view = &view1;

	timeMin = (timeSec - gameTimer.getElapsedTime().asSeconds())+pausedTime;
	timeMin /= 60;
	timeSec = (timeSec - gameTimer.getElapsedTime().asSeconds() + pausedTime);
	timeSec %= 60;
	words = "Time: " + to_string(timeMin) + ":" + to_string(timeSec);
	if (timeSec < 10)
	{
		words = "Time: " + to_string(timeMin) + ":0" + to_string(timeSec);
	}
	

	setUpText(&gameTime, 3, words, &font);
	texts.push_back(&gameTime);

	makeHighScoreWhole = player->getHighScore();
	words = "Score: " + to_string(makeHighScoreWhole);
	setUpText(&highscore, 1,words,&font);
	texts.push_back(&highscore);

	
	if (gameOver == 1)
	{
		gameover = "Game Over " +words;
		setUpText(&text, 2,gameover,&font);
		texts.push_back(&text);
	}
	window->clear();
	window->setView(*view);
	for (int c = 0; c < boxes.size(); c++)
	{
		window->draw(*boxes.at(c)->getShape());
	}
	for (int c = 0; c < ladders.size(); c++)
	{
		window->draw(*ladders.at(c)->getShape());
	}
	for (int c = 0; c < powerups.size(); c++)
	{
		window->draw(*powerups.at(c)->getSkin());
	}
	for (int c = 0; c < monsters.size(); c++)
	{
		window->draw(*monsters.at(c)->getSkin());
	}
	for (int c = 0; c<droppables.size(); c++)
	{
		window->draw(*droppables.at(c)->getSkin());
	}
	for (int c = 0; c < monsterPowerups.size(); c++)
	{
		window->draw(*monsterPowerups.at(c)->getSkin());
	}
	for (int c = 0; c < texts.size(); c++)
	{
		window->draw(*texts.at(c));
	}
	window->display();
	if (gameOver == true)
	{
		Sleep(3000);
		window->clear();
		string replay,enter1,quit1;
		replay = "Play Again? ";
		setUpText(&playAgain, 2, replay, &font);
		window->draw(playAgain);
		enter1 = "Press Enter";
		setUpText(&enter, 4, enter1, &font);
		window->draw(enter);
		quit1 = "Press Q to quit";		
		setUpText(&quit, 5, quit1, &font);
		window->draw(quit);
		window->display();

		sf::Event event;
		do
		{
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Q)
					{
						gameOver = 1;
						return;
					}
					else if (event.key.code == sf::Keyboard::Return)
					{
						restart(window);
						return;
					}
				}
			}
		} while (event.key.code != sf::Keyboard::Return || event.key.code != sf::Keyboard::Q);
	}
}


