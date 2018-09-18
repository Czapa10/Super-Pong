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
    void collision(int paddle1PosY, int paddle2PosY, bool isIncreasing1, bool isIncreasing2,
                   float increase1, float increase2, float powerP1, float powerP2);
    void setVelocity(float vel);
};
