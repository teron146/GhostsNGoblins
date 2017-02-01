#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"

class Entity
{
    public:
        Entity();
        ~Entity();
        sf::Vector2<float> get_Position(std::string i = "current");
        bool isKill();
        void moveEntity(sf::Vector2<float>);
        void moveEntity(float, float);
        sf::FloatRect getBoundingBox(std::string i = "current");
        sf::Vector2<float> get_Velocity();
        bool hasID(std::string);
        //This returns what sprite to draw based on current conditions
        virtual sf::RectangleShape& draw();
        //This returns what sound to create based on current conditions
        virtual sf::Sound& sound();
        //This checks if a sound should be requested from the entity
        bool requestNoise();
        std::vector< std::string > getID();
        sf::Texture getTexture(std::string);
        Animation& getAnimation(std::string);


        //Player specific functions
        virtual void crouch();
        virtual void run(bool);
        virtual void idle();
        virtual void toss(bool);
        virtual void jump(bool);
        virtual void changeDirection(bool);
        virtual void climb(int);
        virtual void pickup(std::string);
        virtual std::string getType();
        bool hasArmor;
        bool onLadder;
        bool faceRight;
        bool climbing;
        bool getDirection();
        //Zombie
        virtual void spawn(sf::Vector2f);
        virtual void movement(sf::Vector2f);
        bool grounded;
        bool crouching;

        //Bool
        virtual bool killProjectile();


    protected:
        bool kill;
        sf::Time eventTime;
        int healthPoints;
        //This is the shape that will actually be the entity
        sf::RectangleShape rect;
        sf::Vector2<float> velocity_m;
        sf::Vector2<float> position_m;
        sf::Vector2<float> oldPosition_m;
        bool noise;
        //Index of sprite currently being displayed
        int currentAnimation;
        float deltaTime;
        sf::Clock clock;
        std::vector< sf::Texture > texture;
        std::vector< Animation* > animations;
        std::vector< sf::Sound* > sounds;
        sf::Vector2<float> spriteScale;
        //This will let the state know how to handle the given entity
        std::vector< std::string > ID;

};

#endif // ENTITY_H
