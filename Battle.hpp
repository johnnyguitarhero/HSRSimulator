#pragma once

#include <vector>
#include <iostream>

#include "curses.h"
#include "Team.hpp"
//#include "Character.hpp"
#include "TurnCounter.hpp"
//#include "AllMobileEntities.hpp"

class Battle
{
public:
	Battle();
	~Battle();

	void InitBattle(Team* pTeam, int turn);
	void MainBattle();
	void DrawScreen();	

private:
	int m_turn; // Number of turns left in the battle
	float m_timer; // Timer of the battle
	TurnCounter* m_pTurnCounter; // Pointer to the turn counter mobile entity
	std::vector<MobileEntity*> m_actionQueue; // Action queue that contains all mobile entities of a battle
	Team* m_pTeam; // Pointers to my team

	// Selection variables
	int m_curActionSelection;
	int m_curTargetSelection;
	int m_curTargetType;
};