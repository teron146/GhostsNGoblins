#include "GameState.h"

GameState::GameState(std::string level)
{
    files.load("Game", level);
    entityVector.push_back(new Player(100, 0));
    for(int i = 0; i < 10000; i += 50)
        entityVector.push_back(new Zombie(600 + i, 850));
    entityVector.push_back(new tile(10000.0f, 500.0f, 0, 1000.0f));
    stateSwitch = false;
    files.getMusic(0)->play();
    files.getMusic(0)->setLoop(true);
    playerPOS.x = 100;
    playerPOS.y = 0;
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
            if( entityVector.at(i)->getID().at(r) == "playerEvents")
            {
                PlayerEvents(*entityVector.at(i), event);
            }
        }
    }
 }

void GameState::process(sf::RenderWindow &window)
{
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); ++i)
    {
        //Loops through entities ID's
        for(int r = 0; r < entityVector.at(i)->getID().size(); r++ )
        {
            //Handles Entities with playerMovement ID
            if( entityVector.at(i)->getID().at(r) == "playerMovement")
            {
                PlayerMovement(*entityVector.at(i));

            }
            if( entityVector.at(i)->getID().at(r) == "gravity")
            {
                gravity(*entityVector.at(i));
            }
            if(entityVector.at(i)->getID().at(r) == "moves")
            {
                collide(*entityVector.at(i));
            }
            if(entityVector.at(i)->getID().at(r) == "zombie")
                Zombies(*entityVector.at(i));
            if(entityVector.at(i)->getID().at(r) == "projectile")
            {
                if(entityVector.at(i)->killProjectile())
                {
                    killList.push_back(entityVector.at(i));
                }
            }
        }
    }
    Cleanup();
}
void GameState::gravity(Entity& entity)
{
    entity.moveEntity(0, 15);
}

//Moves the player based on keyboard input
void GameState::PlayerMovement(Entity& player)
{
    if(inputManager.keyDown(sf::Keyboard::D))
    {
        player.run(true);
    }
    else if(inputManager.keyDown(sf::Keyboard::A))
    {
        player.run(false);
    }
    else if(!inputManager.keyDown(sf::Keyboard::W))
        player.idle();

    player.crouching = false;
    if(inputManager.keyDown(sf::Keyboard::S))
    {
        player.crouch();
    }
    player.jump(false);
    playerPOS = player.get_Position();
}

void GameState::PlayerEvents(Entity& player, sf::Event& event)
{
    if(inputManager.keyReleased(sf::Keyboard::W) && player.grounded == true)
    {
        player.jump(true);
    }
    if(inputManager.keyReleased(sf::Keyboard::LShift))
    {
        entityVector.push_back(new Projectile("Dagger", player.get_Position()));
    }
}
void GameState::draw(sf::RenderWindow & window)
{

    window.setView(camera);
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); i++)
    {
        for(int r = 0; r < entityVector.at(i)->getID().size(); r++ )
        {
            if( entityVector.at(i)->getID().at(r) == "playerMovement")
            {
                camera.setCenter(entityVector.at(i)->get_Position());

            }
        }
        window.draw(entityVector.at(i)->draw());
    }
}

void GameState::Zombies(Entity& entity)
{
    entity.spawn(playerPOS);
    entity.movement(playerPOS);
}

void GameState::Cleanup()
{
    for(int i = 0; i < killList.size(); i++)
    {
        for(int x = 0; x < entityVector.size(); x++)
        {
            if(entityVector.at(x) == killList.at(i))
                entityVector.erase(entityVector.begin() + x);
        }
    }
}

void GameState::collide(Entity& entity)
{
    int meme;
    entity.grounded = false;
    sf::FloatRect box1 = entity.getBoundingBox();
    std::cout << "Old: ";
    std::cout << "( " << entity.get_Position("old").x << ", " << entity.get_Position("old").y << ")" << std::endl;
    std::cout << "Current: ";
    std::cout << "( " << entity.get_Position().x << ", " << entity.get_Position().y << ")" << std::endl;
    sf::FloatRect oldBox1 = entity.getBoundingBox("old");
    //Loops through all entities
    for(int i = 0; i < entityVector.size(); i++)
    {
        if(entityVector.at(i) == &entity)
            continue;
        sf::FloatRect box2 = entityVector.at(i)->getBoundingBox();
        if(box1.intersects(box2) && !entity.hasID("projectile") && !entityVector.at(i)->hasID("projectile"))
        {
            float box1_bottom = box1.top + box1.height;
            float OldBox1_bottom = oldBox1.top + oldBox1.height;
            float box2_bottom = box2.top + box2.height;
            float box1_right = box1.left + box1.width;
            float OldBox1_right = oldBox1.left + oldBox1.width;
            float box2_right = box2.left + box2.width;

            float left_collision = box1_right - box2.left;
            float right_collision = box2_right - box1.left;
            float top_collision = box1_bottom - box2.top;
            float bot_collision = box2_bottom - box1.top;

            std::cout << "Old Box 1" << std::endl << "\tBottom: " << OldBox1_bottom
            << "\n\tTop: " << oldBox1.top << "\n\tLeft: " << oldBox1.left << "\n\tRight: " << OldBox1_right << "\n";
            std::cout << "Box 1" << std::endl << "\tBottom: " << box1_bottom
            << "\n\tTop: " << box1.top << "\n\tLeft: " << box1.left << "\n\tRight: " << box1_right << "\n";
            std::cout << "Box 2" << std::endl << "\tBottom: " << box2_bottom
            << "\n\tTop: " << box2.top << "\n\tLeft: " << box2.left << "\n\tRight: " << box2_right << "\n";

            //box1 right colliding with box2 left
            if (OldBox1_right <= box2.left
                && box1_right > box2.left)
                entity.moveEntity(-left_collision,0);

            //box1 left colliding with box2 right
            else if (oldBox1.left >= box2_right
                     && box1.left < box2_right)
                entity.moveEntity(right_collision,0);


            //box1 bottom colliding with box2 top
            else if (OldBox1_bottom <= box2.top
                     && box1_bottom > box2.top)
            {
                entity.moveEntity(0, -top_collision);
                entity.grounded = true;
            }

            //box1 top colliding with box2 bottom
            else if (oldBox1.top <= box2_bottom
                     && box1_bottom > box2_bottom && !entityVector.at(i)->hasID("zombie"))
                entity.moveEntity(0, bot_collision);
        }
        else if(entity.hasID("projectile") && entityVector.at(i)->hasID("enemy") && box1.intersects(box2))
        {
            killList.push_back(entityVector.at(i));
            killList.push_back(&entity);
        }
    }
}


