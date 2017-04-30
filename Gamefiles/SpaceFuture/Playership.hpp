#ifndef PLAYERSHIP_HPP
#define PLAYERSHIP_HPP

#include <Spaceship.hpp>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "ObjectTime.hpp"
#include "UIElement.hpp"

class Playership : public Spaceship
{
    public:
        Playership(std::string texturePath, sf::Vector2f position);
        ~Playership();

        void update(Framework &frmwrk);
        void handle(Framework &frmwrk);
        void render(Framework &frmwrk);

    private:
        void EvaluatePressedKeys(Framework &frmwrk);

        UIElement Buttons;
};

#endif // PLAYERSHIP_HPP
