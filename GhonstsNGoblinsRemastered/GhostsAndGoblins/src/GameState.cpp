#include "GameState.h"

GameState::GameState(std::string level)
{
    files.load("Game", level);
    entityVector.push_back(new backGround(8, 8, *files.getSprites(0)));
    entityVector.push_back(new Player(*files.getSprites(0)));
    stateSwitch = false;
    files.getMusic(0)->play();
    files.getMusic(0)->setLoop(true);
    for(int i = 0; i < entityVector.size(); i++)
    {
        for(int r = 0; r < entityVector.at(i)->getID().size(); r++ )
        {
            if( entityVector.at(i)->getID().at(r) == "player")
            {
               cameraPosition = entityVector.at(i)->get_Position();
            }
        }
    }
}

GameState::~GameState()
{
    //dtor
}

void GameState::pause()
{

}

void GameState::processEvents(sf::RenderWindow &window, sf::Event event)
{
    inputManager.update(event);
    if(inputManager.keyReleased(sf::Keyboard::Escape))
    {
        stateSwitch = true;
        nextStateS = "MenuState";
    }
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); i++)
    {
        //Loops through entities ID's
        for(int r = 0; r < entityVector.at(i)->getID().size(); r++ )
        {
        }
    }
}

void GameState::process(sf::RenderWindow &window)
{
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); i++)
    {
        //Loops through entities ID's
        for(int r = 0; r < entityVector.at(i)->getID().size(); r++ )
        {
            //Handles Entities with playerMovement ID
            if( entityVector.at(i)->getID().at(r) == "playerMovement")
            {
                handlePlayer(*entityVector.at(i));
            }
            if( entityVector.at(i)->getID().at(r) == "gravity")
            {
                gravity(*entityVector.at(i));
            }
        }
    }
}
void GameState::gravity(Entity& entity)
{
    entity.moveEntity(0, 1);
    if( collide(entity) )
    {
        entity.moveEntity(0, -1);
    }
}

void GameState::handlePlayer(Entity& player)
{
    if(inputManager.keyDown(sf::Keyboard::D))
    {
        player.moveEntity(10, 0);
        if( collide( player ) )
        {
            player.moveEntity(-10, 0);
            std::cout << player.get_Position().x << ", " << player.get_Position().y << std::endl;
        }
    }
    else if(inputManager.keyDown(sf::Keyboard::A))
    {
        player.moveEntity(-10, 0);
        if( collide( player ) )
        {
            player.moveEntity(10, 0);
            std::cout << player.get_Position().x << ", " << player.get_Position().y << std::endl;
        }
    }

    if(inputManager.keyDown(sf::Keyboard::W))
    {
        player.moveEntity(0, -10);
        if( collide( player ) )
        {
            player.moveEntity(0, 10);
            std::cout << player.get_Position().x << ", " << player.get_Position().y << std::endl;
        }
    }

    if(inputManager.keyDown(sf::Keyboard::S))
    {
        //player.crouch();
    }
    else if(inputManager.keyReleased(sf::Keyboard::S))
    {
        //player.crouch();
    }

    cameraPosition = player.get_Position();
}

void GameState::draw(sf::RenderWindow & window)
{
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); i++)
    {
        //Only draws things in camera range
       // if(entityVector.at(i)->get_Position().x > cameraPosition.x
        //   && entityVector.at(i)->get_Position().x < cameraPosition.x + window.getSize().x
        //   && entityVector.at(i)->get_Position().y > cameraPosition.y
        //   && entityVector.at(i)->get_Position().y < cameraPosition.y + window.getSize().y)
        //{
            window.draw(entityVector.at(i)->draw());
       // }
    }
}

//Only Returns false atm for debugging program
bool GameState::collide(Entity& entity)
{
    //Loops through all entities
    //Loops through all entities
    /*
    for(int i = 0; i < entityVector.size(); i++)
    {
        //Loops through entities ID's
        for(int r = 0; r < entityVector.at(i)->getID().size(); r++ )
        {
           if()
        }
    }
    */
    return false;
}

