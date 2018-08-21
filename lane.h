#include <SFML/Graphics.hpp>
#include "entity.h"
using namespace sf;

class Lane : public Entity
{
    //int score1, score2;
    int speed1 = 144, speed2 = 144;
    int increase1 = 144, increase2 = 144;
public:
    RectangleShape LspeedSubtitle, LincreaseSubtitle, Lspeed, Lincrease, Lscore;
    RectangleShape RspeedSubtitle, RincreaseSubtitle, Rspeed, Rincrease, Rscore;
    Text score1T;

    Lane();
    void setSpeed1(int);
    void setSpeed2(int);
    void minusSpeed1(int);
    void minusSpeed2(int);
    void setIncrease1(int);
    void setIncrease2(int);
    void minusIncrease1(int);
    void minusIncrease2(int);
};
