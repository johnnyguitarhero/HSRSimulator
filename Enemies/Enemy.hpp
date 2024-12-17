#pragma once

#include <vector>
#include <queue>
#include "MobileEntity.hpp"
#include "CharacterEnums.hpp"
#include "EnemyEnums.hpp"
//#include "AnimatedCharacter.hpp"

class EnemyTeam;

struct EnemyBuff
{
	EnemyBuff(ENEMY_STATS type, float percentage, int remainingTurns, bool buffChangeTime)
	{
		m_type = type;
		m_percentage = percentage;
		m_remainingTurns = remainingTurns;
		m_buffChangeTime = buffChangeTime;
	}
	ENEMY_STATS m_type;
	float m_percentage;
	int m_remainingTurns;
	bool m_buffChangeTime;
};

class Enemy : public MobileEntity
{
public:
	Enemy()
	{
		m_curStats = std::vector<float>(ENEMY_STATS::NUM_ENEMY_STATS, 0.0f);
		m_stats = std::vector<float>(ENEMY_STATS::NUM_ENEMY_STATS, 0.0f);
		m_actionTargetType = std::vector<TARGET_TYPE>(CHARACTER_ACTION::NUM_ACTION_TYPE, (TARGET_TYPE)0);
		m_curEnergy = 0.0f;
		m_maxEnergy = 100.0f;
		m_ultReady = false;
		m_targeted = false;
	}
	~Enemy() {}

	static const std::vector<std::vector<std::string>> m_idleAnimation;

	virtual void UseBasicAtk()
	{
	
	}
	virtual void UseSkill()
	{

	}
	virtual void UseUltimate()
	{
		
	}
	virtual void InitEnemy() = 0;

	// Get target number from action type
	TARGET_TYPE GetTargetType(CHARACTER_ACTION type)
	{
		return m_actionTargetType[type];
	}

	// Get element type
	ELEMENT_TYPE GetElementType()
	{
		return m_elementType;
	}


	// Target selection
	MobileEntity* AddTarget(MobileEntity* p_tgtMobileEntity)
	{
		m_pTargetList.push_back(p_tgtMobileEntity);
		return this;
	}

	// Being target
	void SelectedAsTarget(bool targeted)
	{
		m_targeted = targeted;
	}


	bool IsTarget()
	{
		return m_targeted;
	}

	// Add buffs
	void AddBuff(ENEMY_STATS type, float percentage, int remainingTurns, bool preTurn)
	{
		m_buffList.push_back(EnemyBuff(type, percentage, remainingTurns, preTurn));
	}



	float GetStatsPercentage(ENEMY_STATS stat)
	{
		return m_curStats[stat] / m_stats[stat] * 100.0;
	}

	float GetEnergyPercentage()
	{
		return m_curEnergy / m_maxEnergy * 100.0;
	}

	bool UltReady()
	{
		return m_ultReady;
	}


protected:
	std::vector<float> m_curStats; // Current character stats
	std::vector<float> m_stats; // Character stats off battle
	std::vector<EnemyBuff> m_buffList; // List of buffs
	std::vector<TARGET_TYPE> m_actionTargetType; // Action type list
	std::vector<MobileEntity*> m_pTargetList;
	ELEMENT_TYPE m_elementType;
	EnemyTeam* m_pTeam;
	float m_curEnergy;
	float m_maxEnergy;
	bool m_ultReady;
	bool m_targeted;

	friend EnemyTeam;

private:
	// Sort helper function
	struct CompareBuffTurn {
		bool operator()(const EnemyBuff& b1, const EnemyBuff& b2) const {
			return b1.m_remainingTurns > b2.m_remainingTurns;
		}
	};
};