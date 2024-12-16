#pragma once

#include <vector>
#include <string>

#include "curses.h"

const std::vector<std::vector<std::string>> EMPTY_ANIMATION = { {} };

class Animation
{
public:
	Animation(bool infinite): m_frameData(EMPTY_ANIMATION), m_infinite(infinite)
	{
		m_frameCounter = 0;
		m_renderFrameCounter = 0;
	}

	Animation(const std::vector<std::vector<std::string>> &frameData, bool infinite) : m_frameData(frameData), m_infinite(infinite)
	{
		m_frameCounter = 0;
		m_renderFrameCounter = 0;
	}

	~Animation(){}

	bool IsInfinite()
	{
		return m_infinite;
	}

	bool IsFinished()
	{
		return m_endFlag;
	}

	virtual void RenderFrame() = 0;
	virtual void OnEntry() = 0;
	virtual void OnExit() = 0;

protected:
	int m_framePeriod=10; // length of each frame
	uint64_t m_renderFrameCounter; // Render frame counter
	int m_frameCounter; // counter used to decide which frame of the frameData needs to be rendered

	const std::vector<std::vector<std::string>> &m_frameData;
	std::vector<std::vector<int>> m_trajectory;

	bool m_infinite; // Whether the animation is endless or not
	bool m_endFlag = false; // End flag set to true if animation finishes

private:
};