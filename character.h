#include <SFML/Graphics.hpp>
#include "entity.h"

class Character : public Entity
{
    float speed, power, speedUp, speedUpContainer, increase, increaseContainer;

public:
    Character(float = 6, float = 6, float = 6, float = 6, float = 6, float = 6);
};
