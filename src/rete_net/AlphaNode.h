#pragma once

#include "Node.h"
#include "BetaNode.h"
#include <string>
#include <cstdlib>

class AlphaNode : public Node
{
public:
	//Connected Node (I am not sure with this)
	vector<Node*> listOfBetaPairsInNode;

	//Test Result
	vector<pair<int, int>> testRes;

	//connect to next beta Node
	//BetaNode* betaPair;
	vector<BetaNode*> listOfBetaPairs;

	//Starter kit
	int id;
	int getID();
	string getType();
	AlphaNode();
	AlphaNode(int id, string condition);
	string getAlphaDataType();

	//Condition
	string thisDataType;
	string thisCondition;
	string thisVarLimit;

	int BaseNodeID;
	string tempComingCondition;

	//Lets connect it
	int checkExistPair(BetaNode* pairs);
	int addBetaPair(BetaNode* pair);

	int addBetaPairInNode(BetaNode* pair);

	//Test
	void testAlphaAndSaveHere(vector<pair<int, int>> test_cases);
	bool testDataType(string condition);
	//int testSingleInAlpha(pair<int, int> test_case);
	//vector<pair<int, int>> testAlphaNode(vector<pair<int, int>> test_cases);

	//Initialization
	int ResetNode();
};

