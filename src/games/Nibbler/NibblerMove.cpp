/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-azyanah.olaytan
** File description:
** NibblerMove
*/

#include "./includes/NibblerGame.hpp"

int NibblerGame::canMove()
{
     if (down && isdigit(map[x + 1][y])) {
        down = false;
        if ((!isdigit(map[x][y - 1]) || map[x][y - 1] != 'X') && (isdigit(map[x][y + 1]) || map[x][y + 1] == 'X')) {
            left = true;
            move = "q";
            return 0;
        } else if ((isdigit(map[x][y - 1]) || map[x][y - 1] == 'X') && (!isdigit(map[x][y + 1]) || map[x][y + 1] == 'X')) {
            right = true;
            "d";
            return 0;
        }
            return -1;
    }
    if (up && isdigit(map[x - 1][y])) {
        up = false;
        if ((!isdigit(map[x][y - 1]) || map[x][y - 1] != 'X') && (isdigit(map[x][y + 1])|| map[x][y + 1] == 'X')) {
            left = true;
            move = "q";
            return 0;
        } else if ((isdigit(map[x][y - 1]) || map[x][y - 1] == 'X') && (!isdigit(map[x][y + 1]) || map[x][y + 1] == 'X')) {
            right = true;
            move = "d";
            return 0;
        }
        return -1;
    }
    if (left && isdigit(map[x][y - 1])) {
        left = false;
        if ((!isdigit(map[x - 1][y]) || map[x - 1][y] != 'X') && (isdigit(map[x + 1][y]) || map[x + 1][y] == 'X')) {
            up = true;
            move = "z";
            return 0;
        } else if ((isdigit(map[x - 1][y]) || map[x - 1][y] == 'X') && (!isdigit(map[x + 1][y]) || map[x + 1][y] == 'X')) {
            down = true;
            move = "s";
            return 0;
        }
        return -1;
    }
    if (right && isdigit(map[x][y + 1])) {
        right = false;
        if ((!isdigit(map[x - 1][y]) || map[x - 1][y] != 'X') && (isdigit(map[x + 1][y]) || map[x + 1][y] == 'X')) {
            up = true;
            move = "z";
            return 0;
        } else if ((isdigit(map[x - 1][y]) || map[x - 1][y] == 'X') && (!isdigit(map[x + 1][y]) || map[x + 1][y] == 'X')) {
            down = true;
            move = "s";
            return 0;
        }
        return -1;
    }
    return 0;
}

int NibblerGame::setMoveSnack(std::string _move)
{
    if (!strcmp(_move.c_str(), "z")) {
        move = "z";
        up = true;
    }
    else if (!strcmp(_move.c_str(), "s")) {
        move = "s";
        down = true;
    }
    else if (!strcmp(_move.c_str(), "q")) {
        move = "q";
        left = true;
    }
    else if (!strcmp(_move.c_str(), "d")) {
        move = "d";
        right = true;
    }
    else {
        return 0;
    }
    return 1;
}

void NibblerGame::moveBobySnake()
{
    size_t j = 0;
    cleanMap();

    for (int i = 0; i < sizeSnake && j != allMove.size(); i++, j++)
        map[allMove[i][0]][allMove[i][1]] = 'X';
}

int NibblerGame::moveUp()
{
    up = false;

    if (!strcmp(prevMove.c_str(), "s"))
        return -1;

    allMove.insert(allMove.begin(), {x, y});
    if (map[x - 1][y] == 'X') {
        restart();
        nibblerTime = 990;
        live--;
        return -1;
    }
    map[x][y] = ' ';
    x--;
    return 0;
}

int NibblerGame::moveDown()
{
    down = false;

    if (!strcmp(prevMove.c_str(), "z"))
        return -1;

    allMove.insert(allMove.begin(), {x, y});
    if (map[x + 1][y] == 'X') {
        restart();
        nibblerTime = 990;
        live--;
        return -1;
    }
    map[x][y] = ' ';
    x++;

    return 0;
}

int NibblerGame::moveLeft()
{
    left = false;

    if (!strcmp(prevMove.c_str(), "d"))
        return -1;

    allMove.insert(allMove.begin(), {x, y});
    if (map[x][y - 1] == 'X') {
        restart();
        nibblerTime = 990;
        live--;
        return -1;
    }
    map[x][y] = ' ';
    y--;

    return 0;
}

int NibblerGame::moveRight()
{
    right = false;

    if (!strcmp(prevMove.c_str(), "q"))
        return -1;

    allMove.insert(allMove.begin(), {x, y});
    if (map[x][y + 1] == 'X') {
        restart();
        nibblerTime = 990;
        live--;
        return -1;
    }
    map[x][y] = ' ';
    y++;

    return 0;
}

int NibblerGame::moveHeadSnack()
{
    if (up && moveUp() == -1) {
        return -1;
    }
    if (down && moveDown() == -1) {
        return -1;
    }
    if (left && moveLeft() == -1) {
        return -1;
    }
    if (right && moveRight() == -1) {
        return -1;
    }
    eat();
    moveBobySnake();
    return 0;
}
