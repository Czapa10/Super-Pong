#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Ball : public Entity
{
    int UpDownVelocity{8};
    int LeftRightVelocity{8};
public:
    Ball();
    void updateMovement();
    void collision();
};
