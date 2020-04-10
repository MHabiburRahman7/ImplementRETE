#include "ReteGraph.h"

Node* ReteGraph::tempNode;

vector<int> ReteGraph::alphaListIDDictionary;
vector<int> ReteGraph::betaListIDDictionary;
vector<int> ReteGraph::termListIDDictionary;

vector<Node*> ReteGraph::NodeList;


int ReteGraph::addAlpha(string condition)
{
	if (condition.back() == ' ') {
		condition.pop_back();
	}
	
	//duplicate check
	for (int i = 0; i < ReteGraph::alphaListIDDictionary.size(); i++) {
		if (ReteGraph::NodeList[ReteGraph::alphaListIDDictionary[i]]->justCondition == condition)
			return 1;
	}

	//Try to use OOP
	int masterNodeID = NodeList.size();
	tempNode = new AlphaNode(masterNodeID, condition);
	NodeList.push_back(tempNode);

	alphaListIDDictionary.push_back(masterNodeID);

	//AlphaNode* justForTest = static_cast<AlphaNode*>(tempNode);
	//BetaNode* justForTest = dynamic_cast<BetaNode*>(tempNode);

	return 0;
}

int ReteGraph::addBeta(string condition)
{
	//duplicate check
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		if (NodeList[betaListIDDictionary[i]]->justCondition == condition)
			return 1;
	}

	////Try to use OOP
	int masterNodeID = NodeList.size();
	tempNode = new BetaNode(masterNodeID, condition);
	NodeList.push_back(tempNode);

	betaListIDDictionary.push_back(masterNodeID);

	return 0;
}

int ReteGraph::addTerminal(string terminalName)
{
	for (int i = 0; i < termListIDDictionary.size(); i++) {
		if (NodeList[termListIDDictionary[i]]->justCondition == terminalName)
			return 1;
	}
	//Try OOP approach
	int masterNodeID = NodeList.size();
	tempNode = new TerminalNode(masterNodeID, terminalName);
	NodeList.push_back(tempNode);

	termListIDDictionary.push_back(masterNodeID);

	return 0;
}

int ReteGraph::buildCurrentAlphaBeta()
{
	//If OOP, this thing should be fixed too

	//alpha to beta & beta to beta
	//for (int i = 0; i < betaList.size(); i++) {
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		Node* alpha1 = nullptr, * alpha2 = nullptr;
		Node* beta1 = nullptr, * beta2 = nullptr;
		alpha1 = findAlphaAndReturnNode(static_cast<AlphaNode*>(
			static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->leftConnectionInNode)
		);
		alpha2 = findAlphaAndReturnNode(static_cast<AlphaNode*>(
			static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->rightConnectionInNode)
		);

		//Will be depreciated soon
		if (alpha1 == nullptr && alpha2 == nullptr) { // both beta
			
			beta1 = static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->leftConnectionInNode;
			beta2 = static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->rightConnectionInNode;
													  
			//beta1 = findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->leftConnectionInNode);
			//beta2 = findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->rightSource);
		}
		else if (alpha1 == nullptr || alpha2 == nullptr) { // one of them is beta
			
			beta1 = static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->leftConnectionInNode;

			//beta1 = findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->leftSource);
			if (beta1 == nullptr)
				beta1 = static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->rightConnectionInNode;
				//beta1 = findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->rightSource);
		}

		if (alpha1 != nullptr && alpha2 != nullptr) // alpha 1 and 2 is alpha node
		{
			//OOP Approach
			connectTwoInputNodeNode(*findAlphaAndReturnNode(static_cast<AlphaNode*>(alpha1)),
				*findAlphaAndReturnNode(static_cast<AlphaNode*>(alpha2)), *NodeList[betaListIDDictionary[i]]);
		}
		else if (alpha1 == nullptr && alpha2 != nullptr) // alpha 1 is beta
		{
			//OOP Approach
			connectTwoInputNodeNode(*findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(beta1)),
				*findAlphaAndReturnNode(static_cast<AlphaNode*>(alpha2)), *NodeList[betaListIDDictionary[i]]);
		}
		else if (alpha1 != nullptr && alpha2 == nullptr) // alpha 2 is beta
		{
			//OOP approach
			connectTwoInputNodeNode(*findAlphaAndReturnNode(static_cast<AlphaNode*>(alpha1)),
				*findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(beta2)), *NodeList[betaListIDDictionary[i]]);
		}
		else if (alpha1 == nullptr && alpha2 == nullptr) {// both beta
			//OOP approach
			connectTwoInputNodeNode(*findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(beta1)),
				*findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(beta2)), *NodeList[betaListIDDictionary[i]]);
		}
		else
			continue;
	}

	//beta to terminal
	for (int i = 0; i < termListIDDictionary.size(); i++) {
		Node* betaId = nullptr;

		betaId = findBetaBasedOnProductAndReturnNode(static_cast<TerminalNode*>(NodeList[termListIDDictionary[i]])->prevBetaProduct);
		if (betaId != nullptr) {
			//connectBetaToTerminal(betaList[betaId], termList[i]);
			connectBetaToTerminalNode(*findBetaBasedOnProductAndReturnNode(static_cast<BetaNode*>(betaId)),
				*NodeList[termListIDDictionary[i]]);
		}
	}

	return 0;
}

void ReteGraph::resetAndClearNet()
{
	for (int i = 0; i < alphaListIDDictionary.size(); i++) {
		static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[i]])->ResetNode();
	}
	//beta nodes
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->ResetNode();
	}
}

int ReteGraph::connectTwoInputNodeNode(Node& n1, Node& n2, Node& n3)
{
	if (static_cast<BetaNode*>(&n3)->leftSourceType != "" ||
		static_cast<BetaNode*>(&n3)->rightSourceType != "") {
		cout << "ALERT :" << static_cast<BetaNode*>(&n3)->thisProduct << " IS ALREADY OCCUPIED SOURCE" << endl;
		return -1;
	}
	//alpha - alpha - beta
	if (dynamic_cast<AlphaNode*>(&n1) && dynamic_cast<AlphaNode*>(&n2)
		&& dynamic_cast<BetaNode*>(&n3)) {

		static_cast<AlphaNode*>(&n1)->addBetaPairInNode(static_cast<BetaNode*>(&n3));
		static_cast<AlphaNode*>(&n2)->addBetaPairInNode(static_cast<BetaNode*>(&n3));

		static_cast<BetaNode*>(&n3)->leftConnectionInNode = &n1;
		static_cast<BetaNode*>(&n3)->rightConnectionInNode = &n2;
		static_cast<BetaNode*>(&n3)->leftSourceType = "Alpha";
		static_cast<BetaNode*>(&n3)->rightSourceType = "Alpha";
	}
	//beta - alpha - beta
	else if (dynamic_cast<BetaNode*>(&n1) && dynamic_cast<AlphaNode*>(&n2)
		&& dynamic_cast<BetaNode*>(&n3)) {

		static_cast<BetaNode*>(&n1)->addBetaPairInNode(static_cast<BetaNode*>(&n3));
		static_cast<AlphaNode*>(&n2)->addBetaPairInNode(static_cast<BetaNode*>(&n3));

		static_cast<BetaNode*>(&n3)->leftConnectionInNode = &n1;
		static_cast<BetaNode*>(&n3)->rightConnectionInNode = &n2;
		static_cast<BetaNode*>(&n3)->leftSourceType = "Beta";
		static_cast<BetaNode*>(&n3)->rightSourceType = "Alpha";
	}
	//beta - beta - beta
	else if (dynamic_cast<BetaNode*>(&n1) && dynamic_cast<BetaNode*>(&n2)
		&& dynamic_cast<BetaNode*>(&n3)) {

		static_cast<BetaNode*>(&n1)->addBetaPairInNode(static_cast<BetaNode*>(&n3));
		static_cast<BetaNode*>(&n2)->addBetaPairInNode(static_cast<BetaNode*>(&n3));

		static_cast<BetaNode*>(&n3)->leftConnectionInNode = &n1;
		static_cast<BetaNode*>(&n3)->rightConnectionInNode = &n2;
		static_cast<BetaNode*>(&n3)->leftSourceType = "Beta";
		static_cast<BetaNode*>(&n3)->rightSourceType = "Beta";
	}

	return 0;
}

int ReteGraph::connectBetaToTerminalNode(Node& n1, Node& n2)
{
	static_cast<BetaNode*>(&n1)->terminalConnectionInNode = &n2;
	//static_cast<BetaNode*>(&n1)->addBetaPairInNode(n2);

	static_cast<TerminalNode*>(&n2)->prevBetaConnection = &n1;

	return 1;
}

int ReteGraph::findAlpha(string dataType)
{
	for (int i = 0; i < alphaListIDDictionary.size(); i++) {
		if (strcmp(static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[i]])->thisDataType.c_str(),
			dataType.c_str()) == 0)
			return i;
	}
	return -1;
}

int ReteGraph::findBeta(string BCode)
{
	int num = -1;

	int len = BCode.length();
	num = atoi(BCode.substr(1, len).c_str());

	return num;
}

AlphaNode* ReteGraph::findAlphaAndReturnNode(AlphaNode* tempNode)
{
	//return dynamic_cast<AlphaNode*>(NodeList[static_cast<Node*>(tempNode)->SuperNodeID]);
	return nullptr;
}

BetaNode* ReteGraph::findBetaBasedOnProductAndReturnNode(string product)
{
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		if (NodeList[betaListIDDictionary[i]]->justCondition ==
			product)
			return static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]]);
	}
	return nullptr;
}

BetaNode* ReteGraph::findBetaBasedOnProductAndReturnNode(BetaNode* tempNode)
{
	return dynamic_cast<BetaNode*>(NodeList[static_cast<Node*>(tempNode)->SuperNodeID]);
	//return nullptr;
}

TerminalNode* ReteGraph::findTerminalAndReturnNode(TerminalNode* tempNode)
{
	return dynamic_cast<TerminalNode*>(NodeList[static_cast<Node*>(tempNode)->SuperNodeID]);
	//return nullptr;
}



