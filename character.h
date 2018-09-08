#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"

class Character : public Entity
{
    float speed, power, speedUp, speedUpContainer, increase, increaseContainer;
    std::string name;

public:
    Character(float = 6, float = 6, float = 6, float = 6, float = 6, float = 6, std::string = "Frog");

    std::string getName(){return name;}
    float getSpeed(){return speed;}
    float getPower(){return power;}
    float getSpeedUp(){return speedUp;}
    float getSpeedUpContainer(){return speedUpContainer;}
    float getIncrease(){return increase;}
    float getIncreaseContainer(){return increaseContainer;}
};
