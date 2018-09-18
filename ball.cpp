#include <SFML/Graphics.hpp>
#include <iostream>
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

void Ball::collision(int paddle1PosY, int paddle2PosY, bool isIncreasing1, bool isIncreasing2,
                     float increase1, float increase2, float powerP1, float powerP2)
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
        if(LeftRightVelocity < 0)
        {
            LeftRightVelocity -= powerP1/10;
            UpDownVelocity -= powerP1/10;
        }
        else
        {
            LeftRightVelocity += powerP2/10;
            UpDownVelocity -= powerP2/10;
        }
        LeftRightVelocity = - LeftRightVelocity;
    }
}

void Ball::setVelocity(float vel)
{
    LeftRightVelocity = vel;
    UpDownVelocity = vel;
}
