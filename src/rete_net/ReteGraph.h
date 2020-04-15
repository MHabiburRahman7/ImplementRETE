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
	ReteGraph() {
		//IsCreated = false;
	};

	static Node* tempNode;
	//Maybe i need this
	//static bool IsCreated;

	//Store Nodes
	static vector<int> alphaListIDDictionary;
	static vector<int> betaListIDDictionary;
	static vector<int> termListIDDictionary;

	// Next time, change this into unordered_map for faster development :p
	static vector<Node*> NodeList;

	//FindMatch
	//vector<int> findMatch(WMSet* temp_wm);
	//void testBFS(WMSet* temp_wm);
	//vector<int> findMatchUsingBFS(WMSet* temp_wm);ReteGraph::
	//vector<Node*> findMatchUsingBFSNode(WMSet* temp_wm);

	//Add Alpha or Beta
	static void addFullCondition(list<string> fullCondition);
	int addAlpha(string condition);
	int addBeta(string condition);
	int addTerminal(string terminalName);

	//Building network
	int buildCurrentAlphaBeta();
	void resetAndClearNet();

	int connectTwoInputNodeNode(Node& n1, Node& n2, Node& n3);
	int connectBetaToTerminalNode(Node& n1, Node& n2);

	//find function
	int findAlpha(string dataType);
	int findBeta(string BCode);
	//static int findBetaBasedOnProduct(string product);
	AlphaNode* findAlphaAndReturnNode(string dataType);
	AlphaNode* findAlphaAndReturnNode(AlphaNode* tempNode);
	BetaNode* findBetaBasedOnProductAndReturnNode(string product);
	BetaNode* findBetaBasedOnProductAndReturnNode(BetaNode* tempNode);
	TerminalNode* findTerminalAndReturnNode(TerminalNode* tempNode);
};

