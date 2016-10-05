#include "stdafx.h"
#include <string>
#include <fstream>
#include "GameLogic.h"
#include "Player.h"
#include "Box.h"
#include <math.h>


using namespace sf;
using namespace std;


GameLogic::GameLogic()
{

}


GameLogic::~GameLogic()
{
}


//Executes commands based on the key given
//Precondition: The given event type, the key, the vector of non monster sprites, vector of monsters
void GameLogic::gameLogic(sf::Clock timer, sf::Event::EventType type, sf::Keyboard::Key keyToSuccess,
	vector<PowerUp*>* powerups, vector<Monster*>* monsters, vector<Box*>* boxes,
	vector<Ladder*>* ladders, sf::View* view, vector<PowerUp*>* monsterPowerups, vector<Music*>* musics)
{
	enum actions
	{
		still, jump, right, attack, left, down, duck, climbUp, hang, duckAttack, dead, climbDown,
		start, attackRight, attackLeft, spawnLeft, spawnRight
	};
	if (monsters->at(0)->deadTime.getElapsedTime().asSeconds() > 1)
	{
		if (type == sf::Event::KeyPressed)
		{
			switch (keyToSuccess)
			{
				//To change different weapons for testing
			case sf::Keyboard::Num1:
				monsters->at(0)->setPowerUpType(1);
				break;
			case sf::Keyboard::Num2:
				monsters->at(0)->setPowerUpType(2);
				break;
			case sf::Keyboard::Num3:
				monsters->at(0)->setPowerUpType(3);
				break;
			case sf::Keyboard::Num4:
				monsters->at(0)->setPowerUpType(4);
				break;
			case sf::Keyboard::Num5:
				monsters->at(0)->setPowerUpType(5);
				break;
				//To change armor for testing
			case sf::Keyboard::Q:
				monsters->at(0)->changeArmor(true);
				break;
			case sf::Keyboard::E:
				monsters->at(0)->changeArmor(false);
				break;
			case sf::Keyboard::M:
				if (musics->at(0)->getVolume() == 0)
				{
					for (int i = 0; i < musics->size(); i++)
					{
						musics->at(i)->setVolume(50);
					}
				}
				else
				{
					for (int i = 0; i < musics->size(); i++)
					{
						musics->at(i)->setVolume(0);
					}
				}
				break;
			case sf::Keyboard::Space:
				checkBoxCollision(monsters, powerups, *boxes, *ladders, monsterPowerups);
				if (monsters->at(0)->isGrounded() && !checkLadders(monsters->at(0), *ladders, Keyboard::Space, Event::KeyPressed) && !monsters->at(0)->isDucked())
				{
					monsters->at(0)->jump(screenHeight);
					monsters->at(0)->currentAction = jump;
				}
				break;
			case sf::Keyboard::W:
				if (checkLadders(monsters->at(0), *ladders, Keyboard::W, Event::KeyPressed))
				{
					monsters->at(0)->currentAction = climbUp;
				}
				break;
			case sf::Keyboard::A:
				checkBoxCollision(monsters, powerups, *boxes, *ladders, monsterPowerups);

				if (monsters->at(0)->getMonsterVelocity().x > -20)
				{
					monsters->at(0)->changeVelocity(sf::Vector2f(-20, 0));
					timer.restart();
				}
				if (checkLadders(monsters->at(0), *ladders, Keyboard::A, Event::KeyReleased))
				{
					monsters->at(0)->currentAction = hang;
					sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
					for (int i = 0; i < ladders->size(); i++)
					{
						sf::FloatRect boundingBox = ladders->at(i)->getShape()->getGlobalBounds();
						if (onTop(monsterBox, boundingBox))
							monsters->at(0)->currentAction = left;
					}
				}
				else if (!monsters->at(0)->isDucked())
					monsters->at(0)->currentAction = left;
				monsters->at(0)->monsterDirection();
				break;
			case sf::Keyboard::S:
				if (checkLadders(monsters->at(0), *ladders, Keyboard::S, Event::KeyPressed))
				{

					monsters->at(0)->currentAction = climbDown;
				}
				else
				{
					monsters->at(0)->setDucked(true);
					monsters->at(0)->currentAction = duck;
				}

				break;
			case sf::Keyboard::D:
				checkBoxCollision(monsters, powerups, *boxes, *ladders, monsterPowerups);
				if (monsters->at(0)->getMonsterVelocity().x < 20)
				{
					monsters->at(0)->changeVelocity(sf::Vector2f(20, 0));
					timer.restart();
				}
				if (checkLadders(monsters->at(0), *ladders, Keyboard::D, Event::KeyReleased))
				{
					monsters->at(0)->currentAction = hang;
					sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
					for (int i = 0; i < ladders->size(); i++)
					{
						sf::FloatRect boundingBox = ladders->at(i)->getShape()->getGlobalBounds();
						if (onTop(monsterBox, boundingBox))
							monsters->at(0)->currentAction = right;
					}
				}
				else if (!monsters->at(0)->isDucked())
					monsters->at(0)->currentAction = right;
				monsters->at(0)->monsterDirection();
				break;
			case sf::Keyboard::C:
				if (!checkLadders(monsters->at(0), *ladders, Keyboard::C, Event::KeyPressed))
				{
					if (fireTime.getElapsedTime().asSeconds() > .2)
					{
						fireTime.restart();
						PowerUp* newMissle = monsters->at(0)->createPowerUp();
						newMissle->changeVelocity(monsters->at(0)->attack(newMissle));
						sf::FloatRect  bounds(monsters->at(0)->getSkin()->getGlobalBounds());
						sf::Vector2f temppos;
						if (monsters->at(0)->isFlipped())
							temppos = sf::Vector2f(bounds.left - 5, bounds.top + (bounds.height));
						else if (monsters->at(0)->isDucked())
							temppos = sf::Vector2f(bounds.left + 100, bounds.top + (bounds.height));
						else
							temppos = sf::Vector2f(bounds.left + bounds.height - 20, bounds.top + (bounds.height));
						newMissle->getSkin()->setPosition(temppos);
						timer.restart();
						powerups->push_back(newMissle);

						if (monsters->at(0)->isDucked())
							monsters->at(0)->currentAction = duckAttack;
						else
							monsters->at(0)->currentAction = attack;
					}
				}


				break;
			}

		}
		//Stops the player from moving if ducked
		if (monsters->at(0)->isDucked())
		{
			float b = monsters->at(0)->getMonsterVelocity().x;
			monsters->at(0)->changeVelocity(sf::Vector2f(-b, 0));
		}
		if (type == sf::Event::KeyReleased)
		{
			switch (keyToSuccess)
			{
			case sf::Keyboard::A:
				float x;
				x = monsters->at(0)->getMonsterVelocity().x;
				monsters->at(0)->changeVelocity(sf::Vector2f(-x, 0));
				if (checkLadders(monsters->at(0), *ladders, Keyboard::D, Event::KeyReleased))
				{
					monsters->at(0)->currentAction = hang;
					sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
					for (int i = 0; i < ladders->size(); i++)
					{
						sf::FloatRect boundingBox = ladders->at(i)->getShape()->getGlobalBounds();
						if (onTop(monsterBox, boundingBox))
							monsters->at(0)->currentAction = still;
					}
				}
				else
					monsters->at(0)->currentAction = still;

				break;
			case sf::Keyboard::D:
				x = monsters->at(0)->getMonsterVelocity().x;
				monsters->at(0)->changeVelocity(sf::Vector2f(-x, 0));
				if (checkLadders(monsters->at(0), *ladders, Keyboard::D, Event::KeyReleased))
				{
					monsters->at(0)->currentAction = hang;
					sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
					for (int i = 0; i < ladders->size(); i++)
					{
						sf::FloatRect boundingBox = ladders->at(i)->getShape()->getGlobalBounds();
						if (onTop(monsterBox, boundingBox))
							monsters->at(0)->currentAction = still;
					}
				}
				else
					monsters->at(0)->currentAction = still;

				break;
			case sf::Keyboard::S:
				if (monsters->at(0)->getMonsterVelocity().y >= 0)
				{
					float y = monsters->at(0)->getMonsterVelocity().y;
					monsters->at(0)->changeVelocity(sf::Vector2f(0, -y));
					if (checkLadders(monsters->at(0), *ladders, Keyboard::S, Event::KeyReleased))
						monsters->at(0)->currentAction = hang;
					else
						monsters->at(0)->currentAction = still;
				}
				monsters->at(0)->setDucked(false);

				break;
			case sf::Keyboard::W:
				if (monsters->at(0)->getMonsterVelocity().y < 0)
				{
					float y = monsters->at(0)->getMonsterVelocity().y;
					monsters->at(0)->changeVelocity(sf::Vector2f(0, -y));
					if (checkLadders(monsters->at(0), *ladders, Keyboard::W, Event::KeyReleased))
					{
						monsters->at(0)->currentAction = hang;
						sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
						for (int i = 0; i < ladders->size(); i++)
						{
							sf::FloatRect boundingBox = ladders->at(i)->getShape()->getGlobalBounds();
							if (onTop(monsterBox, boundingBox))
								monsters->at(0)->currentAction = still;
						}
					}
					else
						monsters->at(0)->currentAction = still;
				}
				break;
			default:
				if (checkLadders(monsters->at(0), *ladders, Keyboard::Dash, Event::KeyReleased))
				{
					monsters->at(0)->currentAction = hang;
					sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
					for (int i = 0; i < ladders->size(); i++)
					{
						sf::FloatRect boundingBox = ladders->at(i)->getShape()->getGlobalBounds();
						if (onTop(monsterBox, boundingBox))
							monsters->at(0)->currentAction = still;
					}
				}
				else
					monsters->at(0)->currentAction = still;
				break;
			}
		}
	}
}


//Returns the current level
//Post condition:int
int GameLogic::getLevel()
{
	return level;
}


//Based on the level counter create the level
void GameLogic::loadLevel()
{
	switch (level)
	{

	}
}


//Changes the level counter
void GameLogic::nextLevel()
{
	level++;
}


//Loads the map
//Precondition : vector<Image*>* vector<Box*>* vector<Ladder*>*
void GameLogic::loadMap(vector<Image*>* images, vector<Box*>* boxes, vector<Ladder*>* ladders, double screenHeight)
{
	//For backgound
	string code;
	ifstream myfile("L1/0.map");
	if (myfile.is_open())
	{
		while (myfile >> code)
		{
		}
	}

	switch (level)
	{
	case 0:
		//The Floor
		Box* floor = new Box(6000, 100);
		floor->getShape()->setPosition(-100, screenHeight);
		floor->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(floor);
		
		//Temporary Testing Map
		Box* floor2 = new Box(100, 1000);
		floor2->getShape()->setPosition(-100, screenHeight-1000);
		floor2->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(floor2);
		Box* box = new Box(80, 80);
		box->getShape()->setPosition(800, screenHeight-80);
		box->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box);
		Box* box2 = new Box(80, 80);
		box2->getShape()->setPosition(2200, screenHeight - 80);
		box2->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box2);
		Box* box3 = new Box(400, 50);
		box3->getShape()->setPosition(2700, screenHeight - 400);
		box3->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box3);
		Box* box4 = new Box(2000, 50);
		box4->getShape()->setPosition(3200, screenHeight - 400);
		box4->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box4);
		Box* box5 = new Box(80, 80);
		box5->getShape()->setPosition(3500, screenHeight - 480);
		box5->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box5);
		Box* box6 = new Box(80, 80);
		box6->getShape()->setPosition(3300, screenHeight - 80);
		box6->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box6);
		Box* box7 = new Box(80, 80);
		box7->getShape()->setPosition(4200, screenHeight - 80);
		box7->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box7);
		Box* box8 = new Box(80, 80);
		box8->getShape()->setPosition(4500, screenHeight - 480);
		box8->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box8); 
		Box* box9 = new Box(80, 80);
		box9->getShape()->setPosition(5000, screenHeight - 80);
		box9->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box9);
		Box* box11 = new Box(80, 80);
		box11->getShape()->setPosition(5500, screenHeight - 80);
		box11->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box11);
		Ladder* ladder1 = new Ladder(100, 400);
		ladder1->getShape()->setPosition(3100, screenHeight - 400);
		ladder1->setSkin("arthur.png", 10, 10, 10, 10);
		ladders->push_back(ladder1);
		Box* box22 = new Box(200, 100);
		box22->getShape()->setPosition(6250, screenHeight);
		box22->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box22);
		Box* box33 = new Box(1500, 100);
		box33->getShape()->setPosition(6700, screenHeight);
		box33->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box33);
		Box* box44 = new Box(3000, 100);
		box44->getShape()->setPosition(8450, screenHeight);
		box44->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box44);
		Box* box55 = new Box(500, 500);
		box55->getShape()->setPosition(10950, screenHeight-500);
		box55->setSkin("bossroom.png", 0, 0, 15, 15);
		boxes->push_back(box55);
	}
}

//Loads the monsters for the map when the player dies
//Precondition: double, vector<Monster*>
void GameLogic::loadMonsters(double screenHeight, vector<Monster*>* monsters)
{
	switch (level)
	{
	case 0:
		monsters->push_back(new Monster);
		monsters->at(monsters->size() - 1)->setName("plant");
		monsters->at(monsters->size() - 1)->changeArmor(false);
		monsters->at(monsters->size() - 1)->setSkin("Enemies.png", 165, 215, 19, 27);
		monsters->at(monsters->size() - 1)->getSkin()->scale(sf::Vector2f(4, 4));
		monsters->at(monsters->size() - 1)->getSkin()->setPosition(3700, screenHeight-500);
		monsters->at(monsters->size() - 1)->getSkin()->setOrigin(monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().width / 2, monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().height);
		monsters->push_back(new Monster);
		monsters->at(monsters->size() - 1)->setName("blue bird");
		monsters->at(monsters->size() - 1)->changeArmor(false);
		monsters->at(monsters->size() - 1)->setSkin("Enemies.png", 116, 102, 17, 17);
		monsters->at(monsters->size() - 1)->getSkin()->scale(sf::Vector2f(4, 4));
		monsters->at(monsters->size() - 1)->getSkin()->setPosition(3300, screenHeight - 70);
		monsters->at(monsters->size() - 1)->getSkin()->setOrigin(monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().width / 2, monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().height);
		monsters->push_back(new Monster);
		monsters->at(monsters->size() - 1)->setName("blue bird");
		monsters->at(monsters->size() - 1)->changeArmor(false);
		monsters->at(monsters->size() - 1)->setSkin("Enemies.png", 116, 102, 17, 17);
		monsters->at(monsters->size() - 1)->getSkin()->scale(sf::Vector2f(4, 4));
		monsters->at(monsters->size() - 1)->getSkin()->setPosition(4200, screenHeight - 70);
		monsters->at(monsters->size() - 1)->getSkin()->setOrigin(monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().width / 2, monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().height);
		monsters->push_back(new Monster);
		monsters->at(monsters->size() - 1)->setName("red bird");
		monsters->at(monsters->size() - 1)->changeArmor(false);
		monsters->at(monsters->size() - 1)->setSkin("Enemies.png", 116, 102, 17, 17);
		monsters->at(monsters->size() - 1)->getSkin()->scale(sf::Vector2f(4, 4));
		monsters->at(monsters->size() - 1)->getSkin()->setPosition(5000, screenHeight - 70);
		monsters->at(monsters->size() - 1)->getSkin()->setOrigin(monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().width / 2, monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().height);
		break;
	}
}

//Checks if monsters are on a ladder
//Precondition: vector<Monster*> vector<Ladder*>
//Postcondition: bool
bool GameLogic::checkLadders(Monster* monster, vector<Ladder*> ladders, Keyboard::Key key, Event::EventType eventType)
{
	bool grounded = monster->isGrounded();
	sf::FloatRect monsterBox = monster->getSkin()->getGlobalBounds();
	for (int c = 0; c < ladders.size(); c++)
	{
		bool collisionFound = false;
		sf::FloatRect boundingBox = ladders.at(c)->getShape()->getGlobalBounds();
		if (monsterBox.intersects(boundingBox) && inBox(monsterBox, boundingBox))
		{
			monster->setGrounded(true);
			if (eventType == Event::KeyPressed)
			{
				if (key == Keyboard::W)
				{
					if (monsterBox.top - 20 < boundingBox.top && monsterBox.top > boundingBox.top)
					{
						float y = monster->getMonsterVelocity().y;
						monster->changeVelocity(sf::Vector2f(0, -y - (monsterBox.top - boundingBox.top)));
					}
					else
					{
						float y = monster->getMonsterVelocity().y;
						monster->changeVelocity(sf::Vector2f(0, -y - 20));
					}
				}
				else if (key == Keyboard::S)
				{
					if (monsterBox.top + monsterBox.height + 20 > boundingBox.top + boundingBox.height &&  monsterBox.top + monsterBox.height < boundingBox.top + boundingBox.height)
					{
						float y = monster->getMonsterVelocity().y;
						monster->changeVelocity(sf::Vector2f(0, -y + ((monsterBox.top + monsterBox.height) - (boundingBox.top + boundingBox.height))));
					}
					else
					{
						float y = monster->getMonsterVelocity().y;
						monster->changeVelocity(sf::Vector2f(0, -y + 20));
					}
				}
			}
			if (eventType != Event::KeyPressed)
			{
				float y = monster->getMonsterVelocity().y;
				monster->changeVelocity(sf::Vector2f(0, -y));
			}
			monster->setGrounded(true);
			return true;
		}
		if (onTop(monsterBox, boundingBox))
		{
			float y = monster->getMonsterVelocity().y;
			if (y > 0)
				monster->changeVelocity(sf::Vector2f(0, -y));
			monster->setGrounded(true);
			return false;
		}
	}
	return false;
}


//Gravity, Checks if the monster/player should move down
//Precondition: vector<Monster*> 
void GameLogic::gravity(vector<Monster*>* monsters, vector<PowerUp*>* powerups)
{
	for (int c = 0; c < powerups->size(); c++)
	{
		if (powerups->at(c)->getPowerType() == 1 || powerups->at(c)->getPowerType() == 2)
		{
			powerups->at(c)->changeVelocity(sf::Vector2f(0, 6));
		}
	}
	for (int c = 0; c < monsters->size(); c++)
	{
		if (!monsters->at(c)->isGrounded())
		{
			if (monsters->at(c)->getMonsterVelocity().y < 24)
			{
				monsters->at(c)->changeVelocity(sf::Vector2f(0, 6));
			}

		}
	}
}


//Executes non button game logic
//Precondition: vector of the monsters, width and height of screen
void GameLogic::constantLogic(vector<Monster*>* monsters, vector<PowerUp*>* powerups, vector<Box*>* boxes,
	vector<Ladder*> ladders, sf::View* view, float leftOfScreen, vector<Text*>* texts,
	vector<Droppable*>* droppables, vector<PowerUp*>* monsterPowerups, float topOfScreen)
{
	viewTop = topOfScreen;
	viewLeft = leftOfScreen;
	manageDrops(droppables);
	checkDroppables(monsters, droppables);
	checkLadders(monsters->at(0), ladders, Keyboard::Dash, Event::KeyPressed);
	checkBoxCollision(monsters, powerups, *boxes, ladders, monsterPowerups);
	checkIfHit(monsters, powerups, texts, droppables, monsterPowerups);
	createMonsters(monsters, monsterPowerups);
	monstersAttack(monsters, monsterPowerups);
	gravity(monsters, powerups);
	applyVelocity(monsters, powerups, view, monsterPowerups, boxes);
	for (int i = 0; i < monsters->size(); i++)
		animation(monsters->at(i));
}


//Checks if play contacts any droppables
//Precondition: vector<Monster*>* vector<Droppable*>*
void GameLogic::checkDroppables(vector<Monster*>* monsters, vector<Droppable*>* droppables)
{
	sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
	for (int i = 0; i < droppables->size(); i++)
	{
		sf::FloatRect dropBox = droppables->at(i)->getSkin()->getGlobalBounds();
		if (monsterBox.intersects(dropBox))
		{
			monsters->at(0)->addToHighScore(50);
			Droppable *ptr = droppables->at(i);
			int temp = droppables->at(i)->getDropType();
			switch (temp)
			{
			case 1:
				monsters->at(0)->setPowerUpType(1);
				droppables->erase(droppables->begin() + i);
				delete ptr;
				droppables->shrink_to_fit();
				break;
			case 2:
				monsters->at(0)->setPowerUpType(2);
				droppables->erase(droppables->begin() + i);
				delete ptr;
				droppables->shrink_to_fit();
				break;
			case 3:
				monsters->at(0)->setPowerUpType(3);
				droppables->erase(droppables->begin() + i);
				delete ptr;
				droppables->shrink_to_fit();
				break;
			case 4:
				monsters->at(0)->setPowerUpType(4);
				droppables->erase(droppables->begin() + i);
				delete ptr;
				droppables->shrink_to_fit();
				break;
			case 5:
				monsters->at(0)->setPowerUpType(5);
				droppables->erase(droppables->begin() + i);
				delete ptr;
				droppables->shrink_to_fit();
				break;
			case 6:
				monsters->at(0)->changeArmor(true);
				droppables->erase(droppables->begin() + i);
				delete ptr;
				droppables->shrink_to_fit();
				break;
			}


		}
	}
}


//Checks if any monsters are hit by a projectile
//Precondition: vector<Monster*> vector<PowerUp*>*
void GameLogic::checkIfHit(vector<Monster*>* monsters, vector<PowerUp*>* powerups, vector<Text*>* texts, vector<Droppable*>* droppables, vector<PowerUp*>* monsterpowerups)
{
	if (monsters->at(0)->deadTime.getElapsedTime().asSeconds() > 2)
	{
		bool monsterhit = false;
		for (int a = 1; a < monsters->size(); a++)
		{
			monsterhit = false;
			sf::FloatRect monsterBox = monsters->at(a)->getSkin()->getGlobalBounds();
			for (int b = 0; b < powerups->size(); b++)
			{
				sf::FloatRect boundingBox = powerups->at(b)->getSkin()->getGlobalBounds();
				if (monsterBox.intersects(boundingBox))
				{
					monsterhit = true;
					if (a == 0)
					{
						//Destroy Powerup
						PowerUp *ptr = powerups->at(b);
						powerups->erase(powerups->begin() + b);
						delete ptr;
						powerups->shrink_to_fit();

						//Check if armor
						if (monsters->at(a)->checkArmor())
						{
							monsters->at(a)->changeArmor(false);
						}
						else
						{
							lifeCounter--;
							//No armor game over
							Monster *ptr2 = monsters->at(0);
							monsters->erase(monsters->begin());
							delete ptr2;
							monsters->shrink_to_fit();
						}
					}
					else if (monsters->at(a)->getName() == "astaroth")
					{
						//Destroy Powerup
						PowerUp *ptr = powerups->at(b);
						powerups->erase(powerups->begin() + b);
						delete ptr;
						powerups->shrink_to_fit();
						sf::FloatRect monsterBox = monsters->at(a)->getSkin()->getGlobalBounds();
						sf::FloatRect powerupBox = monsters->at(a)->getSkin()->getGlobalBounds();
						if (powerupBox.contains(sf::Vector2f(monsterBox.left, monsterBox.height / 2 + monsterBox.top))
							|| powerupBox.contains(sf::Vector2f(monsterBox.left + monsterBox.width, monsterBox.height / 2 + monsterBox.top)))
						{
							if (monsters->at(a)->monsterarmor > 0)
							{
								monsters->at(a)->monsterarmor--;
							}
							else
							{
								monsters->at(0)->addToHighScore(10000);
								//If has drop create droppable
								if (monsters->at(a)->hasDroppable() != 0)
								{
									Droppable *ptr = new Droppable();
									ptr->setDropType(monsters->at(a)->hasDroppable());
									sf::FloatRect bounds = ptr->getSkin()->getGlobalBounds();
									ptr->getSkin()->setOrigin(bounds.width / 2, bounds.top + bounds.height);
									ptr->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition());
									ptr->getSkin()->scale(4, 4);
									droppables->push_back(ptr);
								}
								//Destroy Monster
								Monster *ptr2 = monsters->at(a);
								monsters->erase(monsters->begin() + a);
								delete ptr2;
								powerups->shrink_to_fit();
							}
						}
					}
					else if (monsters->at(a)->getName() == "flying knight")
					{

						if (powerups->at(b)->getVelocity().x < 0)
						{
							monsters->at(0)->addToHighScore(100);
							//if has drop create droppable
							if (monsters->at(a)->hasDroppable() != 0)
							{
								Droppable *ptr = new Droppable();
								ptr->setDropType(monsters->at(a)->hasDroppable());
								sf::FloatRect bounds = ptr->getSkin()->getGlobalBounds();
								ptr->getSkin()->setOrigin(bounds.width / 2, bounds.top + bounds.height);
								ptr->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition());
								ptr->getSkin()->scale(4, 4);
								droppables->push_back(ptr);
							}
							//Destroy Monster
							Monster *ptr2 = monsters->at(a);
							monsters->erase(monsters->begin() + a);
							delete ptr2;
							monsters->shrink_to_fit();

						}
						//Destroy Powerup
						PowerUp *ptr = powerups->at(b);
						powerups->erase(powerups->begin() + b);
						delete ptr;
						powerups->shrink_to_fit();
					}
					else
					{
						//Destroy Powerup
						PowerUp *ptr = powerups->at(b);
						powerups->erase(powerups->begin() + b);
						delete ptr;
						powerups->shrink_to_fit();
						if (monsters->at(a)->monsterarmor > 0)
						{
							monsters->at(a)->monsterarmor--;
						}
						else
						{
							if (monsters->at(a)->getName() == "satan")
							{
								monsters->at(0)->addToHighScore(3000);
							}
							else if (monsters->at(a)->getName() == "zombie")
							{
								monsters->at(0)->addToHighScore(200);
							}
							else if (monsters->at(a)->getName() == "unicorn")
							{
								monsters->at(0)->addToHighScore(2000);
							}
							else if (monsters->at(a)->getName() == "golem")
							{
								monsters->at(0)->addToHighScore(500);
							}
							else if (monsters->at(a)->getName() == "arremer")
							{
								monsters->at(0)->addToHighScore(1000);
							}
							else
							{
								monsters->at(0)->addToHighScore(100);
							}
							//If has drop create droppable
							if (monsters->at(a)->hasDroppable() != 0)
							{
								Droppable *ptr = new Droppable();
								ptr->setDropType(monsters->at(a)->hasDroppable());
								sf::FloatRect bounds = ptr->getSkin()->getGlobalBounds();
								ptr->getSkin()->setOrigin(bounds.width / 2, bounds.top + bounds.height);
								ptr->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition());
								ptr->getSkin()->scale(4, 4);
								droppables->push_back(ptr);
							}
							//Destroy Monster
							Monster *ptr2 = monsters->at(a);
							monsters->erase(monsters->begin() + a);
							delete ptr2;
							powerups->shrink_to_fit();
						}
					}
				}
			}
		}
		if (monsterhit == false)
		{
			sf::FloatRect playerBox = monsters->at(0)->getSkin()->getGlobalBounds();
			for (int a = 1; a < monsters->size(); a++)
			{
				sf::FloatRect monsterBox = monsters->at(a)->getSkin()->getGlobalBounds();
				if (playerBox.intersects(monsterBox) && monsters->at(0)->deadTime.getElapsedTime().asSeconds() > 2)
				{
					enum actions
					{
						still, jump, right, attack, left, down, duck, climbUp, hang, duckAttack, dead, climbDown,
						start, attackRight, attackLeft, spawnLeft, spawnRight
					};
					monsterhit == true;
					if (monsters->at(a)->monsterarmor >0)
					{
						monsters->at(a)->monsterarmor--;
						monsters->at(0)->currentAction = dead;
						monsters->at(0)->deadTime.restart();
					}
					else
					{
						//Destroy Monster
						Monster *ptr = monsters->at(a);
						monsters->erase(monsters->begin() + a);
						delete ptr;
						monsters->shrink_to_fit();
						monsters->at(0)->currentAction = dead;
						monsters->at(0)->deadTime.restart();
					}
					//Check if armor
					if (monsters->at(0)->checkArmor())
					{
						monsters->at(0)->changeArmor(false);
					}
					else
					{
						lifeCounter--;
						//No armor game over
					}
				}
			}
		}
		if (monsterhit == false)
		{
			sf::FloatRect monsterBox = monsters->at(0)->getSkin()->getGlobalBounds();
			for (int b = 0; b < monsterpowerups->size(); b++)
			{
				sf::FloatRect boundingBox = monsterpowerups->at(b)->getSkin()->getGlobalBounds();
				if (monsterBox.intersects(boundingBox) && monsters->at(0)->deadTime.getElapsedTime().asSeconds() > 2)
				{
					enum actions
					{
						still, jump, right, attack, left, down, duck, climbUp, hang, duckAttack, dead, climbDown,
						start, attackRight, attackLeft, spawnLeft, spawnRight
					};

					monsterhit = true;
					if (boundingBox.intersects(monsterBox))
					{
						monsterhit == true;
						//Destroy Powerup
						PowerUp *ptr = monsterpowerups->at(b);
						monsterpowerups->erase(monsterpowerups->begin() + b);
						delete ptr;
						monsterpowerups->shrink_to_fit();

						monsters->at(0)->deadTime.restart();
						monsters->at(0)->currentAction = dead;
						//Check if armor
						if (monsters->at(0)->checkArmor())
						{
							monsters->at(0)->changeArmor(false);
						}
						else
						{
							lifeCounter--;
							//No armor game over
						}
					}
				}
			}
		}
	}
	for (int a = 0; a < monsters->size(); a++)
	{
		if (monsters->at(a)->getSkin()->getPosition().y > screenHeight + 200)
		{
			if (a == 0)
			{
				lifeCounter--;
			}
			//Destroy Monster
			else
			{
				Monster *ptr = monsters->at(a);
				monsters->erase(monsters->begin() + a);
				delete ptr;
				monsters->shrink_to_fit();
			}
		}
	}
}


//Manages droppables ex. delete after certain amount of time
//Precondition: vector<droppable*>*
void GameLogic::manageDrops(vector<Droppable*>* droppables)
{
	for (int a = 0; a < droppables->size(); a++)
	{
		Droppable* drop = droppables->at(a);
		if (drop->getDropTime().getElapsedTime().asSeconds()>5)
		{
			//Destroy Monster
			cout << "monster hit" << endl;

			droppables->erase(droppables->begin() + a);
			delete drop;
			droppables->shrink_to_fit();
		}
	}
}


//Add lives
//Pre condition bool
void GameLogic::addLives(int lives)
{
	lifeCounter = lives;
}


//If the player dies, resets the game
//precondition vector<Monster*>* vector<PowerUp*>* vector<Text*>*
void GameLogic::playerDeath(vector<Monster*>* monsters, vector<PowerUp*>* powerups, vector<Text*>* texts, vector<Droppable*>* droppables, vector<PowerUp*>*monsterpowerups)
{
	//Do stuff
	for (int i = 1; i < monsters->size(); i++)
	{
		//Delete all monsters minus plalyer

		Monster *ptr = monsters->at(i);
		monsters->erase(monsters->begin() + i);
		delete ptr;
		monsters->shrink_to_fit();
	}
	//Delete Powerups
	for (int a = 0; a < powerups->size(); a++)
	{
		//Destroy Powerup
		PowerUp *ptr = powerups->at(a);
		powerups->erase(powerups->begin() + a);
		delete ptr;
		powerups->shrink_to_fit();
	}
	//Delete Powerups
	for (int a = 0; a < monsterpowerups->size(); a++)
	{
		//Destroy Powerup
		PowerUp *ptr = monsterpowerups->at(a);
		monsterpowerups->erase(monsterpowerups->begin() + a);
		delete ptr;
		monsterpowerups->shrink_to_fit();
	}

	//Delete Drops
	for (int a = 0; a < droppables->size(); a++)
	{
		//Destroy drops
		Droppable *ptr = droppables->at(a);
		droppables->erase(droppables->begin() + a);
		delete ptr;
		droppables->shrink_to_fit();
	}
	//Reset player position
	monsters->at(0)->getSkin()->setPosition(500, screenHeight);
	monsters->at(0)->changeArmor(true);
}


//Get gameover
//post condition int
int GameLogic::getLifeCounter()
{
	return lifeCounter;
}


//Check for collisions with boxes for powerups and monsters Also deltes powerups if off screen
//Pre condition: vector<Monster*> vector<Powerup*> vector<Box*>
void GameLogic::checkBoxCollision(vector<Monster*>* monsters, vector<PowerUp*>* powerups,
	vector<Box*> boxes, vector<Ladder*> ladders, vector<PowerUp*>* monsterpowerups)
{
	for (int a = 0; a < monsters->size(); a++)
	{
		bool grounded = false;
		sf::FloatRect monsterBox = monsters->at(a)->getSkin()->getGlobalBounds();
		for (int c = 0; c < boxes.size(); c++)
		{
			sf::FloatRect boundingBox = boxes.at(c)->getShape()->getGlobalBounds();
			if (monsterBox.intersects(boundingBox))
			{
				float monster_bottom = monsterBox.top + monsterBox.height;
				float box_bottom = boundingBox.top + boundingBox.height;
				float monster_right = monsterBox.left + monsterBox.width;
				float box_right = boundingBox.left + boundingBox.width;

				float b_collision = box_bottom - monsterBox.top;
				float t_collision = monster_bottom - boundingBox.top;
				float l_collision = monster_right - boundingBox.left;
				float r_collision = box_right - monsterBox.left;

				if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
				{
					//bottom collision
					float y, y2;
					monsters->at(a)->setGrounded(true);
					y = monsters->at(a)->getMonsterVelocity().y;
					monsters->at(a)->changeVelocity(sf::Vector2f(0, -y));
					y2 = monsterBox.height + monsterBox.top - boundingBox.top + 1;
					monsters->at(a)->getSkin()->move(0, -y2 + 1);
					grounded = true;
				}
				else if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
				{
					//Top collision
					float y, y2;
					y = monsters->at(a)->getMonsterVelocity().y;
					monsters->at(a)->changeVelocity(sf::Vector2f(0, -y));
					y2 = monsterBox.height + monsterBox.top - boundingBox.top + 1;

				}
				if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
				{
					//Right collision
					float x, x2;
					x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-x, 0));
					x2 = monsterBox.left + monsterBox.width - boundingBox.left;
					monsters->at(a)->getSkin()->move(-x2, 0);

				}
				else if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
				{
					//Left collision
					float x, x2;
					x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-x, 0));
					x2 = monsterBox.left - (boundingBox.left + boundingBox.width);
					monsters->at(a)->getSkin()->move(-x2, 0);
				}
			}
			if (onTop(monsterBox, boundingBox))
			{
				float y, y2;
				monsters->at(a)->setGrounded(true);
				y = monsters->at(a)->getMonsterVelocity().y;
				monsters->at(a)->changeVelocity(sf::Vector2f(0, -y));
				y2 = monsterBox.height + monsterBox.top - boundingBox.top + 1;
				monsters->at(a)->getSkin()->move(0, -y2 + 1);
				grounded = true;
			}

		}
		if (grounded == false)
		{
			grounded = checkLadders(monsters->at(0), ladders, Keyboard::Dash, Event::KeyPressed);
		}
		if (grounded == false)
		{
			monsters->at(a)->setGrounded(false);
		}
	}


	for (int a = 0; a < powerups->size(); a++)
	{
		sf::FloatRect monsterBox = powerups->at(a)->getSkin()->getGlobalBounds();
		for (int c = 0; c < boxes.size(); c++)
		{
			sf::FloatRect boundingBox = boxes.at(c)->getShape()->getGlobalBounds();
			if (monsterBox.intersects(boundingBox))
			{
				//Destroy Powerup
				PowerUp *ptr = powerups->at(a);
				powerups->erase(powerups->begin() + a);
				delete ptr;
				powerups->shrink_to_fit();
			}

		}

	}
	for (int a = 0; a < powerups->size(); a++)
	{
		if (powerups->at(a)->getSkin()->getPosition().x < viewLeft - 1000 || powerups->at(a)->getSkin()->getPosition().x > viewLeft + screenWidth + 1000)
		{
			//Destroy Powerup
			PowerUp *ptr = powerups->at(a);
			powerups->erase(powerups->begin() + a);
			delete ptr;
			powerups->shrink_to_fit();
		}

	}
	for (int a = 0; a < monsterpowerups->size(); a++)
	{
		if (monsterpowerups->at(a)->getSkin()->getPosition().x < viewLeft - 1000 || monsterpowerups->at(a)->getSkin()->getPosition().x > viewLeft + screenWidth + 1000)
		{
			//Destroy Powerup
			PowerUp *ptr = monsterpowerups->at(a);
			monsterpowerups->erase(monsterpowerups->begin() + a);
			delete ptr;
			monsterpowerups->shrink_to_fit();
		}

	}
	for (int a = 0; a < powerups->size(); a++)
	{
		if (powerups->at(a)->getSkin()->getPosition().y > screenHeight + powerups->at(a)->getSkin()->getGlobalBounds().height)
		{
			PowerUp *ptr = powerups->at(a);
			powerups->erase(powerups->begin() + a);
			delete ptr;
			powerups->shrink_to_fit();
		}
	}
	for (int a = 0; a < monsterpowerups->size(); a++)
	{
		if (monsterpowerups->at(a)->getSkin()->getPosition().y > screenHeight + monsterpowerups->at(a)->getSkin()->getGlobalBounds().height)
		{
			//Destroy Powerup
			PowerUp *ptr = monsterpowerups->at(a);
			monsterpowerups->erase(monsterpowerups->begin() + a);
			delete ptr;
			monsterpowerups->shrink_to_fit();
		}
	}


	for (int a = 0; a < powerups->size(); a++)
	{
		sf::FloatRect powerupBox = powerups->at(a)->getSkin()->getGlobalBounds();
		for (int b = 0; b < monsterpowerups->size(); b++)
		{
			sf::FloatRect boundingBox = monsterpowerups->at(b)->getSkin()->getGlobalBounds();
			if (powerupBox.intersects(boundingBox))
			{
				if (boundingBox.intersects(powerupBox))
				{
					if (powerups->at(a)->getPowerType() == 5)
					{
						monsters->at(0)->addToHighScore(25);
						//Destroy MonsterPowerup
						PowerUp *ptr = monsterpowerups->at(b);
						monsterpowerups->erase(monsterpowerups->begin() + b);
						delete ptr;
						monsterpowerups->shrink_to_fit();

						//Destroy Powerup
						PowerUp *ptr2 = powerups->at(a);
						powerups->erase(powerups->begin() + a);
						delete ptr2;
						powerups->shrink_to_fit();
					}
				}
			}
		}
	}
}


//Tests if one rectangle is on top of another but not intersecting
//Precondition: float rectangle x2
//Postcondition: bool
bool GameLogic::onTop(sf::FloatRect & top, sf::FloatRect &bottom)
{
	bool result = false;
	if (top.top + top.height == bottom.top)
	{
		if (top.left < (bottom.left + bottom.width) && top.left > bottom.left)
			result = true;
		else if (top.left + top.width > bottom.left && top.left + top.width < bottom.left + bottom.width)
			result = true;
	}
	return result;
}


//Tests if one box is inside of another
//Precondition: float rectangle x2
//Postcondition: bool
bool GameLogic::inBox(sf::FloatRect & monster, sf::FloatRect & box)
{
	if (monster.left < (box.left + box.width) && monster.left > box.left)
	{
		return true;
	}
	else if (monster.left + monster.width > box.left &&
		monster.left + monster.width < box.left + box.width)
	{
		return true;
	}
	else
		return false;
}


//Applys animations to the vectors
//Precondition: vector of monsters, vector powerups
//returns the appropriate skin based on the action, the time passed, 
//and whether or not the player is wear armor
//Precondition: vector of monsters, vector powerups
void GameLogic::animation(Monster* player)
{

	Clock tempClock = player->animationClock;
	dt = tempClock.getElapsedTime().asSeconds();
	enum actions
	{
		still, jump, right, attack, left, down, duck, climbUp, hang, duckAttack, dead, climbDown,
		start, attackRight, attackLeft, spawnLeft, spawnRight
	};

	if (player->getName() == "arthur.png")
	{
		if (player->deadTime.getElapsedTime().asSeconds() < 1)
		{
			player->currentAction = dead;
		}
		player->getSkin()->setOrigin(12, 30);

		//apply the sprites with armor for the player
		if (player->checkArmor())
		{

			switch (player->currentAction)
			{
			case jump:
				player->setSkin("Arthur.png", 99, 42, 27, 26);
				break;
			case right:
				if (dt < .1)
					player->setSkin("Arthur.png", 26, 40, 19, 31);
				else if (dt < .2)
					player->setSkin("Arthur.png", 49, 42, 24, 29);
				else if (dt < .3)
					player->setSkin("Arthur.png", 75, 42, 24, 29);
				else
					player->animationClock.restart();
				break;
			case attack:
				if (dt < .1)
					player->setSkin("Arthur.png", 168, 40, 23, 30);
				else if (dt < .2)
					player->setSkin("Arthur.png", 195, 44, 23, 25);
				else
					player->animationClock.restart();
				break;
			case left:
				if (dt < .1)
					player->setSkin("Arthur.png", 26, 40, 19, 31);
				else if (dt < .2)
					player->setSkin("Arthur.png", 49, 42, 24, 29);
				else if (dt < .3)
					player->setSkin("Arthur.png", 75, 42, 24, 29);
				else
					player->animationClock.restart();
				break;
			case climbUp:
				if (dt < .1)
					player->setSkin("Arthur.png", 226, 41, 21, 30);
				else if (dt < .2)
					player->setSkin("Arthur.png", 248, 45, 22, 25);
				else if (dt < .3)
					player->setSkin("Arthur.png", 273, 46, 21, 16);
				else
					player->animationClock.restart();
				break;
			case hang:
				player->setSkin("Arthur.png", 226, 41, 21, 30);
				break;
			case duck:
				player->setSkin("Arthur.png", 298, 39, 22, 22);
				player->getSkin()->setOrigin(11, 22);
				break;
			case duckAttack:
				player->getSkin()->setOrigin(11, 22);
				if (dt < .1)
					player->setSkin("Arthur.png", 324, 40, 26, 21);
				else
					player->setSkin("Arthur.png", 298, 39, 22, 22);
				if (dt > .2)
					player->animationClock.restart();
				break;
			case climbDown:
				if (dt < .1)
					player->setSkin("Arthur.png", 273, 46, 21, 16);
				else if (dt < .2)
					player->setSkin("Arthur.png", 248, 45, 22, 25);
				else if (dt < .3)
					player->setSkin("Arthur.png", 226, 41, 21, 30);
				else
					player->animationClock.restart();
				break;
				//default:
			}
		}
		//apply the sprites without armor for the player
		else
		{

			switch (player->currentAction)
			{
			case jump:
				player->setSkin("Arthur.png", 100, 5, 23, 23);
				break;
			case right:
				if (dt < .1)
					player->setSkin("Arthur.png", 31, 1, 15, 29);
				else if (dt < .2)
					player->setSkin("Arthur.png", 48, 5, 24, 24);
				else if (dt < .3)
					player->setSkin("Arthur.png", 73, 6, 24, 23);
				else
					player->animationClock.restart();
				break;
			case attack:
				if (dt < .1)
					player->setSkin("Arthur.png", 174, 0, 19, 28);
				else if (dt < .2)
					player->setSkin("Arthur.png", 194, 5, 23, 25);
				else
					player->animationClock.restart();
				break;
			case left:
				if (dt < .1)
					player->setSkin("Arthur.png", 31, 1, 15, 29);
				else if (dt < .2)
					player->setSkin("Arthur.png", 48, 5, 24, 24);
				else if (dt < .3)
					player->setSkin("Arthur.png", 73, 6, 24, 23);
				else
					player->animationClock.restart();
				break;
			case climbUp:
				if (dt < .1)
					player->setSkin("Arthur.png", 221, 1, 20, 30);
				else if (dt < .2)
					player->setSkin("Arthur.png", 245, 8, 21, 24);
				else if (dt < .3)
					player->setSkin("Arthur.png", 269, 9, 21, 15);
				else
					player->animationClock.restart();
				break;
			case hang:
				player->setSkin("Arthur.png", 221, 1, 20, 30);
				break;
			case duck:
				player->setSkin("Arthur.png", 303, 5, 19, 19);
				player->getSkin()->setOrigin(11, 22);
				break;
			case duckAttack:
				player->getSkin()->setOrigin(11, 22);
				if (dt < .1)
					player->setSkin("Arthur.png", 325, 6, 23, 18);
				else
					player->setSkin("Arthur.png", 303, 5, 19, 19);
				if (dt > .2)
					player->animationClock.restart();
				break;
			case dead:

				if (dt < .1)
					player->setSkin("Arthur.png", 81, 86, 24, 26);
				else if (dt < .2)
					player->setSkin("Arthur.png", 115, 89, 31, 27);
				else if (dt < .3)
					player->setSkin("Arthur.png", 154, 88, 30, 25);
				else if (dt<.4)
					player->setSkin("Arthur.png", 190, 101, 28, 12);
				else if (dt < .5)
				{
					player->setSkin("Arthur.png", 225, 101, 28, 12);
					player->getSkin()->setOrigin(player->getSkin()->getOrigin().x - 1, (player->getSkin()->getOrigin().y - 1));
				}

				else
					player->setSkin("Arthur.png", 225, 101, 28, 12);
				break;

			}
		}
	}

	//update the animations for zombies
	if (player->getName() == "zombie")
	{
		switch (player->currentAction)
		{
		case left:
			if (dt < .2)
				player->setSkin("Enemies.png", 259, 66, 23, 33);
			else if (dt < .4)
				player->setSkin("Enemies.png", 281, 65, 23, 34);
			else if (dt < .6)
				player->setSkin("Enemies.png", 304, 65, 25, 34);
			else
				player->animationClock.restart();
			break;
		case right:
			if (dt < .2)
				player->setSkin("Enemies.png", 259, 66, 23, 33);
			else if (dt<.4)
				player->setSkin("Enemies.png", 281, 65, 23, 34);
			else if (dt < .6)
				player->setSkin("Enemies.png", 304, 65, 25, 34);
			else
				player->animationClock.restart();
			break;
		case spawnRight:
		case spawnLeft:
			if (dt < .2)
			{
				player->setSkin("Enemies.png", 119, 90, 17, 10);
			}
			else if (dt <.4)
			{
				player->setSkin("Enemies.png", 137, 86, 28, 13);

			}
			else if (dt <.6)
			{
				player->setSkin("Enemies.png", 167, 73, 22, 27);
			}
			else
				player->animationClock.restart();
		}

		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == left)
			player->getSkin()->setScale(-4.f, 4.f);
		if (player->currentAction == spawnRight)
			player->getSkin()->setScale(-4.f, 4.f);

	}

	//update animations for blue bird
	if (player->getName() == "blue bird")
	{
		switch (player->currentAction)
		{
		case still:
			player->setSkin("Enemies.png", 116, 102, 17, 17);
			break;
		case start:
			if (dt < .1)
				player->setSkin("Enemies.png", 133, 102, 19, 17);
			else if (dt < .2)
				player->setSkin("Enemies.png", 151, 102, 19, 17);
			else if (dt < .3)
				player->setSkin("Enemies.png", 165, 102, 19, 17);
			else
				player->animationClock.restart();
			break;
		case left:
			if (dt < .1)
				player->setSkin("Enemies.png", 182, 102, 19, 19);
			else if (dt < .2)
				player->setSkin("Enemies.png", 205, 102, 18, 15);
			else if (dt < .3)
				player->setSkin("Enemies.png", 223, 104, 19, 12);
			else if (dt < .4)
				player->setSkin("Enemies.png", 241, 102, 18, 16);
			else
				player->animationClock.restart();
			break;

		case right:
			if (dt < .1)
				player->setSkin("Enemies.png", 182, 102, 19, 19);
			else if (dt < .2)
				player->setSkin("Enemies.png", 205, 102, 18, 15);
			else if (dt < .3)
				player->setSkin("Enemies.png", 223, 104, 19, 12);
			else if (dt < .4)
				player->setSkin("Enemies.png", 241, 102, 18, 16);
			else
				player->animationClock.restart();

			break;

		}
		player->getSkin()->setScale(4.f, 4.f);
		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);

	}

	//update animations for red bird
	if (player->getName() == "red bird")
	{
		switch (player->currentAction)
		{
		case still:
			player->setSkin("Enemies.png", 116, 122, 17, 17);
			break;
		case start:
			if (dt < .15)
				player->setSkin("Enemies.png", 133, 122, 19, 17);
			else if (dt < .3)
				player->setSkin("Enemies.png", 151, 122, 19, 17);
			else if (dt < .15)
				player->setSkin("Enemies.png", 165, 122, 19, 17);
			else
				player->animationClock.restart();
			break;
		case left:
			if (dt < .1)
				player->setSkin("Enemies.png", 182, 122, 19, 19);
			else if (dt < .2)
				player->setSkin("Enemies.png", 205, 122, 18, 15);
			else if (dt < .3)
				player->setSkin("Enemies.png", 223, 124, 19, 12);
			else if (dt < .4)
				player->setSkin("Enemies.png", 241, 122, 18, 16);
			else
				player->animationClock.restart();
			break;

		case right:
			if (dt < .1)
				player->setSkin("Enemies.png", 182, 122, 19, 19);
			else if (dt < .2)
				player->setSkin("Enemies.png", 205, 122, 18, 15);
			else if (dt < .3)
				player->setSkin("Enemies.png", 223, 124, 19, 12);
			else if (dt < .4)
				player->setSkin("Enemies.png", 241, 122, 18, 16);
			else
				player->animationClock.restart();
			break;

		}

		player->getSkin()->setScale(4.f, 4.f);
		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);

	}

	//apply animations to plant 

	if (player->getName() == "plant")
	{
		switch (player->currentAction)
		{
		case right:
			if (dt < .2)
				player->setSkin("Enemies.png", 165, 215, 19, 27);
			else if (dt < .4)
				player->setSkin("Enemies.png", 182, 215, 19, 27);
			else if (dt < .6)
				player->setSkin("Enemies.png", 205, 208, 18, 34);
			else if (dt < .8)
				player->setSkin("Enemies.png", 222, 208, 18, 32);
			else if (dt < 1)
				player->setSkin("Enemies.png", 241, 208, 18, 34);
			break;

		case left:
			if (dt < .2)
				player->setSkin("Enemies.png", 165, 215, 19, 27);
			else if (dt < .4)
				player->setSkin("Enemies.png", 182, 215, 19, 27);
			else if (dt < .6)
				player->setSkin("Enemies.png", 205, 208, 18, 34);
			else if (dt < .8)
				player->setSkin("Enemies.png", 222, 208, 18, 32);
			else if (dt < 1)
				player->setSkin("Enemies.png", 241, 208, 18, 34);

			break;
		}
		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == left)
			player->getSkin()->setScale(-4.f, 4.f);
	}

	//update the animations for golem
	if (player->getName() == "golem")
	{
		switch (player->currentAction)
		{

		case left:
			if (dt < .2)
				player->setSkin("enemies.png", 131, 141, 30, 34);
			else if (dt < .4)
				player->setSkin("enemies.png", 163, 141, 31, 34);
			else if (dt < .6)
				player->setSkin("enemies.png", 196, 141, 31, 33);
			else
				player->animationClock.restart();

			break;

		case right:
			if (dt < .2)
				player->setSkin("enemies.png", 131, 141, 30, 34);
			else if (dt < .4)
				player->setSkin("enemies.png", 163, 141, 31, 34);
			else if (dt < .6)
				player->setSkin("enemies.png", 196, 141, 31, 33);
			else
				player->animationClock.restart();


			break;

		case attackRight:
		case attackLeft:
			if (dt < .2)
				player->setSkin("enemies.png", 163, 174, 35, 33);
			else if (dt < .4)
				player->setSkin("enemies.png", 197, 173, 36, 33);
			else
				player->animationClock.restart();


			break;
		}
		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);
		if (player->currentAction == attackRight)
			player->getSkin()->setScale(-4.f, 4.f);

	}

	//update the animations for bat
	if (player->getName() == "bat")
	{
		switch (player->currentAction)
		{
		case right:
			if (dt < .15)
				player->setSkin("enemies.png", 259, 369, 23, 17);
			else if (dt < .3)
				player->setSkin("enemies.png", 282, 371, 20, 17);
			else if (dt < .45)
				player->setSkin("enemies.png", 316, 369, 26, 18);
			else if (dt < .6)
				player->setSkin("enemies.png", 342, 369, 36, 18);
			else
				player->animationClock.restart();
			break;

		case left:
			if (dt < .15)
				player->setSkin("enemies.png", 259, 369, 23, 17);
			else if (dt < .3)
				player->setSkin("enemies.png", 282, 371, 20, 17);
			else if (dt < .45)
				player->setSkin("enemies.png", 316, 369, 26, 18);
			else if (dt < .6)
				player->setSkin("enemies.png", 342, 369, 36, 18);
			else
				player->animationClock.restart();

			break;
		}

		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == left)
			player->getSkin()->setScale(-4.f, 4.f);
	}

	//update the animations for flying knight
	if (player->getName() == "flying knight")
	{
		switch (player->currentAction)
		{
		case left:
			if (dt < .15)
				player->setSkin("enemies.png", 182, 520, 18, 30);
			else if (dt < .3)
				player->setSkin("enemies.png", 205, 517, 17, 32);
			else if (dt < .45)
				player->setSkin("enemies.png", 221, 519, 19, 30);
			else if (dt < .6)
				player->setSkin("enemies.png", 241, 521, 19, 28);
			else
				player->animationClock.restart();

			break;

		case right:
			if (dt < .15)
				player->setSkin("enemies.png", 182, 520, 18, 30);
			else if (dt < .3)
				player->setSkin("enemies.png", 205, 517, 17, 32);
			else if (dt < .45)
				player->setSkin("enemies.png", 221, 519, 19, 30);
			else if (dt < .6)
				player->setSkin("enemies.png", 241, 521, 19, 28);
			else
				player->animationClock.restart();

			break;

		}

		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);
	}

	//update the animations for arremer
	if (player->getName() == "arremer")
	{
		switch (player->currentAction)
		{
		case left:
			if (dt < .2)
				player->setSkin("enemies.png", 165, 271, 32, 33);
			else if (dt < .4)
				player->setSkin("enemies.png", 197, 271, 31, 33);
			else if (dt < .6)
				player->setSkin("enemies.png", 230, 270, 29, 34);
			else
				player->animationClock.restart();

			break;
		case right:
			if (dt < .2)
				player->setSkin("enemies.png", 165, 271, 32, 33);
			else if (dt < .4)
				player->setSkin("enemies.png", 197, 271, 31, 33);
			else if (dt < .6)
				player->setSkin("enemies.png", 230, 270, 29, 34);
			else
				player->animationClock.restart();

			player->getSkin()->setScale(-1.f, 1.f);
			break;

		}
		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == right)
		{
			player->getSkin()->setScale(-4.f, 4.f);
		}
	}

	//update the animations for satan
	if (player->getName() == "satan")
	{
		switch (player->currentAction)
		{
		case left:
			player->setSkin("bosses.png", 174, 105, 51, 47);
			break;
		case right:
			player->setSkin("bosses.png", 174, 105, 51, 47);
			break;
		}
		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);
	}

	//update the animations for unicorn
	if (player->getName() == "unicorn")
	{
		switch (player->currentAction)
		{
		case left:
			if (dt < .2)
				player->setSkin("bosses.png", 6, 5, 52, 52);
			else if (dt < .4)
				player->setSkin("bosses.png", 120, 7, 48, 50);
			else
				player->animationClock.restart();

			break;

		case right:
			if (dt < .2)
				player->setSkin("bosses.png", 6, 5, 52, 52);
			else if (dt < .4)
				player->setSkin("bosses.png", 120, 7, 48, 50);
			else
				player->animationClock.restart();

			player->getSkin()->setScale(-1.f, 1.f);
			break;

		case still:
			player->setSkin("bosses.png", 61, 7, 51, 51);
			break;

		case jump:
			if (dt < .15)
				player->setSkin("bosses.png", 401, 6, 48, 52);
			else if (dt < .3)
				player->setSkin("bosses.png", 341, 6, 53, 49);
			else if (dt < .45)
				player->setSkin("bosses.png", 454, 5, 53, 54);
			else
				player->animationClock.restart();
			break;
		}

		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);
	}

	//update the animations for astaroth
	if (player->getName() == "astaroth")
	{
		switch (player->currentAction)
		{
		case right:
		case left:
			if (dt < .25)
				player->setSkin("bosses.png", 9, 160, 69, 69);
			else if (dt < .5)
				player->setSkin("bosses.png", 79, 160, 69, 69);
			else if (dt < .75)
				player->setSkin("bosses.png", 150, 158, 72, 71);
			else if (dt < 1)
				player->setSkin("bosses.png", 223, 160, 73, 69);
			else
				player->animationClock.restart();

			break;
		}
		player->getSkin()->setScale(4.f, 4.f);

		if (player->currentAction == right)
			player->getSkin()->setScale(-4.f, 4.f);
	}
	return;
}


//Applys movement to all monsters and objects
//Precondition:the vector of the monsters used
void GameLogic::applyVelocity(vector<Monster*>* monsters, vector<PowerUp*>* powerups, sf::View* view, vector<PowerUp*>* monsterpowerups, vector<Box*>* boxes)
{
	for (int c = 0; c < monsters->size(); c++)
	{
		float x, y;
		x = monsters->at(c)->getMonsterVelocity().x;
		y = monsters->at(c)->getMonsterVelocity().y;
		monsters->at(c)->getSkin()->move(x, y);

	}
	for (int c = 0; c < powerups->size(); c++)
	{
		float x, y;
		x = powerups->at(c)->getVelocity().x;
		y = powerups->at(c)->getVelocity().y;
		powerups->at(c)->getSkin()->move(x, y);
	}
	for (int c = 0; c < monsterpowerups->size(); c++)
	{
		float x, y;
		x = monsterpowerups->at(c)->getVelocity().x;
		y = monsterpowerups->at(c)->getVelocity().y;
		monsterpowerups->at(c)->getSkin()->move(x, y);
	}
	for (int c = 0; c < boxes->size(); c++)
	{
		float x, y;
		x = boxes->at(c)->getVelocity().x;
		y = boxes->at(c)->getVelocity().y;
		boxes->at(c)->getShape()->move(x, y);
	}
}


//Creates only zombies...for now
//Create monsters and destroy monsters after a time
//Precondition: vector<Monster*>
void GameLogic::createMonsters(vector<Monster*>* monsters, vector<PowerUp*>* monsterPowerups)
{
	if (monsters->size() <= 0)
	{
		float x, randNum, drop = (rand() % 5) + 1, noDrop = rand() % 5;
		monsters->push_back(new Monster);
		monsters->at(monsters->size() - 1)->setName("zombie");
		monsters->at(monsters->size() - 1)->changeArmor(false);
		if (noDrop == 3)
		{
			if (rand() % 3 == 1)
			{
				monsters->at(monsters->size() - 1)->setDroppable(drop);

			}
			else
			{
				monsters->at(monsters->size() - 1)->setDroppable(6);//armor

			}
			monsters->at(monsters->size() - 1)->getSkin()->setColor(sf::Color(200, 200, 200));
		}
		monsters->at(monsters->size() - 1)->setSkin("enemies.png", 260, 67, 21, 31);
		monsters->at(monsters->size() - 1)->getSkin()->scale(sf::Vector2f(4, 4));
		randNum = (rand() % 1500) - 750;
		if (randNum<500 && randNum>-500)
		{
			if (randNum >= 0)
				randNum = 500;
			else
				randNum = -500;
		}
		x = monsters->at(0)->getSkin()->getPosition().x + randNum;
		monsters->at(monsters->size() - 1)->getSkin()->setPosition(x, screenHeight);
		monsters->at(monsters->size() - 1)->getSkin()->setOrigin(monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().width / 2, monsters->at(monsters->size() - 1)->getSkin()->getLocalBounds().height);
	}
	for (int a = 1; a < monsters->size(); a++)
	{
		Monster* monster = monsters->at(a);
		string name = monster->getName();
		if (name == "zombie")
		{
			if (monster->getMonsterTimer()->getElapsedTime().asSeconds()>7)
			{
				//Destroy Monster
				monsters->erase(monsters->begin() + a);
				delete monster;
				monsters->shrink_to_fit();
			}
		}
	}
}


//Makes monsters attack
//Precondition vector<Monster*>*
void GameLogic::monstersAttack(vector<Monster*>* monsters, vector<PowerUp*>* powerups)
{
	enum actions
	{
		still, jump, right, attack, left, down, duck, climbUp, hang, duckAttack, dead, climbDown,
		start, attackRight, attackLeft, spawnLeft, spawnRight
	};

	for (int a = 1; a < monsters->size(); a++)
	{
		if (monsters->at(a)->getName() == "zombie")
		{
			if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > .6)
			{
				if (monsters->at(a)->getChaseDirection() == 0)
				{
					if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
					{
						if (monsters->at(a)->getMonsterVelocity().x < 16)
						{
							//Chase Right
							float x = monsters->at(a)->getMonsterVelocity().x;
							monsters->at(a)->changeVelocity(sf::Vector2f(12 - x, 0));
							monsters->at(a)->setChaseDirection(2);
							monsters->at(a)->currentAction = right;
						}
					}
					else
					{
						if (monsters->at(a)->getMonsterVelocity().x > -16)
						{
							//Chase Left
							float x = monsters->at(a)->getMonsterVelocity().x;
							monsters->at(a)->changeVelocity(sf::Vector2f(-12 - x, 0));
							monsters->at(a)->setChaseDirection(1);
							monsters->at(a)->currentAction = left;
						}
					}
				}
			}
			if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() < .6)
			{
				if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
				{
					monsters->at(a)->currentAction = spawnRight;
				}
				else
				{
					monsters->at(a)->currentAction = spawnLeft;
				}
			}

		}


		if (monsters->at(a)->getName() == "plant")
		{
			if (monsters->at(a)->getSkin()->getPosition().x > viewLeft && monsters->at(a)->getSkin()->getPosition().x < viewLeft + screenWidth)
			{
				if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() >= 2)
				{
					monsters->at(a)->getMonsterTimer()->restart().asSeconds();
					if (monsters->at(a)->getSkin()->getPosition().x > monsters->at(0)->getSkin()->getPosition().x + 10)
					{
						//Attack Left
						float speed, x, y;
						sf::Vector2f leftSide(-10, -20), playerPos;
						PowerUp* newMissle = monsters->at(a)->createPowerUp();
						playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
						x = playerPos.x;
						y = playerPos.y;
						speed = sqrt(x*x + y*y);
						newMissle->changeVelocity(sf::Vector2f(x / speed * 10, y / speed * 10));
						newMissle->setPowerType(1);
						newMissle->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition() + leftSide);
						powerups->push_back(newMissle);
						monsters->at(a)->currentAction = left;
					}
					if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x - 10)
					{
						//Attack Right
						float speed, x, y;
						sf::Vector2f rightSide(10, -20), playerPos;
						PowerUp* newMissle = monsters->at(a)->createPowerUp();
						playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
						x = playerPos.x;
						y = playerPos.y;
						speed = sqrt(x*x + y*y);
						newMissle->changeVelocity(sf::Vector2f(x / speed * 10, y / speed * 10));
						newMissle->setPowerType(1);
						newMissle->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition() + rightSide);
						powerups->push_back(newMissle);
						monsters->at(a)->currentAction = right;
					}
				}
			}

		}


		if (monsters->at(a)->getName() == "red bird")
		{

			if (monsters->at(a)->getMonsterVelocity().y > 6)
			{
				monsters->at(a)->changeVelocity(sf::Vector2f(0, -18));
			}
			if (monsters->at(a)->getChaseDirection() == 0)
			{
				if (monsters->at(a)->getSkin()->getPosition().x < screenWidth*.9 + viewLeft)
				{
					monsters->at(a)->setGrounded(true);
					if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
					{
						if (monsters->at(a)->getMonsterVelocity().x < 16)
						{
							//Chase Right
							float speed, x, y;
							sf::Vector2f playerPos;
							playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
							x = playerPos.x;
							y = playerPos.y;
							speed = sqrt(x*x + y*y);
							monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 15, -y / speed * 15));
							monsters->at(a)->setChaseDirection(2);
							monsters->at(a)->currentAction = right;
						}
					}
					else
					{
						if (monsters->at(a)->getMonsterVelocity().x > -16)
						{
							//Chase Left
							float speed, x, y;
							sf::Vector2f playerPos;
							playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
							x = playerPos.x;
							y = playerPos.y;
							speed = sqrt(x*x + y*y);
							monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 15, -y / speed * 15));
							monsters->at(a)->setChaseDirection(1);
							monsters->at(a)->currentAction = left;
						}
					}
				}

			}
		}


		if (monsters->at(a)->getName() == "blue bird")
		{
			if (monsters->at(a)->getMonsterVelocity().y > 6)
			{
				monsters->at(a)->changeVelocity(sf::Vector2f(0, -26));
			}
			if (monsters->at(a)->getChaseDirection() == 0)
			{
				if (monsters->at(a)->getSkin()->getPosition().x < screenWidth*.9 + viewLeft)
				{
					monsters->at(a)->setGrounded(true);
					if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
					{
						if (monsters->at(a)->getMonsterVelocity().x <16)
						{
							//Chase Right
							float x = monsters->at(a)->getMonsterVelocity().x;
							monsters->at(a)->changeVelocity(sf::Vector2f(12 - x, -20));
							monsters->at(a)->setChaseDirection(2);
							monsters->at(a)->currentAction = right;
						}
					}
					else
					{
						if (monsters->at(a)->getMonsterVelocity().x>-16)
						{
							//Chase Left
							float x = monsters->at(a)->getMonsterVelocity().x;
							monsters->at(a)->changeVelocity(sf::Vector2f(-12 - x, -20));
							monsters->at(a)->setChaseDirection(1);
							monsters->at(a)->currentAction = left;
						}
					}
				}
			}
		}


		if (monsters->at(a)->getName() == "golem")
		{
			if (monsters->at(a)->getSkin()->getPosition().x < screenWidth + viewLeft)
			{
				int time = monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds();
				if (time % 6 < 3)
				{
					if (monsters->at(a)->getMonsterVelocity().x < 10)
					{
						//Chase Right
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(10, 0));
						monsters->at(a)->currentAction = right;
					}
				}
				else
				{
					if (monsters->at(a)->getMonsterVelocity().x>-10)
					{
						//Chase Left
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(-10, 0));
						monsters->at(a)->currentAction = left;
					}
				}
				if (time > 6)
					monsters->at(a)->getMonsterTimer()->restart();
				float distance = monsters->at(a)->getSkin()->getPosition().x - monsters->at(0)->getSkin()->getPosition().x;
				if (sqrt(distance * distance) < 400 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() < 2)
				{

					if (monsters->at(a)->getSkin()->getPosition().x > monsters->at(0)->getSkin()->getPosition().x)
					{
						//charge left
						if (monsters->at(a)->getMonsterVelocity().x >= -15)
							monsters->at(a)->changeVelocity(sf::Vector2f(-15, 0));
						monsters->at(a)->currentAction = attackLeft;
						monsters->at(a)->setChaseDirection(2);
					}
					else if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
					{
						//charge right
						if (monsters->at(a)->getMonsterVelocity().x <= 15)
							monsters->at(a)->changeVelocity(sf::Vector2f(15, 0));
						monsters->at(a)->currentAction = attackRight;
						monsters->at(a)->setChaseDirection(1);
					}
				}
			}
		}


		if (monsters->at(a)->getName() == "bat")
		{
			if (monsters->at(a)->getSkin()->getPosition().y > monsters->at(0)->getSkin()->getPosition().y - 250)
			{
				if (monsters->at(a)->getMonsterVelocity().y > 6)
				{
					monsters->at(a)->changeVelocity(sf::Vector2f(0, -23));
				}
			}
			if (monsters->at(a)->getChaseDirection() == 0)
			{
				if (monsters->at(a)->getSkin()->getPosition().x < screenWidth + viewLeft)
				{
					float distance = monsters->at(a)->getSkin()->getPosition().x - monsters->at(0)->getSkin()->getPosition().x;
					if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
					{
						if (monsters->at(a)->getMonsterVelocity().x < 16)
						{
							//Chase Right
							float speed, x, y;
							sf::Vector2f playerPos;
							playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
							x = playerPos.x;
							y = playerPos.y;
							speed = sqrt(x*x + y*y);
							monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 10, -y / speed));
							if (sqrt(distance* distance) < 10 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
								monsters->at(a)->setChaseDirection(2);
							monsters->at(a)->currentAction = right;
						}
					}
					else
					{
						if (monsters->at(a)->getMonsterVelocity().x > -16)
						{
							//Chase Left
							float speed, x, y;
							sf::Vector2f playerPos;
							playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
							x = playerPos.x;
							y = playerPos.y;
							speed = sqrt(x*x + y*y);
							monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 10, -y / speed));
							if (sqrt(distance * distance) < 10 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
								monsters->at(a)->setChaseDirection(1);
							monsters->at(a)->currentAction = left;
						}
					}
				}
			}
		}

		if (monsters->at(a)->getName() == "flying knight")
		{

			if (monsters->at(a)->getSkin()->getPosition().y > screenHeight - 50)
			{
				if (monsters->at(a)->getMonsterVelocity().y > 6)
				{
					if (monsters->at(a)->getMonsterVelocity().y > -200)
					{
						monsters->at(a)->changeVelocity(sf::Vector2f(0, -100));
					}
				}
			}
			if (monsters->at(a)->getChaseDirection() == 0)
			{
				if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
				{
					if (monsters->at(a)->getMonsterVelocity().x < 16)
					{
						//Chase Right
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(12 - x, 0));
						monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
				}
				else
				{
					if (monsters->at(a)->getMonsterVelocity().x > -16)
					{
						//Chase Left
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(-12 - x, 0));
						monsters->at(a)->setChaseDirection(1);
						monsters->at(a)->currentAction = left;
					}
				}
			}

		}
		if (monsters->at(a)->getName() == "arremer")
		{
			float distance = monsters->at(a)->getSkin()->getPosition().x - monsters->at(0)->getSkin()->getPosition().x;
			if (monsters->at(a)->getSkin()->getPosition().x < screenWidth + viewLeft && sqrt(distance * distance) < 500 || monsters->at(a)->monsterarmor < 3)
			{
				float y = monsters->at(a)->getMonsterVelocity().y, x = monsters->at(a)->getMonsterVelocity().x;
				if (fireTime.getElapsedTime().asSeconds() < 2)
				{
					if (y > -12)
					{
						monsters->at(a)->changeVelocity(sf::Vector2f(0, -15));

					}
					if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 4)
					{
						monsters->at(a)->getMonsterTimer()->restart();
					}
				}
				else if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
				{
					if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() < 2 && y != 0)
					{
						//Chase Right
						float speed, x, y;
						sf::Vector2f playerPos;
						playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
						x = playerPos.x;
						y = playerPos.y + 30;
						speed = sqrt(x*x + y*y);
						monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 10, -y / speed));
						if (sqrt(distance* distance) < 10 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
							monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
					else
					{
						//Chase Right
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(12 - x, 0));
						monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
				}
				else if (monsters->at(a)->getSkin()->getPosition().x > monsters->at(0)->getSkin()->getPosition().x)
				{
					if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() < 2 && y != 0)
					{
						//Chase Left
						float speed, x, y;
						sf::Vector2f playerPos;
						playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
						x = playerPos.x;
						y = playerPos.y + 30;
						speed = sqrt(x*x + y*y);
						monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 10, -y / speed));
						if (sqrt(distance* distance) < 10 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
							monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
					else
					{
						//Chase Left
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(-12 - x, 0));
						monsters->at(a)->setChaseDirection(1);
						monsters->at(a)->currentAction = left;
					}
				}
			}
		}

		if (monsters->at(a)->getName() == "satan")
		{
			float distance = monsters->at(a)->getSkin()->getPosition().x - monsters->at(0)->getSkin()->getPosition().x;
			if (monsters->at(a)->getSkin()->getPosition().x < screenWidth + viewLeft && sqrt(distance * distance) < 500 || monsters->at(a)->monsterarmor < 3)
			{
				float y = monsters->at(a)->getMonsterVelocity().y, x = monsters->at(a)->getMonsterVelocity().x;
				if (fireTime.getElapsedTime().asSeconds() < 2)
				{
					if (y > -12)
					{
						monsters->at(a)->changeVelocity(sf::Vector2f(0, -15));

					}
					if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 4)
					{
						monsters->at(a)->getMonsterTimer()->restart();
					}
				}
				else if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x)
				{
					if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() < 2 && y != 0)
					{
						//Chase Right
						float speed, x, y;
						sf::Vector2f playerPos;
						playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
						x = playerPos.x;
						y = playerPos.y + 30;
						speed = sqrt(x*x + y*y);
						monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 10, -y / speed));
						if (sqrt(distance* distance) < 10 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
							monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
					else
					{
						//Chase Right
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(12 - x, 0));
						monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
				}
				else if (monsters->at(a)->getSkin()->getPosition().x > monsters->at(0)->getSkin()->getPosition().x)
				{
					if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() < 2 && y != 0)
					{
						//Chase Left
						float speed, x, y;
						sf::Vector2f playerPos;
						playerPos = monsters->at(0)->getSkin()->getPosition() - monsters->at(a)->getSkin()->getPosition();
						x = playerPos.x;
						y = playerPos.y + 30;
						speed = sqrt(x*x + y*y);
						monsters->at(a)->changeVelocity(sf::Vector2f(x / speed * 10, -y / speed));
						if (sqrt(distance* distance) < 10 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
							monsters->at(a)->setChaseDirection(2);
						monsters->at(a)->currentAction = right;
					}
					else
					{
						//Chase Left
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(-12 - x, 0));
						monsters->at(a)->setChaseDirection(1);
						monsters->at(a)->currentAction = left;
					}
				}
			}
		}
		if (monsters->at(a)->getName() == "unicorn")
		{
			float y = monsters->at(a)->getMonsterVelocity().y, x = monsters->at(a)->getMonsterVelocity().x;
			if (monsters->at(a)->getChaseDirection() == 0)
			{
				monsters->at(a)->getMonsterTimer()->restart();
			}
			if (monsters->at(a)->isGrounded())
			{
				if (fireTime.getElapsedTime().asSeconds() < 0.5)
				{
					if (y > -12)
					{
						float x = monsters->at(a)->getMonsterVelocity().x;
						monsters->at(a)->changeVelocity(sf::Vector2f(x / 4, -60));
					}
				}
			}
			if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x && monsters->at(a)->isGrounded() == true)
			{
				if (monsters->at(a)->getMonsterVelocity().x > 16 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
				{
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-x + 12, 0));
				}
				if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() >8)
				{
					monsters->at(a)->getMonsterTimer()->restart();
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(30 - x, 0));
					monsters->at(a)->setChaseDirection(2);
					monsters->at(a)->currentAction = right;
				}
				else if (monsters->at(a)->getMonsterVelocity().x < 16)
				{
					//Chase Right
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(12 - x, 0));
					monsters->at(a)->setChaseDirection(2);
					monsters->at(a)->currentAction = right;
				}

			}
			else if (monsters->at(a)->isGrounded() == true)
			{
				if (monsters->at(a)->getMonsterVelocity().x > -16 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
				{
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-x - 12, 0));
				}
				if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() >8)
				{
					monsters->at(a)->getMonsterTimer()->restart();
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-30 - x, 0));
					monsters->at(a)->setChaseDirection(1);
					monsters->at(a)->currentAction = left;
				}
				else if (monsters->at(a)->getMonsterVelocity().x > -16)
				{
					//Chase Left
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-12 - x, 0));
					monsters->at(a)->setChaseDirection(1);
					monsters->at(a)->currentAction = left;
				}
			}
		}

		if (monsters->at(a)->getName() == "astaroth")
		{
			float y = monsters->at(a)->getMonsterVelocity().y, x = monsters->at(a)->getMonsterVelocity().x;
			if (monsters->at(a)->getChaseDirection() == 0)
			{
				monsters->at(a)->getMonsterTimer()->restart();
			}
			else if (monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 6)
			{
				monsters->at(a)->setPowerUpType(1);
				monsters->at(a)->getMonsterTimer()->restart();
				if (monsters->at(a)->getSkin()->getPosition().x > monsters->at(0)->getSkin()->getPosition().x + 10)
				{
					//Fire Left
					float speed, x, y;
					sf::Vector2f leftSide(-10, -30), playerPos;
					PowerUp* newMissle = monsters->at(a)->createPowerUp();
					newMissle->changeVelocity(sf::Vector2f(-20, 0));
					newMissle->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition() + leftSide);
					powerups->push_back(newMissle);

				}
				if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x - 10)
				{
					//Fire Right
					float speed, x, y;
					sf::Vector2f rightSide(10, -30), playerPos;
					PowerUp* newMissle = monsters->at(a)->createPowerUp();
					newMissle->changeVelocity(sf::Vector2f(20, 0));
					newMissle->getSkin()->setPosition(monsters->at(a)->getSkin()->getPosition() + rightSide);
					powerups->push_back(newMissle);
				}
			}
			if (monsters->at(a)->getSkin()->getPosition().x < monsters->at(0)->getSkin()->getPosition().x && monsters->at(a)->isGrounded() == true)
			{
				if (monsters->at(a)->getMonsterVelocity().x > 16 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
				{
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-x + 12, 0));
				}
				if (monsters->at(a)->getMonsterVelocity().x < 10)
				{

					monsters->at(a)->changeVelocity(sf::Vector2f(12, 0));
					monsters->at(a)->setChaseDirection(2);
					monsters->at(a)->currentAction = right;
				}

			}
			else if (monsters->at(a)->isGrounded() == true)
			{
				if (monsters->at(a)->getMonsterVelocity().x > -16 && monsters->at(a)->getMonsterTimer()->getElapsedTime().asSeconds() > 3)
				{
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-x - 12, 0));
				}
				if (monsters->at(a)->getMonsterVelocity().x > -10)
				{
					//Chase Left
					float x = monsters->at(a)->getMonsterVelocity().x;
					monsters->at(a)->changeVelocity(sf::Vector2f(-12, 0));
					monsters->at(a)->setChaseDirection(1);
					monsters->at(a)->currentAction = left;
				}
			}
		}
	}
}


//Lose a life
void GameLogic::loseLife()
{
	lifeCounter--;
	return;
}


//Returns the height of the screen
//Post condition double
double GameLogic::getScreenHeight()
{
	return screenHeight;
}


//Returns the height of the screen
//Post condition double
double GameLogic::getScreenWidth()
{
	return screenWidth;
}


//Sets the height of the screen
//Precondition double
void GameLogic::setScreenHeight(double temp)
{
	screenHeight = temp;
}


//Returns the height of the screen
void GameLogic::setScreenWidth(double temp)
{
	screenWidth = temp;
}