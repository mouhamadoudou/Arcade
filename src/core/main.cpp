/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** main
*/

#include "dl/dl.hpp"
#include "../games/IGames.hpp"
#include "Core.hpp"

int check_arg(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "Wrong arguments\n\tUse --info for help" << std::endl;
        return 1;
    }
    if (std::string(av[1]) == "-i\n" || std::string(av[1]) == "--info") {
        std::cout << "You can play to Pacman and Nibbler with Ncurses, SDL2 and SFML library.\nUse ZQSD to move you caracter\n Use M to open the menu, Z and S to navigate in the menu, and Q to save and quit\nAt any time, click on ESC to escape the program\n ENJOOOY !" << std::endl;
        return 1;
    }
    if (std::string(av[1]) != "./lib/arcade_sfml.so" && std::string(av[1]) != "./lib/arcade_sdl2.so" && std::string(av[1]) != "./lib/arcade_ncurses.so") {
        std::cout << "Graphic library error " << std::endl;
        return 1;
    }
    return 0;
}

int main(int ac, char **av)
{
    if (check_arg(ac, av))
        return 84;
    try {
        Core core;
        core.loadLib(std::string(av[1]));
        core.loadGame("./lib/arcade_nibbler.so");
        while (core.isWindowOpen()) {
            core.update();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
    
    return 0;
}
