#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "character.h"

Character::Character(float speed_, float power_, float speedUp_, float speedUpContainer_,
                     float increase_, float increaseContainer_, string name_)
{
    speed = speed_;
    power = power_;
    speedUp = speedUp_;
    speedUpContainer = speedUpContainer_;
    increase = increase_;
    increaseContainer = increaseContainer_;
    name = name_;
}

void Character::setStatistics(float speed_,float power_,float speedUp_,float speedUpContainer_,float increase_,float increaseContainer_)
{
    speed = speed_;
    power = power_;
    speedUp = speedUp_;
    speedUpContainer = speedUpContainer_;
    increase = increase_;
    increaseContainer = increaseContainer_;
}

bool Character::didIplayVs(string checkingMan)
{
    for(int i=0; i<6; i++)
    {
        if(checkingMan == name) return true;
        if(checkingMan == withWhoPlayed[i]) return true;
    }
    return false;
}

void Character::setIplayedVs(string man)
{
    for(int i=0;i<6;++i)
    {
        if(withWhoPlayed[i]==""){withWhoPlayed[i] = man; break;}
    }
}

void Character::toFileWithWhoIplayed()
{
    fstream file;
    file.open("save.txt",ios::out | ios::app);

    for(int i=0; i<6; i++)
    {
         file<<withWhoPlayed[i]<<std::endl;
    }

    file.close();
}

void Character::resetLeague()
{
    for(int i=0; i<6; i++){withWhoPlayed[i] = "";}
    didIpaused = false;
    amIinMatch = false;
}
