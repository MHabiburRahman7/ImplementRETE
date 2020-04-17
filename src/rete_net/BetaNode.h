#pragma once
#include "Node.h"
#include "TerminalNode.h"

#include "Utilities.h"

#include <string>
#include <queue>
#include "../execution/EventProcess.h"

class BetaNode : public Node
{
public:
	//vector<pair<int, string>> testRes;

	//BetaNode();
	BetaNode(int id, string condition);
	
	//int BaseNodeID; // unused
	//string tempComingCondition; // unused

	//Connected to beta and terminal what
	//BetaNode* betaPair;
	//vector<Node*> listOfBetaPair;

	//bool leftSourceBool = false, rightSourceBool = false;
	
	//int testToken();
	//If both are alpha nodes
	//int testBetaNode(vector<pair<int, int>> WME, vector<pair<int, int>> WME1);
	//If one of them is beta
	//int testBetaNode(vector<pair<int, string>> WME, vector<pair<int, int>> WME1);
	//if both are beta nodes
	//int testBetaNode(vector<pair<int, string>> WME, vector<pair<int, string>> WME1);
	//Break into piece
	//int testAndCondition()??

	//connecting beta & terminal
	int addBetaPair(Node* pair);
	int checkBeta(Node* pair);

	//Init function
	int ClearConnection();
	int ResetNode();
	int ClearResult();

	//getSet Function
	int getID();
	string getProduct();
	string getType();
	Node* getLeftConnNode();
	Node* getRightConnNode();
	string getLeftConnName();
	string getRightConnName();
	Node* getSinglePair(int i);
	vector<Node*> getAllPairs();

	int setLeftConnection(Node* node);
	int setRightConnection(Node* node);

	int processBetaNode(int timeSlice);

	bool isEmptyResult();

	queue<EventPtr>* getEvRes();
	
private:
	int id;
	string thisCondition; //AND OR
	//string leftSource;
	//string rightSource;
	string thisProduct; //Then expression or RHS

	string leftSourceType, rightSourceType;

	pair<string, Node*> leftSourcePair, rightSourcePair, termPair;

	queue<EventPtr>* EventResult = new queue<EventPtr>();
	TerminalNode* terminalPair;

	//Connected Pairs (I am not sure with this)
	vector<Node*> listOfBetaPairInNode;
};

