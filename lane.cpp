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
    Rspeed.setPosition(Vector2f(864,0));
    Rspeed.setFillColor(Color(185,9,31));

    ///right increase box
    Rincrease.setSize(Vector2f(144,50));
    Rincrease.setPosition(Vector2f(864,50));
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
