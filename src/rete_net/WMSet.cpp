//#include "stdafx.h"
#include "WMSet.h"

vector<queue<EventPtr>*> WMSet::getWMInputQueue()
{
	return inputQueues;
}

vector<queue<EventPtr>*> WMSet::getWMInputQueueProcessingUnit()
{
	return inputQueueSetOfDownstreamProcessUnit;
}

void WMSet::createInputQueue(string inputNames)
{
	inputQueues.push_back(new queue<EventPtr>());
}

void WMSet::printInsisde()
{
	for (int i = 0; i < inputQueues.size(); i++) {
		//cout << inputQueues[i] << endl;
	}
}

void WMSet::clearSet()
{
	inputQueues.clear();
}
