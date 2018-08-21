#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "entity.h"
#include "ball.h"
#include "paddle.h"
#include "lane.h"

#define BUTTON_SIZE Vector2f(300,100)
using namespace sf;

enum class Tstate{logos,menu,game};
Tstate state{Tstate::logos};

constexpr int WINDOW_WIDTH{1300};
constexpr int WINDOW_HEIGTH{900};

Text matchStartT;
int counter, counter2;
int score1, score2;
bool gamePause{true};

///------declarations of functions-------------------
void getPoint(Ball& ball,Text& s1,Text& s2,Paddle& paddle,Paddle& paddle2);
int random(int x);
///--------------------------------------------------

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Super Pong");
    window.setFramerateLimit(100);

    srand(time(NULL));

    ///loading*************************************************
    Font font1; font1.loadFromFile("resources/font1.ttf");
    Font font2; font2.loadFromFile("resources/font2.ttf");
    Texture MaineCoonLogoT;
    MaineCoonLogoT.loadFromFile("resources/MaineCoonLogo.jpg");
    Sprite MaineCoonLogoS(MaineCoonLogoT); MaineCoonLogoS.setScale(Vector2f(1.6,1.6));
    RectangleShape button1(BUTTON_SIZE);button1.setPosition(WINDOW_WIDTH/2 - 150, 250);
    button1.setFillColor(Color(12,147,4)); button1.setOutlineThickness(5);
    RectangleShape button2(BUTTON_SIZE);button2.setPosition(WINDOW_WIDTH/2 - 150, 400);
    button2.setFillColor(Color(9,18,142)); button2.setOutlineThickness(5);
    RectangleShape button3(BUTTON_SIZE);button3.setPosition(WINDOW_WIDTH/2 - 150, 550);
    button3.setFillColor(Color(5,142,146)); button3.setOutlineThickness(5);
    RectangleShape button4(BUTTON_SIZE);button4.setPosition(WINDOW_WIDTH/2 - 150, 700);
    button4.setFillColor(Color(213,2,34)); button4.setOutlineThickness(5);
    Text menuT1("SUPER PONG",font1,160); menuT1.setPosition(Vector2f(20, 20));
    Text menuT2("Career",font2,50); menuT2.setPosition(Vector2f(button1.getPosition().x + 55,button1.getPosition().y + 10));
    Text menuT3("Single match",font2,50); menuT3.setPosition(Vector2f(button2.getPosition().x + 5,button2.getPosition().y + 10));
    Text menuT4("Settings",font2,50); menuT4.setPosition(Vector2f(button3.getPosition().x + 60,button3.getPosition().y + 10));
    Text menuT5("Exit",font2,50); menuT5.setPosition(Vector2f(button4.getPosition().x + 95,button4.getPosition().y + 10));
    CircleShape circle(20); circle.setFillColor(Color::Yellow); circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
    matchStartT.setPosition(Vector2f(WINDOW_WIDTH/2 - 200, WINDOW_HEIGTH/2 + 15)); matchStartT.setFont(font2); matchStartT.setCharacterSize(50);// Text matchStartT("Player 1 will begin",font2,50);
    Ball ball;
    Paddle paddle1;
    Paddle paddle2(1265); paddle2.rect.setFillColor(Color::Cyan);
    Lane lane;
    Text score1T("0",font1,80);score1T.setPosition(Vector2f(505,10));
    Text score2T("0",font1,80);score2T.setPosition(Vector2f(721,10));
    Text gameSpeedL("SPEED",font2,20); gameSpeedL.setPosition(Vector2f(225,11));
    Text gameIncreaseL("INCREASE",font2,14); gameIncreaseL.setPosition(Vector2f(222,65));
    Text gameSpeedR("SPEED",font2,20); gameSpeedR.setPosition(Vector2f(1017,11));
    Text gameIncreaseR("INCREASE",font2,14); gameIncreaseR.setPosition(Vector2f(1014,65));

    ///end of the loading**************************************

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)){if (event.type == Event::Closed)window.close();}

        window.clear();

        ///state LOGOS*****************************************
        if(state == Tstate::logos)
        {
            window.draw(MaineCoonLogoS);
            counter++;
            if(counter>200)
            {
                state = Tstate::menu;
                counter = 1;
            }
        }
        ///*****************************************state LOGOS


        ///state MENU******************************************
        if(state == Tstate::menu)
        {
            window.draw(menuT1);
            window.draw(button1);
            window.draw(button2);
            window.draw(button3);
            window.draw(button4);
            window.draw(menuT2);
            window.draw(menuT3);
            window.draw(menuT4);
            window.draw(menuT5);
            window.draw(circle);

            if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                if(!counter2)
                {
                    if(counter == 4)
                    {
                        counter = 1;
                        circle.move(0,-450);
                    }else{
                        counter++;
                        circle.move(0,150);
                    }
                    counter2 = 12;
                }
                else counter2--;
            }

            if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                if(!counter2)
                {
                    if(counter == 1)
                    {
                        counter = 4;
                        circle.move(0,450);
                    }else{
                        counter--;
                        circle.move(0,-150);
                    }
                    counter2 = 11;
                }
                else counter2--;
            }

            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if(counter == 2)
                {
                    state = Tstate::game;
                    window.setFramerateLimit(60);
                    score1 = 0; score2 = 0; score1T.setString("0"); score2T.setString("0");
                    counter = 115; counter2 = 0;
                    lane.setIncrease1(144); lane.setIncrease2(144); lane.setSpeed1(144); lane.setSpeed2(144);
                    lane.minusSpeed1(0); lane.minusSpeed2(0); lane.minusIncrease1(0); lane.minusIncrease2(0);
                    gamePause = true;

                    if(random(2))//1
                    {
                        ball.circle.setPosition(Vector2f(35, WINDOW_HEIGTH/2 - 20));
                        matchStartT.setString("Player 1 will began");
                    }
                    else//2
                    {
                        ball.circle.setPosition(Vector2f(1225, WINDOW_HEIGTH/2 - 20));
                        matchStartT.setString("Player 2 will began");
                    }

                }
                else if(counter == 4)
                {
                    window.close();
                }
            }
        }
        ///******************************************state MENU


        ///state GAME******************************************
        if(state == Tstate::game)
        {
            if(Keyboard::isKeyPressed(Keyboard::Space))
            {
                window.setFramerateLimit(5);
            }
            else window.setFramerateLimit(60);

            if(Keyboard::isKeyPressed(Keyboard::R))
            {
                ball.circle.setPosition(Vector2f(WINDOW_WIDTH/2 - 20, WINDOW_HEIGTH/2 - 20));
                ball.setVelocity(10);
                paddle1.rect.setPosition(Vector2f(10,400));
                paddle2.rect.setPosition(Vector2f(1265,400));
                score1 = 0; score2 = 0;
                score1T.setString("0"); score2T.setString("0");
            }

            ///player 1 speed & increase
            if((Keyboard::isKeyPressed(Keyboard::A))&&(!gamePause))
            {
                bool x = lane.minusSpeed1(1);
                if(x) paddle1.setVelocity(12);
                else paddle1.setVelocity(6);
            }
            else paddle1.setVelocity(6);

            if(Keyboard::isKeyPressed(Keyboard::D))
            {
                lane.minusIncrease1(1);
            }

            ///player 2 speed & increase
            if((Keyboard::isKeyPressed(Keyboard::Left))&&(!gamePause))
            {
                bool x = lane.minusSpeed2(1);
                if(x) paddle2.setVelocity(12);
                else paddle2.setVelocity(6);
            }
            else paddle2.setVelocity(6);

            std::cout<<"1:"<<paddle1.velocity<<" 2:"<<paddle2.velocity<<std::endl;

            if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                lane.minusIncrease2(1);
            }

            if(!gamePause)
            {
            getPoint(ball,score1T,score2T,paddle1,paddle2);
            ball.collision(paddle1.rect.getPosition().y, paddle2.rect.getPosition().y);
            ball.updateMovement();
            paddle1.movement(2);
            paddle2.movement(1);
            }

            window.draw(ball.circle);
            window.draw(paddle1.rect);
            window.draw(paddle2.rect);
            window.draw(lane.rect);
            window.draw(lane.Lspeed);
            window.draw(lane.Lincrease);
            window.draw(lane.Rspeed);
            window.draw(lane.Rincrease);
            window.draw(lane.LspeedSubtitle);
            window.draw(lane.LincreaseSubtitle);
            window.draw(lane.Lscore);
            window.draw(lane.Rscore);
            window.draw(lane.RspeedSubtitle);
            window.draw(lane.RincreaseSubtitle);
            window.draw(score1T);
            window.draw(score2T);
            window.draw(gameSpeedL);
            window.draw(gameIncreaseL);
            window.draw(gameIncreaseR);
            window.draw(gameSpeedR);

            if(counter > 0)
            {
                window.draw(matchStartT);
                counter--;
                if(counter == 1) gamePause = false;
            }
            if(counter2 > 0)
            {
                window.draw(matchStartT);
                counter2--;
                if(counter2 < 55) gamePause = true;
                if(counter2 == 1)
                {
                    state = Tstate::menu;
                    circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
                    counter = 1; counter2 = 0;
                }
            }
        }
        ///******************************************state GAME

        window.display();
    }

    return 0;
}

void getPoint(Ball& ball,Text& s1,Text& s2,Paddle& paddle1,Paddle& paddle2)
{
    if((ball.circle.getPosition().x < - 45)||(ball.circle.getPosition().x > 1345))///if someone got point
    {
        paddle1.rect.setPosition(Vector2f(10,400));
        paddle2.rect.setPosition(Vector2f(1265,400));
        ball.setVelocity(10);
        counter =  100;
        gamePause = true;
    }
    if(ball.circle.getPosition().x < - 45)///if player 2 got point
    {
        ball.circle.setPosition(Vector2f(35, WINDOW_HEIGTH/2 - 20));
        matchStartT.setString("Player 1 will serw");

        score1++;
        if(score1 == 1) s2.setString("1");
        else if(score1 == 2) s2.setString("2");
        else if(score1 == 3) s2.setString("3");
        else if(score1 == 4)
        {
            s2.setString("4");
            matchStartT.setString("Player 2 won");
            gamePause = true;
            counter2 = 150;
        }
    }
    else if(ball.circle.getPosition().x > 1345)///if player 1 got point
    {
        ball.circle.setPosition(Vector2f(1225, WINDOW_HEIGTH/2 - 20));
        matchStartT.setString("Player 2 will serw");

        score2++;
        if(score2 == 1) s1.setString("1");
        else if(score2 == 2) s1.setString("2");
        else if(score2 == 3) s1.setString("3");
        else if(score2 == 4)
        {
            s1.setString("4");
            matchStartT.setString("Player 1 won");
            gamePause = true;
            counter2 = 150;
        }
    }
}

int random(int x)//how many lots
{
    int lot;
    lot = rand()%x;
    return lot;
}
