#include <SFML/Graphics.hpp>
#include "mouseEvents.h"
#include <iostream>
using namespace sf;

bool MouseEvents::isOnMouse(RectangleShape rect, Vector2f mousePos){
    if(  (mousePos.x > rect.getPosition().x)
       &&(mousePos.x < rect.getPosition().x + rect.getSize().x)
       &&(mousePos.y > rect.getPosition().y)
       &&(mousePos.y < rect.getPosition().y + rect.getSize().y)  )
    return true;
    return false;
}

bool MouseEvents::isOnMouse(CircleShape circle, Vector2f mousePos){
    if(  (mousePos.x > circle.getPosition().x)
       &&(mousePos.x < circle.getPosition().x + circle.getRadius() * 2)
       &&(mousePos.y > circle.getPosition().y)
       &&(mousePos.y < circle.getPosition().y + circle.getRadius() * 2)  )
    return true;
    return false;
}

bool MouseEvents::isOnMouse(int xPos, int yPos, int xSize, int ySize, Vector2f mousePos){
    if(  (mousePos.x > xPos)
       &&(mousePos.x < xPos + xSize)
       &&(mousePos.y > yPos)
       &&(mousePos.y < yPos + ySize)  )
    return true;
    return false;
}

bool MouseEvents::left(Event event){
    if(Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(event.key.code == Mouse::Left) return true;
        else  return false;
    }
    else  return false;
}

bool MouseEvents::left(){
    Event event;
    if(event.type == Event::MouseButtonPressed)
    {
        if(event.key.code == Mouse::Left) return true;
        else  return false;
    }
    else  return false;
}
