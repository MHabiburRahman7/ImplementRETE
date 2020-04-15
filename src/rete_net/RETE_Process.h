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

	//RETE_Process();

	ReteGraph* theGraph;

	static bool isExist;

	void resetAndClearGraph();
	void buildGraph();
	static void addCondition(list<string> input);

	RETE_Process(vector<string> inputStreamNames, string outputStreamName, ReteGraph* exactGraph);
	~RETE_Process();

	//---------------------------
	//implemented methods
	//-------------------------
	bool process(int timeSlice)override;
	//string outputStreamNameOfProcess, the output stream name connected to this process unit.
	void addOutputQueue(queue<EventPtr>* outputQueue, string outputStreamNameOfProcess)override;
	vector<string> getInputStreamNames()override;
	vector<queue<EventPtr>*> getInputQueues()override;
	string getOutputStreamName()override;
	set<string> getConnectedOutputNameSet()override;

	//Process unit B connects to A downstream. It means that the input of B is from A.
	bool removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB) override;
	bool removeAllDownStreamQueuesAndNames() override;

private:
	vector<string> inputStreamNames;
	//vector<Window*> windowList;

	//the result name of stream after processing
	string outputStreamName;
	vector<queue<EventPtr>*> inputQueues;
	//the input queue of other processing units.
	vector<queue<EventPtr>*> inputQueueSetOfDownstreamProcessUnit;
	//the output names of process that connects to this process unit.
	vector<string> outputNameSetOfDownstreamProcessUnit;
	// all stateless operatorPredicates and simple predicates share one queue reader.
};

