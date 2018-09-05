#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "entity.h"
#include "ball.h"
#include "paddle.h"
#include "lane.h"
#include "character.h"

#define BUTTON_SIZE Vector2f(300,100)
using namespace sf;

enum class Tstate{logos,menu,game,singleOr2players,characterChoise};
Tstate state{Tstate::logos};

constexpr int WINDOW_WIDTH{1300};
constexpr int WINDOW_HEIGTH{900};

int counter, counter2, counter3, counter4, counter5;
int score1, score2;
bool gamePause{true};

///------declarations of functions-------------------
void getPoint(Ball& ball,Text& s1,Text& s2,Text& t1,Text& t2,Paddle& paddle,Paddle& paddle2);
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
    Texture MaineCoonLogoT; MaineCoonLogoT.loadFromFile("resources/MaineCoonLogo.jpg");
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
    RectangleShape pauseResume(BUTTON_SIZE); pauseResume.setPosition(Vector2f(500,350)); pauseResume.setOutlineThickness(5); pauseResume.setFillColor(Color(45,188,14));
    RectangleShape pauseExit(BUTTON_SIZE); pauseExit.setPosition(Vector2f(500,550)); pauseExit.setOutlineThickness(5); pauseExit.setFillColor(Color::Red);
    Text pauseResumeT("RESUME",font2,70); pauseResumeT.setPosition(Vector2f(532,360));
    Text pauseExitT("EXIT",font2,70); pauseExitT.setPosition(Vector2f(580,560));
    Text pauseSubtitleT("PAUSE",font2,130); pauseSubtitleT.setPosition(Vector2f(280,110)); pauseSubtitleT.setLetterSpacing(10);
    CircleShape circle(20); circle.setFillColor(Color::Yellow); circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
    CircleShape circle2(20); circle2.setFillColor(Color::Yellow); circle2.setPosition(Vector2f(pauseResume.getPosition().x - 50, pauseResume.getPosition().y + 30));
    Text matchStartT("Player 1 will begin",font2,50); matchStartT.setPosition(Vector2f(WINDOW_WIDTH/2 - 200, WINDOW_HEIGTH/2 + 15));
    Text matchWinT("player 1 won",font2,150); matchWinT.setFillColor(Color::Yellow); matchWinT.setPosition(Vector2f(WINDOW_WIDTH/2 - 400, WINDOW_HEIGTH/2 - 90));
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
    RectangleShape sinOr2pSingle(Vector2f(400,400)); sinOr2pSingle.setPosition(Vector2f(200,200)); sinOr2pSingle.setFillColor(Color(20,11,200));
    RectangleShape sinOr2pMulti(Vector2f(400,400)); sinOr2pMulti.setPosition(Vector2f(700,200)); sinOr2pMulti.setFillColor(Color(233,120,7));
    RectangleShape sinOr2pExit(Vector2f(900,200)); sinOr2pExit.setPosition(Vector2f(200,650)); sinOr2pExit.setFillColor(Color(213,2,34));
    Text sinOr2pChoiseT("CHOISE MODE",font1,115); sinOr2pChoiseT.setPosition(Vector2f(155,15));
    Text sinOr2pSingleT("1 player",font2,80); sinOr2pSingleT.setPosition(Vector2f(230,215));
    Text sinOr2pMultiT("2 players",font2,80); sinOr2pMultiT.setPosition(Vector2f(730,215));
    Text sinOr2pExitT("exit",font2,120); sinOr2pExitT.setPosition(Vector2f(530,660));
    Texture sinOr2pSingleTexture; sinOr2pSingleTexture.loadFromFile("resources/1player.png");
    Sprite sinOr2pSingleSprite(sinOr2pSingleTexture); sinOr2pSingleSprite.setScale(Vector2f(0.5,0.5)); sinOr2pSingleSprite.setPosition(Vector2f(300,345));
    Texture sinOr2pMultiTexture; sinOr2pMultiTexture.loadFromFile("resources/2player.png");
    Sprite sinOr2pMultiSprite(sinOr2pMultiTexture); sinOr2pMultiSprite.setScale(Vector2f(0.5,0.5)); sinOr2pMultiSprite.setPosition(Vector2f(700,345));
    Text characterChoiseT("CHARACTER CHOISE",font1,90); characterChoiseT.setPosition(Vector2f(100,10));
    Text characterChoiseT2("player 1",font2,85); characterChoiseT2.setPosition(Vector2f(480,105)); characterChoiseT2.setFillColor(Color(237,103,3));
    Text characterChoiseT3("player 2",font2,85); characterChoiseT3.setPosition(Vector2f(900,105)); characterChoiseT3.setFillColor(Color(26,64,215));
    RectangleShape characterChoiseRect1(Vector2f(120,120)); characterChoiseRect1.setPosition(Vector2f(565,245));
    RectangleShape characterChoiseRect2(Vector2f(120,120)); characterChoiseRect2.setPosition(Vector2f(1015,245));
    CircleShape triangle1(20,3); triangle1.setPosition(Vector2f(525,325)); triangle1.setRotation(-90);
    CircleShape triangle2(20,3); triangle2.setPosition(Vector2f(725,285)); triangle2.setRotation(90);
    CircleShape triangle3(20,3); triangle3.setPosition(Vector2f(975,325)); triangle3.setRotation(-90);
    CircleShape triangle4(20,3); triangle4.setPosition(Vector2f(1180,285)); triangle4.setRotation(90);
    Text characterChoiseName1T("el Gato",font2,65); characterChoiseName1T.setPosition(Vector2f(550,375)); characterChoiseName1T.setFillColor(Color::Yellow);
    Text characterChoiseName2T("Frog",font2,65); characterChoiseName2T.setPosition(Vector2f(1000,375)); characterChoiseName2T.setFillColor(Color::Yellow);
    Text characterChoiseSpeed1T("speed:",font2,50); characterChoiseSpeed1T.setPosition(Vector2f(15,465)); characterChoiseSpeed1T.setFillColor(Color(4,200,29));
    Text characterChoisePower1T("power:",font2,50); characterChoisePower1T.setPosition(Vector2f(15,515)); characterChoisePower1T.setFillColor(Color(208,21,35));
    Text characterChoiseSpeedUp1T("speed up:",font2,50); characterChoiseSpeedUp1T.setPosition(Vector2f(15,565)); characterChoiseSpeedUp1T.setFillColor(Color(11,107,149));
    Text characterChoiseSpeedUpContainer1T("speed up container:",font2,50); characterChoiseSpeedUpContainer1T.setPosition(Vector2f(15,615)); characterChoiseSpeedUpContainer1T.setFillColor(Color(230,207,2));
    Text characterChoiseIncrease1T("increase:",font2,50); characterChoiseIncrease1T.setPosition(Vector2f(15,665)); characterChoiseIncrease1T.setFillColor(Color(64,155,96));
    Text characterChoiseIncreaseContainer1T("increase container:",font2,50); characterChoiseIncreaseContainer1T.setPosition(Vector2f(15,715)); characterChoiseIncreaseContainer1T.setFillColor(Color(12,243,232));
    Text characterChoiseSpeed2T("6",font2,50); characterChoiseSpeed2T.setPosition(Vector2f(600,465)); characterChoiseSpeed2T.setFillColor(Color(4,200,29));
    Text characterChoiseSpeed3T("6",font2,50); characterChoiseSpeed3T.setPosition(Vector2f(1050,465)); characterChoiseSpeed3T.setFillColor(Color(4,200,29));
    Text characterChoisePower2T("6",font2,50); characterChoisePower2T.setPosition(Vector2f(600,515)); characterChoisePower2T.setFillColor(Color(208,21,35));
    Text characterChoisePower3T("6",font2,50); characterChoisePower3T.setPosition(Vector2f(1050,515)); characterChoisePower3T.setFillColor(Color(208,21,35));
    Text characterChoiseSpeedUp2T("6",font2,50); characterChoiseSpeedUp2T.setPosition(Vector2f(600,565)); characterChoiseSpeedUp2T.setFillColor(Color(11,107,149));
    Text characterChoiseSpeedUp3T("6",font2,50); characterChoiseSpeedUp3T.setPosition(Vector2f(1050,565)); characterChoiseSpeedUp3T.setFillColor(Color(11,107,149));
    Text characterChoiseSpeedUpContainer2T("6",font2,50); characterChoiseSpeedUpContainer2T.setPosition(Vector2f(600,615)); characterChoiseSpeedUpContainer2T.setFillColor(Color(230,207,2));
    Text characterChoiseSpeedUpContainer3T("6",font2,50); characterChoiseSpeedUpContainer3T.setPosition(Vector2f(1050,615)); characterChoiseSpeedUpContainer3T.setFillColor(Color(230,207,2));
    Text characterChoiseIncrease2T("6",font2,50); characterChoiseIncrease2T.setPosition(Vector2f(600,665)); characterChoiseIncrease2T.setFillColor(Color(64,155,96));
    Text characterChoiseIncrease3T("6",font2,50); characterChoiseIncrease3T.setPosition(Vector2f(1050,665)); characterChoiseIncrease3T.setFillColor(Color(64,155,96));
    Text characterChoiseIncreaseContainer2T("6",font2,50); characterChoiseIncreaseContainer2T.setPosition(Vector2f(600,715)); characterChoiseIncreaseContainer2T.setFillColor(Color(12,243,232));
    Text characterChoiseIncreaseContainer3T("6",font2,50); characterChoiseIncreaseContainer3T.setPosition(Vector2f(1050,715)); characterChoiseIncreaseContainer3T.setFillColor(Color(12,243,232));

    Character frog(5,4,3,5,6,5);
    Character elGato(8,3,7,2,6,5);
    Character kuszczak(4,6,4,4,8,10);
    Character gandalf(3,10,4,4,6,6);
    Character lennon(5,7,7,6,2,5);
    Character blackMan(10,8,10,10,2,3);
    Character alien(9,9,9,9,9,9);
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
        else if(state == Tstate::menu)
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
                    state = Tstate::singleOr2players;
                    counter = 1;
                    counter2 = 0;
                }
                else if(counter == 4)
                {
                    window.close();
                }
            }
        }
        ///******************************************state MENU


        ///state GAME******************************************
        else if(state == Tstate::game)
        {
            static bool pauseScreen{false};

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
                lane.setIncrease1(144); lane.setIncrease2(144); lane.setSpeed1(144); lane.setSpeed2(144);
                lane.minusSpeed1(0); lane.minusSpeed2(0); lane.minusIncrease1(0); lane.minusIncrease2(0);
            }

            ///pause screen
            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                if((!gamePause)&&(!pauseScreen)&&(counter3 == 0))
                {
                    pauseScreen = true;
                    gamePause = true;
                    counter3 = 12;
                    counter4 = 1;
                    counter5 = 0;
                }
                if((counter3 == 0)&&(pauseScreen))
                {
                    pauseScreen = false;
                    gamePause = false;
                    counter3 = 12;
                }
            }

            ///player 1 speed & increase
            if((Keyboard::isKeyPressed(Keyboard::A))&&(!gamePause))
            {
                bool x = lane.minusSpeed1(1);
                if(x) paddle1.setVelocity(12);
                else paddle1.setVelocity(6);
            }
            else paddle1.setVelocity(6);

            if((Keyboard::isKeyPressed(Keyboard::D))&&(!gamePause))
            {
                if(lane.minusIncrease1(1))paddle1.increase(1);
                else paddle1.increaseStop(1);
            }
            else paddle1.increaseStop(1);

            ///player 2 speed & increase
            if((Keyboard::isKeyPressed(Keyboard::Left))&&(!gamePause))
            {
                bool x = lane.minusSpeed2(1);
                if(x) paddle2.setVelocity(12);
                else paddle2.setVelocity(6);
            }
            else paddle2.setVelocity(6);

            if((Keyboard::isKeyPressed(Keyboard::Right))&&(!gamePause))
            {
                if(lane.minusIncrease2(1))paddle2.increase(2);
                else paddle2.increaseStop(2);
            }
            else paddle2.increaseStop(2);

            if(!gamePause)
            {
            getPoint(ball,score1T,score2T,matchStartT,matchWinT,paddle1,paddle2);
            ball.collision(paddle1.rect.getPosition().y, paddle2.rect.getPosition().y, paddle1.getIncrease(), paddle2.getIncrease());
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

            if((counter > 0)&&(!counter2))
            {
                window.draw(matchStartT);
                counter--;
                if(counter == 1) gamePause = false;
            }
            if(counter2 > 0)
            {
                window.draw(matchWinT);
                counter2--;
                if(counter2 < 55) gamePause = true;
                if(counter2 == 1)
                {
                    state = Tstate::menu;
                    circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
                    counter = 1; counter2 = 0;
                }
            }
            if(pauseScreen)
            {
                if(((Keyboard::isKeyPressed(Keyboard::Up))||(Keyboard::isKeyPressed(Keyboard::Down)))&&(!counter5))
                {
                    if(counter4 == 1)
                    {
                        circle2.setPosition(Vector2f(pauseExit.getPosition().x - 50, pauseExit.getPosition().y + 30));
                        counter4++;
                        counter5 = 12;
                    }
                    else
                    {
                        circle2.setPosition(Vector2f(pauseResume.getPosition().x - 50, pauseResume.getPosition().y + 30));
                        counter4--;
                        counter5 = 12;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(counter4 == 1)
                    {
                        pauseScreen = false;
                        gamePause = false;
                    }
                    else
                    {
                        state = Tstate::menu;
                        circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
                        counter = 1; counter2 = 0;
                        pauseScreen = false;
                    }
                }
                if(counter5 > 0)counter5--;

                window.draw(pauseSubtitleT);
                window.draw(pauseExit);
                window.draw(pauseResume);
                window.draw(pauseExitT);
                window.draw(pauseResumeT);
                window.draw(circle2);
            }
            if(counter3 > 0)counter3--;
        }
        ///******************************************state GAME


        ///state singleOr2players******************************
        else if(state == Tstate::singleOr2players)
        {
            window.draw(sinOr2pSingle);
            window.draw(sinOr2pMulti);
            window.draw(sinOr2pExit);
            window.draw(sinOr2pChoiseT);
            window.draw(sinOr2pSingleT);
            window.draw(sinOr2pMultiT);
            window.draw(sinOr2pExitT);
            window.draw(sinOr2pSingleSprite);
            window.draw(sinOr2pMultiSprite);

            if(counter == 1) sinOr2pSingle.setOutlineThickness(5);
            else sinOr2pSingle.setOutlineThickness(0);
            if(counter == 2) sinOr2pMulti.setOutlineThickness(5);
            else sinOr2pMulti.setOutlineThickness(0);
            if(counter == 3) sinOr2pExit.setOutlineThickness(5);
            else sinOr2pExit.setOutlineThickness(0);

            if(!counter2)
            {
                if(counter == 1)
                {
                    if(Keyboard::isKeyPressed(Keyboard::Right)){counter = 2; counter2 = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Down)){counter = 3; counter2 = 12;}
                }
                if(counter == 2)
                {
                    if(Keyboard::isKeyPressed(Keyboard::Left)){counter = 1; counter2 = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Down)){counter = 3; counter2 = 12;}
                }
                if(counter == 3)
                {
                    if(Keyboard::isKeyPressed(Keyboard::Up)){counter = 1; counter2 = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Left)){counter = 1; counter2 = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Right)){counter = 2; counter2 = 12;}
                }
            }
            if(counter2 > 0)counter2--;

            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if(counter == 1)
                {
                    state = Tstate::characterChoise;
                }
                else if(counter == 2)
                {
                    state = Tstate::game;
                    window.setFramerateLimit(60);
                    score1 = 0; score2 = 0; score1T.setString("0"); score2T.setString("0");
                    counter = 115; counter2 = 0;
                    lane.setIncrease1(144); lane.setIncrease2(144); lane.setSpeed1(144); lane.setSpeed2(144);
                    lane.minusSpeed1(0); lane.minusSpeed2(0); lane.minusIncrease1(0); lane.minusIncrease2(0);
                    gamePause = true;

                    state = Tstate::characterChoise;

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
                else if(counter == 3)
                {
                    state = Tstate::menu;
                    circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
                    counter = 1; counter2 = 0;
                }
            }
        }
        ///******************************state singleOr2players


        ///state character choise******************************
        else if(state == Tstate::characterChoise)
        {
            window.draw(characterChoiseT);
            window.draw(characterChoiseT2);
            window.draw(characterChoiseT3);
            window.draw(characterChoiseRect1);
            window.draw(characterChoiseRect2);
            window.draw(triangle1);
            window.draw(triangle2);
            window.draw(triangle3);
            window.draw(triangle4);
            window.draw(characterChoiseName1T);
            window.draw(characterChoiseName2T);
            window.draw(characterChoiseSpeed1T);
            window.draw(characterChoisePower1T);
            window.draw(characterChoiseSpeedUp1T);
            window.draw(characterChoiseSpeedUpContainer1T);
            window.draw(characterChoiseIncrease1T);
            window.draw(characterChoiseIncreaseContainer1T);
            window.draw(characterChoisePower2T);
            window.draw(characterChoisePower3T);
            window.draw(characterChoiseSpeed2T);
            window.draw(characterChoiseSpeed3T);
            window.draw(characterChoiseSpeedUp2T);
            window.draw(characterChoiseSpeedUp3T);
            window.draw(characterChoiseIncrease2T);
            window.draw(characterChoiseIncrease3T);
            window.draw(characterChoiseSpeedUpContainer2T);
            window.draw(characterChoiseSpeedUpContainer3T);
            window.draw(characterChoiseIncreaseContainer2T);
            window.draw(characterChoiseIncreaseContainer3T);
        }
        ///******************************state character choise

        window.display();
    }

    return 0;
}

void getPoint(Ball& ball,Text& s1,Text& s2,Text& t1,Text& t2,Paddle& paddle1,Paddle& paddle2)
{
    if((ball.circle.getPosition().x < - 45)||(ball.circle.getPosition().x > 1345))///if someone got point
    {
        paddle1.rect.setPosition(Vector2f(10,400));
        paddle2.rect.setPosition(Vector2f(1265,400));
        counter =  100;
        gamePause = true;
    }
    if(ball.circle.getPosition().x < - 45)///if player 2 got point
    {
        ball.circle.setPosition(Vector2f(35, WINDOW_HEIGTH/2 - 20));
        t1.setString("Player 1 will serw");
        ball.setVelocity(10);

        score1++;
        if(score1 == 1) s2.setString("1");
        else if(score1 == 2) s2.setString("2");
        else if(score1 == 3) s2.setString("3");
        else if(score1 == 4)
        {
            s2.setString("4");
            t2.setString("Player 2 won");
            gamePause = true;
            counter2 = 230;
        }
    }
    else if(ball.circle.getPosition().x > 1345)///if player 1 got point
    {
        ball.circle.setPosition(Vector2f(1225, WINDOW_HEIGTH/2 - 20));
        t1.setString("Player 2 will serw");
        ball.setVelocity(-10);

        score2++;
        if(score2 == 1) s1.setString("1");
        else if(score2 == 2) s1.setString("2");
        else if(score2 == 3) s1.setString("3");
        else if(score2 == 4)
        {
            s1.setString("4");
            t2.setString("Player 1 won");
            gamePause = true;
            counter2 = 230;
        }
    }
}

int random(int x)//how many lots
{
    int lot;
    lot = rand()%x;
    return lot;
}
