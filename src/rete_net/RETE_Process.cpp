#include "RETE_Process.h"

bool RETE_Process::isExist;

void RETE_Process::resetAndClearGraph()
{
	//theGraph.resetAndClearNet();
	isExist = false;
}

void RETE_Process::buildGraph()
{
	//theGraph.buildCurrentAlphaBeta();
	isExist = true;
}


void RETE_Process::addCondition(list<string> input)
{
	//cannot handle list, lets go for vector
	vector<string> newInputForm;
	for (auto v : input) {
		newInputForm.push_back(v);
	}

	//edit & into AND
	string temp;
	for (auto v : newInputForm[0]) {
		if (v == '&') {
			temp += " AND ";
		}
		else {
			temp += v;
		}
	}
	newInputForm[0] = temp;

	//separate

	//main part
	string finalTerm;
	
	vector<pair<string, string>> made;
	made = Utilities::tokenize(newInputForm[0] + " " + newInputForm[2]);

	char* token;
	char* str = (char*)malloc(100);

	//This belong to beta and terminal
	if (made.size() == 2) {
		for (int i = 0; i < made.size(); i++) {
			//beta node
			if (i == 0) {
				finalTerm += made[i].second;
				finalTerm += " then ";
			}
			else {
				finalTerm += made[i].second;
			}
		}

		//cqRete.addTerminal(finalTerm);

		int a;
	}
	//This belong to alpha-beta or beta-beta
	else if (made.size() > 2) {
		for (int i = 0; i < made.size(); i++) {

			if (i == 3) {
				finalTerm += "then ";
			}

			if (made[i].first == "Alpha") {
				//if alpha is exist

				//if alpha is not exist
				//cqRete.addAlpha(made[i].second);

				finalTerm += made[i].second;
				finalTerm += " ";
			}
			else {
				finalTerm += made[i].second;
				finalTerm += " ";
			}
			token = strtok(str, " ");
		}

		//cqRete.addBeta(finalTerm);
	}
}

RETE_Process::RETE_Process(vector<string> inputStreamNames, string outputStreamName, ReteGraph* exactGraph)
{
	this->outputStreamName = outputStreamName;
	this->inputStreamNames = inputStreamNames;
	for (int i = 0; i < inputStreamNames.size(); i++) {
		this->inputQueues.push_back(new queue<EventPtr>());
	}
	theGraph = exactGraph;
}

RETE_Process::~RETE_Process()
{
	//should be delete whole rete created;
}

bool RETE_Process::process(int timeSlice)
{
	return false;
}

void RETE_Process::addOutputQueue(queue<EventPtr>* outputQueue, string outputStreamNameOfProcess)
{
	inputQueueSetOfDownstreamProcessUnit.push_back(outputQueue);
	outputNameSetOfDownstreamProcessUnit.push_back(outputStreamNameOfProcess);
}

vector<string> RETE_Process::getInputStreamNames()
{
	return inputStreamNames;
}

vector<queue<EventPtr>*> RETE_Process::getInputQueues()
{
	return inputQueues;
}

string RETE_Process::getOutputStreamName()
{
	return outputStreamName;
}

set<string> RETE_Process::getConnectedOutputNameSet()
{
	set<string> nameSet;
	for (string name : outputNameSetOfDownstreamProcessUnit) {
		nameSet.insert(name);
	}
	return nameSet;
}

bool RETE_Process::removeOutputQueueAndNameFromA(string outputNameOfProcessUnitB)
{
	for (int i = 0; i < outputNameSetOfDownstreamProcessUnit.size(); i++) {
		if (outputNameSetOfDownstreamProcessUnit[i] == outputNameOfProcessUnitB) {//exists
			delete inputQueueSetOfDownstreamProcessUnit[i];

			int j = i + 1;
			for (; j < outputNameSetOfDownstreamProcessUnit.size(); j++) {//move reaward one step.
				outputNameSetOfDownstreamProcessUnit[j - 1] = outputNameSetOfDownstreamProcessUnit[j];
				inputQueueSetOfDownstreamProcessUnit[j - 1] = inputQueueSetOfDownstreamProcessUnit[j];
			}
			outputNameSetOfDownstreamProcessUnit.pop_back();
			inputQueueSetOfDownstreamProcessUnit.pop_back();
			return true;
		}
	}
	return false;
}

bool RETE_Process::removeAllDownStreamQueuesAndNames()
{
	inputQueueSetOfDownstreamProcessUnit.clear();
	outputNameSetOfDownstreamProcessUnit.clear();
	return true;
}
