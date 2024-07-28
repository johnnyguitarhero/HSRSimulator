#pragma once

#include <vector>
#include <string>

#include "curses.h"

class Animation
{
public:
	Animation(const std::vector<std::vector<std::string>> &frameData) : m_frameData(frameData) 
	{
		m_frameCounter = 0;
		m_renderFrameCounter = 0;
	}
	~Animation(){}

	virtual void RenderFrame() = 0;

protected:
	int m_framePeriod=10; // length of each frame
	int m_renderFrameCounter; // counter used to decide the render period, increments from 0 to m_framePeriod
	int m_frameCounter; // counter used to decide which frame of the frameData needs to be rendered

	const std::vector<std::vector<std::string>> &m_frameData;
	std::vector<std::vector<int>> m_trajectory;

private:
};