#pragma once

#include "AlphaNode.h"
#include "BetaNode.h"
#include "TerminalNode.h"

#include "../common/Event.h"

//#include "WMSet.h"

#include "Node.h"

using namespace std;

class ReteGraph
{
	ReteGraph() {};

	Node* temp;

	//Store Nodes
	vector<int>alphaListIDDictionary;
	vector<int>betaListIDDictionary;
	vector<int>termListIDDictionary;

	vector<Node*> NodeList;

	//FindMatch
	//vector<int> findMatch(WMSet* temp_wm);
	//void testBFS(WMSet* temp_wm);
	//vector<int> findMatchUsingBFS(WMSet* temp_wm);
	//vector<Node*> findMatchUsingBFSNode(WMSet* temp_wm);

	//Add Alpha or Beta
	int addAlpha(string condition);
	int addBeta(string condition);
	int addTerminal(string terminalName);

	AlphaNode addAlphaAndReturn(string condition);
	BetaNode addBetaAndReturn(string condition);

	//Building network
	int buildCurrentAlphaBeta();
	int buildCurrentNetNodes();

	//Difference is only on the parameter used
	int connectTwoInputNode(AlphaNode& a1, AlphaNode& a2, BetaNode& b1);
	int connectTwoInputNode(BetaNode& b1, AlphaNode& a2, BetaNode& b2);
	int connectTwoInputNode(BetaNode& b1, BetaNode& b2, BetaNode& b3);
	int connectBetaToTerminal(BetaNode& b1, TerminalNode& t1);

	int connectTwoInputNodeNode(Node&, Node&, Node&);
	int connectBetaToTerminalNode(Node& n1, Node& n2);

	//find function
	int findAlpha(string dataType);
	int findBeta(string BCode);
	int findBetaBasedOnProduct(string product);
	AlphaNode* findAlphaAndReturnNode(string dataType);
	AlphaNode* findAlphaAndReturnNode(AlphaNode* tempNode);
	BetaNode* findBetaBasedOnProductAndReturnNode(string product);
	BetaNode* findBetaBasedOnProductAndReturnNode(BetaNode* tempNode);
	TerminalNode* findTerminalAndReturnNode(TerminalNode* tempNode);
};

