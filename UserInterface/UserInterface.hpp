#pragma once

#include <vector>
#include "curses.h"
#include "WindowsAPI.hpp"
#include "Battle.hpp"
#include "Logger.hpp"

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

	void CloseUI()
	{
		endwin();
	}

	void DrawScreen(Battle* battle);

private:

	int m_height;
	int m_width;

	void DisplayMessages();
	void DisplayBattleInfo(Battle* battle);

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