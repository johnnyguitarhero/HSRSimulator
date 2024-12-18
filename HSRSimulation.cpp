// HSRSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono> // for std::chrono

#include "Battle.hpp"
#include "UserInterface.hpp"
#include "Team.hpp"
#include "AllMobileEntities.hpp"
#include "Curses.h"
using namespace std;

// Global variable
Battle battle;
UserInterface ui;

// Function to be executed in the new thread
void UpdateDrawing() 
{
	while (true) 
	{
		ui.DrawScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Sleep for 16ms -> 60Hz refresh rate :)
	}
}

int main()
{	
	ui.InitUI();

	// Add characters to the team
	Team* pMyTeam = new Team();
	pMyTeam->AddCharacter(new Huohuo());
	pMyTeam->AddCharacter(new Seele());
	pMyTeam->AddCharacter(new Sparkle());

	// Add enemies to the team
	EnemyTeam* pEnemyTeam = new EnemyTeam();
	pEnemyTeam->AddEnemy(new Vagrant());
	pEnemyTeam->AddEnemy(new Vagrant());
	pEnemyTeam->AddEnemy(new Vagrant());
	pEnemyTeam->AddEnemy(new Vagrant());
	pEnemyTeam->AddEnemy(new Vagrant());

	// Create a 3 turn battle
	battle.InitBattle(pMyTeam, pEnemyTeam, 3);
	ui.RegisterBattle(&battle);
	ui.PlaceAnimatedObjects();

	std::thread t(UpdateDrawing);
	t.detach();
	battle.MainBattle();

	delete pMyTeam;

	ui.CloseUI();
	
	system("pause");
	return 0;
}

