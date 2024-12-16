#include "LinearMotion.hpp"

void LinearMotion::RenderFrame()
{ 
	// Render a frame according to curRow and curCol
	for (int row = 0; row < m_frameData[0].size(); row++)
	{
		mvprintw((int)m_curRow + row, (int)m_curCol, m_frameData[m_frameCounter][row].c_str());
	}

	// Move along the trajectory at m_moveSpeed
	m_curRow = m_curRow + (m_trajectory[m_curTarget][0] - m_trajectory[m_curTarget - 1][0]) / m_trajectoryLength[m_curTarget - 1] * m_moveSpeed;
	m_curCol = m_curCol + (m_trajectory[m_curTarget][1] - m_trajectory[m_curTarget - 1][1]) / m_trajectoryLength[m_curTarget - 1] * m_moveSpeed;

	// If it gets close enough to the current target, set the next target
	if (sqrtf(powf(m_curRow - m_trajectory[m_curTarget][0], 2) + powf(m_curCol - m_trajectory[m_curTarget][1], 2)) < 4)
	{
		m_curRow = m_trajectory[m_curTarget][0];
		m_curCol = m_trajectory[m_curTarget][1];
		m_curTarget++;
	}

	// End of animation 
	if (m_curTarget >= m_trajectory.size())
	{
		m_endFlag = true;
	}

	m_renderFrameCounter++;
	if (m_renderFrameCounter == m_framePeriod)
	{
		m_frameCounter = (m_frameCounter + 1) % m_frameData.size();
		m_renderFrameCounter = 0;
	}
}