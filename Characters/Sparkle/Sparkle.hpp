#pragma once

#include "Character.hpp"

class Sparkle : public Character
{
public:
	Sparkle()
	{
		InitCharacter();
	}
	~Sparkle() {}

	void UseBasicAtk() {}
	void UseSkill()
	{
		for (int i = 0; i < m_pTargetList.size(); i++)
		{
			m_pTargetList[i]->m_remainTime = std::max(0.0f, m_pTargetList[i]->m_remainTime - 50.0f);
			m_pTargetList[i]->m_distance = std::max(0.0f, m_pTargetList[i]->m_distance - 50.0f * m_pTargetList[i]->cur_speed);
			m_pTargetList[i]->AddBuff(CHARACTER_STATS::CRIT_DMG, this->m_curStats[CHARACTER_STATS::CRIT_DMG] * 0.24f + 45.0f, 2, PRE_TURN);
		}

		m_pTargetList.clear();
	}
	void UseUltimate() {}

private:
	void InitCharacter()
	{
		// Name
		m_name = "Sparkle";

		// Actions
		m_actionTargetType[CHARACTER_ACTION::BASIC_ATTACK] = TARGET_TYPE::SINGLE_ENEMY;
		m_actionTargetType[CHARACTER_ACTION::SKILL] = TARGET_TYPE::SINGLE_TEAMMATE;
		m_actionTargetType[CHARACTER_ACTION::ULTIMATE] = TARGET_TYPE::AOE_TEAMMATE;

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
			101.0f, // Base Spd
			57.0f, // Extra Spd
			101.0f + 57.0f, // Spd
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
	}

	int m_spdUpLevel;
};