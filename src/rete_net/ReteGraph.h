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
public:
	ReteGraph() {};

	static Node* tempNode;

	//Store Nodes
	static vector<int> alphaListIDDictionary;
	static vector<int> betaListIDDictionary;
	static vector<int> termListIDDictionary;

	static vector<Node*> NodeList;

	//FindMatch
	//vector<int> findMatch(WMSet* temp_wm);
	//void testBFS(WMSet* temp_wm);
	//vector<int> findMatchUsingBFS(WMSet* temp_wm);ReteGraph::
	//vector<Node*> findMatchUsingBFSNode(WMSet* temp_wm);

	//Add Alpha or Beta
	static int addAlpha(string condition);
	static int addBeta(string condition);
	static int addTerminal(string terminalName);

	/*
	AlphaNode addAlphaAndReturn(string condition);
	BetaNode addBetaAndReturn(string condition);
	*/

	//Building network
	static int buildCurrentAlphaBeta();
	static void resetAndClearNet();

	//Difference is only on the parameter used
	/*static int connectTwoInputNode(AlphaNode& a1, AlphaNode& a2, BetaNode& b1);
	static int connectTwoInputNode(BetaNode& b1, AlphaNode& a2, BetaNode& b2);
	static int connectTwoInputNode(BetaNode& b1, BetaNode& b2, BetaNode& b3);
	static int connectBetaToTerminal(BetaNode& b1, TerminalNode& t1);
	*/

	static int connectTwoInputNodeNode(Node& n1, Node& n2, Node& n3);
	static int connectBetaToTerminalNode(Node& n1, Node& n2);

	//find function
	static int findAlpha(string dataType);
	static int findBeta(string BCode);
	//static int findBetaBasedOnProduct(string product);
	//static AlphaNode* findAlphaAndReturnNode(string dataType);
	static AlphaNode* findAlphaAndReturnNode(AlphaNode* tempNode);
	static BetaNode* findBetaBasedOnProductAndReturnNode(string product);
	static BetaNode* findBetaBasedOnProductAndReturnNode(BetaNode* tempNode);
	static TerminalNode* findTerminalAndReturnNode(TerminalNode* tempNode);
};

