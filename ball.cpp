#include <SFML/Graphics.hpp>
#include "ball.h"
using namespace sf;

Ball::Ball()
{
    circle.setRadius(20);
    circle.setPosition(Vector2f(WINDOW_WIDTH/2 - 20, WINDOW_HEIGTH/2 - 20));
    circle.setFillColor(Color::Yellow);
}

void Ball::updateMovement()
{
    circle.move(Vector2f(LeftRightVelocity,UpDownVelocity));
}

void Ball::collision(int paddle1PosY, int paddle2PosY, bool isIncreasing1, bool isIncreasing2)
{
    ///up & down colision
    if((circle.getPosition().y <= 100)||(circle.getPosition().y + 40 >= WINDOW_HEIGTH))
    {
        UpDownVelocity = -UpDownVelocity;
    }

    ///colision with paddles
    int paddle1DownBound, paddle2DownBound;

    if(isIncreasing1) paddle1DownBound = 200;
    else paddle1DownBound = 100;
    if(isIncreasing2) paddle2DownBound = 200;
    else paddle2DownBound = 100;

    if((((circle.getPosition().x <= 35)&&(circle.getPosition().x >= 10))&&((circle.getPosition().y >= paddle1PosY - 40)&&(circle.getPosition().y <= paddle1PosY + paddle1DownBound)))
    ||(((circle.getPosition().x >= 1225)&&(circle.getPosition().x <= 1250))&&((circle.getPosition().y >= paddle2PosY - 40)&&(circle.getPosition().y <= paddle2PosY + paddle2DownBound))))
    {
        LeftRightVelocity = - LeftRightVelocity;
        if(UpDownVelocity < 0)
        {
            UpDownVelocity -= 0.5;
            LeftRightVelocity -= 0.5;
        }
        else
        {
            UpDownVelocity += 0.5;
            LeftRightVelocity += 0.5;
        }
    }
}

void Ball::setVelocity(float vel)
{
    LeftRightVelocity = vel;
    UpDownVelocity = vel;
}
