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
#include <stdbool.h>
#include "../IGames.hpp"

namespace pm
{
    struct CoordInfo {
    	std::map <std::string, int> Before;
    	std::map <std::string, int> Current;
    	char c;
	};
    class Bot
    {
    public:
        Bot(std::map<std::string, int> Bpos);
        ~Bot(){};
        CoordInfo getPos(char (*cmap)[29]);
        void botMoov(char (*cmap)[29]);
        void loadFile();
        void print();
        CoordInfo Bpos;

    protected:
        std::map<std::string, bool> blocked;
        std::map<std::string, int> mngMoov;

    private:
        void firstCallDirection(int direction, char (*cmap)[29]);
        void checkBlocked(char (*cmap)[29]);
        void GiveNewDirection(char (*cmap)[29]);
        void MoovUp(char (*cmap)[29]);
		void MoovRight(char (*cmap)[29]);
		void MoovDown(char (*cmap)[29]);
		void MoovLeft(char (*cmap)[29]);
        std::chrono::time_point<std::chrono::system_clock> botClock = std::chrono::system_clock::now();
    };
}