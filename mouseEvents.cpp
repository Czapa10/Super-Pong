#include <SFML/Graphics.hpp>
#include "mouseEvents.h"
#include <iostream>
using namespace sf;
extern RenderWindow window;

bool MouseEvents::isOnMouse(RectangleShape rect, Vector2f mousePos){
    if(  (mousePos.x > rect.getPosition().x)
       &&(mousePos.x < rect.getPosition().x + rect.getSize().x)
       &&(mousePos.y > rect.getPosition().y)
       &&(mousePos.y < rect.getPosition().y + rect.getSize().y)  )
    return true;
    else return false;
}

bool MouseEvents::isOnMouse(int xPos, int yPos, int xSize, int ySize, Vector2f mousePos){
    if(  (Mouse::getPosition(window).x > xPos)
       &&(Mouse::getPosition(window).x < xPos + xSize)
       &&(Mouse::getPosition(window).y > yPos)
       &&(Mouse::getPosition(window).y < yPos + ySize)  )
    return true;
    else return false;
}

bool MouseEvents::left(Event event){
    if(event.type == Event::MouseButtonPressed)
    {
        std::cout<<"key is pressed"<<std::endl;
        if(event.key.code == Mouse::Left) {std::cout<<"left"<<std::endl; return true;}
        else  return false;
    }
    else  return false;
}
