#pragma once

#include "Node.h"

class TerminalNode : public Node
{
public:
	int thisId;
	int getID();
	string getType();

	string prevBetaProduct;

	//BetaNode* connectedBetaNodes;
	Node* prevBetaConnection;

	int BaseNodeID;
	string tempComingCondition;

	TerminalNode(int id, string termName);

	string term;
	vector<pair<int, int>> matchMade;
};

