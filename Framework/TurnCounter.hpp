#pragma once

#include "MobileEntity.hpp"

class TurnCounter : public MobileEntity
{
public:
	TurnCounter()
	{
		cur_speed = m_distance / 150.0f;
		m_remainTime = m_distance / cur_speed;
		m_name = "TurnCounter";
	}
	~TurnCounter() {}

	void ResetCounter()
	{
		cur_speed = DISTANCE / 100.0f;
	}
};