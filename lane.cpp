#include <SFML/Graphics.hpp>
#include "lane.h"

#define COLOR setFillColor(Color::Transparent);
#define OUT_COLOR setOutlineColor(Color::White);
#define OUT_CHIC setOutlineThickness(3);
using namespace sf;

Lane::Lane()
{
    ///whole table
    rect.setSize(Vector2f(WINDOW_WIDTH,100));
    rect.setFillColor(Color::Blue);
    rect.setOutlineThickness(3);

    ///left speed subtitle box
    LspeedSubtitle.setSize(Vector2f(72,50));
    LspeedSubtitle.setPosition(Vector2f(216,0));
    LspeedSubtitle.COLOR LspeedSubtitle.OUT_COLOR LspeedSubtitle.OUT_CHIC

    ///left increase subtitle box
    LincreaseSubtitle.setSize(Vector2f(72,50));
    LincreaseSubtitle.setPosition(Vector2f(216,50));
    LincreaseSubtitle.COLOR LincreaseSubtitle.OUT_COLOR LincreaseSubtitle.OUT_CHIC

    ///left speed box
    Lspeed.setSize(Vector2f(144,50));
    Lspeed.setPosition(Vector2f(288,0));
    Lspeed.setFillColor(Color(185,9,31));

    ///left increase box
    Lincrease.setSize(Vector2f(144,50));
    Lincrease.setPosition(Vector2f(288,50));
    Lincrease.setFillColor(Color(97,180,14));

    ///left score box
    Lscore.setSize(Vector2f(216,100));
    Lscore.setPosition(Vector2f(432,0));
    Lscore.COLOR Lscore.OUT_COLOR Lscore.OUT_CHIC

    ///right score box
    Rscore.setSize(Vector2f(215,100));
    Rscore.setPosition(Vector2f(648,0));
    Rscore.COLOR Rscore.OUT_COLOR Rscore.OUT_CHIC

    ///right speed box
    Rspeed.setSize(Vector2f(144,50));
    Rspeed.setPosition(Vector2f(1008,50));
    Rspeed.setRotation(180);
    Rspeed.setFillColor(Color(185,9,31));

    ///right increase box
    Rincrease.setSize(Vector2f(144,50));
    Rincrease.setPosition(Vector2f(1008,100));
    Rincrease.setRotation(180);
    Rincrease.setFillColor(Color(97,180,14));

    ///right speed subtitle box
    RspeedSubtitle.setSize(Vector2f(72,50));
    RspeedSubtitle.setPosition(Vector2f(1008,0));
    RspeedSubtitle.COLOR RspeedSubtitle.OUT_COLOR RspeedSubtitle.OUT_CHIC

    ///right increase subtitle box
    RincreaseSubtitle.setSize(Vector2f(72,50));
    RincreaseSubtitle.setPosition(Vector2f(1008,50));
    RincreaseSubtitle.COLOR RincreaseSubtitle.OUT_COLOR RincreaseSubtitle.OUT_CHIC
}

void Lane::setSpeed1(int x){speed1 = x;}

void Lane::setSpeed2(int x){speed2 = x;}

bool Lane::minusSpeed1(int x)
{

    if(speed1)
    {
        speed1 -= x;
        Lspeed.setSize(Vector2f(speed1,50));
        return 1;
    }
    else return 0;
}
bool Lane::minusSpeed2(int x)
{
    if(speed2)
    {
        speed2 -= x;
        Rspeed.setSize(Vector2f(speed2,50));
        return 1;
    }
    else return 0;
}

void Lane::setIncrease1(int x){increase1 = x;}

void Lane::setIncrease2(int x){increase2 = x;}

bool Lane::minusIncrease1(int x)
{
    if(increase1)
    {
        increase1 -= x;
        Lincrease.setSize(Vector2f(increase1,50));
        return 1;
    }
    else return 0;
}

bool Lane::minusIncrease2(int x)
{
    if(increase2)
    {
        increase2 -= x;
        Rincrease.setSize(Vector2f(increase2,50));
        return 1;
    }
    else return 0;
}
