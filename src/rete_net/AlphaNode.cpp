#include "AlphaNode.h"

int AlphaNode::getID()
{
	return id;
}

string AlphaNode::getType()
{
	return "Alpha";
}

AlphaNode::AlphaNode() : Node(BaseNodeID, tempComingCondition)
{
}

AlphaNode::AlphaNode(int id_given, string condition) : Node(id_given, condition)
{
	int itt = 0;

	id = id_given;

	char* str = (char*)malloc(100);
	strcpy(str, condition.c_str());
	// Returns first token  
	char* token = strtok(str, " ");

	// Keep printing tokens while one of the 
	// delimiters present in str[].
	thisDataType = token;
	while (token != NULL)
	{
		//printf("%s\n", token);
		token = strtok(NULL, " ");
		if (itt == 0)
			thisCondition = token;
		else if (itt == 1)
			thisVarLimit = token;
		itt++;
	}
}

string AlphaNode::getAlphaDataType()
{
	return thisDataType;
}

int AlphaNode::checkExistPair(BetaNode* pairs)
{
	for (int i = 0; i < listOfBetaPairs.size(); i++) {
		if (listOfBetaPairs[i] == pairs)
			return 1;
	}

	return 0;
}

int AlphaNode::addBetaPair(BetaNode* pair)
{
	int isExist = checkExistPair(pair);
	if (isExist)
		return 1;
	else {
		listOfBetaPairs.push_back(pair);
		return 1;
	}
	return -1;
}

int AlphaNode::addBetaPairInNode(BetaNode* pair)
{
	int isExist = checkExistPair(pair);
	if (isExist)
		return 1;
	else {
		//listOfBetaPairsInNode.push_back(static_cast<Node*>(pair));
		listOfBetaPairsInNode.push_back(pair);
		return 1;
	}

	return -1;
}

void AlphaNode::testAlphaAndSaveHere(vector<pair<int, int>> test_cases)
{
	testRes = {};
	int limit = atoi(thisVarLimit.c_str());

	int cases = -1;
	// 0 -> equal less
	// 1 -> equal more
	// 2 -> less
	// 3 -> more
	if (thisCondition == "<=")
		cases = 0;
	else if (thisCondition == ">=")
		cases = 1;
	else if (thisCondition == "<")
		cases = 2;
	else if (thisCondition == ">")
		cases = 3;

	for (int i = 0; i < test_cases.size(); i++) {
		if (cases == 0 && test_cases[i].second <= limit) {
			testRes.push_back(test_cases[i]);
		}
		else if (cases == 1 && test_cases[i].second >= limit) {
			testRes.push_back(test_cases[i]);
		}
		else if (cases == 2 && test_cases[i].second < limit) {
			testRes.push_back(test_cases[i]);
		}
		else if (cases == 3 && test_cases[i].second > limit) {
			testRes.push_back(test_cases[i]);
		}
		//In case join-marking is implemented
		/*else {
			testRes.push_back({ -1, 0 });
		}*/
	}
}

bool AlphaNode::testDataType(string condition_test)
{
	if (strcmp(condition_test.c_str(), thisCondition.c_str()) != 0)
		return false;
	else
		return true;
}

int AlphaNode::ResetNode()
{
	testRes = {};
	listOfBetaPairs = {};
	//betaPair = NULL;
	return 1;
}
