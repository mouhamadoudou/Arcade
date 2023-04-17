/*
** EPITECH PROJECT, 2023
** B-PDG-300-LIL-3-1-PDGRUSH3-yacine.ourtanane
** File description:
** Ncurses
*/

#pragma once
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
#include <unordered_map>
#include <functional>
#include "Bot.hpp"
#include "../IGames.hpp"

namespace pm
{
    class Pac : public IGames
    {
    public:
        Pac(){};
        virtual ~Pac(){};
        void loadFile();
        std::map <int, std::unique_ptr<pm::Bot>> bot; 
        std::vector<std::string> getMapPac() const ;
        std::map<char, std::string> getAssetsPac() const ;
        int getScore() const ;
    protected:
		std::map <std::string, int> Ppos;
        char cmap[30][29];
        int score;
        bool Bloose;
        std::unordered_map<std::string, std::function<void(void)>> cmd;
    private:
    };
}