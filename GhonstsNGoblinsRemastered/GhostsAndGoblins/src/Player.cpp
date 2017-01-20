#include "Player.h"

Player::Player(float posX, float posY)
{
    sf::Vector2f temp;
    temp.x = 100;
    temp.y = 120;
    rect.setSize(temp);
    rect.setPosition(posX, posY);

    ID.push_back("playerMovement");
    ID.push_back("playerAction");
    ID.push_back("gravity");
    ID.push_back("moves");
    ID.push_back("playerEvents");

    //File grabbing
    getTexture("./Textures/Arthur1.png");


    //Animation

    //0
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.6f, 0 ) );
    animations.at(animations.size() - 1)->ID = "no_armor_idle";
    //1
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 1 ) );
    animations.at(animations.size() - 1)->ID = "no_armor_run_right";
    //2
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 1, false ) );
    animations.at(animations.size() - 1)->ID = "no_armor_run_left";
    //3
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 5) );
    animations.at(animations.size() - 1)->ID = "no_armor_jump";
    deltaTime = 0.0f;
    currentAnimation = 1;

    //Other
    crouching = false;
    kill = false;
}

Player::~Player()
{
    //dtor
}

sf::RectangleShape& Player::draw()
{
    deltaTime = clock.restart().asSeconds();
    animations.at(currentAnimation)->update(deltaTime);
    rect.setTextureRect(animations.at(currentAnimation)->uvRect);
    return rect;
}

sf::Sound& Player::sound()
{
    return *sounds.back();
}

void Player::crouch()
{
    if(crouching)
        crouching = false;
    else
        crouching = true;
}

void Player::run(bool right)
{
    if(right)
    {
        currentAnimation = 1;
        moveEntity(10, 0);
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
    else
    {
        currentAnimation = 2;
        moveEntity(-10, 0);
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
}

void Player::idle()
{
    currentAnimation = 0;
    rect.setTexture(animations.at(currentAnimation)->texture);
}

void Player::jump()
{
    currentAnimation = 3;
    rect.setTexture(animations.at(currentAnimation)->texture);
}



