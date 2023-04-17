/*
** EPITECH PROJECT, 2023
** FileName
** File description:
** FileDescription
*/

#include "Bot.hpp"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

pm::Bot::Bot(std::map<std::string, int> Bpos)
{
    this->Bpos.Current = Bpos;
    this->Bpos.Before = Bpos;
    this->Bpos.c = ' ';
    this->blocked["up"] = false;
    this->blocked["down"] = false;
    this->blocked["left"] = true;
    this->blocked["right"] = true;
    
    this->mngMoov["direction"] = 0;
    this->mngMoov["nbMoov"] = 0;
}

int randomMoov()
{
    srand(time(NULL));
    int x = rand() % 10 + 3;
    return x;
}

int randDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(2.5, 1.5);
    int x = static_cast<int>(std::round(dist(gen)));
    return x;
}

void pm::Bot::checkBlocked(char (*cmap)[29])
{
    if (cmap[(Bpos.Current["y"] - 1)][Bpos.Current["x"]] == 'X') {
        this->blocked["up"] = false;
    } else
        this->blocked["up"] = true;

    if (cmap[(Bpos.Current["y"])][(Bpos.Current["x"] + 1)] == 'X') {
        this->blocked["right"] = false;
    } else
        this->blocked["right"] = true;
    
    if (cmap[(Bpos.Current["y"] + 1)][Bpos.Current["x"]] == 'X') {
        this->blocked["down"] = false;
    } else
        this->blocked["down"] = true;
    
    if (cmap[(Bpos.Current["y"])][(Bpos.Current["x"] - 1)] == 'X') {
        this->blocked["left"] = false;
    } else 
        this->blocked["left"] = true;
}

void pm::Bot::MoovUp(char (*cmap)[29])
{
    if (cmap[(Bpos.Current["y"] - 1)][Bpos.Current["x"]] == 'X') {   
        this->blocked["up"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    if (this->mngMoov["nbMoov"] == 0) {
        this->blocked["up"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    this->mngMoov["nbMoov"]--;
    this->Bpos.Before = this->Bpos.Current;
    Bpos.Current["y"] = Bpos.Current["y"] - 1;
    if (cmap[Bpos.Current["y"]][Bpos.Current["x"]] == '.' || cmap[Bpos.Current["y"]][Bpos.Current["x"]] == ' ') {
        this->Bpos.c = cmap[Bpos.Current["y"]][Bpos.Current["x"]];
    } else
        this->Bpos.c = ' ';
    this->blocked["up"] = true;
}

void pm::Bot::MoovRight(char (*cmap)[29])
{
    if (cmap[(Bpos.Current["y"])][(Bpos.Current["x"] + 1)] == 'X') {
        this->blocked["right"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    if (this->mngMoov["nbMoov"] == 0) {
        this->blocked["right"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    this->mngMoov["nbMoov"]--;
    this->Bpos.Before = this->Bpos.Current;
    Bpos.Current["x"] = Bpos.Current["x"] + 1;
    if (cmap[Bpos.Current["y"]][Bpos.Current["x"]] == '.' || cmap[Bpos.Current["y"]][Bpos.Current["x"]] == ' ') {
        this->Bpos.c = cmap[Bpos.Current["y"]][Bpos.Current["x"]];
    } else
        this->Bpos.c = ' ';
    this->blocked["right"] = true;
}

void pm::Bot::MoovDown(char (*cmap)[29])
{
    if (cmap[(Bpos.Current["y"] + 1)][Bpos.Current["x"]] == 'X') {
        this->blocked["down"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    if (this->mngMoov["nbMoov"] == 0) {
        this->blocked["down"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    this->mngMoov["nbMoov"]--;
    this->Bpos.Before = this->Bpos.Current;
    Bpos.Current["y"] = Bpos.Current["y"] + 1;
    if (cmap[Bpos.Current["y"]][Bpos.Current["x"]] == '.' || cmap[Bpos.Current["y"]][Bpos.Current["x"]] == ' ') {
        this->Bpos.c = cmap[Bpos.Current["y"]][Bpos.Current["x"]];
    } else
        this->Bpos.c = ' ';
    this->blocked["down"] = true;
}

void pm::Bot::MoovLeft(char (*cmap)[29])
{
    if (cmap[(Bpos.Current["y"])][(Bpos.Current["x"] - 1)] == 'X') {
        this->blocked["left"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    if (this->mngMoov["nbMoov"] == 0) {
        this->blocked["left"] = false;
        this->mngMoov["direction"] = 0;
        return;
    }
    this->mngMoov["nbMoov"]--;
    this->Bpos.Before = this->Bpos.Current;
    Bpos.Current["x"] = Bpos.Current["x"] - 1;
    if (cmap[Bpos.Current["y"]][Bpos.Current["x"]] == '.' || cmap[Bpos.Current["y"]][Bpos.Current["x"]] == ' ') {
        this->Bpos.c = cmap[Bpos.Current["y"]][Bpos.Current["x"]];
    } else
        this->Bpos.c = ' '; 
    this->blocked["left"] = true;
}

void pm::Bot::firstCallDirection(int direction, char (*cmap)[29])
{
    switch (direction) {
    case 1:
        this->mngMoov["direction"] = 1;
        this->mngMoov["nbMoov"]= randomMoov();
        MoovUp(cmap);
        break;
    case 2:
        this->mngMoov["direction"] = 2;
        this->mngMoov["nbMoov"]= randomMoov();
        MoovRight(cmap);
        break;
    case 3:
        this->mngMoov["direction"] = 3;
        this->mngMoov["nbMoov"]= randomMoov();
        MoovDown(cmap);
        break;
    case 4:
        this->mngMoov["direction"] = 4;
        this->mngMoov["nbMoov"]= randomMoov();
        MoovLeft(cmap);
        break;
    default:
        break;
    }
}

void pm::Bot::GiveNewDirection(char (*cmap)[29])
{
    int direction = 0;
    checkBlocked(cmap);
    if (this->mngMoov["direction"] != 0) {
        direction = this->mngMoov["direction"];
    } else {
        direction = 4;
        while (1) {
            direction = randDirection();
            if (direction == 1 && this->blocked["up"] == true)
                break;
            if (direction == 2 && this->blocked["right"] == true)
                break;
            if (direction == 3 && this->blocked["down"] == true)
                break;
            if (direction == 4 && this->blocked["left"] == true)
                break;
            checkBlocked(cmap);            
        }
        firstCallDirection(direction, cmap);
        return;
    }

    switch (direction) {
    case 1:
        MoovUp(cmap);
        break;
    case 2:
        MoovRight(cmap);
        break;
    case 3:
        MoovDown(cmap);
        break;
    case 4:
        MoovLeft(cmap);
        break;
    default:
        break;
    }
}

void pm::Bot::botMoov(char (*map)[29])
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - botClock).count() > 400) {
        GiveNewDirection(map);
        botClock = std::chrono::system_clock::now();
    }

}

pm::CoordInfo pm::Bot::getPos(char (*map)[29])
{
    botMoov(map);
    return this->Bpos;
}
