#pragma once

#include <vector>
#include <iostream>
#include "Enemy.hpp"
//#include "AllMobileEntities.hpp"

class EnemyTeam
{
public:
	EnemyTeam() : m_maxTeamSize(5), m_curTeamSize(0)
	{
		m_pEnemies.clear();
	}
	~EnemyTeam()
	{
		for (int i = 0; i < m_pEnemies.size(); i++)
		{
			delete m_pEnemies[i];
		}
	}


	bool AddEnemy(Enemy* pEnemy)
	{
		if (m_curTeamSize < m_maxTeamSize)
		{
			m_pEnemies.push_back(pEnemy);
			pEnemy->m_pTeam = this;
			m_curTeamSize++;
			return true;
		}
		else
		{
			return false;
		}
	}

	void ClearTargetStatus()
	{
		for (int i = 0; i < m_curTeamSize; i++)
		{
			m_pEnemies[i]->SelectedAsTarget(false);
		}
	}

	int m_curTeamSize;
	int m_maxTeamSize;
	std::vector<Enemy*> m_pEnemies;
};