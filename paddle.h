#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Paddle : public Entity
{
public:
    int velocity;
    Paddle(int=10, int=400, int=6);
    void movement(int = 1);
    void setVelocity(int);
};
