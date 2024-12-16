#pragma once

#include "AnimatedObject.hpp"
#include "Idle.hpp"
#include "Freeze.hpp"
#include "LinearMotion.hpp"


// When adding new animations, the order has to follow this table
enum CHARACTER_ANIMATION_STATES
{
	FREEZE = 0,
	IDLE,
	INTERACT_ENEMY_1,
	INTERACT_ENEMY_2,
	INTERACT_ENEMY_3,
	INTERACT_ENEMY_4,
	INTERACT_TEAMMATE_1,
	INTERACT_TEAMMATE_2,
	INTERACT_TEAMMATE_3,
	INTERACT_TEAMMATE_4
};

class AnimatedCharacter : public AnimatedObject
{
public:
	AnimatedCharacter(const std::vector<std::vector<std::string>>& frameData, int row, int col): AnimatedObject(frameData)
	{
		m_pAnimationList.push_back(new Freeze(frameData, row, col));
		m_pAnimationList.push_back(new Idle(frameData, row, col));
		m_pCurAnimation = m_pAnimationList[0];
		m_pNextAnimation = m_pAnimationList[0];
	}
	~AnimatedCharacter()
	{
		for (int i = 0; i < m_pAnimationList.size(); i++)
		{
			delete m_pAnimationList[i];
		}
	}

	void AddInteraction(const std::vector<std::vector<float>>& trajectory, float speed)
	{
		m_pAnimationList.push_back(new LinearMotion(m_frameData, trajectory, speed));
	}
	
};