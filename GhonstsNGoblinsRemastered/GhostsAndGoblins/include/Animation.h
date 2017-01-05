#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount,
                   float switchTime, int row,  bool faceRight = true);
        ~Animation();
        void update(float deltaTime);
        sf::IntRect uvRect;
        sf::Texture* texture;
        std::string ID;
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        int row;
        float totalTime;
        bool faceRight;
        float switchTime;
};

#endif // ANIMATION_H
