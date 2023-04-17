/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-azyanah.olaytan
** File description:
** SDL
*/

#pragma once
#include <bits/stdc++.h>
#include "../ILib.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class SDL final : public ILib{
    public:
        SDL();
        ~SDL();

        void setAsset(std::map<char, std::string> asset) override;
        void drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames);
        void setMap(std::vector<std::string> map) override{
            _map = map;
        };
        void draw() override;

        bool isOpen() override {return open;};
        void loadAsset();
        std::string getEvent() override;
        void setScore(std::string _score) {
            score = _score;
        }
    protected:
    private:
    std::string score;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int tile_width = 32;
        int tile_height = 32;
        std::vector<std::string> _map;
        std::map<char, std::string> _asset;
        std::map<char, SDL_Texture*> _mapSprite;
        bool open;
        TTF_Font *font;
        SDL_Color black_color = {255, 255, 255};
        SDL_Color red_color = {255, 0, 0};
};
