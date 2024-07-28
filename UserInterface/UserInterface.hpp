#pragma once

#include <vector>
#include "curses.h"
#include "WindowsAPI.hpp"
#include "Battle.hpp"
#include "Logger.hpp"
#include "AnimatedCharacter.hpp"

class UserInterface
{
public:

	static const int NUM_MSG = 5;

	UserInterface(){}
	~UserInterface(){}
	void InitUI()
	{
		SetConsoleEncoding();

		initscr();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_CYAN, COLOR_BLACK);
		init_pair(4, COLOR_RED, COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_YELLOW, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);

	}

	void RegisterBattle(Battle* battle)
	{
		m_battle = battle;	
	}

	void PlaceAnimatedObjects()
	{
		// Characters
		for (int i = 0; i < m_battle->m_pTeam->m_pCharacters.size(); i++)
		{
			AnimatedCharacter* curAnimatedCharacter = new AnimatedCharacter(m_battle->m_pTeam->m_pCharacters[i]->m_idleAnimation, 20, 10 + i * 25);
			m_animatedCharacters.push_back(curAnimatedCharacter);
			m_battle->m_pTeam->m_pCharacters[i]->RegisterAnimation(curAnimatedCharacter);
		}
	}

	void CloseUI()
	{
		endwin();
	}

	void DrawScreen();

private:
	Battle* m_battle;
	std::vector<AnimatedCharacter*> m_animatedCharacters;

	int m_height;
	int m_width;

	void DisplayMessages();
	void DisplayBattleInfo();

	std::string GenPercentageBar(float percent)
	{
		std::string output = "[         ] "+std::to_string((int)percent)+"%";
		for (int i = 1; i < (int)(percent/10.0f); i++)
		{
			output[i] = '=';
		}
		return output;
	}

	std::vector<Message> m_onScreenMsg;

};