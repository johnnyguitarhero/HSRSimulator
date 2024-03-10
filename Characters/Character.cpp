#include "Character.hpp"

// Events before each character moves
void Character::BuffEvents(bool curTime)
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