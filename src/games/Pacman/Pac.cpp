/*
** EPITECH PROJECT, 2023
** FileName
** File description:
** FileDescription
*/

#include "Pac.hpp"
#include <cstring>

int pm::Pac::getScore() const
{
    return score;
}

void pm::Pac::loadFile()
{
    std::string tmp;
    std::fstream folder;
    int i = 0;
    this->score = 0;
    this->Bloose = false;

   folder.open("src/games/Pacman/mapPacv2.txt", std::ios::in);
    
    if (folder.is_open()) { 
        while (getline(folder, tmp)) { 
            strcpy(this->cmap[i], tmp.c_str());
            i++;
        }
        folder.close(); 
    } else
        exit(84);
}

std::vector<std::string> pm::Pac::getMapPac() const
{
    std::vector<std::string> result;
    for (int i = 0; i < 30; i++) {
        std::string row(cmap[i], cmap[i] + 29);
        result.push_back(row);
    }
    return result;
}

std::map<char, std::string> pm::Pac::getAssetsPac() const
{
    std::map<char, std::string> toto;
    return toto;
}
