#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.h"
using namespace sf;

extern int random(int x);

Ball::Ball()
{
    circle.setRadius(20);
    circle.setPosition(Vector2f(WINDOW_WIDTH/2 - 20, WINDOW_HEIGTH/2 - 20));
    circle.setFillColor(Color::Yellow);
}

void Ball::updateMovement()
{
    static bool wasCorrected{false}; //<--- was position corected a moment ago?

    if((circle.getPosition().y + UpDownVelocity < 100)&&(circle.getPosition().y > 100)&&(UpDownVelocity < 0)&&(!wasCorrected))
    {
        int toMoveUD{-(100 - circle.getPosition().y )};
        int proportion = UpDownVelocity / (circle.getPosition().y - 100);
        int toMoveLR{LeftRightVelocity / proportion};
        circle.move(Vector2f(-toMoveLR, toMoveUD));
        UpDownVelocity = -UpDownVelocity;

        wasCorrected = 1;
        return;
    }
    if((circle.getPosition().y + UpDownVelocity > 900)&&(circle.getPosition().y < 900)&&(UpDownVelocity > 0)&&(!wasCorrected))
    {
        int toMoveUD{900 - circle.getPosition().y};
        int proportion = UpDownVelocity / (900 - circle.getPosition().y);
        int toMoveLR{LeftRightVelocity / proportion};
        circle.move(Vector2f(toMoveLR, toMoveUD));
        UpDownVelocity = -UpDownVelocity;

        wasCorrected = 1;
        return;
    }
    wasCorrected = 0;

    circle.move(Vector2f(LeftRightVelocity,UpDownVelocity));
}

void Ball::collision(int paddle1PosY, int paddle2PosY, bool isIncreasing1, bool isIncreasing2,
                     float increase1, float increase2, float powerP1, float powerP2, int godMode)
{
    ///up & down colision
    if((circle.getPosition().y <= 100)||(circle.getPosition().y + 40 >= WINDOW_HEIGTH))
    {
        UpDownVelocity = -UpDownVelocity;
    }

    ///colision with paddles
    int paddle1DownBound, paddle2DownBound;

    if(isIncreasing1) paddle1DownBound = 100 + (increase1 * 20);
    else paddle1DownBound = 100;
    if(isIncreasing2) paddle2DownBound = 100 + (increase2 * 20);
    else paddle2DownBound = 100;

    if((((circle.getPosition().x <= 35)&&(circle.getPosition().x >= -15))&&((circle.getPosition().y >= paddle1PosY - 40)&&(circle.getPosition().y <= paddle1PosY + paddle1DownBound)))
    ||(((circle.getPosition().x >= 1225)&&(circle.getPosition().x <= 1275))&&((circle.getPosition().y >= paddle2PosY - 40)&&(circle.getPosition().y <= paddle2PosY + paddle2DownBound))))
    {
        float randomNumber = random(10)/4;

        if((LeftRightVelocity < 0)&&(godMode != 2))
        {
            if(LeftRightVelocity < 49) LeftRightVelocity -= (powerP1/10);
            UpDownVelocity -= (powerP1/10 + randomNumber);
            LeftRightVelocity = - LeftRightVelocity;
        }
        else if(godMode != 1)
        {
            if(LeftRightVelocity < 49) LeftRightVelocity += (powerP2/10);
            UpDownVelocity -= (powerP2/10 + randomNumber);
            LeftRightVelocity = - LeftRightVelocity;
        }
    }

    if((godMode == 1)&&(circle.getPosition().x > 1225))
    {
        float randomNumber = random(10)/4;
        LeftRightVelocity += (powerP2/10);
        UpDownVelocity -= (powerP2/10 + randomNumber);
        LeftRightVelocity = - LeftRightVelocity;
    }
    if((godMode == 2)&&(circle.getPosition().x < 35))
    {
        float randomNumber = random(10)/4;
        LeftRightVelocity -= (powerP1/10);
        UpDownVelocity -= (powerP1/10 + randomNumber);
        LeftRightVelocity = - LeftRightVelocity;
    }
}

void Ball::collision(int controlIn1player)
{
    ///up & down colision
    if((circle.getPosition().y <= 100)||(circle.getPosition().y + 40 >= WINDOW_HEIGTH))
    {
        UpDownVelocity = -UpDownVelocity;
    }
    ///left wall colision
    if((circle.getPosition().x < 15)&&(controlIn1player == 1))
    {
        setVelocity(0);
    }
    ///right wall colision
    else if((circle.getPosition().x > 1245)&&(controlIn1player == 2))
    {
        setVelocity(0);
    }
}

void Ball::setVelocity(float vel)
{
    LeftRightVelocity = vel;
    UpDownVelocity = vel;
}
