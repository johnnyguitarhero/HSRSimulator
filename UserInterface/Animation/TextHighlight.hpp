#pragma once

#include "Animation.hpp"

class TextHighlight : public Animation
{
public:
	TextHighlight(int row, int col) : Animation(EMPTY_ANIMATION, true)
	{
		m_startRow = row;
		m_startCol = col;
		m_curHighlightedCol = 0;
		m_text = "";

		m_framePeriod = 10;
	}
	~TextHighlight() {}

	void SetText(std::string str, char* f="s")
	{
		m_text = str;
		m_format = f;
	}

	void RenderFrame()
	{
		attron(COLOR_PAIR(m_curHighlightedCol%8));
		//mvprintw(m_startRow, m_startCol + m_curHighlightedCol, &m_text[m_curHighlightedCol]);
		mvprintw(m_startRow, m_startCol, m_format, m_text.c_str());
		attroff(COLOR_PAIR(m_curHighlightedCol%8));

		m_renderFrameCounter++;
		if (m_renderFrameCounter == m_framePeriod)
		{
			m_curHighlightedCol = (m_curHighlightedCol + 1) % m_text.length();
			m_renderFrameCounter = 0;
		}
	}

	void OnEntry() {}
	void OnExit() {}

private:
	std::string m_text;
	char* m_format;
	int m_startRow;
	int m_startCol;
	int m_curHighlightedCol;
};