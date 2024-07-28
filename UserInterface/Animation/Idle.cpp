#include "Idle.hpp"

void Idle::RenderFrame()
{
	for (int row = 0; row < m_frameData[0].size(); row++)
	{
		mvprintw(m_startRow+row, m_startCol, m_frameData[m_frameCounter][row].c_str());
	}
	
	m_renderFrameCounter++;
	if (m_renderFrameCounter == m_framePeriod)
	{
		m_frameCounter = (m_frameCounter + 1) % m_frameData.size();
		m_renderFrameCounter = 0;
	}
	
}