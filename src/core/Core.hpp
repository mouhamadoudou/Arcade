/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Core
*/

#pragma once

#include <bits/stdc++.h>
#include "../games/IGames.hpp"
#include "../lib/ILib.hpp"
#include "dl/dl.hpp"
class Core {
    public:
        Core();
        ~Core();

        void update();

        void loadGame(std::string gameName);
        void loadLib(std::string libName);

        bool isWindowOpen() { return _lib->isOpen(); }
    protected:
    private:
        std::string toLowerCase(const std::string& str);
        std::shared_ptr<dl> _gameDL;
        std::shared_ptr<IGames> (*_dlCreateGame)(void) = nullptr;
        std::shared_ptr<IGames> _game;

        std::shared_ptr<dl> _libDL;
        std::shared_ptr<ILib> (*_dlCreateLib)(void) = nullptr;
        std::shared_ptr<ILib> _lib;
        std::vector<std::pair<std::string, bool>> menuGraphic = {{"./lib/arcade_sfml.so", false}, {"./lib/arcade_ncurses.so", true}, {"./lib/arcade_sdl2.so", false}};
        std::vector<std::pair<std::string, bool>> menuGames = {{"./lib/arcade_pacman.so", false}, {"./lib/arcade_nibbler.so", true}};
        void loadGoodLib();
        int handleMenu(std::string _move);
        std::string oldGame = "";
        std::string oldLib = "";
        int open_menu = 0;
};
