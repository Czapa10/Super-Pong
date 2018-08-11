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

void Ball::collision()
{
    if((circle.getPosition().y <= 0)||(circle.getPosition().y + 40 >= WINDOW_HEIGTH))
    {
        UpDownVelocity = -UpDownVelocity;
    }
}
