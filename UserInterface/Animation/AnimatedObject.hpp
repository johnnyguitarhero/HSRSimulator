#pragma once

#include <vector>
#include <string>

#include "Animation.hpp"

class AnimatedObject
{
public:
	AnimatedObject(const std::vector<std::vector<std::string>>& frameData):m_frameData(frameData)
	{

	}
	~AnimatedObject(){}

	void Render()
	{		
		m_pCurAnimation->RenderFrame();			

		if (m_pNextAnimation!=m_pCurAnimation)
		{
			m_pCurAnimation = m_pNextAnimation;
		}
	}

	// Expected to be called from another thread
	void SetNextState(unsigned state)
	{
		m_pNextAnimation = m_pAnimationList[state];
	}

protected:
	const std::vector<std::vector<std::string>>& m_frameData;
	Animation* m_pCurAnimation;
	Animation* m_pNextAnimation;
	std::vector<Animation*> m_pAnimationList;

};