#pragma once

#include <vector>
#include <string>
#include <thread>
#include <chrono> // for std::chrono
#include "Animation.hpp"

class AnimatedObject
{
public:
	AnimatedObject(const std::vector<std::vector<std::string>>& frameData):m_frameData(frameData), m_stateLock(false)
	{

	}
	~AnimatedObject(){}

	void Render()
	{		
		m_pCurAnimation->RenderFrame();			

		// If current animation is finished, go back to the previous state
		if (!m_pCurAnimation->IsInfinite() && m_pCurAnimation->IsFinished())
		{
			m_pCurAnimation = m_pLastAnimation;
			m_pNextAnimation = m_pCurAnimation;
			m_stateLock = false;
		}

		// If next animation is different, switch to the next animation
		if (m_pNextAnimation!=m_pCurAnimation)
		{
			m_pCurAnimation->OnExit();
			m_pLastAnimation = m_pCurAnimation;
			m_pCurAnimation = m_pNextAnimation;
			m_pCurAnimation->OnEntry();
		}
	}

	// Expected to be called from another thread
	bool SetNextState(unsigned state)
	{	
		// Wait until render thread release the lock
		while(m_stateLock){}

		// Only infinte animation can be interrupted
		if (m_pCurAnimation->IsInfinite())
		{
			m_pNextAnimation = m_pAnimationList[state];
			if (!m_pNextAnimation->IsInfinite())
			{
				m_stateLock = true;
			}
			return true;
		}
		else
		{
			return false;
		}
	}


protected:
	const std::vector<std::vector<std::string>>& m_frameData;
	bool m_stateLock; // Prevent setting next state when the existing next state is not processed
	Animation* m_pCurAnimation;
	Animation* m_pNextAnimation;
	Animation* m_pLastAnimation;
	std::vector<Animation*> m_pAnimationList;

};