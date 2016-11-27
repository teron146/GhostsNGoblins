#include "Player.h"

Player::Player(std::vector<sf::Sprite*> &spriteSet)
{
    ID.push_back("playerMovement");
    ID.push_back("playerAction");
    ID.push_back("gravity");
    ID.push_back("moves");
    sprites = spriteSet;
    crouching = false;
    kill = false;
    currentSprite = sprites.size() - 1;
}

Player::~Player()
{
    //dtor
}

sf::Sprite& Player::draw()
{
    return *sprites.at(currentSprite);
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



