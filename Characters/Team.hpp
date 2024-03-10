#pragma once

#include <vector>
#include <iostream>
#include "Character.hpp"
//#include "AllMobileEntities.hpp"

class Team
{
public:
	Team():m_maxSkillPoints(5), m_curSkillPoints(3), m_maxTeamSize(4), m_curTeamSize(0)
	{
		m_pCharacters.clear();
	}
	~Team()
	{
		for (int i = 0; i < m_pCharacters.size(); i++)
		{
			delete m_pCharacters[i];
		}
	}


	void InitSkillPoint()
	{
		m_curSkillPoints = 3;
	}

	bool AddCharacter(Character* pCharacter)
	{
		if (m_curTeamSize < m_maxTeamSize)
		{
			m_pCharacters.push_back(pCharacter);
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
			m_pCharacters[i]->SelectedAsTarget(false);
		}
	}

	int m_curSkillPoints;
	int m_maxSkillPoints;
	int m_curTeamSize;
	int m_maxTeamSize;
	std::vector<Character*> m_pCharacters;
};