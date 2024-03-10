#pragma once

#include <string>
#define DISTANCE 10000.0f

class MobileEntity
{
public:
	MobileEntity()
	{
		m_distance = DISTANCE;
	}
	virtual ~MobileEntity(){}

	void Reset()
	{
		m_distance = DISTANCE;
		m_remainTime = m_distance / cur_speed;
	}

	// Name
	std::string m_name;

	// Distance
	float m_distance;

	// Speed
	//float m_speed;
	float cur_speed;

	// Remaining Time
	float m_remainTime;
};

struct CompareTime {
	bool operator()(const MobileEntity* a1, const MobileEntity* a2) const {
		return a1->m_remainTime < a2->m_remainTime; // Use > for ascending order or < for descending order
	}
};