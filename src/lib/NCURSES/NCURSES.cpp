/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** NCURSES
*/

#include "NCURSES.hpp"

NCURSES::NCURSES()
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    open = true;
}

NCURSES::~NCURSES()
{
    endwin();
}

void NCURSES::setMap(std::vector<std::string> map)
{
    _map = map;
}

void NCURSES::draw()
{
    clear();
    int i;
    for (i = 0; i < _map.size() ; i++) {
        printw(_map[i].c_str());
        printw("\n");
    }
    printw(score.c_str());

    refresh();
    usleep(100000);
}

std::string NCURSES::getEvent()
{
    int getch = getch();
    if (getch == 27) {
        endwin();
        open = false;
    }
    if (getch == ERR) { 
        return "";
    }
    else {
        return std::string(1, (char)getch);
    }
}

void NCURSES::drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames)
{
    clear();
    int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	int column_width = max_x / 2;
	for (int i = 0; i < menuGraphic.size(); i++)
	{
    	std::string text = menuGraphic[i].first;
    	bool selected = menuGraphic[i].second;
    	attron(selected ? A_REVERSE : A_NORMAL);
    	mvprintw(i, column_width, "%-*s", column_width, text.c_str());
    	attroff(selected ? A_REVERSE : A_NORMAL);
	}
    for (int i = 0; i < menuGames.size(); i++)
	{
    	std::string text = menuGames[i].first;
    	bool selected = menuGames[i].second;
    	attron(selected ? A_REVERSE : A_NORMAL);
    	mvprintw(i, 0, "%-*s", column_width, text.c_str());
    	attroff(selected ? A_REVERSE : A_NORMAL);
	}
	refresh();
    usleep(100000);
}

extern "C" std::shared_ptr<ILib> create()
{
    return std::make_shared<NCURSES>();
}
