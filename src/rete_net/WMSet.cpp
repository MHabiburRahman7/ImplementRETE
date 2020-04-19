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

queue<EventPtr>* WMSet::getSingleInputQueue(int i)
{
	return inputQueues[i];
}

string WMSet::getSingleInputQueueName(int i)
{
	return inputStreamNames[i];
}

queue<EventPtr>* WMSet::getSingleInputQueue(string name)
{
	for (int i = 0; i < inputStreamNames.size(); i++)
		if (name == inputStreamNames[i])
			return inputQueues[i];
	return nullptr;
}

//string WMSet::getSingleInputName(int i)
//{
//	return inputStreamNames[i];
//}

void WMSet::createInputQueue(string inputNames)
{
	for (int i = 0; i < inputStreamNames.size(); i++) {
		if (inputStreamNames[i] == inputNames)
			break;
	}

	inputStreamNames.push_back(inputNames);
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
