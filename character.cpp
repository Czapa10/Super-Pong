#include <SFML/Graphics.hpp>
#include "character.h"

Character::Character(float speed_, float power_, float speedUp_, float speedUpContainer_,
                     float increase_, float increaseContainer_)
{
    speed = speed_;
    power = power_;
    speedUp = speedUp_;
    speedUpContainer = speedUpContainer_;
    increase = increase_;
    increaseContainer = increaseContainer_;
}
