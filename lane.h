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

    Lane();
    void setSpeed1(int);
    void setSpeed2(int);
    bool minusSpeed1(int);
    bool minusSpeed2(int);
    void setIncrease1(int);
    void setIncrease2(int);
    bool minusIncrease1(int);
    bool minusIncrease2(int);
};
