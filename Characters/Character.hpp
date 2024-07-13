#pragma once

#include <vector>
#include <queue>
#include "MobileEntity.hpp"
#include "CharacterEnums.hpp"

#define PRE_TURN true
#define POST_TURN false

struct Buff
{
	Buff(CHARACTER_STATS type, float percentage, int remainingTurns, bool buffChangeTime)
	{
		m_type = type;
		m_percentage = percentage;
		m_remainingTurns = remainingTurns;
		m_buffChangeTime = buffChangeTime;
	}
	CHARACTER_STATS m_type;
	float m_percentage;
	int m_remainingTurns;
	bool m_buffChangeTime;
};

class Character: public MobileEntity
{
public:
	Character()
	{
		m_curStats = std::vector<float>(CHARACTER_STATS::NUM_STATS, 0.0f);
		m_stats = std::vector<float>(CHARACTER_STATS::NUM_STATS, 0.0f);
		m_actionTargetType = std::vector<TARGET_TYPE>(CHARACTER_ACTION::NUM_ACTION_TYPE, (TARGET_TYPE)0);
		m_curEnergy = 0.0f;
		m_maxEnergy = 100.0f;
		m_ultReady = false;
		m_targeted = false;
	}
	~Character(){}

	virtual void UseBasicAtk()
	{
		m_curEnergy += ENERGY_RECHARGE_BASIC_ATK;
		if(m_curEnergy>=m_maxEnergy)
		{
			m_curEnergy = m_maxEnergy;
			m_ultReady = true;
		}
	}
	virtual void UseSkill()
	{
		m_curEnergy += ENERGY_RECHARGE_SKILL;
		if (m_curEnergy >= m_maxEnergy)
		{
			m_curEnergy = m_maxEnergy;
			m_ultReady = true;
		}
	}
	virtual void UseUltimate()
	{
		m_curEnergy = 0.0f;
		m_ultReady = false;
	}
	virtual void InitCharacter() = 0;

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
	Character* AddTarget(Character* p_tgtCharacter)
	{
		m_pTargetList.push_back(p_tgtCharacter);
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
	void AddBuff(CHARACTER_STATS type, float percentage, int remainingTurns, bool preTurn)
	{
		m_buffList.push_back(Buff(type, percentage, remainingTurns, preTurn));
	}

	

	std::string DisplayStats(CHARACTER_STATS stat)
	{
		float percentage = m_curStats[stat] / m_stats[stat] * 10.0;
		std::string output = "[         ]";
		for (int i = 1; i < (int)percentage; i++)
		{
			output[i] = '=';
		}
		return output;
	}

	std::string DisplayEnergy()
	{
		float percentage = m_curEnergy / m_maxEnergy * 10.0;
		std::string output = "[         ]";
		for (int i = 1; i < (int)percentage; i++)
		{
			output[i] = '=';
		}
		return output;
	}

	bool UltReady()
	{
		return m_ultReady;
	}

	void BuffEvents(bool curTime);

protected:
	std::vector<float> m_curStats; // Current character stats
	std::vector<float> m_stats; // Character stats off battle
	std::vector<Buff> m_buffList; // List of buffs
	std::vector<TARGET_TYPE> m_actionTargetType; // Action type list
	std::vector<Character*> m_pTargetList;
	ELEMENT_TYPE m_elementType;
	float m_curEnergy;
	float m_maxEnergy;
	bool m_ultReady;
	bool m_targeted;

private:
	// Sort helper function
	struct CompareBuffTurn {
		bool operator()(const Buff& b1, const Buff& b2) const {
			return b1.m_remainingTurns > b2.m_remainingTurns;
		}
	};
};