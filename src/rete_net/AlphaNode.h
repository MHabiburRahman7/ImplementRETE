#pragma once

#include "Node.h"
#include "BetaNode.h"
#include <string>
#include <cstdlib>

#include "../execution/EventProcess.h"
#include "../op/win/NaiveTimeSlidingWindow.h"
#include "../op/win/Window.h"
#include "../op/ExistOp.h"

#include "../util/Utils.h"

class AlphaNode : public Node
{
public:
	//Starter kit
	int getID();
	string getType();
	//AlphaNode();
	AlphaNode(int id, string condition, string wmNum);

	//Lets connect it
	int checkExistPair(Node* pairs);
	int addBetaPair(Node* pair);

	//Test
	void testAlphaAndSaveHere(vector<pair<int, int>> test_cases);
	bool testDataType(string condition);

	//Initialization
	int ResetNode();
	int ClearResults();

	void testAlphaAndSaveHere(queue<EventPtr>* input, int TimeSlice);

	bool isEmptyResult();

	//get/set function
	string getAlphaDataType();
	string getCondition();
	string getVarLimit();
	string getWmName();
	Node* getSinglePair(int i);
	vector<Node*> getAllPairs();

	queue<EventPtr>* getEvRes();

	void setWindow(int len, int slide);
	void refreshEvent(queue<EventPtr> &eventQueue);

	void setWindowLiyang(int len, int slide);

private:
	int id;
	string wmNumber;
	queue<EventPtr>* EventResult = new queue<EventPtr>();

	//Condition
	string thisDataType;
	string thisCondition;
	string thisVarLimit;

	string additionalStr;

	//Connected Node (I am not sure with this)
	vector<Node*> listOfBetaPairsInNode;

	//windows thing
	vector<Window*> alphaWindowList;
	int winLen = -1;
	int winSlide = -1;
	long long nextTime = -1;
	bool initiated = false;
};

