#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <algorithm>
#include "entity.h"
#include "ball.h"
#include "paddle.h"
#include "lane.h"
#include "character.h"

#define VERSION "BETA 0.6"
#define BUTTON_SIZE Vector2f(300,100)
using namespace sf;
using namespace std;

enum class Tstate{logos,menu,game,singleOr2players,characterChoise,controlsTip,dificultyLevel,settings,LnewGameOrcontinue,LcharacterChoise,
                  LdificultyLevel,LeagueInterface,exitScreen};
Tstate state{Tstate::logos};
enum class Tlevel{easy,medium,hard};
Tlevel difficultyLevel{Tlevel::easy};

constexpr int WINDOW_WIDTH{1300};
constexpr int WINDOW_HEIGTH{900};

int counter ,counterIncreaseBox1, counterSpeedUpBox1, counterIncreaseBox2, counterSpeedUpBox2;
int score1, score2;
int oneOr2Players;
bool gamePause{true};
bool showControlTip{true};
bool developerMode{false};
bool leagueMode;
bool doNextMatches;
int leagueInitialization; //1 - new game | 2 - continue | 0 - do nothing
int lengthOfTheMatch{4};
int paddle1Control, paddle2Control, controlIn1player{1};
Texture frogT; Texture gatoT; Texture kuszczakT; Texture gandalfT; Texture lennonT; Texture blackManT; Texture alienT; Texture pauseT;
Texture frogT2; Texture gatoT2; Texture kuszczakT2; Texture gandalfT2; Texture lennonT2; Texture blackManT2; Texture alienT2;
Character player1;
Character player2;
Character characterInLeague;
string opponentInLeagueMode;
string nameOfPlayer1, nameOfPlayer2;
int whoWon;
string nameMatch1a, nameMatch1b, nameMatch2a, nameMatch2b, nameMatch3a, nameMatch3b;
int inWhichMatchIsPlayerGLOBAL;
struct pos //auxiliary class to operate on league table
{
    string name;
    int numberOfPoints;
};
pos posInTable[7];
Character nothing;
Character chara[7]{nothing};//alien,blackMan,gandalf,elGato,frog,kuszczak,lennon
int table[7]{10}; //random chara

///------declarations of functions-------------------
void getPoint(Ball& ball,Text& s1,Text& s2,Text& t1,Text& t2,Paddle& paddle1,Paddle& paddle2,int& counterMatchStart, int& counterMatchWin);
void changeCharacterStatistics(int additionalMode,Sprite& sprite1,Sprite& sprite2,Sprite& spriteInGame1,Sprite& spriteInGame2,Text& name1,Text& name2,Text& speed1,Text& speed2,Text& power1,Text& power2Text,Text& speedUp1,Text& speedUp2,Text& speedUpContainer1,Text& speedUpContainer2,Text& increase1,Text& increase2,Text& increaseContainer1, Text& increaseContainer2,Character frog,Character gato,Character kuszczak,Character gandalf,Character lennon,Character black,Character alien);
void setLeagueTable(string nameOf1player,string nameOf2player, Text &name1,Text &name2,Text &name3,Text &name4,Text &name5,Text &name6,Text &name7,Text &points1,Text &points2,Text &points3,Text &points4,Text &points5,Text &points6,Text &points7);
void setPaddlesSpeed(Paddle& pad1,Paddle& pad2,Character p1,Character p2);
void setPaddlesSpeed(Paddle& pad1,Character p1);
void setPaddlesSpeed(Character p2,Paddle& pad2);
void myToUpper(char *letter);
string floatTostring(float x);
string intToStr(int n);
int random(int x);
///--------------------------------------------------

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Super Pong");
    window.setFramerateLimit(100);

    srand(time(NULL));

    ///loading graphics*************************************************
    Font font1; font1.loadFromFile("font1.ttf");
    Font font2; font2.loadFromFile("font2.ttf");
    Texture MaineCoonLogoT; MaineCoonLogoT.loadFromFile("MaineCoonLogo.jpg");
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
    Text menuT2("League",font2,50); menuT2.setPosition(Vector2f(button1.getPosition().x + 55,button1.getPosition().y + 10));
    Text menuT3("Single match",font2,50); menuT3.setPosition(Vector2f(button2.getPosition().x + 5,button2.getPosition().y + 10));
    Text menuT4("Settings",font2,50); menuT4.setPosition(Vector2f(button3.getPosition().x + 60,button3.getPosition().y + 10));
    Text menuT5("Exit",font2,50); menuT5.setPosition(Vector2f(button4.getPosition().x + 95,button4.getPosition().y + 10));
    Text versionT(VERSION,font2,40); versionT.setPosition(Vector2f(10,830));
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
    Ball AIball;
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
    Texture sinOr2pSingleTexture; sinOr2pSingleTexture.loadFromFile("1player.png");
    Sprite sinOr2pSingleSprite(sinOr2pSingleTexture); sinOr2pSingleSprite.setScale(Vector2f(0.5,0.5)); sinOr2pSingleSprite.setPosition(Vector2f(300,345));
    Texture sinOr2pMultiTexture; sinOr2pMultiTexture.loadFromFile("2player.png");
    Sprite sinOr2pMultiSprite(sinOr2pMultiTexture); sinOr2pMultiSprite.setScale(Vector2f(0.5,0.5)); sinOr2pMultiSprite.setPosition(Vector2f(700,345));
    Text characterChoiseT("CHARACTER CHOISE",font1,90); characterChoiseT.setPosition(Vector2f(100,10));
    Text characterChoiseT2("player 1",font2,85); characterChoiseT2.setPosition(Vector2f(480,105)); characterChoiseT2.setFillColor(Color(237,103,3));
    Text characterChoiseT3("player 2",font2,85); characterChoiseT3.setPosition(Vector2f(900,105)); characterChoiseT3.setFillColor(Color(26,64,215));
    frogT.loadFromFile("frog.jpg");
    gatoT.loadFromFile("gato.png");
    kuszczakT.loadFromFile("kuszczak.jpg");
    gandalfT.loadFromFile("gandalf.jpg");
    lennonT.loadFromFile("lennon.jpg");
    blackManT.loadFromFile("black-man.jpg");
    alienT.loadFromFile("alien.jpg");
    frogT2.loadFromFile("frog2.jpg");
    gatoT2.loadFromFile("gato2.png");
    kuszczakT2.loadFromFile("kuszczak2.jpg");
    gandalfT2.loadFromFile("gandalf2.jpg");
    lennonT2.loadFromFile("lennon2.jpg");
    blackManT2.loadFromFile("black-man2.jpg");
    alienT2.loadFromFile("alien2.jpg");
    pauseT.loadFromFile("pause-button.jpg");
    Sprite player1S(frogT); player1S.setPosition(Vector2f(565,245)); player1S.setTextureRect(IntRect(0,0,120,120));
    Sprite player2S(gatoT); player2S.setPosition(Vector2f(1015,245)); player2S.setTextureRect(IntRect(0,0,120,120));
    Sprite gameLeftPicture(frogT2); gameLeftPicture.setPosition(Vector2f(-5,0));
    Sprite gameRightPicture(gatoT2); gameRightPicture.setPosition(Vector2f(1085,0));
    CircleShape triangle1(20,3); triangle1.setPosition(Vector2f(525,325)); triangle1.setRotation(-90);
    CircleShape triangle2(20,3); triangle2.setPosition(Vector2f(725,285)); triangle2.setRotation(90);
    CircleShape triangle3(20,3); triangle3.setPosition(Vector2f(975,325)); triangle3.setRotation(-90);
    CircleShape triangle4(20,3); triangle4.setPosition(Vector2f(1180,285)); triangle4.setRotation(90);
    Text characterChoiseName1T("Frog",font2,65); characterChoiseName1T.setPosition(Vector2f(550,375)); characterChoiseName1T.setFillColor(Color::Yellow);
    Text characterChoiseName2T("el Gato",font2,65); characterChoiseName2T.setPosition(Vector2f(1000,375)); characterChoiseName2T.setFillColor(Color::Yellow);
    Text characterChoiseSpeed1T("speed:",font2,50); characterChoiseSpeed1T.setPosition(Vector2f(15,465)); characterChoiseSpeed1T.setFillColor(Color(4,200,29));
    Text characterChoisePower1T("power:",font2,50); characterChoisePower1T.setPosition(Vector2f(15,515)); characterChoisePower1T.setFillColor(Color(208,21,35));
    Text characterChoiseSpeedUp1T("speed up:",font2,50); characterChoiseSpeedUp1T.setPosition(Vector2f(15,565)); characterChoiseSpeedUp1T.setFillColor(Color(11,107,149));
    Text characterChoiseSpeedUpContainer1T("speed up container:",font2,50); characterChoiseSpeedUpContainer1T.setPosition(Vector2f(15,615)); characterChoiseSpeedUpContainer1T.setFillColor(Color(230,207,2));
    Text characterChoiseIncrease1T("increase:",font2,50); characterChoiseIncrease1T.setPosition(Vector2f(15,665)); characterChoiseIncrease1T.setFillColor(Color(64,155,96));
    Text characterChoiseIncreaseContainer1T("increase container:",font2,50); characterChoiseIncreaseContainer1T.setPosition(Vector2f(15,715)); characterChoiseIncreaseContainer1T.setFillColor(Color(12,243,232));
    Text characterChoiseSpeed2T("5",font2,50); characterChoiseSpeed2T.setPosition(Vector2f(600,465)); characterChoiseSpeed2T.setFillColor(Color(4,200,29));
    Text characterChoiseSpeed3T("8",font2,50); characterChoiseSpeed3T.setPosition(Vector2f(1050,465)); characterChoiseSpeed3T.setFillColor(Color(4,200,29));
    Text characterChoisePower2T("4",font2,50); characterChoisePower2T.setPosition(Vector2f(600,515)); characterChoisePower2T.setFillColor(Color(208,21,35));
    Text characterChoisePower3T("3",font2,50); characterChoisePower3T.setPosition(Vector2f(1050,515)); characterChoisePower3T.setFillColor(Color(208,21,35));
    Text characterChoiseSpeedUp2T("3",font2,50); characterChoiseSpeedUp2T.setPosition(Vector2f(600,565)); characterChoiseSpeedUp2T.setFillColor(Color(11,107,149));
    Text characterChoiseSpeedUp3T("7",font2,50); characterChoiseSpeedUp3T.setPosition(Vector2f(1050,565)); characterChoiseSpeedUp3T.setFillColor(Color(11,107,149));
    Text characterChoiseSpeedUpContainer2T("5",font2,50); characterChoiseSpeedUpContainer2T.setPosition(Vector2f(600,615)); characterChoiseSpeedUpContainer2T.setFillColor(Color(230,207,2));
    Text characterChoiseSpeedUpContainer3T("2",font2,50); characterChoiseSpeedUpContainer3T.setPosition(Vector2f(1050,615)); characterChoiseSpeedUpContainer3T.setFillColor(Color(230,207,2));
    Text characterChoiseIncrease2T("6",font2,50); characterChoiseIncrease2T.setPosition(Vector2f(600,665)); characterChoiseIncrease2T.setFillColor(Color(64,155,96));
    Text characterChoiseIncrease3T("6",font2,50); characterChoiseIncrease3T.setPosition(Vector2f(1050,665)); characterChoiseIncrease3T.setFillColor(Color(64,155,96));
    Text characterChoiseIncreaseContainer2T("5",font2,50); characterChoiseIncreaseContainer2T.setPosition(Vector2f(600,715)); characterChoiseIncreaseContainer2T.setFillColor(Color(12,243,232));
    Text characterChoiseIncreaseContainer3T("5",font2,50); characterChoiseIncreaseContainer3T.setPosition(Vector2f(1050,715)); characterChoiseIncreaseContainer3T.setFillColor(Color(12,243,232));
    Text characterChoiseExitT("Exit - ESC",font2,80); characterChoiseExitT.setPosition(Vector2f(150,780)); characterChoiseExitT.setFillColor(Color::Red);
    Text characterChoiseNextT("Next - ENTER",font2,80); characterChoiseNextT.setPosition(Vector2f(800,780)); characterChoiseNextT.setFillColor(Color::Green);
    Text characterChoiseAT("A",font2,20); characterChoiseAT.setPosition(Vector2f(540,290)); characterChoiseAT.setFillColor(Color::Black);
    Text characterChoiseDT("D",font2,20); characterChoiseDT.setPosition(Vector2f(695,290)); characterChoiseDT.setFillColor(Color::Black);
    Text controlsTipT("Controls",font2,100); controlsTipT.setPosition(Vector2f(450,5)); controlsTipT.setFillColor(Color::Yellow);
    Text controlsTipPlayT("ENTER - play",font2,80); controlsTipPlayT.setPosition(Vector2f(100,800)); controlsTipPlayT.setFillColor(Color::Green);
    Text controlsTipBackT("ESC - back",font2,80); controlsTipBackT.setPosition(Vector2f(800,800)); controlsTipBackT.setFillColor(Color::Red);
    Text controlsTipPlayer1T("player 1",font2,70); controlsTipPlayer1T.setPosition(Vector2f(100,100));
    Text controlsTipPlayer2T("player 2",font2,70); controlsTipPlayer2T.setPosition(Vector2f(850,100));
    Text controlsTipAT("SPEED UP",font2,65); controlsTipAT.setPosition(Vector2f(110,310));
    Text controlsTipWT("MOVE UP",font2,65); controlsTipWT.setPosition(Vector2f(110,410));
    Text controlsTipST("MOVE DOWN",font2,65); controlsTipST.setPosition(Vector2f(110,510));
    Text controlsTipDT("INCREASE",font2,65); controlsTipDT.setPosition(Vector2f(110,610));
    Text controlsTipLeftArrowT("SPEED UP",font2,65); controlsTipLeftArrowT.setPosition(Vector2f(915,310));
    Text controlsTipRightArrowT("INCREASE",font2,65); controlsTipRightArrowT.setPosition(Vector2f(905,410));
    Text controlsTipUpArrowT("MOVE UP",font2,65); controlsTipUpArrowT.setPosition(Vector2f(915,510));
    Text controlsTipDownArrowT("MOVE DOWN",font2,65); controlsTipDownArrowT.setPosition(Vector2f(815,610));
    RectangleShape blackBox(Vector2f(450,900)); blackBox.setFillColor(Color::Black);
    RectangleShape blackBox2(Vector2f(200,200)); blackBox2.setFillColor(Color::Black);
    RectangleShape blackBox3(Vector2f(850,680)); blackBox3.setFillColor(Color::Black); blackBox3.setPosition(Vector2f(0,110));
    RectangleShape blackBox4(Vector2f(650,900)); blackBox4.setFillColor(Color::Black);
    RectangleShape blackBox5(Vector2f(1300,200)); blackBox5.setFillColor(Color::Black); blackBox5.setPosition(Vector2f(0,700));
    Texture awsd; awsd.loadFromFile("awsd.png");
    Texture arrows; arrows.loadFromFile("KeyboardArrows.jpg");
    Sprite A(awsd); A.setTextureRect(IntRect(7,96,94,89)); A.setPosition(Vector2f(10,300));
    Sprite W(awsd); W.setTextureRect(IntRect(99,5,94,89)); W.setPosition(Vector2f(10,400));
    Sprite S(awsd); S.setTextureRect(IntRect(106,96,94,89)); S.setPosition(Vector2f(10,500));
    Sprite D(awsd); D.setTextureRect(IntRect(201,96,94,89)); D.setPosition(Vector2f(10,600));
    Sprite leftArrow(arrows); leftArrow.setTextureRect(IntRect(19,116,83,83)); leftArrow.setPosition(Vector2f(1196,300));
    Sprite rightArrow(arrows); rightArrow.setTextureRect(IntRect(200,116,83,83)); rightArrow.setPosition(Vector2f(1196,400));
    Sprite upArrow(arrows); upArrow.setTextureRect(IntRect(109,27,83,83)); upArrow.setPosition(Vector2f(1196,500));
    Sprite downArrow(arrows); downArrow.setTextureRect(IntRect(109,116,83,83)); downArrow.setPosition(Vector2f(1196,600));
    Text dificultyLevelT("DIFFICULTY LEVEL",font1,100); dificultyLevelT.setPosition(Vector2f(30,5));
    Text dificultyLevelEasyT("EASY",font2,50); dificultyLevelEasyT.setPosition(Vector2f(button1.getPosition().x + 80, button1.getPosition().y + 20));
    Text dificultyLevelMediumT("MEDIUM",font2,50); dificultyLevelMediumT.setPosition(Vector2f(button2.getPosition().x + 60, button2.getPosition().y + 20));
    Text dificultyLevelHardT("HARD",font2,50); dificultyLevelHardT.setPosition(Vector2f(button3.getPosition().x + 75, button3.getPosition().y + 20));
    Text dificultyLevelExitT("EXIT",font2,50); dificultyLevelExitT.setPosition(Vector2f(button4.getPosition().x + 80, button4.getPosition().y + 20));
    RectangleShape dificultyLevelEasyR(BUTTON_SIZE); dificultyLevelEasyR.setPosition(Vector2f(button1.getPosition().x, button1.getPosition().y)); dificultyLevelEasyR.setFillColor(Color::Green);
    RectangleShape dificultyLevelMediumR(BUTTON_SIZE); dificultyLevelMediumR.setPosition(Vector2f(button2.getPosition().x, button2.getPosition().y)); dificultyLevelMediumR.setFillColor(Color(236,111,9));
    RectangleShape dificultyLevelHardR(BUTTON_SIZE); dificultyLevelHardR.setPosition(Vector2f(button3.getPosition().x, button3.getPosition().y)); dificultyLevelHardR.setFillColor(Color(206,17,17));
    RectangleShape dificultyLevelExitR(BUTTON_SIZE); dificultyLevelExitR.setPosition(Vector2f(button4.getPosition().x, button4.getPosition().y)); dificultyLevelExitR.setFillColor(Color::Red);
    Text settingsT("SETTINGS",font1,100); settingsT.setPosition(Vector2f(300,5));
    Text settingsTExit("ESC - exit",font2,70); settingsTExit.setPosition(Vector2f(450,800)); settingsTExit.setFillColor(Color::Red);
    Text settingsTControlsInOnePlayer("Control in one player match:  Arrows",font2,60); settingsTControlsInOnePlayer.setPosition(Vector2f(50,200)); settingsTControlsInOnePlayer.setFillColor(Color::Yellow);
    Text settingsTShowControlsTip("Show control tip before match:  Yes",font2,60); settingsTShowControlsTip.setPosition(Vector2f(50,300));
    Text settingsTLengthOfMatch("Length Of Match:  4",font2,60); settingsTLengthOfMatch.setPosition(Vector2f(50,400));
    Text devT("Dev Mode",font2,20); devT.setPosition(Vector2f(5,870));
    Text devTgodMode("God Mode",font2,20); devTgodMode.setPosition(Vector2f(180,870));
    Text LcharacterChoiseT1("Welcome in the League Mode.",font2,47); LcharacterChoiseT1.setPosition(Vector2f(10,200));
    Text LcharacterChoiseT2("You'll play one match with every character.",font2,47); LcharacterChoiseT2.setPosition(Vector2f(10,300));
    Text LcharacterChoiseT3("Points will be saving in league table.",font2,47); LcharacterChoiseT3.setPosition(Vector2f(10,400));
    Text LcharacterChoiseT4("Choose your character and have a good fun!",font2,47); LcharacterChoiseT4.setPosition(Vector2f(10,500));
    Text LIexitT("Save & Exit - ESC",font2,80); LIexitT.setPosition(Vector2f(650,800)); LIexitT.setFillColor(Color::Red);
    Text LInextMatchT("Next match",font2,90); LInextMatchT.setPosition(Vector2f(110,110)); LInextMatchT.setFillColor(Color::Cyan);
    Text LIvsT("vs Frog",font2,90); LIvsT.setPosition(Vector2f(110,190)); LIvsT.setFillColor(Color::Cyan);
    Sprite LIvsS(frogT); LIvsS.setPosition(Vector2f(110,350)); LIvsS.setScale(Vector2f(3,3));
    Text LIlevelT("level of difficulty - Hard",font2,35); LIlevelT.setPosition(Vector2f(10,5));
    Text LItableT("TABLE",font2,100); LItableT.setPosition(Vector2f(900,1)); LItableT.setFillColor(Color::Yellow);
    Text LI1T("1.",font2,70); LI1T.setPosition(Vector2f(730,110)); LI1T.setFillColor(Color::Yellow);
    Text LI2T("2.",font2,70); LI2T.setPosition(Vector2f(730,190)); LI2T.setFillColor(Color::Yellow);
    Text LI3T("3.",font2,70); LI3T.setPosition(Vector2f(730,270)); LI3T.setFillColor(Color::Yellow);
    Text LI4T("4.",font2,70); LI4T.setPosition(Vector2f(730,350)); LI4T.setFillColor(Color::Yellow);
    Text LI5T("5.",font2,70); LI5T.setPosition(Vector2f(730,430)); LI5T.setFillColor(Color::Yellow);
    Text LI6T("6.",font2,70); LI6T.setPosition(Vector2f(730,510)); LI6T.setFillColor(Color::Yellow);
    Text LI7T("7.",font2,70); LI7T.setPosition(Vector2f(730,590)); LI7T.setFillColor(Color::Yellow);
    Text LI1nameT("Alien",font2,70); LI1nameT.setPosition(Vector2f(810,110)); LI1nameT.setFillColor(Color::Yellow);
    Text LI2nameT("Black Man",font2,70); LI2nameT.setPosition(Vector2f(810,190)); LI2nameT.setFillColor(Color::Yellow);
    Text LI3nameT("Gandalf",font2,70); LI3nameT.setPosition(Vector2f(810,270)); LI3nameT.setFillColor(Color::Yellow);
    Text LI4nameT("El Gato",font2,70); LI4nameT.setPosition(Vector2f(810,350)); LI4nameT.setFillColor(Color::Yellow);
    Text LI5nameT("Frog",font2,70); LI5nameT.setPosition(Vector2f(810,430)); LI5nameT.setFillColor(Color::Yellow);
    Text LI6nameT("Kuszczak",font2,70); LI6nameT.setPosition(Vector2f(810,510)); LI6nameT.setFillColor(Color::Yellow);
    Text LI7nameT("Lennon",font2,70); LI7nameT.setPosition(Vector2f(810,590)); LI7nameT.setFillColor(Color::Yellow);
    Text LI1pointsT("0",font2,70); LI1pointsT.setPosition(1200,110); LI1pointsT.setFillColor(Color::Yellow);
    Text LI2pointsT("0",font2,70); LI2pointsT.setPosition(1200,190); LI2pointsT.setFillColor(Color::Yellow);
    Text LI3pointsT("0",font2,70); LI3pointsT.setPosition(1200,270); LI3pointsT.setFillColor(Color::Yellow);
    Text LI4pointsT("0",font2,70); LI4pointsT.setPosition(1200,350); LI4pointsT.setFillColor(Color::Yellow);
    Text LI5pointsT("0",font2,70); LI5pointsT.setPosition(1200,430); LI5pointsT.setFillColor(Color::Yellow);
    Text LI6pointsT("0",font2,70); LI6pointsT.setPosition(1200,510); LI6pointsT.setFillColor(Color::Yellow);
    Text LI7pointsT("0",font2,70); LI7pointsT.setPosition(1200,590); LI7pointsT.setFillColor(Color::Yellow);
    Text LIsummaryT1("LEAGUE SUMMARY",font1,75); LIsummaryT1.setPosition(Vector2f(15,15)); LIsummaryT1.setFillColor(Color::Magenta);
    Text LIsummaryT2("CONGRATULATIONS!",font2,75); LIsummaryT2.setPosition(Vector2f(20,110)); LIsummaryT2.setFillColor(Color::Cyan);
    Text LIsummaryT3("You won the league",font2,75); LIsummaryT3.setPosition(Vector2f(20,200)); LIsummaryT3.setFillColor(Color::Cyan);
    Text LIsummaryT4("------------------",font2,75); LIsummaryT4.setPosition(Vector2f(20,290)); LIsummaryT4.setFillColor(Color::Cyan);
    Text LIsummaryT5("------------------",font2,75); LIsummaryT5.setPosition(Vector2f(20,380)); LIsummaryT5.setFillColor(Color::Cyan);
    Text LIsummaryTexit("ENTER - go to main menu",font2,90); LIsummaryTexit.setPosition(Vector2f(150,760)); LIsummaryTexit.setFillColor(Color::Green);
    Sprite LIsummaryS2_1(frogT); LIsummaryS2_1.setPosition(Vector2f(70,450)); LIsummaryS2_1.setScale(Vector2f(2,2));
    Sprite LIsummaryS2_2(gatoT); LIsummaryS2_2.setPosition(Vector2f(390,450)); LIsummaryS2_2.setScale(Vector2f(2,2));
    Sprite LIsummaryS3_1(frogT); LIsummaryS3_1.setPosition(Vector2f(30,510)); LIsummaryS3_1.setScale(Vector2f(1.5,1.5));
    Sprite LIsummaryS3_2(gatoT); LIsummaryS3_2.setPosition(Vector2f(260,510)); LIsummaryS3_2.setScale(Vector2f(1.5,1.5));
    Sprite LIsummaryS3_3(gandalfT); LIsummaryS3_3.setPosition(Vector2f(490,510)); LIsummaryS3_3.setScale(Vector2f(1.5,1.5));
    Text exitT("Game was made by",font1,90); exitT.setPosition(Vector2f(100,200)); Text exitT2("GRZEGORZ BEDNORZ",font2,100); exitT2.setPosition(Vector2f(150,350)); exitT2.setFillColor(Color::Yellow);

    Character frog(5,4,3,5,6,5,"frog");
    Character elGato(8,3,7,2,6,5,"gato");
    Character kuszczak(4,6,4,4,10,10,"kuszczak");
    Character gandalf(4,10,7,7,6,6,"gandalf");
    Character lennon(6,7,7,6,3,5,"lennon");
    Character blackMan(10,8,10,10,2,3,"black");
    Character alien(9,9,9,9,9,9,"alien");

    ///end of the loading**************************************

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)){if(event.type == Event::Closed)state = Tstate::exitScreen;}

        window.clear();

        ///state LOGOS*****************************************
        if(state == Tstate::logos)
        {
            static int counter{};
            window.draw(MaineCoonLogoS);
            counter++;
            if(counter>200)
            {
                state = Tstate::menu;
            }
        }
        ///*****************************************state LOGOS


        ///state MENU******************************************
        else if(state == Tstate::menu)
        {
            static int isSelected{1};
            static int counter{};

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
            window.draw(versionT);

            if(!counter)
            {
                if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if(isSelected == 4)
                    {
                        isSelected = 1;
                        circle.move(0,-450);
                    }else{
                        isSelected++;
                        circle.move(0,150);
                    }
                    counter = 12;
                }

                if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    if(isSelected == 1)
                    {
                        isSelected = 4;
                        circle.move(0,450);
                    }else{
                        isSelected--;
                        circle.move(0,-150);
                    }
                    counter = 11;
                }

                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(isSelected == 1)
                    {
                        state = Tstate::LnewGameOrcontinue;
                        leagueMode = true;
                    }
                    else if(isSelected == 2)
                    {
                        state = Tstate::singleOr2players;
                        leagueMode = false;
                    }
                    else if(isSelected == 3)
                    {
                        state = Tstate::settings;
                    }
                    else if(isSelected == 4)
                    {
                        state = Tstate::exitScreen;
                    }

                    isSelected = 1;
                    counter = 20;
                    circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
                }
            }else counter--;
        }
        ///******************************************state MENU


        ///state GAME******************************************
        else if(state == Tstate::game)
        {
            static bool pauseScreen{false};
            static int counterPause{};
            static int counterMatchStart{200};
            static int counterMatchWin{};
            static int counterPauseScreen{};
            static int isSelectedPauseMenu{1};
            static int godMode{};

            static bool strategyIsMade{false};
            static bool strategyIsSpeedUp; //true - speed up; false - increase;
            static int BonusAI; //0-nothing; 1-speed up; 2-increase; 3-both;
            static bool thereIsSpeedUp;
            static bool thereIsIncrease;

            if(!developerMode) window.setFramerateLimit(60);

            if(strategyIsMade == false)
            {
                if(controlIn1player == 1)
                {
                    if(player1.getSpeedUp() >= player1.getIncrease()) strategyIsSpeedUp = true;
                    else strategyIsSpeedUp = false;
                }
                else
                {
                    if(player2.getSpeedUp() >= player2.getIncrease()) strategyIsSpeedUp = true;
                    else strategyIsSpeedUp = false;
                }
            }

            ///pause screen
            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                if((!gamePause)&&(!pauseScreen)&&(counterPause == 0))
                {
                    pauseScreen = true;
                    gamePause = true;
                    counterPause = 12;
                    isSelectedPauseMenu = 1;
                }
                if((counterPause == 0)&&(pauseScreen))
                {
                    counterPause = 12;
                    pauseScreen = false;
                    gamePause = false;
                }
            }

            ///player 1 speed & increase
            if((((controlIn1player == 1)&&((BonusAI == 1)||(BonusAI == 3))) || ((Keyboard::isKeyPressed(Keyboard::A))&&((oneOr2Players == 2)||(controlIn1player == 2)))) && (!gamePause))
            {
                bool x;
                if(!counterSpeedUpBox1)
                {
                    x = lane.minusSpeed1(1);
                    thereIsSpeedUp = x;
                    counterSpeedUpBox1 = player1.getSpeedUpContainer();
                }
                else counterSpeedUpBox1--;

                if(x) paddle1.setVelocity(player1.getSpeed() + player1.getSpeedUp());
                else paddle1.setVelocity(player1.getSpeed());
            }
            else setPaddlesSpeed(paddle1,player1);

            if((((controlIn1player == 1)&&((BonusAI == 2)||(BonusAI == 3))) || ((Keyboard::isKeyPressed(Keyboard::D))&&((oneOr2Players == 2)||(controlIn1player == 2)))) && (!gamePause))
            {
                bool x;
                if(!counterIncreaseBox1)
                {
                    x = lane.minusIncrease1(1);
                    thereIsIncrease = x;
                    counterIncreaseBox1 = player1.getIncreaseContainer();
                }
                else counterIncreaseBox1--;

                if(x) paddle1.increase(1,player1.getIncrease());
                else paddle1.increaseStop(1,player1.getIncrease());
            }
            else paddle1.increaseStop(1,player1.getIncrease());

            ///player 2 speed & increase
            if((((controlIn1player == 2)&&((BonusAI == 1)||(BonusAI == 3))) || ((Keyboard::isKeyPressed(Keyboard::Left))&&((oneOr2Players == 2)||(controlIn1player == 1)))) && (!gamePause))
            {
                bool x;
                if(!counterSpeedUpBox2)
                {
                    x = lane.minusSpeed2(1);
                    thereIsSpeedUp = x;
                    counterSpeedUpBox2 = player2.getSpeedUpContainer();
                }
                else counterSpeedUpBox2--;

                if(x) paddle2.setVelocity(player2.getSpeed() + player2.getSpeedUp());
                else paddle2.setVelocity(player2.getSpeed());
            }
            else setPaddlesSpeed(player2,paddle2);

            if((((controlIn1player == 2)&&((BonusAI == 2)||(BonusAI == 3))) || ((Keyboard::isKeyPressed(Keyboard::Right))&&((oneOr2Players == 2)||(controlIn1player == 1)))) && (!gamePause))
            {
                bool x;
                if(!counterIncreaseBox2)
                {
                    x = lane.minusIncrease2(1);
                    thereIsIncrease = x;
                    counterIncreaseBox2 = player2.getIncreaseContainer();
                }
                else counterIncreaseBox2--;

                if(x) paddle2.increase(2,player2.getIncrease());
                else paddle2.increaseStop(2,player2.getIncrease());
            }
            else paddle2.increaseStop(2,player2.getIncrease());

            if(!gamePause)
            {
            getPoint(ball,score1T,score2T,matchStartT,matchWinT,paddle1,paddle2,counterMatchStart,counterMatchWin);
            ball.collision(paddle1.rect.getPosition().y, paddle2.rect.getPosition().y, paddle1.getIncrease(), paddle2.getIncrease(),
                           player1.getIncrease(), player2.getIncrease(), player1.getPower(), player2.getPower(), godMode);
            ball.updateMovement();
            paddle1.movement(paddle1Control);
            paddle2.movement(paddle2Control);
            }

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
            window.draw(gameLeftPicture);
            window.draw(gameRightPicture);
            window.draw(gameSpeedL);
            window.draw(gameIncreaseL);
            window.draw(gameIncreaseR);
            window.draw(gameSpeedR);
            window.draw(ball.circle);

            if(oneOr2Players == 1)
            {
                static bool isPositionCorect{false};

                int AIlevel; float AIballSpeed;
                if(difficultyLevel == Tlevel::easy){AIballSpeed = 2; AIlevel = 1;}
                else if(difficultyLevel == Tlevel::medium){AIballSpeed = 3; AIlevel = 2;}
                else if(difficultyLevel == Tlevel::hard){AIballSpeed = 3.5; AIlevel = 3.5;}

                if(!gamePause)
                {
                    if(controlIn1player == 1) BonusAI = paddle1.AI(AIlevel, AIball.circle.getPosition().y, AIball.circle.getPosition().x, ball.getVelocityLeftRight(), ball.circle.getPosition().y, ball.circle.getPosition().x, controlIn1player, strategyIsSpeedUp, player1.getSpeed(), thereIsSpeedUp, thereIsIncrease, player1.getSpeedUp());
                    if(controlIn1player == 2) BonusAI = paddle2.AI(AIlevel, AIball.circle.getPosition().y, AIball.circle.getPosition().x, ball.getVelocityLeftRight(), ball.circle.getPosition().y, ball.circle.getPosition().x, controlIn1player, strategyIsSpeedUp, player2.getSpeed(), thereIsSpeedUp, thereIsIncrease, player2.getSpeedUp());
                }

                if(((ball.getVelocityLeftRight() < 0)&&(ball.circle.getPosition().x < 1250)&&(controlIn1player == 1))||
                   ((ball.getVelocityLeftRight() > 0)&&(ball.circle.getPosition().x > 50)&&(controlIn1player == 2)))
                {
                    if(!isPositionCorect)
                    {
                        AIball.circle.setPosition(Vector2f(ball.circle.getPosition().x, ball.circle.getPosition().y));
                        AIball.setVelocityUpDown(ball.getVelocityUpDown() * AIballSpeed);
                        AIball.setVelocityLeftRight(ball.getVelocityLeftRight() * AIballSpeed);
                        isPositionCorect = true;
                    }
                    if(!gamePause)
                    {
                        AIball.collision(controlIn1player);
                        AIball.updateMovement();
                    }
                }
                else isPositionCorect = false;
            }

            if((counterMatchStart > 0)&&(score1 < lengthOfTheMatch)&&(score2 < lengthOfTheMatch))
            {
                window.draw(matchStartT);
                counterMatchStart--;
                if(counterMatchStart == 1) gamePause = false;
            }
            if(counterMatchWin > 0)
            {
                window.draw(matchWinT);
                counterMatchWin--;
                if(counterMatchWin < 55) gamePause = true;
                if(counterMatchWin == 1)
                {
                    if(leagueMode)
                    {
                        state = Tstate::LeagueInterface;
                        doNextMatches = true;

                        setLeagueTable(nameOfPlayer1, nameOfPlayer2,
                                       LI1nameT, LI2nameT, LI3nameT, LI4nameT, LI5nameT, LI6nameT, LI7nameT,
                                       LI1pointsT, LI2pointsT, LI3pointsT, LI4pointsT, LI5pointsT, LI6pointsT, LI7pointsT);
                    }
                    else
                    {
                        state = Tstate::menu;
                    }
                    pauseScreen = false;
                    gamePause = true;
                    counterMatchStart = 200;
                    counterMatchWin = 0;
                    developerMode = false;
                    godMode = 0;
                }
            }
            if(pauseScreen)
            {
                if(((Keyboard::isKeyPressed(Keyboard::Up))||(Keyboard::isKeyPressed(Keyboard::Down)))&&(!counterPauseScreen))
                {
                    if(isSelectedPauseMenu == 1)
                    {
                        circle2.setPosition(Vector2f(pauseExit.getPosition().x - 50, pauseExit.getPosition().y + 30));
                        isSelectedPauseMenu++;
                        counterPauseScreen = 12;
                    }
                    else
                    {
                        circle2.setPosition(Vector2f(pauseResume.getPosition().x - 50, pauseResume.getPosition().y + 30));
                        isSelectedPauseMenu--;
                        counterPauseScreen = 12;
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(isSelectedPauseMenu == 1)
                    {
                        pauseScreen = false;
                        gamePause = false;
                    }
                    else
                    {
                        state = Tstate::menu;
                        circle.setPosition(Vector2f(button1.getPosition().x - 50, button1.getPosition().y + 30));
                        circle2.setPosition(Vector2f(pauseResume.getPosition().x - 50, pauseResume.getPosition().y + 30));
                        pauseScreen = false;
                        gamePause = true;
                        counterMatchStart = 200;
                        counterMatchWin = 0;
                        window.setFramerateLimit(100);
                        developerMode = false;
                        godMode = 0;
                    }
                }
                if(counterPauseScreen > 0)counterPauseScreen--;

                window.draw(pauseSubtitleT);
                window.draw(pauseExit);
                window.draw(pauseResume);
                window.draw(pauseExitT);
                window.draw(pauseResumeT);
                window.draw(circle2);
            }
            if(counterPause > 0)counterPause--;


            if(developerMode)
            {
                static int counter{0};
                static bool slowMotion{false};
                static bool visibleAIball{false};

                if((Keyboard::isKeyPressed(Keyboard::LControl))&&(Keyboard::isKeyPressed(Keyboard::D))){developerMode = false; godMode = 0;}

                if((Keyboard::isKeyPressed(Keyboard::Space))&&(!counter))
                {
                    if(!slowMotion){window.setFramerateLimit(5); slowMotion = true;}
                    else{window.setFramerateLimit(60); slowMotion = false;}

                    if(slowMotion) counter = 1;
                    else counter = 12;
                }

                if((Keyboard::isKeyPressed(Keyboard::Home))&&(!counter))
                {
                    if(visibleAIball) visibleAIball = false;
                    else visibleAIball = true;

                    if(slowMotion) counter = 1;
                    else counter = 12;
                }

                if((Keyboard::isKeyPressed(Keyboard::G))&&(!counter)&&(oneOr2Players == 1))
                {
                    if(godMode) godMode = 0;
                    else
                    {
                        if(controlIn1player == 1)godMode = 1;
                        else godMode = 2;
                    }

                    if(slowMotion) counter = 1;
                    else counter = 12;
                }

                if(visibleAIball) window.draw(AIball.circle);

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

                if(counter)counter--;

                window.draw(devT);
                if(godMode) window.draw(devTgodMode);
            }
            else if((Keyboard::isKeyPressed(Keyboard::LControl))&&(Keyboard::isKeyPressed(Keyboard::D))) developerMode = true;
        }
        ///******************************************state GAME


        ///state SINGLE OR 2 PLAYERS******************************
        else if((state == Tstate::singleOr2players)||(state == Tstate::LnewGameOrcontinue))
        {
            if(state == Tstate::singleOr2players)
            {
                sinOr2pChoiseT.setString("CHOISE MODE");
                sinOr2pSingleT.setString("1 player");
                sinOr2pMultiT.setString("2 players");
                sinOr2pExitT.setString("exit");
            }
            else
            {
                sinOr2pChoiseT.setString("LEAGUE MODE");
                sinOr2pSingleT.setString("New game");
                sinOr2pMultiT.setString("Continue");
                sinOr2pExitT.setString("exit");
            }

            static int isSelected{1};
            static int counter{20};

            window.draw(sinOr2pChoiseT);
            window.draw(sinOr2pSingle);
            window.draw(sinOr2pMulti);
            window.draw(sinOr2pExit);
            window.draw(sinOr2pSingleT);
            window.draw(sinOr2pMultiT);
            window.draw(sinOr2pExitT);
            if(state == Tstate::singleOr2players)
            {
                window.draw(sinOr2pSingleSprite);
                window.draw(sinOr2pMultiSprite);
            }

            if(isSelected == 1) sinOr2pSingle.setOutlineThickness(5);
            else sinOr2pSingle.setOutlineThickness(0);
            if(isSelected == 2) sinOr2pMulti.setOutlineThickness(5);
            else sinOr2pMulti.setOutlineThickness(0);
            if(isSelected == 3) sinOr2pExit.setOutlineThickness(5);
            else sinOr2pExit.setOutlineThickness(0);

            if(!counter)
            {
                if(isSelected == 1)
                {
                    if(Keyboard::isKeyPressed(Keyboard::Right)){isSelected = 2; counter = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Down)){isSelected = 3; counter = 12;}
                }
                if(isSelected == 2)
                {
                    if(Keyboard::isKeyPressed(Keyboard::Left)){isSelected = 1; counter = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Down)){isSelected = 3; counter = 12;}
                }
                if(isSelected == 3)
                {
                    if(Keyboard::isKeyPressed(Keyboard::Up)){isSelected = 1; counter = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Left)){isSelected = 1; counter = 12;}
                    if(Keyboard::isKeyPressed(Keyboard::Right)){isSelected = 2; counter = 12;}
                }

                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(state == Tstate::singleOr2players)
                    {
                        if(isSelected == 1)
                        {
                            state = Tstate::characterChoise;
                            oneOr2Players = 1;

                            if(controlIn1player == 2)
                            {
                                paddle1Control = 2;
                                paddle2Control = 0;
                                characterChoiseT2.setString("player");
                                characterChoiseT3.setString("computer");
                            }
                            else
                            {
                                paddle1Control = 0;
                                paddle2Control = 1;
                                characterChoiseT2.setString("computer");
                                characterChoiseT3.setString("player");
                            }
                        }
                        else if(isSelected == 2)
                        {
                            state = Tstate::characterChoise;
                            oneOr2Players = 2;
                            paddle1Control = 2;
                            paddle2Control = 1;
                            characterChoiseT2.setString("player 1");
                            characterChoiseT3.setString("player 2");
                        }
                    }
                    else
                    {
                        if(isSelected == 1)
                        {
                            state = Tstate::LcharacterChoise;
                            leagueInitialization = 1;
                        }
                        else if(isSelected == 2)
                        {
                            fstream file;
                            file.open("save.txt",ios::in);

                            if(file.good() == true)
                            {
                                state = Tstate::LeagueInterface;
                                leagueInitialization = 2;
                            }
                        }
                        oneOr2Players = 1;
                    }


                    if(isSelected == 3)
                    {
                        state = Tstate::menu;
                        counter = 20;
                    }
                    isSelected = 1;
                    counter = 20;
                }
            }else counter--;
        }
        ///******************************state SINGLE OR 2 PLAYERS


        ///state CHARACTER CHOISE******************************
        else if((state == Tstate::characterChoise)||(state == Tstate::LcharacterChoise))
        {
            static int counter{30};

            changeCharacterStatistics(1,player1S, player2S, gameLeftPicture, gameRightPicture, characterChoiseName1T, characterChoiseName2T, characterChoiseSpeed2T, characterChoiseSpeed3T,
                                      characterChoisePower2T, characterChoisePower3T, characterChoiseSpeedUp2T, characterChoiseSpeedUp3T,
                                      characterChoiseSpeedUpContainer2T, characterChoiseSpeedUpContainer3T,
                                      characterChoiseIncrease2T, characterChoiseIncrease3T, characterChoiseIncreaseContainer2T, characterChoiseIncreaseContainer3T,
                                      frog, elGato, kuszczak, gandalf, lennon, blackMan, alien);

            if(Keyboard::isKeyPressed(Keyboard::Escape)&&(!counter))
            {
                if(state == Tstate::characterChoise) state = Tstate::singleOr2players;
                else state = Tstate::LnewGameOrcontinue;
                                    counter = 30;
                changeCharacterStatistics(2,player1S, player2S, gameLeftPicture, gameRightPicture, characterChoiseName1T, characterChoiseName2T, characterChoiseSpeed2T, characterChoiseSpeed3T,
                                      characterChoisePower2T, characterChoisePower3T, characterChoiseSpeedUp2T, characterChoiseSpeedUp3T,
                                      characterChoiseSpeedUpContainer2T, characterChoiseSpeedUpContainer3T,
                                      characterChoiseIncrease2T, characterChoiseIncrease3T, characterChoiseIncreaseContainer2T, characterChoiseIncreaseContainer3T,
                                      frog, elGato, kuszczak, gandalf, lennon, blackMan, alien);
            }
            else if((Keyboard::isKeyPressed(Keyboard::Enter))&&(!counter))
            {
                if(state == Tstate::characterChoise)
                {
                    if((oneOr2Players == 2)&&(showControlTip))state = Tstate::controlsTip;
                    else if((oneOr2Players == 2)&&(!showControlTip))state = Tstate::game;
                    else if((oneOr2Players == 1)&&(!showControlTip))state = Tstate::dificultyLevel;
                    else if((oneOr2Players == 1)&&(showControlTip))
                    {
                        state = Tstate::controlsTip;
                        if(controlIn1player == 1){blackBox.setPosition(Vector2f(0,0)); blackBox2.setPosition(Vector2f(450,450));}
                        else{blackBox.setPosition(Vector2f(850,0)); blackBox2.setPosition(Vector2f(700,550));}
                    }
                }

                counter = 30;

                ball.setVelocity(10);
                paddle1.rect.setPosition(Vector2f(10,400));
                paddle2.rect.setPosition(Vector2f(1265,400));
                score1 = 0; score2 = 0;
                score1T.setString("0"); score2T.setString("0");
                lane.setIncrease1(144); lane.setIncrease2(144); lane.setSpeed1(144); lane.setSpeed2(144);
                lane.minusSpeed1(0); lane.minusSpeed2(0); lane.minusIncrease1(0); lane.minusIncrease2(0);

                changeCharacterStatistics(3,player1S, player2S, gameLeftPicture, gameRightPicture, characterChoiseName1T, characterChoiseName2T, characterChoiseSpeed2T, characterChoiseSpeed3T,
                                      characterChoisePower2T, characterChoisePower3T, characterChoiseSpeedUp2T, characterChoiseSpeedUp3T,
                                      characterChoiseSpeedUpContainer2T, characterChoiseSpeedUpContainer3T,
                                      characterChoiseIncrease2T, characterChoiseIncrease3T, characterChoiseIncreaseContainer2T, characterChoiseIncreaseContainer3T,
                                      frog, elGato, kuszczak, gandalf, lennon, blackMan, alien);

                setPaddlesSpeed(paddle1,paddle2,player1,player2);

                if(state == Tstate::LcharacterChoise)
                {
                    state = Tstate::LdificultyLevel;
                }

                if(random(2))//1
                {
                    ball.circle.setPosition(Vector2f(35, WINDOW_HEIGTH/2 - 20));
                    if(oneOr2Players == 2)matchStartT.setString("Player 1 will begin");
                    else
                    {
                        if(controlIn1player == 1)matchStartT.setString("Computer will begin");
                        else matchStartT.setString("Player will begin");
                    }
                }
                else//2
                {
                    ball.circle.setPosition(Vector2f(1225, WINDOW_HEIGTH/2 - 20));
                    if(oneOr2Players == 2)matchStartT.setString("Player 2 will begin");
                    else
                    {
                        if(controlIn1player == 1)matchStartT.setString("Player will begin");
                        else matchStartT.setString("Computer will begin");
                    }
                }
            }
            if(counter) counter--;

            window.draw(characterChoiseT);
            window.draw(characterChoiseT2);
            if(state == Tstate::characterChoise) window.draw(characterChoiseT3);
            window.draw(player1S);
            window.draw(player2S);
            window.draw(triangle1);
            window.draw(triangle2);
            window.draw(triangle3);
            window.draw(triangle4);
            window.draw(characterChoiseAT);
            window.draw(characterChoiseDT);
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
            window.draw(characterChoiseExitT);
            window.draw(characterChoiseNextT);
            if(state == Tstate::LcharacterChoise)
            {
                window.draw(blackBox3);
                window.draw(LcharacterChoiseT1);
                window.draw(LcharacterChoiseT2);
                window.draw(LcharacterChoiseT3);
                window.draw(LcharacterChoiseT4);
            }
        }
        ///******************************state CHARACTER CHOISE


        ///state CONTROLS TIP******************************
        else if(state == Tstate::controlsTip)
        {
            static int counter{20};

            window.draw(controlsTipT);
            if(oneOr2Players == 2){window.draw(controlsTipPlayer1T); window.draw(controlsTipPlayer2T);}
            window.draw(controlsTipAT); window.draw(controlsTipWT); window.draw(controlsTipST); window.draw(controlsTipDT);
            window.draw(controlsTipLeftArrowT); window.draw(controlsTipRightArrowT); window.draw(controlsTipDownArrowT); window.draw(controlsTipUpArrowT);
            window.draw(A); window.draw(W); window.draw(S); window.draw(D);
            window.draw(rightArrow); window.draw(leftArrow); window.draw(upArrow); window.draw(downArrow);
            if(oneOr2Players == 1){window.draw(blackBox); window.draw(blackBox2);}
            window.draw(controlsTipPlayT);
            window.draw(controlsTipBackT);

            if(!counter)
            {
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(oneOr2Players == 2)state = Tstate::game;
                    else if(leagueMode == false) state = Tstate::dificultyLevel;
                    else state = Tstate::game;
                    counter = 20;
                }
                else if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    if(leagueMode) state = Tstate::LeagueInterface;
                    else state = Tstate::characterChoise;
                    counter = 20;
                }
            }
            else counter--;
        }
        ///******************************state CONTROLS TIP


        ///state DIFFICULTY LEVEL******************************
        else if((state == Tstate::dificultyLevel)||(state == Tstate::LdificultyLevel))
        {
            static int counter{0};
            static int counterEnter{25};
            static int whereIsOutline{1};

            if(whereIsOutline == 1) dificultyLevelEasyR.setOutlineThickness(5);
            else dificultyLevelEasyR.setOutlineThickness(0);
            if(whereIsOutline == 2) dificultyLevelMediumR.setOutlineThickness(5);
            else dificultyLevelMediumR.setOutlineThickness(0);
            if(whereIsOutline == 3) dificultyLevelHardR.setOutlineThickness(5);
            else dificultyLevelHardR.setOutlineThickness(0);
            if(whereIsOutline == 4) dificultyLevelExitR.setOutlineThickness(5);
            else dificultyLevelExitR.setOutlineThickness(0);

            if(!counter)
            {
                if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if(whereIsOutline == 4) whereIsOutline = 1;
                    else whereIsOutline++;
                    counter = 12;
                }
                else if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    if(whereIsOutline == 1) whereIsOutline = 4;
                    else whereIsOutline--;
                    counter = 12;
                }
            }
            else counter--;

            if((!counterEnter)&&(Keyboard::isKeyPressed(Keyboard::Enter)))
            {
                if(state == Tstate::dificultyLevel)
                {
                    if(whereIsOutline == 1)
                    {
                        state = Tstate::game;
                        difficultyLevel = Tlevel::easy;
                    }
                    else if(whereIsOutline == 2)
                    {
                        state = Tstate::game;
                        difficultyLevel = Tlevel::medium;
                    }
                    else if(whereIsOutline == 3)
                    {
                        state = Tstate::game;
                        difficultyLevel = Tlevel::hard;
                    }
                    else if(whereIsOutline == 4)
                    {
                        state = Tstate::characterChoise;
                    }
                }
                else
                {
                    if(whereIsOutline == 1)
                    {
                        state = Tstate::LeagueInterface;
                        difficultyLevel = Tlevel::easy;
                    }
                    else if(whereIsOutline == 2)
                    {
                        state = Tstate::LeagueInterface;
                        difficultyLevel = Tlevel::medium;
                    }
                    else if(whereIsOutline == 3)
                    {
                        state = Tstate::LeagueInterface;
                        difficultyLevel = Tlevel::hard;
                    }
                    else if(whereIsOutline == 4)
                    {
                        state = Tstate::LcharacterChoise;
                    }
                }

                counter = 0;
                counterEnter = 25;
                whereIsOutline = 1;
            }
            if(counterEnter > 0) counterEnter--;

            //rectangle shapes
            window.draw(dificultyLevelEasyR);
            window.draw(dificultyLevelMediumR);
            window.draw(dificultyLevelHardR);
            window.draw(dificultyLevelExitR);
            //texts
            window.draw(dificultyLevelT);
            window.draw(dificultyLevelEasyT);
            window.draw(dificultyLevelMediumT);
            window.draw(dificultyLevelHardT);
            window.draw(dificultyLevelExitT);
        }
        ///******************************state DIFFICULTY LEVEL


        ///state SETTINGS******************************
        else if(state == Tstate::settings)
        {
            static int isSelected{1};
            static int is1Selected{1};
            static int is2Selected{1};
            static int is3Selected{4};
            static int counter{12};

            if(Keyboard::isKeyPressed(Keyboard::Escape))
            {
                state = Tstate::menu;
                isSelected = 1;
                counter = 12;
            }

            if(!counter)
            {
                if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if(isSelected == 3) isSelected = 1;
                    else isSelected++;
                    counter = 12;
                }
                else if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    if(isSelected == 1) isSelected = 3;
                    else isSelected--;
                    counter = 12;
                }

                else if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(isSelected == 1)
                    {
                        if(is1Selected == 1){is1Selected++; controlIn1player = 2;}
                        else{is1Selected--; controlIn1player = 1;}
                        counter = 12;
                    }
                    if(isSelected == 2)
                    {
                        if(is2Selected == 1){is2Selected++; showControlTip = false;}
                        else{is2Selected--; showControlTip = true;}
                        counter = 12;
                    }
                    if(isSelected == 3)
                    {
                        if(is3Selected == 10)is3Selected = 1;
                        else is3Selected++;
                        lengthOfTheMatch = is3Selected;
                        counter = 12;
                    }
                }
            }
            else counter--;

            if(counter == 12)
            {
                if(isSelected == 1) settingsTControlsInOnePlayer.setFillColor(Color::Yellow);
                else settingsTControlsInOnePlayer.setFillColor(Color::White);
                if(isSelected == 2)settingsTShowControlsTip.setFillColor(Color::Yellow);
                else settingsTShowControlsTip.setFillColor(Color::White);
                if(isSelected == 3)settingsTLengthOfMatch.setFillColor(Color::Yellow);
                else settingsTLengthOfMatch.setFillColor(Color::White);

                if(isSelected == 1)
                {
                    if(is1Selected == 1) settingsTControlsInOnePlayer.setString("Control in one player match:  Arrows");
                    else settingsTControlsInOnePlayer.setString("Control in one player match:  AWSD");
                }
                else if(isSelected == 2)
                {
                    if(is2Selected == 1) settingsTShowControlsTip.setString("Show control tip before match:  Yes");
                    else settingsTShowControlsTip.setString("Show control tip before match:  No");
                }
                else if(isSelected == 3)
                {
                    if(is3Selected == 1) settingsTLengthOfMatch.setString("Length Of Match:  1");
                    else if(is3Selected == 2) settingsTLengthOfMatch.setString("Length Of Match:  2");
                    else if(is3Selected == 3) settingsTLengthOfMatch.setString("Length Of Match:  3");
                    else if(is3Selected == 4) settingsTLengthOfMatch.setString("Length Of Match:  4");
                    else if(is3Selected == 5) settingsTLengthOfMatch.setString("Length Of Match:  5");
                    else if(is3Selected == 6) settingsTLengthOfMatch.setString("Length Of Match:  6");
                    else if(is3Selected == 7) settingsTLengthOfMatch.setString("Length Of Match:  7");
                    else if(is3Selected == 8) settingsTLengthOfMatch.setString("Length Of Match:  8");
                    else if(is3Selected == 9) settingsTLengthOfMatch.setString("Length Of Match:  9");
                    else if(is3Selected == 10) settingsTLengthOfMatch.setString("Length Of Match:  10");
                }
            }

            window.draw(settingsT);
            window.draw(settingsTExit);
            window.draw(settingsTControlsInOnePlayer);
            window.draw(settingsTShowControlsTip);
            window.draw(settingsTLengthOfMatch);

        }
        ///******************************state SETTINGS


        ///LeagueInterface******************************
        else if(state == Tstate::LeagueInterface)
        {
            static int counter;
            static int matchDay;
            static string match1a;
            static string match1b;
            static string match2a;
            static string match2b;
            static string match3a;
            static string match3b;
            static string isPausing;
            static string inWhichMatchIsPlayer;
            static string currentOpponentName;

            int howManyWinners{1};
            bool isPlayerWinner;

            if(leagueInitialization == 1)///new league
            {
                cout<<"\nLEAGUE INITIALIZATION == 1 - New game\n";

                counter = 30;
                matchDay = 0;
                doNextMatches = true;
                match1a = ""; match1b = ""; match2a = ""; match2b = ""; match3a = ""; match3b = ""; isPausing = "";
                posInTable[0]={"alien",0};
                posInTable[1]={"black",0};
                posInTable[2]={"gandalf",0};
                posInTable[3]={"gato",0};
                posInTable[4]={"frog",0};
                posInTable[5]={"kuszczak",0};
                posInTable[6]={"lennon",0};

                alien.resetLeague(); blackMan.resetLeague(); gandalf.resetLeague(); elGato.resetLeague();
                frog.resetLeague(); kuszczak.resetLeague(); lennon.resetLeague();

                if(difficultyLevel == Tlevel::easy)LIlevelT.setString("level of difficulty - Easy");
                else if(difficultyLevel == Tlevel::medium)LIlevelT.setString("level of difficulty - Medium");
                else LIlevelT.setString("level of difficulty - Hard");

                leagueInitialization = 0;
            }
            else if(leagueInitialization == 2)///continue - loading save
            {
                cout<<"\nLEAGUE INITIALIZATION == 2 - New game\n";

                fstream file;
                file.open("save.txt",ios::in);

                string line;
                int lineNumber{1};
                int diffLevel; //auxiliary variable to take level of difficulty
                Character copyChara[7]{nothing};

                while(getline(file,line))
                {
                    switch(lineNumber)
                    {
                        case 1:     matchDay = atoi(line.c_str());                      break;
                        case 2:     match1a = line;                                     break;
                        case 3:     match1b = line;                                     break;
                        case 4:     match2a = line;                                     break;
                        case 5:     match2b = line;                                     break;
                        case 6:     match3a = line;                                     break;
                        case 7:     match3b = line;                                     break;
                        case 8:     isPausing = line;                                   break;
                        case 9:     inWhichMatchIsPlayer = line;                        break;
                        case 10:    currentOpponentName = line;
                                    if(line == "frog")LIvsS.setTexture(frogT);
                                    else if(line == "alien")LIvsS.setTexture(alienT);
                                    else if(line == "black")LIvsS.setTexture(blackManT);
                                    else if(line == "gandalf")LIvsS.setTexture(gandalfT);
                                    else if(line == "gato")LIvsS.setTexture(gatoT);
                                    else if(line == "lennon")LIvsS.setTexture(lennonT);
                                    else if(line == "kuszczak")LIvsS.setTexture(kuszczakT);
                                                                                        break;
                        case 11:    characterInLeague.setName(line);                    break;
                        case 12:    nameMatch1a = line;                                 break;
                        case 13:    nameMatch1b = line;                                 break;
                        case 14:    nameMatch2a = line;                                 break;
                        case 15:    nameMatch2b = line;                                 break;
                        case 16:    nameMatch3a = line;                                 break;
                        case 17:    nameMatch3b = line;                                 break;
                        case 18:    inWhichMatchIsPlayerGLOBAL = atoi(line.c_str());    break;
                        case 19:    posInTable[0].name = line;                          break;
                        case 20:    posInTable[0].numberOfPoints = atoi(line.c_str());  break;
                        case 21:    posInTable[1].name = line;                          break;
                        case 22:    posInTable[1].numberOfPoints = atoi(line.c_str());  break;
                        case 23:    posInTable[2].name = line;                          break;
                        case 24:    posInTable[2].numberOfPoints = atoi(line.c_str());  break;
                        case 25:    posInTable[3].name = line;                          break;
                        case 26:    posInTable[3].numberOfPoints = atoi(line.c_str());  break;
                        case 27:    posInTable[4].name = line;                          break;
                        case 28:    posInTable[4].numberOfPoints = atoi(line.c_str());  break;
                        case 29:    posInTable[5].name = line;                          break;
                        case 30:    posInTable[5].numberOfPoints = atoi(line.c_str());  break;
                        case 31:    posInTable[6].name = line;                          break;
                        case 32:    posInTable[6].numberOfPoints = atoi(line.c_str());  break;
                        case 33:    diffLevel = atoi(line.c_str());                     break;
                        case 34:    copyChara[0].setIplayedVs(line);                    break;
                        case 35:    copyChara[0].setIplayedVs(line);                    break;
                        case 36:    copyChara[0].setIplayedVs(line);                    break;
                        case 37:    copyChara[0].setIplayedVs(line);                    break;
                        case 38:    copyChara[0].setIplayedVs(line);                    break;
                        case 39:    copyChara[0].setIplayedVs(line);                    break;
                        case 40:    copyChara[1].setIplayedVs(line);                    break;
                        case 41:    copyChara[1].setIplayedVs(line);                    break;
                        case 42:    copyChara[1].setIplayedVs(line);                    break;
                        case 43:    copyChara[1].setIplayedVs(line);                    break;
                        case 44:    copyChara[1].setIplayedVs(line);                    break;
                        case 45:    copyChara[1].setIplayedVs(line);                    break;
                        case 46:    copyChara[2].setIplayedVs(line);                    break;
                        case 47:    copyChara[2].setIplayedVs(line);                    break;
                        case 48:    copyChara[2].setIplayedVs(line);                    break;
                        case 49:    copyChara[2].setIplayedVs(line);                    break;
                        case 50:    copyChara[2].setIplayedVs(line);                    break;
                        case 51:    copyChara[2].setIplayedVs(line);                    break;
                        case 52:    copyChara[3].setIplayedVs(line);                    break;
                        case 53:    copyChara[3].setIplayedVs(line);                    break;
                        case 54:    copyChara[3].setIplayedVs(line);                    break;
                        case 55:    copyChara[3].setIplayedVs(line);                    break;
                        case 56:    copyChara[3].setIplayedVs(line);                    break;
                        case 57:    copyChara[3].setIplayedVs(line);                    break;
                        case 58:    copyChara[4].setIplayedVs(line);                    break;
                        case 59:    copyChara[4].setIplayedVs(line);                    break;
                        case 60:    copyChara[4].setIplayedVs(line);                    break;
                        case 61:    copyChara[4].setIplayedVs(line);                    break;
                        case 62:    copyChara[4].setIplayedVs(line);                    break;
                        case 63:    copyChara[4].setIplayedVs(line);                    break;
                        case 64:    copyChara[5].setIplayedVs(line);                    break;
                        case 65:    copyChara[5].setIplayedVs(line);                    break;
                        case 66:    copyChara[5].setIplayedVs(line);                    break;
                        case 67:    copyChara[5].setIplayedVs(line);                    break;
                        case 68:    copyChara[5].setIplayedVs(line);                    break;
                        case 69:    copyChara[5].setIplayedVs(line);                    break;
                        case 70:    copyChara[6].setIplayedVs(line);                    break;
                        case 71:    copyChara[6].setIplayedVs(line);                    break;
                        case 72:    copyChara[6].setIplayedVs(line);                    break;
                        case 73:    copyChara[6].setIplayedVs(line);                    break;
                        case 74:    copyChara[6].setIplayedVs(line);                    break;
                        case 75:    copyChara[6].setIplayedVs(line);                    break;
                        case 76:    table[0] = atoi(line.c_str());                      break;
                        case 77:    table[1] = atoi(line.c_str());                      break;
                        case 78:    table[2] = atoi(line.c_str());                      break;
                        case 79:    table[3] = atoi(line.c_str());                      break;
                        case 80:    table[4] = atoi(line.c_str());                      break;
                        case 81:    table[5] = atoi(line.c_str());                      break;
                        case 82:    table[6] = atoi(line.c_str());                      break;
                    }

                    lineNumber++;
                }
                file.close();

                ///load difficulty level
                if(diffLevel == 1)difficultyLevel = Tlevel::easy;
                else if(diffLevel == 2)difficultyLevel = Tlevel::medium;
                else difficultyLevel = Tlevel::hard;

                if(difficultyLevel == Tlevel::easy)LIlevelT.setString("level of difficulty - Easy");
                else if(difficultyLevel == Tlevel::medium)LIlevelT.setString("level of difficulty - Medium");
                else LIlevelT.setString("level of difficulty - Hard");

                ///draw changes in table
                LI1nameT.setString(posInTable[0].name);
                LI1pointsT.setString(intToStr(posInTable[0].numberOfPoints));

                LI2nameT.setString(posInTable[1].name);
                LI2pointsT.setString(intToStr(posInTable[1].numberOfPoints));

                LI3nameT.setString(posInTable[2].name);
                LI3pointsT.setString(intToStr(posInTable[2].numberOfPoints));

                LI4nameT.setString(posInTable[3].name);
                LI4pointsT.setString(intToStr(posInTable[3].numberOfPoints));

                LI5nameT.setString(posInTable[4].name);
                LI5pointsT.setString(intToStr(posInTable[4].numberOfPoints));

                LI6nameT.setString(posInTable[5].name);
                LI6pointsT.setString(intToStr(posInTable[5].numberOfPoints));

                LI7nameT.setString(posInTable[6].name);
                LI7pointsT.setString(intToStr(posInTable[6].numberOfPoints));

                for(int i=0; i<7; i++)
                {
                    cout<<table[i]<<endl;
                }

                int j{};
                while((copyChara[0].getName() == nothing.getName())||(copyChara[1].getName() == nothing.getName())||(copyChara[2].getName() == nothing.getName())||(copyChara[3].getName() == nothing.getName())||(copyChara[4].getName() == nothing.getName())||(copyChara[5].getName() == nothing.getName())||(copyChara[6].getName() == nothing.getName()))
                {
                    switch(j)
                    {
                        case 0:
                            copyChara[table[0]].setName("alien");
                            //copyChara[table[0]].setStatistics()
                            break;
                        case 1:
                            copyChara[table[1]].setName("black");
                            break;
                        case 2:
                            copyChara[table[2]].setName("gandalf");
                            break;
                        case 3:
                            copyChara[table[3]].setName("gato");
                            break;
                        case 4:
                            copyChara[table[4]].setName("frog");
                            break;
                        case 5:
                            copyChara[table[5]].setName("kuszczak");
                            break;
                        case 6:
                            copyChara[table[6]].setName("lennon");
                            break;
                    }
                    j++;
                }

                for(int i=0; i<7; i++)
                {
                    cout<<copyChara[i].getName()<<endl;
                    chara[i] = copyChara[i];
                }

                leagueInitialization = 0;
                counter = 30;
            }

            if(matchDay > 6)///end of the league screen (logic)
            {
                ///check who won and how many persons won

                ///There are 6 options:
                ///1 - Only player won the league               (1 winner)
                ///2 - Player and one another character won     (2 winners)
                ///3 - Player and two another characters won    (3 winners)
                ///4 - Only one bot won the league              (1 winner)
                ///5 - Two bots won                             (2 winners)
                ///6 - Three bots won                           (3 winners)

                if(posInTable[0].numberOfPoints == posInTable[1].numberOfPoints)
                {
                    howManyWinners = 2;

                    if(posInTable[0].numberOfPoints == posInTable[2].numberOfPoints)
                    howManyWinners = 3;
                }

                int onWhichPlaceIsPlayer;

                for(int i=0; i<7; i++)
                {
                    if(characterInLeague.getName() == posInTable[i].name)
                    {
                        if(posInTable[i].numberOfPoints == posInTable[0].numberOfPoints) isPlayerWinner = true;
                        else isPlayerWinner = false;
                        onWhichPlaceIsPlayer = i;
                        break;
                    }
                }

                char *letterPointer = nullptr;
                if(isPlayerWinner)
                {
                    LIsummaryT2.setString("CONGRATULATIONS!");

                    switch(howManyWinners)
                    {
                    case 1:

                        LIsummaryT3.setString("You won the league");
                        break;

                    case 2:
                        {
                            string toSubtitle("You and ");
                            LIsummaryT4.setString("won the league");

                            string aux;
                            if(!onWhichPlaceIsPlayer)aux = posInTable[1].name;
                            else aux = posInTable[0].name;
                            if(aux == "gato") aux.insert(0,"el ");
                            letterPointer = &aux[0];
                            myToUpper(letterPointer);
                            if(aux == "black") aux = "Black man";
                            toSubtitle += aux;

                            LIsummaryT3.setString(toSubtitle);

                            break;
                        }
                    case 3:
                        {
                            string toSubtitle("You, ");
                            for(int i=0; i<2; i++)
                            {
                                if(i == 1) toSubtitle = "and ";

                                string aux;
                                if(onWhichPlaceIsPlayer == 0)aux = posInTable[i+1].name;
                                else if((onWhichPlaceIsPlayer == 1)&&(i == 0))aux = posInTable[i+1].name;
                                else if((onWhichPlaceIsPlayer == 1)&&(i == 1))aux = posInTable[2].name;
                                else aux = posInTable[i].name;

                                if(aux == "gato") aux.insert(0,"el ");
                                letterPointer = &aux[0];
                                myToUpper(letterPointer);
                                if(aux == "black") aux = "Black man";
                                toSubtitle += aux;

                                if(i == 0) LIsummaryT3.setString(toSubtitle);
                                else LIsummaryT4.setString(toSubtitle);
                            }

                            LIsummaryT5.setString("won the league");

                        break;
                        }
                    }
                }
                else
                {
                    {
                        string toSubtitles;
                        toSubtitles = "You finished ";

                        switch(onWhichPlaceIsPlayer)
                        {
                            case 1: toSubtitles += "second"; break;
                            case 2: toSubtitles += "third";  break;
                            case 3: toSubtitles += "fourth"; break;
                            case 4: toSubtitles += "fifth";  break;
                            case 5: toSubtitles += "sixth";  break;
                            case 6: toSubtitles += "seventh";break;
                        }

                        LIsummaryT2.setString(toSubtitles);
                    }

                    switch(howManyWinners)
                    {
                    case 1:
                        {
                            string toSubtitles(" won the league");
                            string aux(posInTable[0].name);
                            if(aux == "gato") aux.insert(0,"El ");
                            letterPointer = &aux[0];
                            myToUpper(letterPointer);
                            if(aux == "black") aux = "Black man";
                            toSubtitles.insert(0,aux);

                            LIsummaryT3.setString(toSubtitles);

                            break;
                        }
                    case 2:
                        {
                            string toSubtitle(" and ");
                            LIsummaryT4.setString("won the league");

                            for(int i=0; i<2; i++)
                            {
                                string aux{posInTable[i].name};
                                if(aux == "gato") aux.insert(0,"el ");
                                letterPointer = &aux[0];
                                myToUpper(letterPointer);
                                if(aux == "black") aux = "Black man";
                                if(!i)toSubtitle.insert(0,aux);
                                else toSubtitle += aux;
                            }

                            LIsummaryT3.setString(toSubtitle);

                            break;
                        }
                    case 3:
                        {
                            string toSubtitle(" , ");
                            for(int i=0; i<3; i++)
                            {
                                if(i == 2) toSubtitle = "and ";

                                string aux{posInTable[i].name};
                                if(aux == "gato") aux.insert(0,"el ");
                                letterPointer = &aux[0];
                                myToUpper(letterPointer);
                                if(aux == "black") aux = "Black man";
                                if(i == 0)toSubtitle.insert(0,aux);
                                else toSubtitle += aux;

                                if(i == 1) LIsummaryT3.setString(toSubtitle);
                                else if(i == 2) LIsummaryT4.setString(toSubtitle);
                            }

                            LIsummaryT5.setString("won the league");

                            break;
                        }
                    }
                }

                ///changing picture textures

                switch(howManyWinners)
                {
                case 1:
                    if(posInTable[0].name == "alien") LIvsS.setTexture(alienT);
                    else if(posInTable[0].name == "black") LIvsS.setTexture(blackManT);
                    else if(posInTable[0].name == "gato") LIvsS.setTexture(gatoT);
                    else if(posInTable[0].name == "gandalf") LIvsS.setTexture(gandalfT);
                    else if(posInTable[0].name == "lennon") LIvsS.setTexture(lennonT);
                    else if(posInTable[0].name == "frog") LIvsS.setTexture(frogT);
                    else if(posInTable[0].name == "kuszczak") LIvsS.setTexture(kuszczakT);
                    break;

                case 2:
                    if(posInTable[0].name == "alien") LIsummaryS2_1.setTexture(alienT);
                    else if(posInTable[0].name == "black") LIsummaryS2_1.setTexture(blackManT);
                    else if(posInTable[0].name == "gato") LIsummaryS2_1.setTexture(gatoT);
                    else if(posInTable[0].name == "gandalf") LIsummaryS2_1.setTexture(gandalfT);
                    else if(posInTable[0].name == "lennon") LIsummaryS2_1.setTexture(lennonT);
                    else if(posInTable[0].name == "frog") LIsummaryS2_1.setTexture(frogT);
                    else if(posInTable[0].name == "kuszczak") LIsummaryS2_1.setTexture(kuszczakT);

                    if(posInTable[1].name == "alien") LIsummaryS2_2.setTexture(alienT);
                    else if(posInTable[1].name == "black") LIsummaryS2_2.setTexture(blackManT);
                    else if(posInTable[1].name == "gato") LIsummaryS2_2.setTexture(gatoT);
                    else if(posInTable[1].name == "gandalf") LIsummaryS2_2.setTexture(gandalfT);
                    else if(posInTable[1].name == "lennon") LIsummaryS2_2.setTexture(lennonT);
                    else if(posInTable[1].name == "frog") LIsummaryS2_2.setTexture(frogT);
                    else if(posInTable[1].name == "kuszczak") LIsummaryS2_2.setTexture(kuszczakT);

                case 3:
                    if(posInTable[0].name == "alien") LIsummaryS3_1.setTexture(alienT);
                    else if(posInTable[0].name == "black") LIsummaryS3_1.setTexture(blackManT);
                    else if(posInTable[0].name == "gato") LIsummaryS3_1.setTexture(gatoT);
                    else if(posInTable[0].name == "gandalf") LIsummaryS3_1.setTexture(gandalfT);
                    else if(posInTable[0].name == "lennon") LIsummaryS3_1.setTexture(lennonT);
                    else if(posInTable[0].name == "frog") LIsummaryS3_1.setTexture(frogT);
                    else if(posInTable[0].name == "kuszczak") LIsummaryS3_1.setTexture(kuszczakT);

                    if(posInTable[1].name == "alien") LIsummaryS3_2.setTexture(alienT);
                    else if(posInTable[1].name == "black") LIsummaryS3_2.setTexture(blackManT);
                    else if(posInTable[1].name == "gato") LIsummaryS3_2.setTexture(gatoT);
                    else if(posInTable[1].name == "gandalf") LIsummaryS3_2.setTexture(gandalfT);
                    else if(posInTable[1].name == "lennon") LIsummaryS3_2.setTexture(lennonT);
                    else if(posInTable[1].name == "frog") LIsummaryS3_2.setTexture(frogT);
                    else if(posInTable[1].name == "kuszczak") LIsummaryS3_2.setTexture(kuszczakT);

                    if(posInTable[2].name == "alien") LIsummaryS3_3.setTexture(alienT);
                    else if(posInTable[2].name == "black") LIsummaryS3_3.setTexture(blackManT);
                    else if(posInTable[2].name == "gato") LIsummaryS3_3.setTexture(gatoT);
                    else if(posInTable[2].name == "gandalf") LIsummaryS3_3.setTexture(gandalfT);
                    else if(posInTable[2].name == "lennon") LIsummaryS3_3.setTexture(lennonT);
                    else if(posInTable[2].name == "frog") LIsummaryS3_3.setTexture(frogT);
                    else if(posInTable[2].name == "kuszczak") LIsummaryS3_3.setTexture(kuszczakT);
                }

            }


            try
            {
                if((doNextMatches)&&(matchDay < 7))
                {
                    matchDay++;

                    if(matchDay == 1)
                    {
                        int i2 = rand()%7;
                        for(int i=0; i<7; i++)
                        {
                            table[i] = i2;
                            i2++;
                            if(i2 == 7) i2 = 0;
                            cout<<i<<": "<<i2<<endl;
                        }

                        for(int i=0; i<10; i++)
                        {
                            int shuffling{rand()%4};
                            int aux;//auxiliary

                            cout<<"shuf: "<<shuffling<<endl;

                            switch(shuffling)
                            {
                            case 0:
                                aux = table[0];
                                table[0] = table[1];
                                table[1] = aux;
                                aux = table[2];
                                table[2] = table[3];
                                table[3] = aux;
                                aux = table[4];
                                table[4] = table[5];
                                table[5] = aux;
                                break;

                            case 1:
                                aux = table[0];
                                table[0] = table[6];
                                table[6] = aux;
                                aux = table[1];
                                table[1] = table[5];
                                table[5] = aux;
                                aux = table[2];
                                table[2] = table[4];
                                table[4] = aux;
                                break;

                            case 2:
                                aux = table[0];
                                table[0] = table[4];
                                table[4] = aux;
                                aux = table[1];
                                table[1] = table[5];
                                table[5] = aux;
                                aux = table[3];
                                table[3] = table[6];
                                table[6] = aux;
                                break;

                            case 3:
                                aux = table[0];
                                table[0] = table[2];
                                table[2] = aux;
                                aux = table[1];
                                table[1] = table[3];
                                table[3] = aux;
                                aux = table[4];
                                table[4] = table[6];
                                table[6] = aux;
                                break;
                            }

                            for(int i=0; i<7; i++)
                            {
                                cout<<table[i]<<endl;
                            }
                        }

                        int j{};
                        while((chara[0].getName() == nothing.getName())||(chara[1].getName() == nothing.getName())||(chara[2].getName() == nothing.getName())||(chara[3].getName() == nothing.getName())||(chara[4].getName() == nothing.getName())||(chara[5].getName() == nothing.getName())||(chara[6].getName() == nothing.getName()))
                        {
                            switch(j)
                            {
                                case 0:
                                    chara[table[0]] = alien;
                                    break;
                                case 1:
                                    chara[table[1]] = blackMan;
                                    break;
                                case 2:
                                    chara[table[2]] = gandalf;
                                    break;
                                case 3:
                                    chara[table[3]] = elGato;
                                    break;
                                case 4:
                                    chara[table[4]] = frog;
                                    break;
                                case 5:
                                    chara[table[5]] = kuszczak;
                                    break;
                                case 6:
                                    chara[table[6]] = lennon;
                                    break;
                            }
                            j++;
                        }


                    }

                    int whichMatchIsDoing{};
                    int baseCharacter{};
                    int character{};

                    match1a = ""; match1b = ""; match2a = ""; match2b = ""; match3a = ""; match3b = ""; isPausing = "";
                    for(int i=0; i<7; i++) {chara[i].setAmIinMatch(false); chara[i].setPaused(false);}

                    isPausing = chara[matchDay - 1].getName();
                    chara[matchDay - 1].setPaused(true);

                    while(whichMatchIsDoing < 3)
                    {
                        whichMatchIsDoing++;
                        cout<<endl<<"whichMatchIsDoing: "<<whichMatchIsDoing<<endl;

                        if(whichMatchIsDoing == 1)while(chara[character].getPaused() == false){character++;}
                        while((chara[character].getAmIinMatch() == true)||(chara[character].getPaused())){character++;}

                        if(character > 6) character = 0;

                        if(whichMatchIsDoing == 1) match1a = chara[character].getName();
                        if(whichMatchIsDoing == 2) match2a = chara[character].getName();
                        if(whichMatchIsDoing == 3) match3a = chara[character].getName();

                        baseCharacter = character;
                        while(1)
                        {
                            do{
                                character++;
                                if(character == 7) character = 0;
                            }
                            while(chara[character].getAmIinMatch() == true);

                            if((chara[baseCharacter].didIplayVs(chara[character].getName()) == false ) )
                            {
                                if(whichMatchIsDoing == 1) match1b = chara[character].getName();
                                else if(whichMatchIsDoing == 2) match2b = chara[character].getName();
                                else if(whichMatchIsDoing == 3) match3b = chara[character].getName();

                                chara[baseCharacter].setIplayedVs(chara[character].getName());
                                chara[character].setIplayedVs(chara[baseCharacter].getName());

                                chara[baseCharacter].setAmIinMatch(true);
                                chara[character].setAmIinMatch(true);

                                chara[baseCharacter].showWithWhoIplayed();
                                chara[character].showWithWhoIplayed();

                                break;
                            }
                        }
                    }
                    doNextMatches = false;


                    cout<<endl<<"Match day: "<<matchDay<<endl;
                    cout<<"1. "<<match1a<<" vs "<<match1b<<endl;
                    cout<<"2. "<<match2a<<" vs "<<match2b<<endl;
                    cout<<"3. "<<match3a<<" vs "<<match3b<<endl;
                    cout<<"is pausing: "<<isPausing<<endl;
                    cout<<endl<<"-----------------------------------------------------------------\n\n";

                    ///checking in which match is player's character
                    if(characterInLeague.getName() == match1a) inWhichMatchIsPlayer = "1a";
                    else if(characterInLeague.getName() == match1b) inWhichMatchIsPlayer = "1b";
                    else if(characterInLeague.getName() == match2a) inWhichMatchIsPlayer = "2a";
                    else if(characterInLeague.getName() == match2b) inWhichMatchIsPlayer = "2b";
                    else if(characterInLeague.getName() == match3a) inWhichMatchIsPlayer = "3a";
                    else if(characterInLeague.getName() == match3b) inWhichMatchIsPlayer = "3b";
                    else if(characterInLeague.getName() == isPausing) inWhichMatchIsPlayer = "pause";

                    ///checking current opponent name
                    if(inWhichMatchIsPlayer == "1a")currentOpponentName = match1b;
                    else if(inWhichMatchIsPlayer == "1b") currentOpponentName = match1a;
                    else if(inWhichMatchIsPlayer == "2a") currentOpponentName = match2b;
                    else if(inWhichMatchIsPlayer == "2b") currentOpponentName = match2a;
                    else if(inWhichMatchIsPlayer == "3a") currentOpponentName = match3b;
                    else if(inWhichMatchIsPlayer == "3b") currentOpponentName = match3a;
                    else if(inWhichMatchIsPlayer == "pause") currentOpponentName = "pause";

                    ///set text with name of your character in League interface (LInextMatchT)
                    if(characterInLeague.getName() == "alien") LInextMatchT.setString("Alien");
                    else if(characterInLeague.getName() == "black") LInextMatchT.setString("Black men");
                    else if(characterInLeague.getName() == "lennon") LInextMatchT.setString("Lennon");
                    else if(characterInLeague.getName() == "gandalf") LInextMatchT.setString("Gandalf");
                    else if(characterInLeague.getName() == "kuszczak") LInextMatchT.setString("Kuszczak");
                    else if(characterInLeague.getName() == "gato") LInextMatchT.setString("El gato");
                    else if(characterInLeague.getName() == "frog") LInextMatchT.setString("Frog");

                    ///set next match opponent text (LIvsT)
                    if(currentOpponentName == "alien") LIvsT.setString("vs Alien");
                    else if(currentOpponentName == "black") LIvsT.setString("vs Black men");
                    else if(currentOpponentName == "lennon") LIvsT.setString("vs Lennon");
                    else if(currentOpponentName == "gandalf") LIvsT.setString("vs Gandalf");
                    else if(currentOpponentName == "kuszczak") LIvsT.setString("vs Kuszczak");
                    else if(currentOpponentName == "gato") LIvsT.setString("vs El gato");
                    else if(currentOpponentName == "frog") LIvsT.setString("vs Frog");
                    else if(currentOpponentName == "pause") LIvsT.setString("is pausing");

                    ///set next match opponent portrait (LIvsS)
                    if(currentOpponentName == "alien") LIvsS.setTexture(alienT);
                    else if(currentOpponentName == "black") LIvsS.setTexture(blackManT);
                    else if(currentOpponentName == "lennon") LIvsS.setTexture(lennonT);
                    else if(currentOpponentName == "gandalf") LIvsS.setTexture(gandalfT);
                    else if(currentOpponentName == "kuszczak") LIvsS.setTexture(kuszczakT);
                    else if(currentOpponentName == "gato") LIvsS.setTexture(gatoT);
                    else if(currentOpponentName == "frog") LIvsS.setTexture(frogT);
                    else if(currentOpponentName == "pause") LIvsS.setTexture(pauseT);

                    if((inWhichMatchIsPlayer == "1a")||(inWhichMatchIsPlayer == "1b"))
                    {
                        nameMatch2a = match2a;  nameMatch2b = match2b;
                        nameMatch3a = match3a;  nameMatch3b = match3b;
                        inWhichMatchIsPlayerGLOBAL = 1;
                    }
                    else if((inWhichMatchIsPlayer == "2a")||(inWhichMatchIsPlayer == "2b"))
                    {
                        nameMatch1a = match1a;  nameMatch1b = match1b;
                        nameMatch3a = match3a;  nameMatch3b = match3b;
                        inWhichMatchIsPlayerGLOBAL = 2;
                    }
                    else if((inWhichMatchIsPlayer == "3a")||(inWhichMatchIsPlayer == "3b"))
                    {
                        nameMatch2a = match2a;  nameMatch2b = match2b;
                        nameMatch1a = match1a;  nameMatch1b = match1b;
                        inWhichMatchIsPlayerGLOBAL = 3;
                    }
                    else
                    {
                        nameMatch1a = match1a;  nameMatch1b = match1b;
                        nameMatch2a = match2a;  nameMatch2b = match2b;
                        nameMatch3a = match3a;  nameMatch3b = match3b;
                        inWhichMatchIsPlayerGLOBAL = 0;
                    }
                }
                else if(doNextMatches) matchDay = 8;
            }
            catch(logic_error)
            {
                cout<<endl<<"logic_error"<<endl;
            }

            if(((Keyboard::isKeyPressed(Keyboard::Escape))||((Keyboard::isKeyPressed(Keyboard::Enter))&&(matchDay == 8)))&&(!counter))
            {
                state = Tstate::menu;
                counter = 30;

                ///save in file
                fstream file;
                file.open("save.txt",ios::out);

                file<<matchDay<<endl;
                file<<match1a<<endl;
                file<<match1b<<endl;
                file<<match2a<<endl;
                file<<match2b<<endl;
                file<<match3a<<endl;
                file<<match3b<<endl;
                file<<isPausing<<endl;
                file<<inWhichMatchIsPlayer<<endl;
                file<<currentOpponentName<<endl;
                file<<characterInLeague.getName()<<endl;
                file<<nameMatch1a<<endl;
                file<<nameMatch1b<<endl;
                file<<nameMatch2a<<endl;
                file<<nameMatch2b<<endl;
                file<<nameMatch3a<<endl;
                file<<nameMatch3b<<endl;
                file<<inWhichMatchIsPlayerGLOBAL<<endl;

                for(int i=0; i<7; i++)
                {
                    file<<posInTable[i].name<<endl;
                    file<<posInTable[i].numberOfPoints<<endl;
                }

                if(difficultyLevel == Tlevel::easy)file<<1<<endl;
                else if(difficultyLevel == Tlevel::medium)file<<2<<endl;
                else file<<3<<endl;


                //with who I played


                file.close();

                for(int i=0; i<7; i++)
                {
                    chara[i].toFileWithWhoIplayed();
                }

                file.open("save.txt",ios::out | ios::app);

                for(int i=0; i<7; i++)
                {
                    file<<table[i]<<endl;
                }

                file.close();

                continue;
            }
            else if((Keyboard::isKeyPressed(Keyboard::Enter))&&(!counter))
            {
                if(isPausing == characterInLeague.getName())//while player is pausing in league
                {
                    setLeagueTable(nameOfPlayer1, nameOfPlayer2,
                                   LI1nameT, LI2nameT, LI3nameT, LI4nameT, LI5nameT, LI6nameT, LI7nameT,
                                   LI1pointsT, LI2pointsT, LI3pointsT, LI4pointsT, LI5pointsT, LI6pointsT, LI7pointsT);
                    doNextMatches = true;
                    counter = 30;
                    continue;
                }

                if(showControlTip == true) state = Tstate::controlsTip;
                else state = Tstate::game;

                opponentInLeagueMode = currentOpponentName;
                changeCharacterStatistics(4,player1S, player2S, gameLeftPicture, gameRightPicture, characterChoiseName1T, characterChoiseName2T, characterChoiseSpeed2T, characterChoiseSpeed3T,
                                  characterChoisePower2T, characterChoisePower3T, characterChoiseSpeedUp2T, characterChoiseSpeedUp3T,
                                  characterChoiseSpeedUpContainer2T, characterChoiseSpeedUpContainer3T,
                                  characterChoiseIncrease2T, characterChoiseIncrease3T, characterChoiseIncreaseContainer2T, characterChoiseIncreaseContainer3T,
                                  frog, elGato, kuszczak, gandalf, lennon, blackMan, alien);

                if(controlIn1player == 2)
                {
                    paddle1Control = 2;
                    paddle2Control = 0;
                    nameOfPlayer2 = characterInLeague.getName();
                    nameOfPlayer1 = currentOpponentName;
                }
                else
                {
                    paddle1Control = 0;
                    paddle2Control = 1;
                    nameOfPlayer1 = characterInLeague.getName();
                    nameOfPlayer2 = currentOpponentName;
                }

                if(controlIn1player == 1){blackBox.setPosition(Vector2f(0,0)); blackBox2.setPosition(Vector2f(450,450));}
                else{blackBox.setPosition(Vector2f(850,0)); blackBox2.setPosition(Vector2f(700,550));}

                ball.setVelocity(10);
                paddle1.rect.setPosition(Vector2f(10,400));
                paddle2.rect.setPosition(Vector2f(1265,400));
                score1 = 0; score2 = 0;
                score1T.setString("0"); score2T.setString("0");
                lane.setIncrease1(144); lane.setIncrease2(144); lane.setSpeed1(144); lane.setSpeed2(144);
                lane.minusSpeed1(0); lane.minusSpeed2(0); lane.minusIncrease1(0); lane.minusIncrease2(0);
                if(random(2))//1
                {
                    ball.circle.setPosition(Vector2f(35, WINDOW_HEIGTH/2 - 20));
                    if(oneOr2Players == 2)matchStartT.setString("Player 1 will begin");
                    else
                    {
                        if(controlIn1player == 1)matchStartT.setString("Computer will begin");
                        else matchStartT.setString("Player will begin");
                    }
                }
                else//2
                {
                    ball.circle.setPosition(Vector2f(1225, WINDOW_HEIGTH/2 - 20));
                    if(oneOr2Players == 2)matchStartT.setString("Player 2 will begin");
                    else
                    {
                        if(controlIn1player == 1)matchStartT.setString("Player will begin");
                        else matchStartT.setString("Computer will begin");
                    }
                }

                setPaddlesSpeed(paddle1,paddle2,player1,player2);

                counter = 30;
            }

            window.draw(LIlevelT);
            window.draw(LItableT);
            window.draw(LI1T); window.draw(LI1nameT); window.draw(LI1pointsT);
            window.draw(LI2T); window.draw(LI2nameT); window.draw(LI2pointsT);
            window.draw(LI3T); window.draw(LI3nameT); window.draw(LI3pointsT);
            window.draw(LI4T); window.draw(LI4nameT); window.draw(LI4pointsT);
            window.draw(LI5T); window.draw(LI5nameT); window.draw(LI5pointsT);
            window.draw(LI6T); window.draw(LI6nameT); window.draw(LI6pointsT);
            window.draw(LI7T); window.draw(LI7nameT); window.draw(LI7pointsT);
            window.draw(LInextMatchT);
            window.draw(LIvsT);
            window.draw(LIvsS);
            window.draw(controlsTipPlayT);
            window.draw(LIexitT);

            if((matchDay == 8)/*&&(doNextMatches == true)*/)///end of the league screen (drawing)
            {
                window.draw(blackBox4); window.draw(blackBox5);
                window.draw(LIsummaryT1); window.draw(LIsummaryT2); window.draw(LIsummaryT3);
                window.draw(LIsummaryTexit);
                switch(howManyWinners)//sprites
                {
                case 1:
                    window.draw(LIvsS);
                    break;
                case 2:
                    window.draw(LIsummaryS2_1); window.draw(LIsummaryS2_2);
                    break;
                case 3:
                    window.draw(LIsummaryS3_1); window.draw(LIsummaryS3_2); window.draw(LIsummaryS3_3);
                    break;
                }
                switch(howManyWinners)//texts
                {
                    case 3: window.draw(LIsummaryT5);
                    case 2: window.draw(LIsummaryT4);
                }
            }

            if(counter)counter--;

        }
        ///******************************LeagueInterface


        ///state EXIT SCREEN******************************
        else if(state == Tstate::exitScreen)
        {
            static int counter{200};
            counter--;
            window.draw(exitT);
            window.draw(exitT2);
            if(counter < 0)window.close();
        }
        ///******************************state EXIT SCREEN

        window.display();
    }

    return 0;
}

void getPoint(Ball& ball,Text& s1,Text& s2,Text& t1,Text& t2,Paddle& paddle1,Paddle& paddle2,int& counterMatchStart, int& counterMatchWin)
{
    if((ball.circle.getPosition().x < - 45)||(ball.circle.getPosition().x > 1345))///if someone got point
    {
        paddle1.rect.setPosition(Vector2f(10,400));
        paddle2.rect.setPosition(Vector2f(1265,400));
        counterMatchStart =  100;
        gamePause = true;
    }
    if(ball.circle.getPosition().x < - 45)///if player 2 got point
    {
        ball.circle.setPosition(Vector2f(45, WINDOW_HEIGTH/2 - 20));
        if(oneOr2Players == 2)t1.setString("Player 1 will serw");
        else
        {
            if(controlIn1player == 1)t1.setString("Computer will serw");
            else t1.setString("Player will serw");
        }
        ball.setVelocity(10);

        score1++;
        s2.setString(floatTostring(score1));

        if(score1 == lengthOfTheMatch)
        {
            if(oneOr2Players == 2)t2.setString("Player 2 won");
            else
            {
                if(controlIn1player == 1){t2.setString("Player won"); whoWon = 2;}
                else {t2.setString("Computer won"); whoWon = 1;}

            }
            gamePause = true;
            counterMatchWin = 230;
        }
    }
    else if(ball.circle.getPosition().x > 1345)///if player 1 got point
    {
        ball.circle.setPosition(Vector2f(1215, WINDOW_HEIGTH/2 - 20));
        if(oneOr2Players == 2)t1.setString("Player 2 will serw");
        else
        {
            if(controlIn1player == 1){t1.setString("Player will serw"); whoWon = 1;}
            else {t1.setString("Computer will serw"); whoWon = 2;}

        }
        ball.setVelocity(-10);

        score2++;
        s1.setString(floatTostring(score2));

        if(score2 == lengthOfTheMatch)
        {
            if(oneOr2Players == 2)t2.setString("Player 1 won");
            else
            {
                if(controlIn1player == 1)t2.setString("Computer won");
                else t2.setString("Player won");
            }
            gamePause = true;
            counterMatchWin = 230;
        }
    }
}

void changeCharacterStatistics(int additionalMode,Sprite& sprite1,Sprite& sprite2,Sprite& spriteInGame1,Sprite& spriteInGame2,
                               Text& name1,Text& name2,Text& speed1,Text& speed2,
                               Text& power1,Text& power2,Text& speedUp1,Text& speedUp2,Text& speedUpContainer1,Text& speedUpContainer2,
                               Text& increase1,Text& increase2,Text& increaseContainer1, Text& increaseContainer2,
                               Character frog,Character gato,Character kuszczak,
                               Character gandalf,Character lennon,Character black,Character alien)
{
    /// frog = 0        kuszczak = 2    lennon = 4      alien = 6
    /// el gato = 1     gandalf = 3     black man = 5

    static int player1 = 0;
    static int player2 = 1;
    static int counter1{};
    static int counter2{};
    bool wasPressed = false;

    if(additionalMode == 2)
    {
        player1 = 0;
        player2 = 1;

        sprite1.setTexture(frogT);
        name1.setString("Frog");
        speed1.setString(floatTostring(frog.getSpeed()));
        power1.setString(floatTostring(frog.getPower()));
        speedUp1.setString(floatTostring(frog.getSpeedUp()));
        speedUpContainer1.setString(floatTostring(frog.getSpeedUpContainer()));
        increase1.setString(floatTostring(frog.getIncrease()));
        increaseContainer1.setString(floatTostring(frog.getIncreaseContainer()));

        sprite2.setTexture(gatoT);
        name2.setString("el Gato");
        speed2.setString(floatTostring(gato.getSpeed()));
        power2.setString(floatTostring(gato.getPower()));
        speedUp2.setString(floatTostring(gato.getSpeedUp()));
        speedUpContainer2.setString(floatTostring(gato.getSpeedUpContainer()));
        increase2.setString(floatTostring(gato.getIncrease()));
        increaseContainer2.setString(floatTostring(gato.getIncreaseContainer()));
    }

    else if(additionalMode == 3)
    {
        if(player1 == 0) {spriteInGame1.setTexture(frogT2); ::player1.setStatistics(frog.getSpeed(),frog.getPower(),frog.getSpeedUp(),frog.getSpeedUpContainer(),frog.getIncrease(),frog.getIncreaseContainer());}
        else if(player1 == 1) {spriteInGame1.setTexture(gatoT2); ::player1.setStatistics(gato.getSpeed(),gato.getPower(),gato.getSpeedUp(),gato.getSpeedUpContainer(),gato.getIncrease(),gato.getIncreaseContainer());}
        else if(player1 == 2) {spriteInGame1.setTexture(kuszczakT2); ::player1.setStatistics(kuszczak.getSpeed(),kuszczak.getPower(),kuszczak.getSpeedUp(),kuszczak.getSpeedUpContainer(),kuszczak.getIncrease(),kuszczak.getIncreaseContainer());}
        else if(player1 == 3) {spriteInGame1.setTexture(gandalfT2); ::player1.setStatistics(gandalf.getSpeed(),gandalf.getPower(),gandalf.getSpeedUp(),gandalf.getSpeedUpContainer(),gandalf.getIncrease(),gandalf.getIncreaseContainer());}
        else if(player1 == 4) {spriteInGame1.setTexture(lennonT2); ::player1.setStatistics(lennon.getSpeed(),lennon.getPower(),lennon.getSpeedUp(),lennon.getSpeedUpContainer(),lennon.getIncrease(),lennon.getIncreaseContainer());}
        else if(player1 == 5) {spriteInGame1.setTexture(blackManT2); ::player1.setStatistics(black.getSpeed(),black.getPower(),black.getSpeedUp(),black.getSpeedUpContainer(),black.getIncrease(),black.getIncreaseContainer());}
        else if(player1 == 6) {spriteInGame1.setTexture(alienT2); ::player1.setStatistics(alien.getSpeed(),alien.getPower(),alien.getSpeedUp(),alien.getSpeedUpContainer(),alien.getIncrease(),alien.getIncreaseContainer());}

        if(player2 == 0) {spriteInGame2.setTexture(frogT2); ::player2.setStatistics(frog.getSpeed(),frog.getPower(),frog.getSpeedUp(),frog.getSpeedUpContainer(),frog.getIncrease(),frog.getIncreaseContainer());}
        else if(player2 == 1) {spriteInGame2.setTexture(gatoT2); ::player2.setStatistics(gato.getSpeed(),gato.getPower(),gato.getSpeedUp(),gato.getSpeedUpContainer(),gato.getIncrease(),gato.getIncreaseContainer());}
        else if(player2 == 2) {spriteInGame2.setTexture(kuszczakT2); ::player2.setStatistics(kuszczak.getSpeed(),kuszczak.getPower(),kuszczak.getSpeedUp(),kuszczak.getSpeedUpContainer(),kuszczak.getIncrease(),kuszczak.getIncreaseContainer());}
        else if(player2 == 3) {spriteInGame2.setTexture(gandalfT2); ::player2.setStatistics(gandalf.getSpeed(),gandalf.getPower(),gandalf.getSpeedUp(),gandalf.getSpeedUpContainer(),gandalf.getIncrease(),gandalf.getIncreaseContainer());}
        else if(player2 == 4) {spriteInGame2.setTexture(lennonT2); ::player2.setStatistics(lennon.getSpeed(),lennon.getPower(),lennon.getSpeedUp(),lennon.getSpeedUpContainer(),lennon.getIncrease(),lennon.getIncreaseContainer());}
        else if(player2 == 5) {spriteInGame2.setTexture(blackManT2); ::player2.setStatistics(black.getSpeed(),black.getPower(),black.getSpeedUp(),black.getSpeedUpContainer(),black.getIncrease(),black.getIncreaseContainer());}
        else if(player2 == 6) {spriteInGame2.setTexture(alienT2); ::player2.setStatistics(alien.getSpeed(),alien.getPower(),alien.getSpeedUp(),alien.getSpeedUpContainer(),alien.getIncrease(),alien.getIncreaseContainer());}

        if(state == Tstate::LcharacterChoise)
        {
            characterInLeague.setStatistics(::player2.getSpeed(),::player2.getPower(),::player2.getSpeedUp(),::player2.getSpeedUpContainer(),::player2.getIncrease(),::player2.getIncreaseContainer());
            switch(player2)
            {
                case 0: characterInLeague.setName(frog.getName());      break;
                case 1: characterInLeague.setName(gato.getName());      break;
                case 2: characterInLeague.setName(kuszczak.getName());  break;
                case 3: characterInLeague.setName(gandalf.getName());   break;
                case 4: characterInLeague.setName(lennon.getName());    break;
                case 5: characterInLeague.setName(black.getName());     break;
                case 6: characterInLeague.setName(alien.getName());     break;
            }
            cout<<"character in league: "<<characterInLeague.getName()<<endl<<endl;
        }
    }
    else if(additionalMode == 4)
    {
        if(controlIn1player == 1)
        {
            if(opponentInLeagueMode == "frog") {spriteInGame1.setTexture(frogT2); ::player1.setStatistics(frog.getSpeed(),frog.getPower(),frog.getSpeedUp(),frog.getSpeedUpContainer(),frog.getIncrease(),frog.getIncreaseContainer());}
            else if(opponentInLeagueMode == "gato") {spriteInGame1.setTexture(gatoT2); ::player1.setStatistics(gato.getSpeed(),gato.getPower(),gato.getSpeedUp(),gato.getSpeedUpContainer(),gato.getIncrease(),gato.getIncreaseContainer());}
            else if(opponentInLeagueMode == "kuszczak") {spriteInGame1.setTexture(kuszczakT2); ::player1.setStatistics(kuszczak.getSpeed(),kuszczak.getPower(),kuszczak.getSpeedUp(),kuszczak.getSpeedUpContainer(),kuszczak.getIncrease(),kuszczak.getIncreaseContainer());}
            else if(opponentInLeagueMode == "gandalf") {spriteInGame1.setTexture(gandalfT2); ::player1.setStatistics(gandalf.getSpeed(),gandalf.getPower(),gandalf.getSpeedUp(),gandalf.getSpeedUpContainer(),gandalf.getIncrease(),gandalf.getIncreaseContainer());}
            else if(opponentInLeagueMode == "lennon") {spriteInGame1.setTexture(lennonT2); ::player1.setStatistics(lennon.getSpeed(),lennon.getPower(),lennon.getSpeedUp(),lennon.getSpeedUpContainer(),lennon.getIncrease(),lennon.getIncreaseContainer());}
            else if(opponentInLeagueMode == "black") {spriteInGame1.setTexture(blackManT2); ::player1.setStatistics(black.getSpeed(),black.getPower(),black.getSpeedUp(),black.getSpeedUpContainer(),black.getIncrease(),black.getIncreaseContainer());}
            else if(opponentInLeagueMode == "alien") {spriteInGame1.setTexture(alienT2); ::player1.setStatistics(alien.getSpeed(),alien.getPower(),alien.getSpeedUp(),alien.getSpeedUpContainer(),alien.getIncrease(),alien.getIncreaseContainer());}

            ::player2.setStatistics(characterInLeague.getSpeed(),characterInLeague.getPower(),characterInLeague.getSpeedUp(),characterInLeague.getSpeedUpContainer(),characterInLeague.getIncrease(),characterInLeague.getIncreaseContainer());

            if(characterInLeague.getName() == "frog")         spriteInGame2.setTexture(frogT2);
            else if(characterInLeague.getName() == "gato")    spriteInGame2.setTexture(gatoT2);
            else if(characterInLeague.getName() == "kuszczak")spriteInGame2.setTexture(kuszczakT2);
            else if(characterInLeague.getName() == "gandalf") spriteInGame2.setTexture(gandalfT2);
            else if(characterInLeague.getName() == "lennon")  spriteInGame2.setTexture(lennonT2);
            else if(characterInLeague.getName() == "black")   spriteInGame2.setTexture(blackManT2);
            else if(characterInLeague.getName() == "alien")   spriteInGame2.setTexture(alienT2);
        }
        else
        {
            if(opponentInLeagueMode == "frog") {spriteInGame2.setTexture(frogT2); ::player2.setStatistics(frog.getSpeed(),frog.getPower(),frog.getSpeedUp(),frog.getSpeedUpContainer(),frog.getIncrease(),frog.getIncreaseContainer());}
            else if(opponentInLeagueMode == "gato") {spriteInGame2.setTexture(gatoT2); ::player2.setStatistics(gato.getSpeed(),gato.getPower(),gato.getSpeedUp(),gato.getSpeedUpContainer(),gato.getIncrease(),gato.getIncreaseContainer());}
            else if(opponentInLeagueMode == "kuszczak") {spriteInGame2.setTexture(kuszczakT2); ::player2.setStatistics(kuszczak.getSpeed(),kuszczak.getPower(),kuszczak.getSpeedUp(),kuszczak.getSpeedUpContainer(),kuszczak.getIncrease(),kuszczak.getIncreaseContainer());}
            else if(opponentInLeagueMode == "gandalf") {spriteInGame2.setTexture(gandalfT2); ::player2.setStatistics(gandalf.getSpeed(),gandalf.getPower(),gandalf.getSpeedUp(),gandalf.getSpeedUpContainer(),gandalf.getIncrease(),gandalf.getIncreaseContainer());}
            else if(opponentInLeagueMode == "lennon") {spriteInGame2.setTexture(lennonT2); ::player2.setStatistics(lennon.getSpeed(),lennon.getPower(),lennon.getSpeedUp(),lennon.getSpeedUpContainer(),lennon.getIncrease(),lennon.getIncreaseContainer());}
            else if(opponentInLeagueMode == "black") {spriteInGame2.setTexture(blackManT2); ::player2.setStatistics(black.getSpeed(),black.getPower(),black.getSpeedUp(),black.getSpeedUpContainer(),black.getIncrease(),black.getIncreaseContainer());}
            else if(opponentInLeagueMode == "alien") {spriteInGame2.setTexture(alienT2); ::player2.setStatistics(alien.getSpeed(),alien.getPower(),alien.getSpeedUp(),alien.getSpeedUpContainer(),alien.getIncrease(),alien.getIncreaseContainer());}

            ::player1.setStatistics(characterInLeague.getSpeed(),characterInLeague.getPower(),characterInLeague.getSpeedUp(),characterInLeague.getSpeedUpContainer(),characterInLeague.getIncrease(),characterInLeague.getIncreaseContainer());

            if(characterInLeague.getName() == "frog")         spriteInGame1.setTexture(frogT2);
            else if(characterInLeague.getName() == "gato")    spriteInGame1.setTexture(gatoT2);
            else if(characterInLeague.getName() == "kuszczak")spriteInGame1.setTexture(kuszczakT2);
            else if(characterInLeague.getName() == "gandalf") spriteInGame1.setTexture(gandalfT2);
            else if(characterInLeague.getName() == "lennon")  spriteInGame1.setTexture(lennonT2);
            else if(characterInLeague.getName() == "black")   spriteInGame1.setTexture(blackManT2);
            else if(characterInLeague.getName() == "alien")   spriteInGame1.setTexture(alienT2);
        }
    }

    if(!counter1)
    {
        ///player 1
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            if(player1 == 0) player1 = 6;
            else player1--;
            wasPressed = true;
            counter1 = 12;
        }
        else if(Keyboard::isKeyPressed(Keyboard::D))
        {
            if(player1 == 6) player1 = 0;
            else player1++;
            wasPressed = true;
            counter1 = 12;
        }
    }
    else counter1--;

    if(!counter2)
    {
        ///player 2
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            if(player2 == 0) player2 = 6;
            else player2--;
            wasPressed = true;
            counter2 = 12;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            if(player2 == 6) player2 = 0;
            else player2++;
            wasPressed = true;
            counter2 = 12;
        }
    }
    else counter2--;

    if(wasPressed)
    {
        ///frog
        if(player1 == 0)
        {
            sprite1.setTexture(frogT);
            name1.setString("Frog");
            speed1.setString(floatTostring(frog.getSpeed()));
            power1.setString(floatTostring(frog.getPower()));
            speedUp1.setString(floatTostring(frog.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(frog.getSpeedUpContainer()));
            increase1.setString(floatTostring(frog.getIncrease()));
            increaseContainer1.setString(floatTostring(frog.getIncreaseContainer()));
        }
        if(player2 == 0)
        {
            sprite2.setTexture(frogT);
            name2.setString("Frog");
            speed2.setString(floatTostring(frog.getSpeed()));
            power2.setString(floatTostring(frog.getPower()));
            speedUp2.setString(floatTostring(frog.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(frog.getSpeedUpContainer()));
            increase2.setString(floatTostring(frog.getIncrease()));
            increaseContainer2.setString(floatTostring(frog.getIncreaseContainer()));
        }

        ///el gato
        if(player1 == 1)
        {
            sprite1.setTexture(gatoT);
            name1.setString("el Gato");
            speed1.setString(floatTostring(gato.getSpeed()));
            power1.setString(floatTostring(gato.getPower()));
            speedUp1.setString(floatTostring(gato.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(gato.getSpeedUpContainer()));
            increase1.setString(floatTostring(gato.getIncrease()));
            increaseContainer1.setString(floatTostring(gato.getIncreaseContainer()));
        }
        if(player2 == 1)
        {
            sprite2.setTexture(gatoT);
            name2.setString("el Gato");
            speed2.setString(floatTostring(gato.getSpeed()));
            power2.setString(floatTostring(gato.getPower()));
            speedUp2.setString(floatTostring(gato.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(gato.getSpeedUpContainer()));
            increase2.setString(floatTostring(gato.getIncrease()));
            increaseContainer2.setString(floatTostring(gato.getIncreaseContainer()));
        }

        ///kuszczak
        if(player1 == 2)
        {
            sprite1.setTexture(kuszczakT);
            name1.setString("Kuszczak");
            speed1.setString(floatTostring(kuszczak.getSpeed()));
            power1.setString(floatTostring(kuszczak.getPower()));
            speedUp1.setString(floatTostring(kuszczak.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(kuszczak.getSpeedUpContainer()));
            increase1.setString(floatTostring(kuszczak.getIncrease()));
            increaseContainer1.setString(floatTostring(kuszczak.getIncreaseContainer()));
        }
        if(player2 == 2)
        {
            sprite2.setTexture(kuszczakT);
            name2.setString("Kuszczak");
            speed2.setString(floatTostring(kuszczak.getSpeed()));
            power2.setString(floatTostring(kuszczak.getPower()));
            speedUp2.setString(floatTostring(kuszczak.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(kuszczak.getSpeedUpContainer()));
            increase2.setString(floatTostring(kuszczak.getIncrease()));
            increaseContainer2.setString(floatTostring(kuszczak.getIncreaseContainer()));
        }

        ///gandalf
        if(player1 == 3)
        {
            sprite1.setTexture(gandalfT);
            name1.setString("Gandalf");
            speed1.setString(floatTostring(gandalf.getSpeed()));
            power1.setString(floatTostring(gandalf.getPower()));
            speedUp1.setString(floatTostring(gandalf.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(gandalf.getSpeedUpContainer()));
            increase1.setString(floatTostring(gandalf.getIncrease()));
            increaseContainer1.setString(floatTostring(gandalf.getIncreaseContainer()));
        }
        if(player2 == 3)
        {
            sprite2.setTexture(gandalfT);
            name2.setString("Gandalf");
            speed2.setString(floatTostring(gandalf.getSpeed()));
            power2.setString(floatTostring(gandalf.getPower()));
            speedUp2.setString(floatTostring(gandalf.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(gandalf.getSpeedUpContainer()));
            increase2.setString(floatTostring(gandalf.getIncrease()));
            increaseContainer2.setString(floatTostring(gandalf.getIncreaseContainer()));
        }

        ///lennon
        if(player1 == 4)
        {
            sprite1.setTexture(lennonT);
            name1.setString("Lennon");
            speed1.setString(floatTostring(lennon.getSpeed()));
            power1.setString(floatTostring(lennon.getPower()));
            speedUp1.setString(floatTostring(lennon.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(lennon.getSpeedUpContainer()));
            increase1.setString(floatTostring(lennon.getIncrease()));
            increaseContainer1.setString(floatTostring(lennon.getIncreaseContainer()));
        }
        if(player2 == 4)
        {
            sprite2.setTexture(lennonT);
            name2.setString("Lennon");
            speed2.setString(floatTostring(lennon.getSpeed()));
            power2.setString(floatTostring(lennon.getPower()));
            speedUp2.setString(floatTostring(lennon.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(lennon.getSpeedUpContainer()));
            increase2.setString(floatTostring(lennon.getIncrease()));
            increaseContainer2.setString(floatTostring(lennon.getIncreaseContainer()));
        }

        ///black man
        if(player1 == 5)
        {
            sprite1.setTexture(blackManT);
            name1.setString("black man");
            speed1.setString(floatTostring(black.getSpeed()));
            power1.setString(floatTostring(black.getPower()));
            speedUp1.setString(floatTostring(black.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(black.getSpeedUpContainer()));
            increase1.setString(floatTostring(black.getIncrease()));
            increaseContainer1.setString(floatTostring(black.getIncreaseContainer()));
        }
        if(player2 == 5)
        {
            sprite2.setTexture(blackManT);
            name2.setString("black man");
            speed2.setString(floatTostring(black.getSpeed()));
            power2.setString(floatTostring(black.getPower()));
            speedUp2.setString(floatTostring(black.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(black.getSpeedUpContainer()));
            increase2.setString(floatTostring(black.getIncrease()));
            increaseContainer2.setString(floatTostring(black.getIncreaseContainer()));
        }

        ///alien
        if(player1 == 6)
        {
            sprite1.setTexture(alienT);
            name1.setString("alien");
            speed1.setString(floatTostring(alien.getSpeed()));
            power1.setString(floatTostring(alien.getPower()));
            speedUp1.setString(floatTostring(alien.getSpeedUp()));
            speedUpContainer1.setString(floatTostring(alien.getSpeedUpContainer()));
            increase1.setString(floatTostring(alien.getIncrease()));
            increaseContainer1.setString(floatTostring(alien.getIncreaseContainer()));
        }
        if(player2 == 6)
        {
            sprite2.setTexture(alienT);
            name2.setString("alien");
            speed2.setString(floatTostring(alien.getSpeed()));
            power2.setString(floatTostring(alien.getPower()));
            speedUp2.setString(floatTostring(alien.getSpeedUp()));
            speedUpContainer2.setString(floatTostring(alien.getSpeedUpContainer()));
            increase2.setString(floatTostring(alien.getIncrease()));
            increaseContainer2.setString(floatTostring(alien.getIncreaseContainer()));
        }
    }
}

void setLeagueTable(string nameOf1player, string nameOf2player,
                    Text &name1, Text &name2, Text &name3, Text &name4, Text &name5, Text &name6, Text &name7,
                    Text &points1, Text &points2, Text &points3, Text &points4, Text &points5, Text &points6, Text &points7)
{
    int firstPlayerPosInTable;
    int secondPlayerPosInTable;
    for(int i=0; i<7; i++)
    {
        if(posInTable[i].name == nameOf1player) firstPlayerPosInTable = i;
        if(posInTable[i].name == nameOf2player) secondPlayerPosInTable = i;
    }

    if(inWhichMatchIsPlayerGLOBAL)
    {
        ///adding points to table
        int x;
        if(controlIn1player == 1) x = 2;
        else x = 1;

        if(whoWon == x)
        {
            posInTable[firstPlayerPosInTable].numberOfPoints += 5;
            posInTable[secondPlayerPosInTable].numberOfPoints += score2;
        }
        else
        {
            posInTable[secondPlayerPosInTable].numberOfPoints += 5;
            posInTable[firstPlayerPosInTable].numberOfPoints += score1;
        }
    }

    int sizeOfTable;
    if(inWhichMatchIsPlayerGLOBAL == 0) sizeOfTable = 3;
    else sizeOfTable = 2;

    string matchA[sizeOfTable], matchB[sizeOfTable];

    ///data capture
    if(inWhichMatchIsPlayerGLOBAL == 1)
    {
        matchA[0] = nameMatch2a; matchB[0] = nameMatch2b;
        matchA[1] = nameMatch3a; matchB[1] = nameMatch3b;
    }
    else if(inWhichMatchIsPlayerGLOBAL == 2)
    {
        matchA[0] = nameMatch1a; matchB[0] = nameMatch1b;
        matchA[1] = nameMatch3a; matchB[1] = nameMatch3b;
    }
    else if(inWhichMatchIsPlayerGLOBAL == 3)
    {
        matchA[0] = nameMatch2a; matchB[0] = nameMatch2b;
        matchA[1] = nameMatch1a; matchB[1] = nameMatch1b;
    }
    else//player is pausing
    {
        matchA[0] = nameMatch1a; matchB[0] = nameMatch1b;
        matchA[1] = nameMatch2a; matchB[1] = nameMatch2b;
        matchA[2] = nameMatch3a; matchB[2] = nameMatch3b;
    }

    ///simulation of other matches algorithm
    for(int i=0; i<sizeOfTable; i++)
    {
        int powerA, powerB;
        if(matchA[i] == "alien")    powerA = 10;
        if(matchA[i] == "black")    powerA = 8;
        if(matchA[i] == "gandalf")  powerA = 4;
        if(matchA[i] == "gato")     powerA = 7;
        if(matchA[i] == "frog")     powerA = 3;
        if(matchA[i] == "kuszczak") powerA = 5;
        if(matchA[i] == "lennon")   powerA = 6;

        if(matchB[i] == "alien")    powerB = 10;
        if(matchB[i] == "black")    powerB = 8;
        if(matchB[i] == "gandalf")  powerB = 4;
        if(matchB[i] == "gato")     powerB = 7;
        if(matchB[i] == "frog")     powerB = 3;
        if(matchB[i] == "kuszczak") powerB = 5;
        if(matchB[i] == "lennon")   powerB = 6;

        int randomA, randomB, randomNumberOfReapeating;
        randomNumberOfReapeating = random(100);
        for(int i=0; i<randomNumberOfReapeating; i++){randomA = random(5);}
        for(int i=0; i<randomNumberOfReapeating; i++){randomB = random(5);}
        powerA += randomA;
        powerB += randomB;

        cout<<endl<<"Power A: "<<powerA<<endl;
        cout<<"Power B: "<<powerB<<endl<<endl;

        int pointsA{}, pointsB{};

        if(powerA > powerB)
        {
            pointsA = 5;

            int aux = (powerA - powerB)/2;
            if(aux < 2) pointsB = 3;
            else if(aux < 3) pointsB = 2;
            else if(aux < 5) pointsB = 1;
        }
        else if(powerB > powerA)
        {
            pointsB = 5;

            int aux = (powerB - powerA)/2;
            if(aux < 2) pointsA = 3;
            else if(aux < 3) pointsA = 2;
            else if(aux < 5) pointsA = 1;
        }
        else//powerB == powerA
        {
            int aux = random(2);
            if(aux){pointsA = 5; pointsB = 3;}
            else{pointsB = 5; pointsA = 3;}
        }
        cout<<endl<<"pointsA: "<<pointsA<<endl;
        cout<<"pointsB: "<<pointsB<<endl<<endl;

        ///data sending
        for(int j=0; j<7; j++)
        {
            if(!i)
            {
                if(posInTable[j].name == matchA[0]) posInTable[j].numberOfPoints += pointsA;
                else if(posInTable[j].name == matchB[0]) posInTable[j].numberOfPoints += pointsB;
            }
            else if(i == 1)
            {
                if(posInTable[j].name == matchA[1]) posInTable[j].numberOfPoints += pointsA;
                else if(posInTable[j].name == matchB[1]) posInTable[j].numberOfPoints += pointsB;
            }
            else//i==2
            {
                if(posInTable[j].name == matchA[2]) posInTable[j].numberOfPoints += pointsA;
                else if(posInTable[j].name == matchB[2]) posInTable[j].numberOfPoints += pointsB;
            }
        }
    }

    cout<<endl;
    for(int i=0; i<7; i++)
    {
        cout<<posInTable[i].name<<"  : "<<posInTable[i].numberOfPoints<<endl;
    }
    cout<<endl;

    ///sorting table - bubble sort
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(posInTable[j].numberOfPoints < posInTable[j+1].numberOfPoints)
            {
                string auxName = posInTable[j].name;
                int auxPoints{posInTable[j].numberOfPoints};

                posInTable[j].numberOfPoints = posInTable[j+1].numberOfPoints;
                posInTable[j].name = posInTable[j+1].name;
                posInTable[j+1].numberOfPoints = auxPoints;
                posInTable[j+1].name = auxName;
            }
        }
    }

    ///draw changes in table
    name1.setString(posInTable[0].name);
    points1.setString(intToStr(posInTable[0].numberOfPoints));

    name2.setString(posInTable[1].name);
    points2.setString(intToStr(posInTable[1].numberOfPoints));

    name3.setString(posInTable[2].name);
    points3.setString(intToStr(posInTable[2].numberOfPoints));

    name4.setString(posInTable[3].name);
    points4.setString(intToStr(posInTable[3].numberOfPoints));

    name5.setString(posInTable[4].name);
    points5.setString(intToStr(posInTable[4].numberOfPoints));

    name6.setString(posInTable[5].name);
    points6.setString(intToStr(posInTable[5].numberOfPoints));

    name7.setString(posInTable[6].name);
    points7.setString(intToStr(posInTable[6].numberOfPoints));
}


void setPaddlesSpeed(Paddle& pad1,Paddle& pad2,Character p1,Character p2)
{
    pad1.setVelocity(p1.getSpeed());
    pad2.setVelocity(p2.getSpeed());
}

void setPaddlesSpeed(Paddle& pad1,Character p1)
{
    pad1.setVelocity(p1.getSpeed());
}
void setPaddlesSpeed(Character p2,Paddle& pad2)
{
    pad2.setVelocity(p2.getSpeed());
}

string intToStr(int n)
{
    string tmp;
    if(n < 0)
    {
    tmp = "-";
    n = -n;
    }
    if(n > 9)
    tmp += intToStr(n / 10);
    tmp += n % 10 + 48;
    return tmp;
}

string floatTostring(float x)
{
    if(x == 1)return "1";
    else if(x == 2)return "2";
    else if(x == 3)return "3";
    else if(x == 4)return "4";
    else if(x == 5)return "5";
    else if(x == 6)return "6";
    else if(x == 7)return "7";
    else if(x == 8)return "8";
    else if(x == 9)return "9";
    else if(x == 10)return "10";
}

int random(int x)//how many lots
{
    int lot;
    lot = rand()%x;
    return lot;
}

//alien,blackMan,gandalf,elGato,frog,kuszczak,lennon
void myToUpper(char *letter)
{
    if(*letter == 'e') *letter = 'E';
    else if(*letter == 'g') *letter = 'G';
    else if(*letter == 'f') *letter = 'F';
    else if(*letter == 'a') *letter = 'A';
    else if(*letter == 'k') *letter = 'K';
    else if(*letter == 'l') *letter = 'L';
    letter = nullptr;
}

