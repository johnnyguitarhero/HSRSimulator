#pragma once

#include "Character.hpp"

class Seele : public Character
{
public:
	Seele()
	{
		InitCharacter();
	}
	~Seele(){}

	void UseBasicAtk()
	{
		Character::UseBasicAtk();
	}

	void UseSkill()
	{	
		// Attack enemy
		for (int i = 0; i < m_pTargetList.size(); i++)
		{
			//m_pTargetList[i]->m_curStats[CHARACTER_STATS::HP] -= 1.0f; // TODO: Set correct damage
		}

		// Buff herself
		this->AddBuff(CHARACTER_STATS::SPD, 25.0f, 2, POST_TURN);
		
		Character::UseSkill();
	}
	void UseUltimate()
	{
		Character::UseUltimate();
	}

private:
	void InitCharacter()
	{
		// Name
		m_name = "Seele";

		// Element Type
		m_elementType = ELEMENT_TYPE::QUANTUM;

		// Actions
		m_actionTargetType[CHARACTER_ACTION::BASIC_ATTACK] = TARGET_TYPE::SINGLE_ENEMY;
		m_actionTargetType[CHARACTER_ACTION::SKILL] = TARGET_TYPE::SINGLE_ENEMY;
		m_actionTargetType[CHARACTER_ACTION::ULTIMATE] = TARGET_TYPE::SINGLE_ENEMY;

		// Character Stats
		m_stats =
		{
			1989.0f, // Base HP
			1075.0f, // Extra HP
			1989.0f + 1075.0f, // HP
			1222.0f, // Base Atk
			2213.0f, // Extra Atk
			1222.0f + 2213.0f, // Atk
			826.0f, // Base Def
			251.0f, // Extra Def
			826.0f + 251.0f, // Def
			115.0f, // Base Spd
			11.8f, // Extra Spd
			115.0f + 11.8f, // Spd
			72.5f, // Crit Rate
			158.8f // Crit Dmg
		};

		for (int i = 0; i < CHARACTER_STATS::NUM_STATS; i++)
		{
			m_curStats[i] = m_stats[i];
		}

		// Initialize battle variables
		cur_speed = m_stats[CHARACTER_STATS::SPD];
		m_remainTime = m_distance / cur_speed;

		m_pTargetList.clear();
		m_spdUpLevel = 0;

	}

	int m_spdUpLevel;
};