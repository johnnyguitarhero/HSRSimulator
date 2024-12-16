#pragma once

#include "Animation.hpp"

class LinearMotion : public Animation
{
public:
	LinearMotion(const std::vector<std::vector<std::string>>& frameData, const std::vector<std::vector<float>>& trajectory, float speed)
		: Animation(frameData,false), m_trajectory(trajectory)
	{
		m_moveSpeed = speed;
		m_curRow = trajectory[0][0];
		m_curCol = trajectory[0][1];
		m_curTarget = 1;
		for (int i = 0; i < trajectory.size() - 1; i++)
		{
			m_trajectoryLength.push_back(sqrtf(powf(trajectory[i][0] - trajectory[i + 1][0], 2) + powf(trajectory[i][1] - trajectory[i + 1][1], 2)));
		}
	}

	void RenderFrame();

	void OnEntry()
	{
		m_curRow = m_trajectory[0][0];
		m_curCol = m_trajectory[0][1];
		m_curTarget = 1;
		m_endFlag = false;
	}

	void OnExit() {};

private:
	std::vector<std::vector<float>> m_trajectory;
	std::vector<float> m_trajectoryLength;
	unsigned m_curTarget; // index of node in the trajectory list
	float m_curRow;
	float m_curCol;
	float m_moveSpeed;
};