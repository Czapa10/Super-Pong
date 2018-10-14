#include <SFML/Graphics.hpp>
#include "paddle.h"
#include <iostream>

#define UP rect.move(Vector2f(0,-velocity));
#define DOWN rect.move(Vector2f(0,velocity));
using namespace sf;

Paddle::Paddle(int X,int Y,int vel)
{
    velocity = vel;

    rect.setFillColor(Color::Green);
    rect.setSize(Vector2f(25,100));
    rect.setPosition(Vector2f(X,Y));
}

void Paddle::movement(int control)///1-arrows | 2-awsd | 0-AI
{
    ///player control
    if(control == 1)///arrows
    {
        if((Keyboard::isKeyPressed(Keyboard::Up))&&(rect.getPosition().y > 100))UP
        else if((Keyboard::isKeyPressed(Keyboard::Down))&&(rect.getPosition().y + 100 < WINDOW_HEIGTH))DOWN
    }
    else if(control == 2)///awsd
    {
        if((Keyboard::isKeyPressed(Keyboard::W))&&(rect.getPosition().y > 100))UP
        else if((Keyboard::isKeyPressed(Keyboard::S))&&(rect.getPosition().y + 100 < WINDOW_HEIGTH))DOWN
    }
}

int Paddle::AI(int difficultyLevel,int AIballYposition,int AIballXposition,float velocityLeftRight,int ballXposition,int controlIn1player,
                bool strategyIsSpeedUp, int AIpaddleSpeed, bool thereIsSpeedUp, bool thereIsIncrease)
{
    ///control in 1 player = 1 (arrows)
    if((velocityLeftRight < 0)&&(AIballXposition < 900))
    {
        if(AIballYposition < rect.getPosition().y + 30)UP
        if(AIballYposition > rect.getPosition().y + 30)DOWN
    }

    ///control in 1 player = 2 (AWSD)
    if((velocityLeftRight > 0)&&(AIballXposition > 400))
    {
        if(AIballYposition < rect.getPosition().y + 30)UP
        if(AIballYposition > rect.getPosition().y + 30)DOWN
    }

    ///speed up & increase
    if(difficultyLevel > 1)
    {
        int distanceBetweenPaddleAndAIBall;
        if(rect.getPosition().y > AIballYposition) distanceBetweenPaddleAndAIBall = rect.getPosition().y - AIballYposition;
        else if(rect.getPosition().y + 100 < AIballYposition) distanceBetweenPaddleAndAIBall = AIballYposition - rect.getPosition().y;
        else distanceBetweenPaddleAndAIBall = 0;

        int paddleRunTime;
        paddleRunTime = distanceBetweenPaddleAndAIBall / velocity;

        int ballRunTime;
        if(controlIn1player == 1) ballRunTime = (ballXposition - 10) / velocityLeftRight;
        else ballRunTime = (1265 - ballXposition) / velocityLeftRight;

        if((((velocityLeftRight < 0)&&(AIballXposition < 100)&&(controlIn1player == 1))||((velocityLeftRight > 0)&&(AIballXposition > 1200)&&(controlIn1player == 2)))&&(paddleRunTime > ballRunTime))
        {
            if(AIballYposition == rect.getPosition().y + 30) return 0;

            if(strategyIsSpeedUp)
            {
                if(thereIsSpeedUp) return 1;
                else if(thereIsIncrease) return 2;
                else return 0;
            }
            else
            {
                if(thereIsIncrease) return 2;
                else if(thereIsSpeedUp) return 1;
                else return 0;
            }

        }
        else return 0;
    }
    else return 0;
}

void Paddle::setVelocity(int x)
{
    velocity = x;
}

void Paddle::increase(int padNumber,float increaseSize)
{
    if(!isIncreasing)
    {
        isIncreasing = true;
        int y{rect.getPosition().y};
        if(padNumber == 1)rect.setPosition(Vector2f(10, y - increaseSize * 10));
        if(padNumber == 2)rect.setPosition(Vector2f(1265, y - increaseSize * 10));
        rect.setSize(Vector2f(25,100 + increaseSize * 20));
    }
}

void Paddle::increaseStop(int padNumber,float increaseSize)
{
    if(isIncreasing)
    {
        isIncreasing = false;
        int y{rect.getPosition().y};
        if(padNumber == 1)rect.setPosition(Vector2f(10, y + increaseSize * 10));
        if(padNumber == 2)rect.setPosition(Vector2f(1265, y + increaseSize * 10));
        rect.setSize(Vector2f(25,100));
    }
}

bool Paddle::getIncrease()
{
    return isIncreasing;
}
