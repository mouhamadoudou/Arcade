/*
** EPITECH PROJECT, 2023
** main.c
** File description: TEST
**std::string get namein.c
*/

#include "Player.hpp"

pm::Player::Player()
{
    this->Ppos["x"] = 0;
    this->Ppos["y"] = 0;
    loadFile();
    setPLayerPos();
}

void pm::Player::update()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - starto).count() > 300) {
        win();
        loose(); 
        displayBot();
        if (cmd != "") {
            this->UploadPLayerPos(cmd[0]);
            cmd = "";
        }
    } 
}

void pm::Player::setEvent(std::string _move)
{
    cmd = _move;
}

std::vector<std::string> pm::Player::getMap() const
{
    return getMapPac();
}

std::map<char, std::string> pm::Player::getAssets() const
{
    std::map<char, std::string> assets;
    assets[' '] = "assets/toot.png";
    assets['X'] = "assets/pacman/block.png";
    assets['.'] = "assets/pacman/coin.png";
    assets['L'] = "assets/pacman/pacmanL.png";
    assets['U'] = "assets/pacman/pacmanU.png";
    assets['D'] = "assets/pacman/pacmanD.png";
    assets['R'] = "assets/pacman/pacmanR.png";
    assets['B'] = "assets/pacman/gost1.png";

    return assets;
}

void freeTmpMap(char **map, int len)
{
    for (int i = 0; i < len; i++) {
        delete[] map[i];
    }
    delete[] map;
}

char **convertCharArray(char (*cmap)[29], int len)
{
    char **map = new char *[len];
    for (int i = 0; i < len; i++) {
        map[i] = new char[29];
        memcpy(map[i], cmap[i], 29);
    }
    return map;
}

void pm::Player::setPLayerPos()
{
    int i = 0;
	std::map <std::string, int> tmpBpos;

    for (int a = 0; a < 30; a++) {
        std::string tmp(this->cmap[a]);
        if (tmp.find('P') != std::string::npos) {
            this->Ppos["y"] = a;
            this->Ppos["x"] = tmp.find('P');
        }
        if (tmp.find('R') != std::string::npos) {
            this->Ppos["y"] = a;
            this->Ppos["x"] = tmp.find('R');
        }
        if (tmp.find('L') != std::string::npos) {
            this->Ppos["y"] = a;
            this->Ppos["x"] = tmp.find('L');
        }
        if (tmp.find('D') != std::string::npos) {
            this->Ppos["y"] = a;
            this->Ppos["x"] = tmp.find('D');
        }
        if (tmp.find('U') != std::string::npos) {
            this->Ppos["y"] = a;
            this->Ppos["x"] = tmp.find('U');
        }
        if (tmp.find('B') != std::string::npos) {
            tmpBpos["y"] = a;
            tmpBpos["x"] = tmp.find('B');
            this->bot[i] = std::make_unique<Bot>(tmpBpos); 
            i++;
        }
    }
}

void pm::Player::displayBot()
{
	pm::CoordInfo TmpCoord;
    int i = 0;
    char **tab = NULL;
    while (i < 4) {
          TmpCoord = this->bot[i]->getPos(this->cmap);

         this->cmap[TmpCoord.Before["y"]][TmpCoord.Before["x"]] = TmpCoord.c;
         this->cmap[TmpCoord.Current["y"]][TmpCoord.Current["x"]] = 'B';
        i++;
    }
}

int NbOccurrences(const std::string& str) {
    int count = 0;
    for (char x : str) {
        if (x == '.') {
            count++;
        }
    }
    return count;
}

void pm::Player::win()
{
    int result = 0;

    for (int a = 0; a < 30; a++) {
        std::string tmp(this->cmap[a]);
        result = result + NbOccurrences(tmp);
    }
    if (this->score == 289) {
        loadFile();
        setPLayerPos();
        return;
    }
    this->score = 289 - result;
}

void pm::Player::loose()
{
    this->Bloose = true;

    for (int a = 0; a < 30; a++) {
        std::string tmp(this->cmap[a]);
        if (tmp.find('P') != std::string::npos || tmp.find('U') != std::string::npos ||
        tmp.find('D') != std::string::npos || tmp.find('L') != std::string::npos ||
        tmp.find('R') != std::string::npos) {
            this->Bloose = false;
        }
    }
    if (this->Bloose) {
        loadFile();
        setPLayerPos();
    }
}

void pm::Player::MoovUp()
{
    if (this->cmap[this->Ppos["y"]][this->Ppos["x"]] != 'X') {
        if (this->cmap[(this->Ppos["y"] - 1)][this->Ppos["x"]] == 'X')
            return;
        this->cmap[this->Ppos["y"]][this->Ppos["x"]] = ' ';
        this->cmap[(this->Ppos["y"] - 1)][this->Ppos["x"]] = 'U';
        this->Ppos["y"] = this->Ppos["y"] - 1;
    }
}

void pm::Player::MoovRight()
{
    if (this->cmap[(this->Ppos["y"])][(this->Ppos["x"] + 1)] == 'X')
        return;
    this->cmap[this->Ppos["y"]][this->Ppos["x"]] = ' ';
    this->cmap[this->Ppos["y"]][(this->Ppos["x"] + 1)] = 'R';
    this->Ppos["x"] = this->Ppos["x"] + 1;
}

void pm::Player::MoovDown()
{
    if (this->cmap[this->Ppos["y"]][this->Ppos["x"]] != 'X') {
        if (this->cmap[(this->Ppos["y"] + 1)][this->Ppos["x"]] == 'X')
            return;
        this->cmap[this->Ppos["y"]][this->Ppos["x"]] = ' ';
        this->cmap[(this->Ppos["y"] + 1)][this->Ppos["x"]] = 'D';
        this->Ppos["y"] = this->Ppos["y"] + 1;
    }
}

void pm::Player::MoovLeft()
{
    if (this->cmap[this->Ppos["y"]][this->Ppos["x"]] != 'X') {
        if (this->cmap[(this->Ppos["y"])][(this->Ppos["x"] - 1)] == 'X')
            return;
        this->cmap[this->Ppos["y"]][this->Ppos["x"]] = ' ';
        this->cmap[this->Ppos["y"]][this->Ppos["x"] - 1] = 'L';
        this->Ppos["x"] = this->Ppos["x"] - 1;
    }
}

void pm::Player::UploadPLayerPos(char cod)
{
    switch (cod)
    {
    case 'z':
        MoovUp();
        break;
    case 'd':
        MoovRight();
        break;
    case 's':
        MoovDown();
        break;
    case 'q':
        MoovLeft();
        break;
    default:
        break;
    }
}

extern "C" std::shared_ptr<IGames> create()
{
    return std::make_shared<pm::Player>();
}
