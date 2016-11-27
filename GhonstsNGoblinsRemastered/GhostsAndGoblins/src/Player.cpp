#include "Player.h"

Player::Player(std::vector<sf::Sprite*> &spriteSet)
{
    ID.push_back("playerMovement");
    ID.push_back("playerAction");
    ID.push_back("gravity");
    sprites = spriteSet;
    crouching = false;
}

Player::~Player()
{
    //dtor
}

sf::Sprite& Player::draw()
{
    sprites.back()->setPosition(position_m);
    return *sprites.back();
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



