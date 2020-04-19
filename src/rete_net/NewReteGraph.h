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

	static Node* addAlphaReturnNode(string condition, string wmSource);
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
	static Node* findNode(string expression, int = -1);

	//About Working Memory
	static void createWMSet(vector<string> inputName);
	static void createWMSet();

	static vector<queue<EventPtr>*> getWMInputQueue();
	static queue<EventPtr>* getSingleInputQueue(int i);
	static string getSingleInputQueueName(int i);
	static queue<EventPtr>* getSingleInputQueue(string inputName);
	static void printWMSet();
	static void clearWM();

	static void regisEcOutput(list<string> input);
	static void regisCqOutput(list<string> input);
	static void regisCEPInput(list<string> input);

private:
	static vector<string> cqOutputList, cepFromList, ecOutputList;
	static WMSet m_WMSet;
	static vector<int>alphaListIDDictionary;
	static vector<int>betaListIDDictionary;
	static vector<int>termListIDDictionary;
	static vector<Node*> NodeList;
};

