/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-azyanah.olaytan
** File description:
** NibblerGame
*/

#ifndef NIBBLERGAME_HPP_
#define NIBBLERGAME_HPP_
#include  "bits/stdc++.h"
#include "../../IGames.hpp"
class NibblerGame : public IGames {
    public:
        NibblerGame();
        ~NibblerGame();

        void start();
        void restart();
        int initMap();
        void getSnake();
        void run(std::string cmd);
        void cleanMap();
        void eat();
        void displayMap();
        void gameTime();
        int setMoveSnack(std::string move);
        int canMove();
        int moveUp();
        int moveDown();
        int moveLeft();
        int moveRight();
        int moveHeadSnack();
        void moveBobySnake();
        void endGameWin();
        void endGameLose();
        std::chrono::time_point<std::chrono::system_clock> starto = std::chrono::system_clock::now();
        int getScore() const;
        std::vector<std::string> getMap() const override;
        std::map<char, std::string> getAssets()const {
            std::map<char, std::string> assets;
            assets[' '] = "assets/toot.png";
            assets['1'] = "assets/nibbler/wallV.png";
            assets['0'] = "assets/nibbler/wallH.png";
            assets['3'] = "assets/nibbler/angleDR.png";
            assets['4'] = "assets/nibbler/angleDL.png";
            assets['5'] = "assets/nibbler/angleUR.png";
            assets['6'] = "assets/nibbler/angleUL.png";
            assets['B'] = "assets/nibbler/baie.png";
            assets['O'] = "assets/nibbler/testhead.png";
            assets['X'] = "assets/nibbler/testbody.png";
            return assets;
        };

        void update() {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - starto).count() > speed) {
                if (move == "")
                    run(prevMove);
                else
                    run(move);
                gameTime();
                starto = std::chrono::system_clock::now();
            } else {
                if (move != "")
                    if (setMoveSnack(move))
                        prevMove = move;
                return;
            }
        }

        void setEvent(std::string cmd) override{
            move = cmd;
        };

    protected:
    private:
        bool up = false;
        bool left = false;
        bool right = false;
        bool down = false;
        int sizeSnake = 3;
        int x = 17;
        int y = 11;
        int lvl = 1;
        int score = 0;
        int live = 3;
        int apple = 12;
        int nibblerTime = 990;
        int speed = 500;
        std::vector<std::string> map;
        std::string move;
        std::string prevMove;
        std::vector<std::vector<int>> allMove;
        std::chrono::system_clock::time_point startTime, endTime;
};

#endif /* !NIBBLERGAME_HPP_ */
