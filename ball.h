#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Ball : public Entity
{
    float UpDownVelocity{10};
    float LeftRightVelocity{10};
public:
    Ball();
    void updateMovement();
    void collision(int paddle1PosY, int paddle2PosY);
    void setVelocity(float vel);
    void point();
};
