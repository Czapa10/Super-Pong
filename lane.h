#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Lane : public Entity
{
    //int score1, score2;
    //int speed1, speed2;
    //int increase1, increase2;
public:
    RectangleShape LspeedSubtitle, LincreaseSubtitle, Lspeed, Lincrease, Lscore;
    RectangleShape RspeedSubtitle, RincreaseSubtitle, Rspeed, Rincrease, Rscore;
    Text score1T;

    Lane();
    //void updateVariables();
};
