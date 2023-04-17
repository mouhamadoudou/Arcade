/*
** EPITECH PROJECT, 2023
** main.c
** File description: TEST
**std::string get namein.c
*/

#pragma once

#include "Pac.hpp"
#include <string>
#include "../IGames.hpp"

namespace pm
{
	class Player : public Pac {
	public:
		Player();
		~Player(){};
		void setPLayerPos();
        // void display();
		void displayBot();
		void UploadPLayerPos(char cod);
		void update();
		std::map<char, std::string> init();
		void setEvent(std::string cmd) override;
		std::vector<std::string> getMap() const override;
		std::map<char, std::string> getAssets() const;
		std::string cmd;

	private:
		void win();
		void loose();
		void MoovUp();
		void MoovRight();
		void MoovDown();
		void MoovLeft();
		std::chrono::time_point<std::chrono::system_clock> starto = std::chrono::system_clock::now();
	};
}
