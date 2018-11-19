#include <SFML/Graphics.hpp>
#pragma once
using namespace sf;

class MouseEvents{
public:
    bool isOnMouse(RectangleShape, Vector2f mousePos);
    bool isOnMouse(int xPos, int yPos, int xSize, int ySize, Vector2f mousePos);
    bool left(Event);
    Window window;
};
