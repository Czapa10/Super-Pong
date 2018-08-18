#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Ball : public Entity
{
    float UpDownVelocity{8};
    float LeftRightVelocity{8};
public:
    Ball();
    void updateMovement();
    void collision(int paddle1PosY, int paddle2PosY);
    void setVelocity(float vel);
};
