#include "MainMenu.hpp"
#include "../Engine/Framework.hpp"
#include "../Engine/ResourceManager.hpp"

MainMenu::MainMenu()
{
    Buttons.addButton(sf::Vector2f(540,300),sf::Vector2f(200,50),"NewGameButton","New Game");
    Buttons.addButton(sf::Vector2f(540,400),sf::Vector2f(200,50),"SettingsButton","Settings");
    Buttons.addButton(sf::Vector2f(540,500),sf::Vector2f(200,50),"ExitButton","Exit Game");

    upBackTexture   = std::move(std::unique_ptr<sf::Texture>(new sf::Texture));
    upBackSprite    = std::move(std::unique_ptr<sf::Sprite>(new sf::Sprite));

    *upBackTexture = ResourceManager::getTexture("assets\\textures\\pillarsofcreation.png");
    upBackSprite->setTexture(*upBackTexture);
}

MainMenu::~MainMenu()
{
    Buttons.deleteButton("NewGameButton");
    Buttons.deleteButton("SettingsButton");
    Buttons.deleteButton("ExitButton");
}

void MainMenu::update(Framework &frmwrk)
{

    frmwrk.setViewToWindowSize();
    Buttons.update(frmwrk);

    Buttons.getButton("NewGameButton").setScale(1,1);
}

void MainMenu::handle(Framework &frmwrk)
{
    Buttons.handle(frmwrk);

    // Switch States with keyboard
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        frmwrk.ChangeState(Framework::gameStates::SETTINGS);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        frmwrk.ChangeState(Framework::gameStates::FLYSHIP);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        frmwrk.quit();

    // handle buttons
    if(frmwrk.spMainEvent->type == sf::Event::MouseButtonPressed && frmwrk.spMainEvent->mouseButton.button == sf::Mouse::Left)
    {
        if(Buttons.getButton("NewGameButton").getMouseOnObject()){
            frmwrk.ChangeState(Framework::gameStates::FLYSHIP);
        } else if (Buttons.getButton("SettingsButton").getMouseOnObject()){
            frmwrk.ChangeState(Framework::gameStates::SETTINGS);
        } else if (Buttons.getButton("ExitButton").getMouseOnObject()){
            frmwrk.quit();
        }
    }

    // catch the resize events
    if (frmwrk.spMainEvent->type == sf::Event::Resized)
    {

    }
}

void MainMenu::render(Framework &frmwrk)
{

    frmwrk.spRenderWindow->draw(*upBackSprite);
    Buttons.render(frmwrk);
}
