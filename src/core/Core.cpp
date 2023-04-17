/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{
}

Core::~Core()
{
}


void Core::update()
{
    std::string _move = _lib->getEvent();
    toLowerCase(_move);
    if (handleMenu(_move))
        return;
    _game->setEvent(_move);
    _game->update();
    _lib->setMap(_game->getMap());
    _lib->setAsset(_game->getAssets());
    _lib->setScore("Score: " + std::to_string(_game->getScore()));
    _lib->draw();
}


void Core::loadGame(std::string gameName)
{
    if (gameName == oldGame)
        return;
    _game.reset();
    this->_gameDL = std::make_shared<dl>(gameName);

    this->_dlCreateGame = (std::shared_ptr<IGames>(*)())_gameDL->getSym("create");
    _game = _dlCreateGame();
    oldGame = gameName;
}

void Core::loadLib(std::string libName)
{
    if (libName == oldLib)
        return;
    _lib.reset();
    this->_libDL = std::make_shared<dl>(libName);
    this->_dlCreateLib = (std::shared_ptr<ILib>(*)())_libDL->getSym("create");
    _lib = _dlCreateLib();
    oldLib = libName;
}

void Core::loadGoodLib()
{
    for (int i = 0; i < menuGraphic.size(); i++)
        if (menuGraphic[i].second) {
            loadLib(menuGraphic[i].first);
            break;
        }
    for (int i = 0; i < menuGames.size(); i++)
        if (menuGames[i].second) {
            loadGame(menuGames[i].first);
            break;
        }
}

int Core::handleMenu(std::string _move)
{
    int nextIndex = 0;
    if (_move == "q" && open_menu) {
        open_menu = 0;
        loadGoodLib();
        return 0;
    }
    if (_move == "m" || open_menu) {
        open_menu = 1;
        _lib->drawMenu(menuGraphic, menuGames);
        if (_move == "z") {
            for (int i = 0; i < menuGraphic.size(); ++i) {
                if (menuGraphic[i].second == true) {
                    menuGraphic[i].second = false;
                    nextIndex = (i + 1) % menuGraphic.size();
                    menuGraphic[nextIndex].second = true;
                    break;
                }
            }
        }
        if (_move == "s") {
            for (int i = 0; i < menuGames.size(); ++i) {
                if (menuGames[i].second == true) {
                    menuGames[i].second = false;
                    nextIndex = (i + 1) % menuGames.size();
                    menuGames[nextIndex].second = true;
                    break;
                }
            }
        }
        return 1;
    }
    return 0;
}

std::string Core::toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}
