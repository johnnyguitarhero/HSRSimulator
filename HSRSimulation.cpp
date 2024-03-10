// HSRSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono> // for std::chrono

#include "Battle.hpp"
#include "Team.hpp"
#include "AllMobileEntities.hpp"
#include "Curses.h"
using namespace std;

// Global variable
Battle battle;

// Function to be executed in the new thread
void UpdateDrawing() 
{
	while (true) 
	{
		battle.DrawScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep for 1 second
	}
}

int main()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);


	// Add characters to the team
	Team* pMyTeam = new Team();
	pMyTeam->AddCharacter(new Huohuo());
	pMyTeam->AddCharacter(new Seele());
	pMyTeam->AddCharacter(new Sparkle());

	// Create a 2 turn battle
	battle.InitBattle(pMyTeam, 2);
	std::thread t(UpdateDrawing);
	t.detach();
	battle.MainBattle();

	delete pMyTeam;
	endwin();
	system("pause");
	return 0;
}

