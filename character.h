#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
using namespace std;

class Character : public Entity
{
    float speed, power, speedUp, speedUpContainer, increase, increaseContainer;
    string name;
    bool didIpaused{false};
    bool amIinMatch{false};

public:

    string withWhoPlayed[6]{};
    Character(float = 6, float = 6, float = 6, float = 6, float = 6, float = 6, std::string = "nothing");
    void setStatistics(float speed_,float power_,float speedUp_,float speedUpContainer_,float increase_,float increaseContainer_);
    bool didIplayVs(string checkingMan);
    void setIplayedVs(string man);
    bool getPaused(){return didIpaused;}
    void setPaused(bool x){didIpaused = x;}
    void setAmIinMatch(bool x){amIinMatch = x;}
    void setName(string _name){name = _name;}
    bool getAmIinMatch(){return amIinMatch;}
    void toFileWithWhoIplayed();
    string getName(){return name;}
    float getSpeed(){return speed;}
    float getPower(){return power;}
    float getSpeedUp(){return speedUp;}
    float getSpeedUpContainer(){return speedUpContainer;}
    float getIncrease(){return increase;}
    float getIncreaseContainer(){return increaseContainer;}
    void showWithWhoIplayed();
    void resetLeague();
};
