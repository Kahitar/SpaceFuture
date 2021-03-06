#include <sstream>
#include <string>

#include "../Engine/Framework.hpp"
#include "Spaceship.hpp"
#include "Playership.hpp"

Playership::Playership(std::string texturePath, sf::Vector2f position)
    :Spaceship(texturePath, position)
{
    ShipSprite.setScale(0.1,0.1);

    mClock.setPosition(sf::Vector2f(300,100));

    Buttons.addButton(sf::Vector2f(250,130),sf::Vector2f(60,28),"VelocityResetButton","Reset");
    Buttons.addButton(sf::Vector2f(250,160),sf::Vector2f(60,28),"PosResetButton","Reset");
}

Playership::~Playership()
{
    Buttons.deleteButton("VelocityResetButton");
    Buttons.deleteButton("PosResetButton");
}

void Playership::update(Framework &frmwrk)
{
    Spaceship::update(frmwrk);

    Buttons.update(frmwrk);
    Buttons.getButton("VelocityResetButton").setPosition(sf::Vector2f(mGamePosition.x-70,mGamePosition.y-70));
    Buttons.getButton("PosResetButton").setPosition(sf::Vector2f(mGamePosition.x-70,mGamePosition.y-40));
}

void Playership::handle(Framework &frmwrk)
{
    Spaceship::handle(frmwrk);

    Buttons.handle(frmwrk);
    if(frmwrk.spMainEvent->type == sf::Event::MouseButtonPressed && frmwrk.spMainEvent->mouseButton.button == sf::Mouse::Left)
    {
        if(Buttons.getButton("PosResetButton").getMouseOnObject()){
            setPosition(sf::Vector2f(0,300));
            setVelocity(0);
            mAcceleratingInDirection = 0;
        }else if(Buttons.getButton("VelocityResetButton").getMouseOnObject()){
            mVelocity = 0;
            mAcceleratingInDirection = 0;
        }
    }

    EvaluatePressedKeys(frmwrk);
}

void Playership::render(Framework &frmwrk)
{
    Spaceship::render(frmwrk);
}

void Playership::EvaluatePressedKeys(Framework &frmwrk)
{
    //Keyboard Key pressed
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        mAcceleratingInDirection = -1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        mAcceleratingInDirection = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        mAcceleratingInDirection = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        setPosition(sf::Vector2f(500,300));
//        setVelocity(0);
    }
}
