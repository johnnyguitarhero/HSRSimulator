#pragma once

#include "Animation.hpp"

class Freeze : public Animation
{
public:
	Freeze(const std::vector<std::vector<std::string>>& frameData, int row, int col) : Animation(frameData)
	{
		m_startRow = row;
		m_startCol = col;
	}
	~Freeze() {}

	void RenderFrame()
	{
		for (int row = 0; row < m_frameData[0].size(); row++)
		{
			mvprintw(m_startRow + row, m_startCol, m_frameData[0][row].c_str());
		}
	}

private:
	int m_startRow;
	int m_startCol;
};