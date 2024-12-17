#pragma once

#include "Enemy.hpp"

class Vagrant : public Enemy
{
public:
	Vagrant()
	{
		InitEnemy();
	}
	~Vagrant() {}


private:
	void InitEnemy()
	{
		// Name
		m_name = "Vagrant";

		// Element Weakness
		m_elementType = ELEMENT_TYPE::QUANTUM;

		// Actions
		m_actionTargetType[ENEMY_ACTION::ENEMY_BASIC_ATTACK] = TARGET_TYPE::SINGLE_ENEMY;
		m_actionTargetType[ENEMY_ACTION::ENEMY_SKILL] = TARGET_TYPE::SINGLE_ENEMY;
		m_actionTargetType[ENEMY_ACTION::ENEMY_ULTIMATE] = TARGET_TYPE::SINGLE_ENEMY;

		// Character Stats
		m_stats =
		{
			5000.0f , // HP
			10.0f, // Toughness
			2213.0f, // Atk
			826.0f, // Def
			80.0f, // Spd
		};

		for (int i = 0; i < ENEMY_STATS::NUM_ENEMY_STATS; i++)
		{
			m_curStats[i] = m_stats[i];
		}

		// Initialize battle variables
		cur_speed = m_stats[ENEMY_STATS::ENEMY_SPD];
		m_remainTime = m_distance / cur_speed;

		m_pTargetList.clear();
	}
};