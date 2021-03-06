#include "Framework.hpp"
#include "ResourceManager.hpp"
#include "..\SpaceFuture\Variables.hpp"

using namespace std;

float Framework::mFrameTime;

void closeSettingsMenu(SettingsMenu *set)
{
    set->close();
}

Framework::Framework(std::string WindowTitle)
    :mRunning(true)
{
    sf::VideoMode newVideoMode(Variables::WINDOW_WIDTH,Variables::WINDOW_HEIGHT,32);
    spRenderWindow = std::move(std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(newVideoMode,
                                                                                      WindowTitle)));
    spMainEvent    = std::move(std::unique_ptr<sf::Event>(new sf::Event));
    upClock        = std::move(std::unique_ptr<sf::Clock>(new sf::Clock));

    spRenderWindow->setPosition(sf::Vector2i(300,50));
    spRenderWindow->setVerticalSyncEnabled(true);
    spRenderWindow->setFramerateLimit(60);

    // Set Gamestate to MAINMENU, in case it is not changed in main
    CurrentState = new MainMenu;
    // CurrentState = std::move(std::unique_ptr<MainMenu>(new MainMenu));
}

Framework::~Framework()
{
    delete CurrentState;
}

void Framework::run()
{
    while(mRunning)
    {
        update(mFrameTime);
        handleEvents();
        render();

        if(mRunning == false)
            quit();
    }
}

void Framework::ChangeState(gameStates newstate)
{
    spRenderWindow->setView(spRenderWindow->getDefaultView());

    switch(newstate)
    {
    case gameStates::FLYSHIP:
        delete CurrentState;
        CurrentState = new FlyShipState;
        // CurrentState = std::move(std::unique_ptr<FlyShipState>(new FlyShipState));
    break;
    case gameStates::MAINMENU:
        delete CurrentState;
        CurrentState = new MainMenu;
        // CurrentState = std::move(std::unique_ptr<MainMenu>(new MainMenu));
    break;
    case gameStates::SETTINGS:
        delete CurrentState;
        CurrentState = new SettingsMenu;
        // CurrentState = std::move(std::unique_ptr<SettingsMenu>(new SettingsMenu));
    break;
    }
}

void Framework::setViewToWindowSize()
{
    // update the view to the new size of the window
    sf::View ResizedView;
    int oldViewX = spRenderWindow->getView().getCenter().x - spRenderWindow->getView().getSize().x/2;
    int oldViewY = spRenderWindow->getView().getCenter().y - spRenderWindow->getView().getSize().y/2;
    sf::FloatRect visibleArea(oldViewX, oldViewY, spRenderWindow->getSize().x, spRenderWindow->getSize().y);
    ResizedView.reset(visibleArea);
    spRenderWindow->setView(ResizedView);
}

void Framework::setView(sf::View newView)
{
    spRenderWindow->setView(newView);
}

void Framework::setView(sf::FloatRect visibleArea)
{
    sf::View newView(visibleArea);
    spRenderWindow->setView(newView);
}

sf::Vector2f Framework::getTransformedMousePosition()
{
    // get the current mouse position in the window
    sf::Vector2i MousePixelPos = sf::Mouse::getPosition(*spRenderWindow);
    // convert it to world coordinates
    return spRenderWindow->mapPixelToCoords(MousePixelPos);
}

sf::View Framework::getView()
{
    return spRenderWindow->getView();
}

float Framework::getFrameTime()
{
    return mFrameTime;
}

void Framework::quit()
{
    spRenderWindow->close();
    mRunning = false;
}

void Framework::update(float FrameTime)
{
    this->CalculateFrameTime();

    CurrentState->update(*this);
}

void Framework::handleEvents()
{
    while(spRenderWindow->pollEvent(*spMainEvent))
    {
        CurrentState->handle(*this);

        // catch Mouse Button events
        if(spMainEvent->type == sf::Event::MouseButtonPressed){
            if(spMainEvent->mouseButton.button == sf::Mouse::Left){
                //Currently the Framework itself handles no pressed buttons
            }
        }

        // catch the close event
        if(spMainEvent->type == sf::Event::Closed)
            mRunning = false;
    }
}

void Framework::render()
{
    spRenderWindow->clear(sf::Color::Black);

    CurrentState->render(*this);

    spRenderWindow->display();
}

void Framework::CalculateFrameTime()
{
    mFrameTime = upClock->getElapsedTime().asSeconds();
    upClock->restart();
//    cout << "FPS:" << 1/mFrameTime << endl;
}
