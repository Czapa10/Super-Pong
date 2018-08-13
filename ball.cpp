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

void Ball::collision(int paddle1PosY, int paddle2PosY)
{
    ///up & down colision
    if((circle.getPosition().y <= 0)||(circle.getPosition().y + 40 >= WINDOW_HEIGTH))
    {
        UpDownVelocity = -UpDownVelocity;
    }

    ///colision with paddles
    if((((circle.getPosition().x <= 35)&&(circle.getPosition().x >= 15))&&((circle.getPosition().y >= paddle1PosY)&&(circle.getPosition().y <= paddle1PosY + 100)))
    ||(((circle.getPosition().x >= 1225)&&(circle.getPosition().x <= 1250))&&((circle.getPosition().y >= paddle2PosY)&&(circle.getPosition().y <= paddle2PosY + 100))))
    {
        LeftRightVelocity = - LeftRightVelocity;
    }
}
