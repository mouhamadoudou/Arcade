/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-azyanah.olaytan
** File description:
** SDL
*/

#include "SDL.hpp"
SDL::SDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("_map du jeu vidéo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    open = true;
    TTF_Init();
    font = TTF_OpenFont("src/lib/SDL2/arial.ttf", 24);
    if (!font)
        throw std::runtime_error("Error while loading font");
}

SDL::~SDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL::draw()
{
    SDL_RenderClear(renderer);
    SDL_Rect dstrect;
    int y, x;
    for (x = 0; x < _map.size(); x++) {
        for (y = 0; y < _map[x].size(); y++) {
            dstrect = { y * 32, x * 32, tile_width, tile_width};
            SDL_RenderCopy(renderer, _mapSprite[_map[x][y]], NULL, &dstrect);
        }
    }
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, score.c_str(), red_color); 
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int width, height;
    TTF_SizeText(font, score.c_str(), &width, &height);
    SDL_Rect textRect = { 1500, y + 50, width, height };
    SDL_RenderCopy(renderer, message, NULL, &textRect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    SDL_RenderPresent(renderer);
}

std::string SDL::getEvent()
{
    SDL_Event event;
    std::string toto = "";
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            SDL_DestroyRenderer(renderer);
            open = false;   
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            open = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode keycode = event.key.keysym.sym;
            toto += static_cast<char>(keycode);
        }
    }
    return toto;
}

void SDL::loadAsset()
{
    for (auto &i : _asset) {
        SDL_Texture *texture = IMG_LoadTexture(renderer, i.second.c_str());
        _mapSprite[i.first] = texture;
    }
}

void SDL::setAsset(std::map<char, std::string> asset)
{
    _asset = asset;
    loadAsset();
}

void SDL::drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int i = 0; i < menuGraphic.size(); i++) {
        bool selected = menuGraphic[i].second;
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, menuGraphic[i].first.c_str(), selected ? red_color : black_color);
        if (!textSurface)
            throw std::runtime_error("Error while rendering text");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect rect;
        rect.x = 100;
        rect.y = 100 + (i * 50);
        rect.w = textSurface->w;
        rect.h = textSurface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);
    }

    for (int i = 0; i < menuGames.size(); i++) {
        bool selected = menuGames[i].second;
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, menuGames[i].first.c_str(), selected ? red_color : black_color);
        if (!textSurface)
            throw std::runtime_error("Error while rendering text");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect rect;
        rect.x = 800;
        rect.y = 100 + (i * 50);
        rect.w = textSurface->w;
        rect.h = textSurface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}


extern "C" std::shared_ptr<ILib> create()
{
    return std::make_shared<SDL>();
}
