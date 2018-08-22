#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Paddle : public Entity
{
    int velocity;
    bool isIncreasing{false};
public:
    Paddle(int=10, int=400, int=6);
    void movement(int = 1);
    void setVelocity(int);
    void increase(int padNumber = 1);
    void increaseStop(int padNumber);
    bool getIncrease();
};
