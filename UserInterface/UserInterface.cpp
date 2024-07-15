#include "UserInterface.hpp"

/*
* @brief Draw battle scene using curses
* TODO: The draw screen function is not thread safe at all!!!
*/
void UserInterface::DrawScreen(Battle* battle)
{
	clear();
	getmaxyx(stdscr, m_height, m_width);

	// Hide cursor
	curs_set(0);

	// Draw borders
	for (int i = 0; i < m_height; i++) {
		mvprintw(i, 0, "|");
		mvprintw(i, m_width - 1, "|");
	}
	for (int i = 0; i < m_width; i++) {
		mvprintw(0, i, "-");
		mvprintw(m_height - 1, i, "-");
	}

	DisplayBattleInfo(battle);
	DisplayMessages();

	refresh();
}

void UserInterface::DisplayBattleInfo(Battle* battle)
{
	// Draw action queue
	mvprintw(1, 2, "------------");
	for (int i = 0; i < battle->m_actionQueue.size(); i++)
	{
		if (battle->m_actionQueue[i]->m_name == "TurnCounter")
		{
			mvprintw(2 + 2 * i, 2, "|%10d|", battle->m_turn);
		}
		else
		{
			mvprintw(2 + 2 * i, 2, "|%10s|", battle->m_actionQueue[i]->m_name.c_str());
		}

		mvprintw(3 + 2 * i, 2, "------------");
	}

	// Draw action menu
	mvprintw(m_height - 10, m_width - 20, "Action Menu:");
	std::vector<std::string> actions = { "Basic Attack", "Skill", "Ultimate" };
	for (int i = 0; i < 3; i++)
	{
		if (i == battle->m_curActionSelection)
		{
			mvprintw(m_height - 8 + i, m_width - 20, "> %s <", actions[i].c_str());
		}
		else
		{
			mvprintw(m_height - 8 + i, m_width - 20, "%s", actions[i].c_str());
		}
	}


	// Draw skill points
	mvprintw(m_height - 4, m_width - 20, "Skill Points:");
	std::string skillPoints = "";
	for (int i = 0; i < battle->m_pTeam->m_maxSkillPoints; i++)
	{
		if (i < battle->m_pTeam->m_curSkillPoints)
		{
			skillPoints += (char)216;
		}
		else
		{
			skillPoints += 'O';
		}		
	}
	mvprintw(m_height - 3, m_width - 20, skillPoints.c_str());

	// Draw enemy
	mvprintw((m_height - 5) / 2 - 1, (m_width - 15) / 2, "/-^-\\");
	mvprintw((m_height - 5) / 2, (m_width - 15) / 2 + 2, "Enemy");

	// Draw Characters
	for (int i = 0; i < battle->m_pTeam->m_curTeamSize; i++)
	{
		// Draw Names/Pictures
		if (battle->m_pTeam->m_pCharacters[i]->IsTarget()) attron(COLOR_PAIR(2));
		if (dynamic_cast<Character*>(battle->m_actionQueue[0]) == battle->m_pTeam->m_pCharacters[i])
		{
			mvprintw(m_height - 3, 2 + i * 20, "[%s]", battle->m_pTeam->m_pCharacters[i]->m_name.c_str());
		}
		else
		{
			mvprintw(m_height - 3, 2 + i * 20, " %s ", battle->m_pTeam->m_pCharacters[i]->m_name.c_str());
		}
		if (battle->m_pTeam->m_pCharacters[i]->IsTarget()) attroff(COLOR_PAIR(2));

		// Draw HP
		mvprintw(m_height - 4, 6 + i * 20, "%s", ("HP: " + battle->m_pTeam->m_pCharacters[i]->DisplayStats(CHARACTER_STATS::HP)).c_str());


		// Draw Energy
		int colorCode = (int)battle->m_pTeam->m_pCharacters[i]->GetElementType() + 1;
		attron(COLOR_PAIR(colorCode));
		mvprintw(m_height - 5, 2 + i * 20, "%s", ("Energy: " + battle->m_pTeam->m_pCharacters[i]->DisplayEnergy()).c_str());
		attroff(COLOR_PAIR(colorCode));

	}
}

void UserInterface::DisplayMessages()
{
	// Print out logs
	if (!Logger::GetInstance().NoMessage())
	{
		// if there is any message, display it on the screen
		m_onScreenMsg.push_back(Logger::GetInstance().ReadLog());
	}

	// Message timer counts down
	for (int i = 0; i < m_onScreenMsg.size(); i++)
	{
		if (m_onScreenMsg[i].expirationTime > 0)
		{
			m_onScreenMsg[i].expirationTime--;
		}
	}

	// Remove expired messages
	std::vector<int> expiredIndex;
	for (int i = 0; i < m_onScreenMsg.size(); i++)
	{
		if (m_onScreenMsg[i].expirationTime == 0)
		{
			expiredIndex.push_back(i);
		}
	}
	for (int i = 0; i < expiredIndex.size(); i++)
	{
		m_onScreenMsg.erase(m_onScreenMsg.begin() + expiredIndex[i]);
	}

	// Only keep 10 messages on the screen
	if (m_onScreenMsg.size() > UserInterface::NUM_MSG)
	{
		int removalIndex = 0;
		// First see if there's any temporary messages
		for (int i = 0; i < m_onScreenMsg.size(); i++)
		{
			if (m_onScreenMsg[i].expirationTime > 0)
			{
				removalIndex = i;
				break;
			}
		}

		// if not, remove the top one
		m_onScreenMsg.erase(m_onScreenMsg.begin()+removalIndex);
	}

	for (int i = 0; i < m_onScreenMsg.size(); i++)
	{
		mvprintw(i + 2, 80, "%s", m_onScreenMsg[i].msg.c_str());
	}
}