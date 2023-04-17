/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML()
{
    _window.create(sf::VideoMode(1920, 1080), "SFML");
    _window.setFramerateLimit(60);
    if (!font.loadFromFile("src/lib/SFML/arial.ttf"))
        throw std::runtime_error("Error while loading font");
    screenTex->loadFromFile("assets/screen.png");
	screen.setTexture(*screenTex);
}

SFML::~SFML()
{
    _window.close();
}

void SFML::setAsset(std::map<char, std::string> asset)
{
    _asset = asset;
    loadAsset();
}

void SFML::loadAsset()
{
    for (auto &i : _asset) {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        sf::Sprite sprite;
        if (!texture->loadFromFile(i.second))
            throw std::runtime_error("Error while loading texture");
        sprite.setTexture(*texture);
        _mapSprite[i.first] = std::make_pair(sprite, texture);
    }
}

void SFML::setMap(std::vector<std::string> map)
{
    _map = map;
}

void SFML::draw()
{
    int x, y;
    _window.clear();
    for (x = 0; x < _map.size(); x++) {
        for (y = 0; y < _map[x].size(); y++) {
            _mapSprite[_map[x][y]].first.setPosition(y * 32 + 520, x * 32 + 140);
            _window.draw(_mapSprite[_map[x][y]].first);
        }
    }
    sf::Text text(score, font, 30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(1500, y + 50);
    _window.draw(screen);
    _window.draw(text);
    _window.display();
}

std::string SFML::getEvent()
{
    sf::Event event;
    std::string key = "";
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _window.close();
            else {
                key += static_cast<char>(event.text.unicode + 97);
                return key;
            }
        }
    }    
    return key;
}

void SFML::getName()
{
    sf::Event event;
    std::string key = "";
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            key += static_cast<char>(event.text.unicode + 97);
        }
    }
    if (key != "")
        name += key;
}

void SFML::drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames)
{
    sf::Text text;
    text.setFont(font);
    _window.clear();
    // getName();
	for (int i = 0; i < menuGraphic.size(); i++) {
        bool selected = menuGraphic[i].second;
    	
    	text.setString(menuGraphic[i].first);
    	text.setCharacterSize(30);
        if (selected)
            text.setFillColor(sf::Color::Red);
    	else
            text.setFillColor(sf::Color::White);
    	text.setPosition(100, 300 + (i * 50));
    	_window.draw(text);
	}
	for (int i = 0; i < menuGames.size(); i++) {
        bool selected = menuGames[i].second;
    	text.setString(menuGames[i].first);
    	text.setCharacterSize(30);
    	if (selected)
            text.setFillColor(sf::Color::Red);
    	else
            text.setFillColor(sf::Color::White);
    	text.setPosition(1000, 300 + (i * 50));
    	_window.draw(text);
	}
    text.setString(name);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    _window.draw(text);
	_window.display();
}

extern "C" std::shared_ptr<ILib> create()
{
    return std::make_shared<SFML>();
}
