#pragma once

#include <vector>
#include <queue>
#include "MobileEntity.hpp"
#include "CharacterStats.hpp"

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
		m_curEnergy = 0.0f;
		m_maxEnergy = 100.0f;
	}
	~Character(){}

	virtual void UseBasicAtk() = 0;
	virtual void UseSkill() = 0;
	virtual void UseUltimate() = 0;
	virtual void InitCharacter() = 0;

	// Target selection
	std::vector<Character*> m_pTargetList;
	Character* AddTarget(Character* p_tgtCharacter)
	{
		m_pTargetList.push_back(p_tgtCharacter);
		return this;
	}

	// Add buffs
	void AddBuff(CHARACTER_STATS type, float percentage, int remainingTurns, bool preTurn)
	{
		m_buffList.push_back(Buff(type, percentage, remainingTurns, preTurn));
	}


	// Events before each character moves
	void BuffEvents( bool curTime )
	{
		// Sort the buffs
		std::sort(m_buffList.begin(), m_buffList.end(), CompareBuffTurn());
		
		// Buff turns decrement
		std::vector<float> buffPercentages(CHARACTER_STATS::NUM_STATS, 1.0f);
		int expiredBuffCount = 0;
		for (int i = 0; i < m_buffList.size(); i++)
		{
			if (m_buffList[i].m_buffChangeTime == curTime)
			{
				// If buff turn decrements
				m_buffList[i].m_remainingTurns--;
				if (m_buffList[i].m_remainingTurns == 0)
				{
					// If buff turn decreased to 0, the buff has expired
					expiredBuffCount++;
				}
			}			
		}

		// Remove expired buffs
		for (int i = 0; i < expiredBuffCount; i++)
		{
			m_buffList.pop_back();
		}

		// Traverse the list to calculate multipliers
		for (int i = 0; i < m_buffList.size(); i++)
		{
			buffPercentages[m_buffList[i].m_type] += m_buffList[i].m_percentage / 100.0f;
		}

		// Apply the buffs
		m_curStats[CHARACTER_STATS::ATK] = buffPercentages[CHARACTER_STATS::ATK] * m_stats[CHARACTER_STATS::BASE_ATK] + m_stats[CHARACTER_STATS::EXTRA_ATK];
		m_curStats[CHARACTER_STATS::DEF] = buffPercentages[CHARACTER_STATS::DEF] * m_stats[CHARACTER_STATS::BASE_DEF] + m_stats[CHARACTER_STATS::EXTRA_DEF];
		m_curStats[CHARACTER_STATS::SPD] = buffPercentages[CHARACTER_STATS::SPD] * m_stats[CHARACTER_STATS::BASE_SPD] + m_stats[CHARACTER_STATS::EXTRA_SPD];
		m_curStats[CHARACTER_STATS::CRIT_DMG] = buffPercentages[CHARACTER_STATS::CRIT_DMG] * m_stats[CHARACTER_STATS::CRIT_DMG];
		cur_speed = m_curStats[CHARACTER_STATS::SPD];
	}

	void DisplayStats()
	{
		std::cout << "               Cur speed = " << m_curStats[CHARACTER_STATS::SPD] << std::endl;
		std::cout << "               Cur crit damage = " << m_curStats[CHARACTER_STATS::CRIT_DMG] << std::endl;
	}

protected:
	std::vector<float> m_curStats; // Current character stats
	std::vector<float> m_stats; // Character stats off battle
	std::vector<Buff> m_buffList; // List of buffs
	float m_curEnergy;
	float m_maxEnergy;

private:
	// Sort helper function
	struct CompareBuffTurn {
		bool operator()(const Buff& b1, const Buff& b2) const {
			return b1.m_remainingTurns > b2.m_remainingTurns;
		}
	};
};