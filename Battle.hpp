#pragma once

#include <vector>
#include <iostream>

#include "curses.h"
#include "Team.hpp"
#include "EnemyTeam.hpp"
//#include "Character.hpp"
#include "TurnCounter.hpp"
//#include "AllMobileEntities.hpp"

class UserInterface;

class Battle
{
public:
	Battle();
	~Battle();

	void InitBattle(Team* pTeam, EnemyTeam* pEnemyTeam, int turn);
	void MainBattle();
	//void DrawScreen();	
	friend class UserInterface;

private:
	int m_turn; // Number of turns left in the battle
	float m_timer; // Timer of the battle
	TurnCounter* m_pTurnCounter; // Pointer to the turn counter mobile entity
	std::vector<MobileEntity*> m_actionQueue; // Action queue that contains all mobile entities of a battle
	Team* m_pTeam; // Pointers to my team
	EnemyTeam* m_pEnemyTeam; // Pointers to enemy team

	// Selection variables
	int m_curActionSelection;
	int m_curTargetSelection;
	int m_curTargetType;
};