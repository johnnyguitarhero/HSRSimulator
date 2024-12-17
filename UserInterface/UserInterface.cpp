#include "UserInterface.hpp"

/*
* @brief Draw battle scene using curses
* TODO: The draw screen function is not thread safe at all!!!
*/
void UserInterface::DrawScreen()
{
	clear();
	getmaxyx(stdscr, m_height, m_width);

	// Hide cursor
	curs_set(0);

	// Draw borders
	for (int i = 0; i < m_height; i++) 
	{
		mvprintw(i, 0, "|");
		mvprintw(i, m_width - 1, "|");
	}
	for (int i = 0; i < m_width; i++) 
	{
		mvprintw(0, i, "-");
		mvprintw(m_height - 1, i, "-");
	}

	DisplayBattleInfo();
	DisplayMessages();

	for (int i = 0; i < m_battle->m_pTeam->m_curTeamSize; i++)
	{
		m_animatedCharacters[i]->Render();
	}
	
	refresh();
}

void UserInterface::DisplayBattleInfo()
{
	// Draw action queue
	mvprintw(1, 2, "------------");
	m_pActionQueueTop->SetText(m_battle->m_actionQueue[0]->m_name, "|%10s|");
	m_pActionQueueTop->RenderFrame();
	mvprintw(3, 2, "------------");

	for (int i = 1; i < 6; i++) // at most draw 6 only
	{
		if (m_battle->m_actionQueue[i]->m_name == "TurnCounter")
		{
			mvprintw(2 + 2 * i, 2, "|%10d|", m_battle->m_turn);
		}
		else
		{
			mvprintw(2 + 2 * i, 2, "|%10s|", m_battle->m_actionQueue[i]->m_name.c_str());
		}

		mvprintw(3 + 2 * i, 2, "------------");
	}

	// Draw action menu
	mvprintw(m_height - 21, 90, "Action Menu:");
	std::vector<std::string> actions = { "Basic Attack", "Skill", "Ultimate" };
	for (int i = 0; i < 3; i++)
	{
		if (i == m_battle->m_curActionSelection)
		{
			mvprintw(m_height - 20 + i, 90, "> %s <", actions[i].c_str());
		}
		else
		{
			mvprintw(m_height - 20 + i, 90, "%s", actions[i].c_str());
		}
	}


	// Draw skill points
	mvprintw(m_height - 15, 90, "Skill Points:");
	std::string skillPoints = "";
	for (int i = 0; i < m_battle->m_pTeam->m_maxSkillPoints; i++)
	{
		if (i < m_battle->m_pTeam->m_curSkillPoints)
		{
			skillPoints += (char)216;
		}
		else
		{
			skillPoints += 'O';
		}		
	}
	mvprintw(m_height - 14, 90, skillPoints.c_str());

	// Draw enemy
	for (int i = 0; i < m_battle->m_pEnemyTeam->m_curTeamSize; i++)
	{
		mvprintw(8, 18 + i * 15, "/-^-\\");
		// Draw Names/Pictures
		if (m_battle->m_pEnemyTeam->m_pEnemies[i]->IsTarget()) attron(COLOR_PAIR(2));
		mvprintw(9, 18 + i * 15, "Enemy");
		if (m_battle->m_pEnemyTeam->m_pEnemies[i]->IsTarget()) attroff(COLOR_PAIR(2));
	}

	// Draw character stats
	for (int i = 0; i < m_battle->m_pTeam->m_curTeamSize; i++)
	{
		// Draw Names/Pictures
		if (m_battle->m_pTeam->m_pCharacters[i]->IsTarget()) attron(COLOR_PAIR(2));
		if (dynamic_cast<Character*>(m_battle->m_actionQueue[0]) == m_battle->m_pTeam->m_pCharacters[i])
		{
			mvprintw(m_height - 3, 2 + i * 25, "[%s]", m_battle->m_pTeam->m_pCharacters[i]->m_name.c_str());
		}
		else
		{
			mvprintw(m_height - 3, 2 + i * 25, " %s ", m_battle->m_pTeam->m_pCharacters[i]->m_name.c_str());
		}
		if (m_battle->m_pTeam->m_pCharacters[i]->IsTarget()) attroff(COLOR_PAIR(2));

		// Draw HP
		mvprintw(m_height - 4, 6 + i * 25, "%s", ("HP: " + GenPercentageBar(m_battle->m_pTeam->m_pCharacters[i]->GetStatsPercentage(CHARACTER_STATS::HP))).c_str());


		// Draw Energy
		int colorCode = (int)m_battle->m_pTeam->m_pCharacters[i]->GetElementType() + 1;
		attron(COLOR_PAIR(colorCode));
		mvprintw(m_height - 5, 2 + i * 25, "%s", ("Energy: " + GenPercentageBar(m_battle->m_pTeam->m_pCharacters[i]->GetEnergyPercentage())).c_str());
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
	// we'll keep as many permanent messages on the screen as possible
	if (m_onScreenMsg.size() > UserInterface::NUM_MSG)
	{
		int removalIndex = 0;
		// First see if there's more than 1 temporary messages
		int tempMsgCount = 0;
		for (int i = 0; i < m_onScreenMsg.size(); i++)
		{
			if (m_onScreenMsg[i].expirationTime > 0)
			{			
				if(tempMsgCount==0) removalIndex = i; // remember the index of the first temp messsage
				tempMsgCount++;
			}
		}

		// if there's <=1 temp message, remove the top message
		if (tempMsgCount <= 1) removalIndex = 0;

		m_onScreenMsg.erase(m_onScreenMsg.begin()+removalIndex);
	}

	mvprintw(2, 90, "%s", "Logs:");
	for (int i = 0; i < m_onScreenMsg.size(); i++)
	{
		mvprintw(i + 3, 90, "%s", m_onScreenMsg[i].msg.c_str());
	}
}