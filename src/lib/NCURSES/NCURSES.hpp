/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** NCURSES
*/

#pragma once

#include <bits/stdc++.h>
#include <ncurses.h>
#include "../ILib.hpp"

class NCURSES final : public ILib {
    public:
        NCURSES();
        ~NCURSES();

        void setAsset(std::map<char, std::string> asset) override {};
        void setMap(std::vector<std::string> map) override;
        void draw() override;
        void loadAsset(){};
        bool isOpen() override { return open;};
        std::string getEvent() override;
        void drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames);
        void setScore(std::string _score) {
            score = _score;
        }
    protected:
    private:
        std::vector<std::string> _map;
        bool open;
        std::string score;
};
