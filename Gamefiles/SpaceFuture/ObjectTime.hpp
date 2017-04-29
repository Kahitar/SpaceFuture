#ifndef OBJECTTIME_HPP
#define OBJECTTIME_HPP

#include <SFML/Graphics.hpp>

class Framework;

class ObjectTime
{
    public:
        ObjectTime();
        ~ObjectTime();

        // Setter //
        void setTime(float time)                     {mTime = time;};
        void setGlobalTimeStep(float GlobalTimeStep) {mGlobalTimeStep = GlobalTimeStep;};
        void setPosition(sf::Vector2f position)      {mPosition = position;};

        // Getter //
        float getTime()              {return mTime;};
        float getNextTimeStep()      {return mNextTimeStep;};
        float getGlobalTimeStep()    {return mGlobalTimeStep;};
        sf::Vector2f getPosition()   {return mPosition;};

        void update(Framework &frmwrk, float velocity);
        void render(Framework &frmwrk);
    private:
        void updateTime(float velocity);
        void calculateNextTimeStep(double v_local);

        float mTime; // time in seconds
        float mNextTimeStep;

        sf::Font font;
        sf::Text mClockText;

        float mGlobalTimeStep;

        sf::Vector2f mPosition;

};

#endif // OBJECTTIME_HPP