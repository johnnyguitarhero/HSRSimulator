#pragma once

#include "AnimatedObject.hpp"
#include "Idle.hpp"
#include "Freeze.hpp"

enum CHARACTER_ANIMATION_STATES
{
	FREEZE = 0,
	IDLE
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
	
};