#pragma once

#include "Node.h"
#include "BetaNode.h"
#include <string>
#include <cstdlib>

#include "../execution/EventProcess.h"

class AlphaNode : public Node
{
public:
	//Test Result
	//vector<pair<int, int>> testRes;

	//Starter kit
	int getID();
	string getType();
	AlphaNode();
	AlphaNode(int id, string condition);
	
	int BaseNodeID; // unused
	string tempComingCondition; //unused

	//Lets connect it
	int checkExistPair(Node* pairs);
	int addBetaPair(Node* pair);

	//Test
	void testAlphaAndSaveHere(vector<pair<int, int>> test_cases);
	bool testDataType(string condition);
	//int testSingleInAlpha(pair<int, int> test_case);
	//vector<pair<int, int>> testAlphaNode(vector<pair<int, int>> test_cases);

	//Initialization
	int ResetNode();
	int ClearResults();

	void testAlphaAndSaveHere(queue<EventPtr>* input, int TimeSlice);

	bool isEmptyResult();

	//get/set function
	string getAlphaDataType();
	string getCondition();
	string getVarLimit();
	Node* getSinglePair(int i);
	vector<Node*> getAllPairs();

private:
	int id;
	queue<EventPtr>* EventResult = new queue<EventPtr>;

	//Condition
	string thisDataType;
	string thisCondition;
	string thisVarLimit;

	//Connected Node (I am not sure with this)
	vector<Node*> listOfBetaPairsInNode;
};

