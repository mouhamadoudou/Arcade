/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-azyanah.olaytan
** File description:
** NibblerGame
*/

#include "./includes/NibblerGame.hpp"
#include "ncurses.h"

NibblerGame::NibblerGame()
{
    initMap();
    getSnake();
    startTime = std::chrono::system_clock::now();
    move = "d";
    prevMove = "d";
}

NibblerGame::~NibblerGame()
{
}

void NibblerGame::displayMap()
{
    for (std::size_t i = 0; i < map.size(); i++)
        std::cout << map[i].c_str() << std::endl;
}

void NibblerGame::restart()
{
    std::vector<std::string> mapTmp = map;

    map.clear();
    map = mapTmp;
    cleanMap();
    allMove.clear();
    x = 17;
    y = 11;
    getSnake();
    sizeSnake = 3;
    moveBobySnake();

    if (live == 0)
        exit(0);
}
int NibblerGame::getScore() const
{
    return score;
}

int NibblerGame::initMap()
{
    std::string nblvl = std::to_string(lvl);
    std::string filename = "src/games/Nibbler/maps/map";
    filename = strcat(strdup(filename.c_str()), nblvl.c_str());
    filename = strcat(strdup(filename.c_str()), ".txt");
    std::ifstream f(filename);
    std::string tmp;

    if (!f.is_open()) {
        std::cerr << "Invalide file\n";
        std::exit(84);
    }

    while (std::getline(f, tmp))
        map.push_back(tmp);

    f.close();
    return 0;
}

void NibblerGame::getSnake()
{
    allMove.push_back({17, 10});
    allMove.push_back({17, 9});
    allMove.push_back({17, 8});
}

void NibblerGame::run(std::string cmd)
{
    if (!setMoveSnack(cmd))
        setMoveSnack(prevMove);
    if (canMove() == -1)
        return;
    if (moveHeadSnack() == -1)
        return;
    prevMove = move;
}


void NibblerGame::endGameLose()
{
    live--;
    nibblerTime = 990;
    map.clear();
    allMove.clear();
    x = 17;
    y = 11;
    apple = 12;
    getSnake();
    sizeSnake = 3;
    moveBobySnake();
    start();
}

void NibblerGame::endGameWin()
{
    lvl++;
    speed -= 10;
    score += nibblerTime;
    nibblerTime = 990;
    if (lvl == 3) {
        lvl = 1;
    }
    map.clear();
    allMove.clear();
    apple = 12;
    x = 17;
    y = 11;
    getSnake();
    sizeSnake = 3;
    moveBobySnake();
    initMap();
    getSnake();
    startTime = std::chrono::system_clock::now();
}

void NibblerGame::eat()
{
    if (map[x][y] == 'B') {
        sizeSnake++;
        score += 10;
        apple--;
        if (apple == 0)
            endGameWin();
    }
}

void NibblerGame::cleanMap()
{
    for (std::size_t i = 0; i < map.size(); i++)
        for (std::size_t j = 0; j < map[i].size(); j++)
            if (map[i][j] == 'X' || map[i][j] == 'O')
                map[i][j] = ' ';

    map[x][y] = 'O';
}


long long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

void NibblerGame::gameTime()
{
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = endTime - startTime;
    if (elapsed_seconds.count() >= 1) {
        nibblerTime -= 10;
        startTime = endTime;
    }
    if (nibblerTime == 0) {
        endGameLose();
    }
    std::string message = "Game Time";
}

std::vector<std::string> NibblerGame::getMap() const
{
    return map;
}

extern "C" std::shared_ptr<IGames> create()
{
    return std::make_shared<NibblerGame>();
}
