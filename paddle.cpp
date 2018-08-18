#include <SFML/Graphics.hpp>
#include "paddle.h"

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

void Paddle::movement(int control)///1-arrows | 2-awsd| 3-mouse
{
    if(control == 1)///arrows
    {
        if((Keyboard::isKeyPressed(Keyboard::Up))&&(rect.getPosition().y > 100))UP
        else if((Keyboard::isKeyPressed(Keyboard::Down))&&(rect.getPosition().y + 100 < WINDOW_HEIGTH)) DOWN
    }
    else if(control == 2)///awsd
    {
        if((Keyboard::isKeyPressed(Keyboard::W))&&(rect.getPosition().y > 100))UP
        else if((Keyboard::isKeyPressed(Keyboard::S))&&(rect.getPosition().y + 100 < WINDOW_HEIGTH)) DOWN
    }
}
