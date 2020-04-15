#pragma once
#include "AlphaNode.h"
#include "BetaNode.h"
#include "TerminalNode.h"
#include "Node.h"

#include "WMSet.h"

#include <list>

using namespace std;

class NewReteGraph
{
public:
	//static void addAlpha(string condition);
	//static void addBeta(string condition);
	//static void addTerminal(string condition);

	static Node* addAlphaReturnNode(string condition);
	static Node* addBetaReturnNode(string condition);
	static Node* addTerminalReturnNode(string condition);

	static void buildNetNode();

	static void parseCondition(list<string> conditionList);
	static void parseConditionOriginal(list<string> condList);

	static void connectNodes(Node& n1, Node& n2, Node& n3);

	//static void process(queue<EventPtr>* input); //idk do i need this?
	//static void processSingle(EventPtr* e);//
	static void processRete(int timeSlice);

	static Node* findAlphaNode(string dataType);
	static Node* findBetaNode(string product);

	//About Working Memory
	static void createWMSet(vector<string> inputName);
	static vector<queue<EventPtr>*> getWMInputQueue();
	static void printWMSet();
	static void clearWM();

private:
	static WMSet m_WMSet;
	static vector<int>alphaListIDDictionary;
	static vector<int>betaListIDDictionary;
	static vector<int>termListIDDictionary;
	static vector<Node*> NodeList;
};

