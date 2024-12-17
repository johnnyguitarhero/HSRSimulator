#pragma once

#include <vector>
#include "curses.h"
#include "WindowsAPI.hpp"
#include "Battle.hpp"
#include "Logger.hpp"
#include "AnimatedCharacter.hpp"
#include "TextHighlight.hpp"

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
		for (int i = 0; i < m_battle->m_pTeam->m_curTeamSize; i++)
		{
			AnimatedCharacter* curAnimatedCharacter = new AnimatedCharacter(m_battle->m_pTeam->m_pCharacters[i]->m_idleAnimation, 20, 10 + i * 25);
			m_animatedCharacters.push_back(curAnimatedCharacter);
			m_battle->m_pTeam->m_pCharacters[i]->RegisterAnimation(curAnimatedCharacter);
		}

		// Enemy-Character interaction
		for (int i = 0; i < m_battle->m_pTeam->m_curTeamSize; i++)
		{
			for (int j = 0; j < m_battle->m_pEnemyTeam->m_curTeamSize; j++) //To do - add enemies
			{
				std::vector<std::vector<float>> trajectory = { {20.0f, 10.0f + i * 25.0f},
															   {10.0f, 18.0f + j * 15.0f},
															   {20.0f, 10.0f + i * 25.0f} };
				m_battle->m_pTeam->m_pCharacters[i]->m_pAnimation->AddInteraction(trajectory, 8.0f);
			}
		}

		// Character-Character interaction
		for (int i = 0; i < m_battle->m_pTeam->m_curTeamSize; i++)
		{
			for (int j = 0; j < m_battle->m_pTeam->m_curTeamSize; j++)
			{
				if (i == j)
				{
					std::vector<std::vector<float>> trajectory = { {20.0f, 10.0f + i * 25.0f},
																   {20.0f, 5.0f + i * 25.0f},
																   {20.0f, 15.0f + i * 25.0f},
																   {20.0f, 10.0f + i * 25.0f} };
					m_battle->m_pTeam->m_pCharacters[i]->m_pAnimation->AddInteraction(trajectory, 8.0f);
				}
				else
				{
					std::vector<std::vector<float>> trajectory = { {20.0f, 10.0f + i * 25.0f},
																   {15.0f, 35.0f},
																   {20.0f, 10.0f + j * 25.0f},
																   {15.0f, 35.0f}, 
																   {20.0f, 10.0f + i * 25.0f} };												 
					m_battle->m_pTeam->m_pCharacters[i]->m_pAnimation->AddInteraction(trajectory, 8.0f);
				}
			}
		}

		// Texts
		m_pActionQueueTop = new TextHighlight(2, 2);
	}

	void CloseUI()
	{
		endwin();
	}

	void DrawScreen();

private:
	Battle* m_battle;

	// Animations
	std::vector<AnimatedCharacter*> m_animatedCharacters;
	TextHighlight* m_pActionQueueTop;

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