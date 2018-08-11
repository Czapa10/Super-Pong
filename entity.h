#include <SFML/Graphics.hpp>
#pragma once
using namespace sf;

class Entity
{
public:
    RectangleShape rect;
    CircleShape circle;
    Text text;
};

const extern int WINDOW_WIDTH;
const extern int WINDOW_HEIGTH;

