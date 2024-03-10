#include "Battle.hpp"

Battle::Battle() : m_turn(0), m_timer(0.0f)
{
	m_actionQueue.clear();
	m_pTeam = nullptr;
	m_pTurnCounter = nullptr;
	m_curActionSelection = 0;
	m_curTargetSelection = 0;
	m_curTargetType = -1;
}

Battle::~Battle()
{
	delete m_pTurnCounter;
}


/*
* @brief Initialize a battle
*
* This function initialized a battle with given turn number.
*
* @param[in] pTeam: pointer to the team object
* @param[in] turn: number of turns allowed in the battle
* 
*/
void Battle::InitBattle(Team* pTeam, int turn)
{
	m_pTeam = pTeam;
	m_turn = turn;

	// Add turn counter to the battle
	m_pTurnCounter = new TurnCounter();
	m_actionQueue.push_back(m_pTurnCounter);

	// Add characters to the battle
	for (int i = 0; i < m_pTeam->m_curTeamSize; i++)
	{
		m_actionQueue.push_back(m_pTeam->m_pCharacters[i]);
	}

	// TODO: Add enemies to the battle

}


/*
* @brief The main battle loop
*
* The main battle loop manages the action queue and user inputs
*
*/
void Battle::MainBattle()
{
	while (m_turn > 0)
	{
		// Sort the action queue
		std::sort(m_actionQueue.begin(), m_actionQueue.end(), CompareTime());

		// Top of the queue would be the current mobile entity
		MobileEntity* currentMobileEntity = m_actionQueue[0];
		float actionTime = currentMobileEntity->m_remainTime;
		m_timer += actionTime;

		// Other mobile entities advance forward
		for (int i = 1; i < m_actionQueue.size(); i++)
		{
			MobileEntity* queuedMobileEntity = m_actionQueue[i];
			queuedMobileEntity->m_distance -= queuedMobileEntity->cur_speed * actionTime;
			queuedMobileEntity->m_remainTime = queuedMobileEntity->m_distance / queuedMobileEntity->cur_speed;
		}

		// Current mobile entity moves
		if (currentMobileEntity->m_name == "TurnCounter")
		{
			// If it's the turn counter
			dynamic_cast<TurnCounter*>(currentMobileEntity)->ResetCounter();
			m_turn--;
		}
		else
		{
			// If it's characters
			Character* curCh = dynamic_cast<Character*>(currentMobileEntity);
			curCh->BuffEvents(PRE_TURN);

			// Selection 1: Action
			m_curActionSelection = 0;
			bool selectionMade = false;
			while (!selectionMade)
			{
				int key = getch();
				switch (key)
				{
				case KEY_DOWN:
					m_curActionSelection = (m_curActionSelection + 1) % 3;
					break;
				case KEY_UP:
					m_curActionSelection = (m_curActionSelection - 1 + 3) % 3;
					break;
				case '\n':
					selectionMade = true;
					break;
				}
			}

			// Selection 2: Pick Targets
			m_curTargetType = (int)(curCh->GetTargetType((CHARACTER_ACTION)m_curActionSelection));
			m_curTargetSelection = 0;
			selectionMade = false;

			if (m_curTargetType == (int)TARGET_TYPE::AOE_ENEMY)
			{
				//curCh->AddTarget
			}
			else if (m_curTargetType == (int)TARGET_TYPE::AOE_TEAMMATE)
			{
				for (int i = 0; i < m_pTeam->m_curTeamSize; i++)
				{
					curCh->AddTarget(m_pTeam->m_pCharacters[i]);
					m_pTeam->m_pCharacters[i]->SelectedAsTarget(true);
				}
				while (!selectionMade)
				{
					int key = getch();
					if (key == '\n')
					{
						m_pTeam->ClearTargetStatus();
						selectionMade = true;
					}
				}
			}
			else if (m_curTargetType == (int)TARGET_TYPE::SINGLE_TEAMMATE)
			{
				m_pTeam->m_pCharacters[m_curTargetSelection]->SelectedAsTarget(true);
				while (!selectionMade)
				{
					int key = getch();
					switch (key)
					{
					case KEY_RIGHT:
					{
						m_curTargetSelection = (m_curTargetSelection + 1) % m_pTeam->m_curTeamSize;
						for (int i = 0; i < m_pTeam->m_curTeamSize; i++)
						{
							m_pTeam->m_pCharacters[i]->SelectedAsTarget(false);
						}
						m_pTeam->m_pCharacters[m_curTargetSelection]->SelectedAsTarget(true);
						break;
					}
					case KEY_LEFT:
					{
						m_curTargetSelection = (m_curTargetSelection - 1 + m_pTeam->m_curTeamSize) % m_pTeam->m_curTeamSize;
						for (int i = 0; i < m_pTeam->m_curTeamSize; i++)
						{
							m_pTeam->m_pCharacters[i]->SelectedAsTarget(false);
						}
						m_pTeam->m_pCharacters[m_curTargetSelection]->SelectedAsTarget(true);
						break;
					}
					case '\n':
					{
						curCh->AddTarget(m_pTeam->m_pCharacters[m_curTargetSelection]);
						m_pTeam->ClearTargetStatus();
						selectionMade = true;
						break;
					}
					}
				}
			}

			switch ((CHARACTER_ACTION)m_curActionSelection)
			{
			case CHARACTER_ACTION::BASIC_ATTACK:
				curCh->UseBasicAtk();
				break;
			case CHARACTER_ACTION::SKILL:
				curCh->UseSkill();
				break;
			case CHARACTER_ACTION::ULTIMATE:
				curCh->UseUltimate();
			}

			curCh->BuffEvents(POST_TURN);
		}

		// Current mobile entity resets to the starting point
		currentMobileEntity->Reset();

	}
}

/*
* @brief Draw battle scene using curses
* TODO: The draw screen function is not thread safe at all!!!
*/
void Battle::DrawScreen()
{
	clear();
	int height, width;
	getmaxyx(stdscr, height, width);

	// Hide cursor
	curs_set(0);

	// Draw borders
	for (int i = 0; i < height; i++) {
		mvprintw(i, 0, "|");
		mvprintw(i, width - 1, "|");
	}
	for (int i = 0; i < width; i++) {
		mvprintw(0, i, "-");
		mvprintw(height - 1, i, "-");
	}

	// Draw action queue
	mvprintw(1, 2, "------------");
	for (int i = 0; i < m_actionQueue.size(); i++)
	{
		if (m_actionQueue[i]->m_name == "TurnCounter")
		{
			mvprintw(2 + 2 * i, 2, "|%10d|", m_turn);
		}
		else
		{
			mvprintw(2 + 2 * i, 2, "|%10s|", m_actionQueue[i]->m_name.c_str());
		}

		mvprintw(3 + 2 * i, 2, "------------");
	}

	// Draw action menu
	mvprintw(height - 10, width - 20, "Action Menu:");
	std::vector<std::string> actions = { "Basic Attack", "Skill", "Ultimate" };
	for (int i = 0; i < 3; i++)
	{
		if (i == m_curActionSelection)
		{
			mvprintw(height - 8 + i, width - 20, "> %s <", actions[i].c_str());
		}
		else
		{
			mvprintw(height - 8 + i, width - 20, "%s", actions[i].c_str());
		}
	}

	// Draw enemy
	mvprintw((height - 5) / 2 - 1, (width - 15) / 2, "/-^-\\");
	mvprintw((height - 5) / 2, (width - 15) / 2 + 2, "Enemy");

	// Draw Characters
	for (int i = 0; i < m_pTeam->m_curTeamSize; i++)
	{
		// Draw Names/Pictures
		if (m_pTeam->m_pCharacters[i]->IsTarget()) attron(COLOR_PAIR(2));
		if (dynamic_cast<Character*>(m_actionQueue[0]) == m_pTeam->m_pCharacters[i])
		{
			mvprintw(height - 3, 2 + i * 20, "[%s]", m_pTeam->m_pCharacters[i]->m_name.c_str());
		}
		else
		{
			mvprintw(height - 3, 2 + i * 20, " %s ", m_pTeam->m_pCharacters[i]->m_name.c_str());
		}
		if (m_pTeam->m_pCharacters[i]->IsTarget()) attroff(COLOR_PAIR(2));

		// Draw HP
		attron(COLOR_PAIR(1));
		mvprintw(height - 4, 2 + i * 20, "%s", ("HP: " + m_pTeam->m_pCharacters[i]->DisplayStats(CHARACTER_STATS::HP)).c_str());
		attroff(COLOR_PAIR(1));

	}


	refresh();
}