#pragma once

#include "Node.h"

class TerminalNode : public Node
{
public:
	int getID();
	string getType();
	bool isEmptyResult();

	string prevBetaProduct;

	//BetaNode* connectedBetaNodes;
	Node* prevBetaConnection;

	int BaseNodeID;
	//string tempComingCondition;

	TerminalNode(int id, string termName);

	string term;
	vector<pair<int, int>> matchMade;

	void addPair(Node* pair);
	int checkPair(Node* pair);

private:
	int thisId;
	vector<Node*> ListOfNextPair;
};

