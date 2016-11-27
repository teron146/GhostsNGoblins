#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        //This returns what sprite to draw based on current conditions
        virtual sf::Sprite& draw();
        //This returns what sound to create based on current conditions
        virtual sf::Sound& sound();
        //This checks if a sound should be requested from the entity
        bool requestNoise();
        std::vector< std::string > getID();


    protected:
        bool kill;
        sf::Clock clock;
        sf::Time eventTime;
        int healthPoints;
        sf::Vector2<float> velocity_m;
        sf::Vector2<float> position_m;
        sf::Vector2<float> oldPosition_m;
        bool noise;
        //Index of sprite currently being displayed
        int currentSprite;
        std::vector< sf::Sprite* > sprites;
        std::vector< sf::Sound* > sounds;
        sf::Vector2<float> spriteScale;
        //This will let the state know how to handle the given entity
        std::vector< std::string > ID;

};

#endif // ENTITY_H
