#pragma once

#include "Animation.hpp"

class Idle : public Animation
{
public:
	Idle(const std::vector<std::vector<std::string>>& frameData, int row, int col)
		: Animation(frameData, true)
	{
		m_startRow = row;
		m_startCol = col;
	}
	~Idle(){}

	void RenderFrame();
	void OnEntry() {}
	void OnExit() {}

private:
	int m_startRow;
	int m_startCol;
};