#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Entity
{
    public:
        Entity();
        Entity(sf::Time, float, float, std::vector<sf::Sprite*>&);
        ~Entity();
        sf::Vector2<float> get_Position();
        bool isKill();
        void moveEntity(sf::Vector2<float>);
        sf::Vector2<float> get_Velocity();
        //This returns what sprite to draw based on current conditions
        virtual sf::Sprite& draw();
        //This returns what sound to create based on current conditions
        virtual sf::Sound& sound();
        //This checks if a sound should be requested from the entity
        bool requestNoise();


    protected:
        bool kill;
        sf::Clock clock;
        sf::Time eventTime;
        int healthPoints;
        sf::Vector2<float> velocity_m;
        sf::Vector2<float> position_m;
        bool noise;
        std::vector< sf::Sprite* > sprites;
        std::vector< sf::Sound* > sounds;
        sf::Vector2<float> spriteScale;

};

#endif // ENTITY_H
