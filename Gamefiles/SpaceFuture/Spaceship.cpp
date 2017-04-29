#include <sstream>
#include <string>

#include "Spaceship.hpp"
#include "Framework.hpp"

Spaceship::Spaceship()
    :mName("Of course I still love you"),mVelocity(0),mMass(10),mForce(0),mPosition(sf::Vector2f(0,0))
{
    font.loadFromFile("assets\\fonts\\PAPYRUS.TTF");
    mVelocityText.setFont(font);
    mVelocityText.setFillColor(sf::Color::Black);
    mVelocityText.setStyle(sf::Text::Bold);
    mVelocityText.setPosition(50,150);
    mVelocityText.setCharacterSize(24);
    mVelocityText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    mPositionText.setFont(font);
    mPositionText.setFillColor(sf::Color::Black);
    mPositionText.setStyle(sf::Text::Bold);
    mPositionText.setPosition(20,150);
    mPositionText.setCharacterSize(24);
    mPositionText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    //TODO: Load these from the ResourceManager
    ShipImage.loadFromFile("assets\\textures\\star_trek_enterprise_botship.png");
    ShipImage.createMaskFromColor(sf::Color::White);
    ShipTexture.loadFromImage(ShipImage);
    ShipSprite.setTexture(ShipTexture);
    ShipSprite.setPosition(500,500);
    ShipSprite.setScale(0.3,0.3);
}

Spaceship::~Spaceship()
{
    //dtor
}

void Spaceship::update(Framework &frmwrk)
{
    mClock.update(frmwrk, mVelocity);
    WriteStateVariables();
    CalculateNewVelocity(mForce);

    ShipSprite.move(mVelocity*frmwrk.getFrameTime(),0);
    mPosition = ShipSprite.getPosition();
    mClock.setPosition(sf::Vector2f(mPosition.x,mPosition.y - 100));
}

void Spaceship::handle(Framework &frmwrk)
{

}

void Spaceship::render(Framework &frmwrk)
{
    mClock.render(frmwrk);
    frmwrk.spRenderWindow->draw(mVelocityText);
    frmwrk.spRenderWindow->draw(mPositionText);
    frmwrk.spRenderWindow->draw(ShipSprite);
}

void Spaceship::CalculateNewVelocity(float force)
{
    float v_old = mVelocity;
    float v_new = v_old + (force/mMass)*mClock.getNextTimeStep();
    mVelocity = v_new;
}

void Spaceship::WriteStateVariables()
{
    // Velocity as function of c
    double c = 299792458;
    double mVAsPercentegeOfC = mVelocity / c ;

    std::stringstream ssVelocity;
    ssVelocity << "v = " << mVAsPercentegeOfC << " * c ";
    std::string sVelocity = ssVelocity.str();
    mVelocityText.setString(sVelocity);

    mVelocityText.setPosition(mPosition.x,mPosition.y-70);

    // Position from origin
    mPositionText.setPosition(mPosition.x,mPosition.y - 40);
    std::stringstream ssPosition;
    ssPosition << "x = " << mPosition.x << " pxls ";
    std::string sPosition = ssPosition.str();
    mPositionText.setString(sPosition);
}
