#include <SFML/Graphics.hpp>
#include "entity.h"
#include "ball.h"

#define BUTTON_SIZE Vector2f(300,100)
using namespace sf;

enum class Tstate{logos,menu,game};
Tstate state{Tstate::logos};

constexpr int WINDOW_WIDTH{1300};
constexpr int WINDOW_HEIGTH{900};

int counter;
int counter2;

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Super Pong");
    window.setFramerateLimit(100);

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
    Text menuT2("Campaign",font2,50); menuT2.setPosition(Vector2f(button1.getPosition().x + 25,button1.getPosition().y + 10));
    Text menuT3("Single match",font2,50); menuT3.setPosition(Vector2f(button2.getPosition().x + 5,button2.getPosition().y + 10));
    Text menuT4("Settings",font2,50); menuT4.setPosition(Vector2f(button3.getPosition().x + 60,button3.getPosition().y + 10));
    Text menuT5("Exit",font2,50); menuT5.setPosition(Vector2f(button4.getPosition().x + 95,button4.getPosition().y + 10));
    CircleShape circle(20); circle.setFillColor(Color::Yellow); circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
    Ball ball;
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
                    counter2 = 13;
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
                    counter2 = 13;
                }
                else counter2--;
            }

            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if(counter == 2)
                {
                    state = Tstate::game;
                    window.setFramerateLimit(60);
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
            ball.collision();
            ball.updateMovement();
            window.draw(ball.circle);
        }
        ///******************************************state GAME

        window.display();
    }

    return 0;
}
