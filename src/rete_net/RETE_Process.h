#pragma once
#include "ReteGraph.h"
#include "Utilities.h"
#include "../execution/Process.h"
#include "../common/Event.h"
#include <iostream>

using namespace std;

class RETE_Process : public Process
{
public:

	RETE_Process();

	static ReteGraph theGraph, cqRete, cepRete;

	static bool isExist;

	static void resetAndClearGraph();
	static void buildGraph();
	bool process(int timeSlice)override;
	static void addCQ(list<string> input);

private:
	//the input queue of other processing units.
	vector<queue<EventPtr>*> inputQueueSetOfDownstreamProcessUnit;
	//the output names of process that connects to this process unit.
	vector<string> outputNameSetOfDownstreamProcessUnit;
};

