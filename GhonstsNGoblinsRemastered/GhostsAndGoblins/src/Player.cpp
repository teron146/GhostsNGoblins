#include "Player.h"

Player::Player(float posX, float posY)
{
    sf::Vector2f temp;
    jumper = 0;
    temp.x = 100;
    temp.y = 120;
    faceRight = true;
    rect.setSize(temp);
    moveEntity(posX, posY);

    ID.push_back("playerMovement");
    ID.push_back("playerAction");
    ID.push_back("gravity");
    ID.push_back("moves");
    ID.push_back("playerEvents");

    //File grabbing
    getTexture("./Textures/Arthur1.png");
    getTexture("./Textures/Arthur2.png");


    //Animation

    //0
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.6f, 0 ) );
    animations.at(animations.size() - 1)->ID = "no_armor_idle_right";
    //1
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 1 ) );
    animations.at(animations.size() - 1)->ID = "no_armor_run_right";
    //2
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 1, false ) );
    animations.at(animations.size() - 1)->ID = "no_armor_run_left";
    //3
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 5) );
    animations.at(animations.size() - 1)->ID = "no_armor_jump_right";
    deltaTime = 0.0f;
    currentAnimation = 1;
    //4
    animations.push_back( new Animation( &texture.at(1), sf::Vector2u(1,5), 0.1f, 2) );
    animations.at(animations.size() - 1)->ID = "no_armor_crouch_right";
    //5
    animations.push_back(new Animation(&texture.at(0), sf::Vector2u(2,17), 0.2f, 6));
    animations.at(animations.size() - 1)->ID = "no_armor_toss_right";
    //6
    animations.push_back(new Animation(&texture.at(0), sf::Vector2u(2,17), 0.2f, 6, false));
    animations.at(animations.size() - 1)->ID = "no_armor_toss_left";
    //7
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 5, false) );
    animations.at(animations.size() - 1)->ID = "no_armor_jump_left";
    //8
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.6f, 0 , false) );
    animations.at(animations.size() - 1)->ID = "no_armor_idle_left";
    //9
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 5, false) );
    animations.at(animations.size() - 1)->ID = "no_armor_jump_left";
    //10
    animations.push_back( new Animation( &texture.at(1), sf::Vector2u(1,5), 0.1f, 2, false) );
    animations.at(animations.size() - 1)->ID = "no_armor_crouch_left";
    //11
    animations.push_back( new Animation( &texture.at(0), sf::Vector2u(2,17), 0.1f, 13, false) );
    animations.at(animations.size() - 1)->ID = "no_armor_climb";

    //Other
    crouching = false;
    kill = false;
    climbing = false;
    tossing = 11;
    onLadder = true;
}

Player::~Player()
{
    //dtor
}

sf::RectangleShape& Player::draw()
{
    onLadder = false;
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
    sf::Vector2f temp;
    if(grounded == true)
    {
        crouching = true;
        if(faceRight)
            currentAnimation = 4;
        else
            currentAnimation = 10;
        temp.x = 80;
        temp.y = 120;
        rect.setSize(temp);
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
}

void Player::run(bool right)
{
    if(crouching == false)
    {
        if(right)
        {
            currentAnimation = 1;
            moveEntity(10, 0);
            rect.setTexture(animations.at(currentAnimation)->texture);
            faceRight = true;
        }
        else
        {
            currentAnimation = 2;
            moveEntity(-10, 0);
            rect.setTexture(animations.at(currentAnimation)->texture);
            faceRight = false;
        }
    }
}

void Player::idle()
{
    sf::Vector2f temp;
    temp.x = 100;
    temp.y = 120;
    rect.setSize(temp);
    if(faceRight == true)
    {
        currentAnimation = 0;
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
    else
    {
        currentAnimation = 8;
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
}

void Player::jump(bool start)
{
    if(start == true)
    {
        if(faceRight == true)
            currentAnimation = 3;
        else
            currentAnimation = 9;
        jumper = 0;
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
    else if (jumper < 30)
    {
        jumper++;
        moveEntity(0, (-40 * pow(0.95, jumper)));
        if(faceRight == true)
            currentAnimation = 3;
        else
            currentAnimation = 9;
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
    else if (jumper == 31)
    {
        jumper = 31;
    }
}

void Player::toss(bool start)
{
    if(start == true)
    {
        if(faceRight == true)
            currentAnimation = 5;
        else
            currentAnimation = 6;
        tossing = 0;
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
    else if (tossing < 10)
    {
        tossing++;
        if(faceRight == true)
            currentAnimation = 5;
        else
            currentAnimation = 6;
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
    else if (tossing == 10)
    {
        tossing = 11;
    }
}

void Player::changeDirection(bool direction)
{
    faceRight = direction;

}

void Player::climb()
{
    climbing = false;
    if(crouching == false && grounded == true)
    {
        climbing = true;
        currentAnimation = 11;
        moveEntity(0, -10);
        rect.setTexture(animations.at(currentAnimation)->texture);
    }
}


