#pragma once
#include <vector>
#include <queue>
#include <string>
#include "../execution/EventProcess.h"

using namespace std;

class WMSet
{
public:
	WMSet() {};
	vector<queue<EventPtr>*> getWMInputQueue();
	vector<queue<EventPtr>*> getWMInputQueueProcessingUnit();
	queue<EventPtr>* getSingleInputQueue(int i);
	string getSingleInputQueueName(int i);
	queue<EventPtr>* getSingleInputQueue(string name);

	void createInputQueue(string inputNames);

	void printInsisde();
	void clearSet();

private:
	string wmName;

	vector<string> inputStreamNames;
	//vector<Window*> windowList;

	//the result name of stream after processing
	//string outputStreamName;
	vector<queue<EventPtr>*> inputQueues;
	//the input queue of other processing units.
	vector<queue<EventPtr>*> inputQueueSetOfDownstreamProcessUnit;
	//the output names of process that connects to this process unit.
	//vector<string> outputNameSetOfDownstreamProcessUnit;
};

