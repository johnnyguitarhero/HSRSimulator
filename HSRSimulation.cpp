// HSRSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "MobileEntity.hpp"
#include "AllMobileEntities.hpp"
using namespace std;

int main()
{
	cout << "======================================" << endl;
	cout << "|                                    |" << endl;
	cout << "|     Honkai Star Rail Simulator     |" << endl;
	cout << "|                                    |" << endl;
	cout << "======================================" << endl;

	// Create team, enemies and turn counter
	unordered_map<string, MobileEntity*> mobileEntityMap;
	vector<MobileEntity*> actionQueue;
	actionQueue.push_back(new TurnCounter());
	actionQueue.push_back(new Sparkle());
	actionQueue.push_back(new Seele());
	actionQueue.push_back(new Huohuo());

	// Create name map for everything except the turn counter
	for (int i = 1; i < actionQueue.size(); i++)
	{
		mobileEntityMap.insert({ actionQueue[i]->m_name, actionQueue[i] });
	}


	int turn = 2;
	float timer = 0.0f;
	while(turn>0)
	{
		// Sort the action queue
		sort(actionQueue.begin(), actionQueue.end(), CompareTime());

		// Top of the queue would be the current mobile entity
		MobileEntity* currentMobileEntity = actionQueue[0];
		float actionTime = currentMobileEntity->m_remainTime;
		timer += actionTime;

		// Other mobile entities advance forward
		for (int i = 1; i < actionQueue.size(); i++)
		{
			MobileEntity* queuedMobileEntity = actionQueue[i];
			queuedMobileEntity->m_distance -= queuedMobileEntity->cur_speed * actionTime;
			queuedMobileEntity->m_remainTime = queuedMobileEntity->m_distance / queuedMobileEntity->cur_speed;
		}
		
		printf("t = %6.2f     ", timer);
		
		// Current mobile entity moves
		if (currentMobileEntity->m_name=="TurnCounter")
		{
			// If it's the turn counter
			cout << "================" << endl;
			dynamic_cast<TurnCounter*>(currentMobileEntity)->ResetCounter();
			turn--;
		}
		else
		{
			// If it's characters
			Character* curCh = dynamic_cast<Character*>(currentMobileEntity);
			curCh->BuffEvents(PRE_TURN);
			if (curCh->m_name == "Sparkle")
			{
				// User input or AI logic
				curCh->AddTarget(dynamic_cast<Character*>(mobileEntityMap["Seele"]));
				curCh->UseSkill();
				cout << curCh->m_name << endl;
				curCh->DisplayStats();
			}
			else if (curCh->m_name == "Seele")
			{
				// User input or AI logic
				curCh->UseSkill();
				cout << curCh->m_name << endl;
				curCh->DisplayStats();
			}
			else if (curCh->m_name == "Huohuo")
			{
				// User input or AI logic
				curCh->AddTarget(dynamic_cast<Character*>(mobileEntityMap["Seele"]))
					 ->AddTarget(dynamic_cast<Character*>(mobileEntityMap["Sparkle"]))
					 ->AddTarget(curCh);
				curCh->UseUltimate();
				cout << curCh->m_name << endl;
				curCh->DisplayStats();
			}
			curCh->BuffEvents(POST_TURN);
		}
		
		// Current mobile entity resets to the starting point
		currentMobileEntity->Reset();

	}


	for (int i = 0; i < actionQueue.size(); i++)
	{
		delete actionQueue[i];
	}


	return 0;
}

