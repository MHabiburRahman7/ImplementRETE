#include "NewReteGraph.h"

vector<int>NewReteGraph::alphaListIDDictionary;
vector<int>NewReteGraph::betaListIDDictionary;
vector<int>NewReteGraph::termListIDDictionary;
vector<Node*> NewReteGraph::NodeList;

WMSet NewReteGraph::m_WMSet;

//void NewReteGraph::addAlpha(string condition)
//{
//	Node* tempNode;
//	//string space = " ";
//	if (condition.back() == ' ') {
//		condition.pop_back();
//	}
//
//	//duplicate check
//	for (int i = 0; i < alphaListIDDictionary.size(); i++) {
//		if (NodeList[alphaListIDDictionary[i]]->justCondition == condition)
//			return;
//	}
//
//	//Try to use OOP
//	int masterNodeID = NodeList.size();
//	tempNode = new AlphaNode(masterNodeID, condition);
//	NodeList.push_back(tempNode);
//}
//
//void NewReteGraph::addBeta(string condition)
//{
//	Node* tempNode;
//	//duplicate check
//	for (int i = 0; i < betaListIDDictionary.size(); i++) {
//		if (NodeList[betaListIDDictionary[i]]->justCondition == condition)
//			return;
//	}
//
//	//Try to use OOP
//	int masterNodeID = NodeList.size();
//	tempNode = new BetaNode(masterNodeID, condition);
//	NodeList.push_back(tempNode);
//}
//
//void NewReteGraph::addTerminal(string condition)
//{
//	Node* tempNode;
//
//	for (int i = 0; i < termListIDDictionary.size(); i++) {
//		if (NodeList[termListIDDictionary[i]]->justCondition == condition)
//			return;
//	}
//	//Try OOP approach
//	int masterNodeID = NodeList.size();
//	tempNode = new TerminalNode(masterNodeID, condition);
//	NodeList.push_back(tempNode);
//}

Node* NewReteGraph::addAlphaReturnNode(string condition)
{
	Node* tempNode;
	//string space = " ";
	if (condition.back() == ' ') {
		condition.pop_back();
	}

	//duplicate check
	for (int i = 0; i < alphaListIDDictionary.size(); i++) {
		if (NodeList[alphaListIDDictionary[i]]->justCondition == condition)
			return nullptr;
	}

	//Try to use OOP
	int masterNodeID = NodeList.size();
	tempNode = new AlphaNode(masterNodeID, condition);
	NodeList.push_back(tempNode);
	alphaListIDDictionary.push_back(masterNodeID);

	return tempNode;
}

Node* NewReteGraph::addBetaReturnNode(string condition)
{
	//string space = " ";
	if (condition.back() == ' ') {
		condition.pop_back();
	}

	Node* tempNode;
	//duplicate check
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		if (NodeList[betaListIDDictionary[i]]->justCondition == condition)
			return nullptr;
	}

	//Try to use OOP
	int masterNodeID = NodeList.size();
	tempNode = new BetaNode(masterNodeID, condition);
	NodeList.push_back(tempNode);

	betaListIDDictionary.push_back(masterNodeID);

	return tempNode;
}

Node* NewReteGraph::addTerminalReturnNode(string condition)
{
	//string space = " ";
	if (condition.back() == ' ') {
		condition.pop_back();
	}

	Node* tempNode;

	for (int i = 0; i < termListIDDictionary.size(); i++) {
		if (NodeList[termListIDDictionary[i]]->justCondition == condition)
			return nullptr;
	}
	//Try OOP approach
	int masterNodeID = NodeList.size();
	tempNode = new TerminalNode(masterNodeID, condition);
	NodeList.push_back(tempNode);

	termListIDDictionary.push_back(masterNodeID);

	return tempNode;
}

void NewReteGraph::buildNetNode()
{
	//check available Nodes
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		//if has fully connected, skip
		if (static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getLeftConnNode() != NULL
			&& static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getRightConnNode() != NULL)
			continue;
		
		Node* alpha1 = nullptr, * alpha2 = nullptr;
		Node* beta1 = nullptr, * beta2 = nullptr;
		alpha1 = findAlphaNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getLeftConnName());
		alpha2 = findAlphaNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getRightConnName());

		//Will be depreciated soon
		if (alpha1 == nullptr && alpha2 == nullptr) { // both beta
			beta1 = findBetaNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getLeftConnName());
			beta2 = findBetaNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getRightConnName());
		}
		else if (alpha1 == nullptr || alpha2 == nullptr) { // one of them is beta
			beta1 = findBetaNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getLeftConnName());
			if (beta1 == nullptr)
				beta1 = findBetaNode(static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getRightConnName());
		}

		if (alpha1 != nullptr && alpha2 != nullptr) // alpha 1 and 2 is alpha node
		{
			//OOP Approach
			connectNodes(*alpha1, *alpha2 , *NodeList[betaListIDDictionary[i]]);
		}
		else if (alpha1 == nullptr && alpha2 != nullptr) // alpha 1 is beta
		{
			//OOP Approach
			connectNodes(*beta1, *alpha2, *NodeList[betaListIDDictionary[i]]);
		}
		else if (alpha1 != nullptr && alpha2 == nullptr) // alpha 2 is beta
		{
			//OOP approach
			connectNodes(*alpha1, *beta2, *NodeList[betaListIDDictionary[i]]);
		}
		else if (alpha1 == nullptr && alpha2 == nullptr) {// both beta
			//OOP approach
			connectNodes(*beta1, *beta2, *NodeList[betaListIDDictionary[i]]);
		}
		else
			continue;
	}
}

void NewReteGraph::parseCondition(list<string> conditionList)
{
	//Parsing parsing~
	vector<vector<pair<string, string>>> collectedMade;
	vector<string> newInputForm;

	for (auto v : conditionList) {
		newInputForm.push_back(v);
	}

	//edit & into AND
	string temp;
	for (auto v : newInputForm[0]) {
		if (v == '&') {
			temp += " AND ";
		}
		else {
			temp += v;
		}
	}
	newInputForm[0] = temp;
	
	//Tokenize to determine alpha, beta, or else
	for (int i = 0; i < newInputForm.size();i++) {
		vector<pair<string, string>> made = {};

		made = Utilities::tokenizeMoreDetail(newInputForm[i]);

		collectedMade.push_back(made);
	}

	//Rebuild the tokenized
	for (int i = 0; i < collectedMade[0].size(); i++) {
		if (collectedMade[0][i].first == "Alpha") {
			addAlphaReturnNode(collectedMade[0][i].second);
		}
	}

	string tempProduct = "";
	vector<string> conditionFromZero, latestBetaMade;
	//Condition from zero means set of And, Or, sequentially from the beginning of IF
	//latestBetaMade means, i tried to build temporary beta

	for (int i = 0; i < collectedMade[0].size(); i++) {
		string tempCondition = "";
		tempProduct = "";

		if (collectedMade[0][i].first != "condition") {
			tempCondition += collectedMade[0][i].second + " ";
			tempCondition += "and ";
			tempCondition += collectedMade[1][0].second;

			tempProduct += collectedMade[0][i].second.substr(0, 2);
			tempProduct += collectedMade[1][0].second.substr(0, 2);

			tempCondition = tempCondition + " then " + tempProduct;

			addBetaReturnNode(tempCondition);

			latestBetaMade.push_back(tempProduct);
		}
		else if (collectedMade[0][i].first == "condition") {
			conditionFromZero.push_back(collectedMade[0][i].second);
		}
	}

	//Clear the unfinished beta
	int n = latestBetaMade.size() - 1;

	for (; conditionFromZero.size() > 0;) {
		string tempCond = "";
		tempProduct = "";

		tempCond += latestBetaMade[n] + " " + conditionFromZero[conditionFromZero.size()-1] + " ";
		tempProduct += latestBetaMade[n].substr(0, 2);
		latestBetaMade.pop_back();
		//*latestBeta--;
		n--;
		tempCond += latestBetaMade[n] + " then ";
		tempProduct += latestBetaMade[n].substr(0, 2);
		latestBetaMade.pop_back();
		n--;

		tempCond += tempProduct;
		
		addBetaReturnNode(tempCond);
		
		conditionFromZero.pop_back();
	}

	//connect with terminal ._.
	addTerminalReturnNode(tempProduct + " then " + collectedMade[collectedMade.size()-1][0].second);
}

void NewReteGraph::parseConditionOriginal(list<string> condList)
{
	//Parsing parsing~
	vector<vector<pair<string, string>>> collectedMade;
	vector<string> newInputForm;

	for (auto v : condList) {
		newInputForm.push_back(v);
	}

	//edit & into AND
	string temp;
	for (auto v : newInputForm[0]) {
		if (v == '&') {
			temp += " AND ";
		}
		else {
			temp += v;
		}
	}
	newInputForm[0] = temp;

	//Tokenize to determine alpha, beta, or else
	for (int i = 0; i < newInputForm.size(); i++) {
		vector<pair<string, string>> made = {};

		made = Utilities::tokenizeMoreDetail(newInputForm[i]);

		collectedMade.push_back(made);
	}

	//Rebuild the tokenized
	vector<Node*> tempBuildNode;
	vector<string> andOrCondition;
	for (int i = 0; i < collectedMade[0].size(); i++) {
		Node* tempSingleNode;

		if (collectedMade[0][i].first == "Alpha") {
			//check if similar alpha node is exist


			//else
			tempSingleNode = addAlphaReturnNode(collectedMade[0][i].second);
			tempBuildNode.push_back(tempSingleNode);
		}
		else if (collectedMade[0][i].first == "condition") {
			andOrCondition.push_back(collectedMade[0][i].second);
		}
	}

	//now build the beta
	string tempBetaProduct, tempBetaCondition;
	for (;0 < tempBuildNode.size();) {
		//it is possible to make connection
		if (tempBuildNode.size() > 1) {
			tempBetaProduct = "", tempBetaCondition = "";
			Node* n1, * n2, * n3;
		
			n2 = tempBuildNode[tempBuildNode.size() - 1];
			if (dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])) { //if it is beta
				tempBetaCondition += dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])->getProduct();
				tempBetaProduct += dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])->getProduct().substr(0, 2);
			}
			else { //if it is alpha
				tempBetaCondition += tempBuildNode[tempBuildNode.size() - 1]->justCondition;
				tempBetaProduct += tempBuildNode[tempBuildNode.size() - 1]->justCondition.substr(0, 2);
			}
			tempBuildNode.pop_back();

			tempBetaCondition += " " + andOrCondition[andOrCondition.size() - 1] + " ";
			
			n1 = tempBuildNode[tempBuildNode.size() - 1];
			if (dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])) { //if it is beta
				tempBetaCondition += dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])->getProduct();
				tempBetaProduct += dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])->getProduct().substr(0, 2);
			}
			else { //if it is alpha
				tempBetaCondition += tempBuildNode[tempBuildNode.size() - 1]->justCondition;
				tempBetaProduct += tempBuildNode[tempBuildNode.size() - 1]->justCondition.substr(0, 2);
			}
			tempBuildNode.pop_back();

			n3 = addBetaReturnNode(tempBetaCondition + " then " + tempBetaProduct);

			connectNodes(*n1, *n2, *n3);

			tempBuildNode.push_back(n3);
		}
		else {
			break;
		}
	}

	//From only contain 1 source
	for (int i = 1; i < collectedMade.size(); i++) {
		//i = 1 -> from clause
		//connect with the from clause
		if (collectedMade[i][0].first == "Beta") {
			// in case if it has more than one Then -> last CollectedMade
			for (int j = 0; j < collectedMade[collectedMade.size() - 1].size(); j++) {
				if (dynamic_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])) {
					addBetaReturnNode(static_cast<BetaNode*>(tempBuildNode[tempBuildNode.size() - 1])->getProduct() + " and "
						+ collectedMade[i][0].second + " then " + collectedMade[collectedMade.size() - 1][j].second);
				}
				else if (dynamic_cast<AlphaNode*>(tempBuildNode[tempBuildNode.size() - 1])) {
					addBetaReturnNode(static_cast<AlphaNode*>(tempBuildNode[tempBuildNode.size() - 1])->getAlphaDataType() + " and "
						+ collectedMade[i][0].second + " then " + collectedMade[collectedMade.size() - 1][j].second);
				}
			}
		}
		
		//if i = 1 -> window clause :v --> this is idk
		//if it is window clause
	}
	
}

void NewReteGraph::connectNodes(Node& n1, Node& n2, Node& n3)
{
	if (static_cast<BetaNode*>(&n3)->getLeftConnNode() != NULL ||
		static_cast<BetaNode*>(&n3)->getRightConnNode() != NULL) {
		cout << "ALERT :" << static_cast<BetaNode*>(&n3)->getProduct() << " IS ALREADY OCCUPIED SOURCE" << endl;
		return ;
	}

	//alpha - alpha - beta
	if (dynamic_cast<AlphaNode*>(&n1) && dynamic_cast<AlphaNode*>(&n2)
		&& dynamic_cast<BetaNode*>(&n3)) {

		static_cast<AlphaNode*>(&n1)->addBetaPair(static_cast<BetaNode*>(&n3));
		static_cast<AlphaNode*>(&n2)->addBetaPair(static_cast<BetaNode*>(&n3));

		static_cast<BetaNode*>(&n3)->setLeftConnection(&n1);
		static_cast<BetaNode*>(&n3)->setRightConnection(&n2);
	}
	//beta - alpha - beta
	else if (dynamic_cast<BetaNode*>(&n1) && dynamic_cast<AlphaNode*>(&n2)
		&& dynamic_cast<BetaNode*>(&n3)) {

		static_cast<BetaNode*>(&n1)->addBetaPair(static_cast<BetaNode*>(&n3));
		static_cast<AlphaNode*>(&n2)->addBetaPair(static_cast<BetaNode*>(&n3));

		static_cast<BetaNode*>(&n3)->setLeftConnection(&n1);
		static_cast<BetaNode*>(&n3)->setRightConnection(&n2);
	}
	//beta - beta - beta
	else if (dynamic_cast<BetaNode*>(&n1) && dynamic_cast<BetaNode*>(&n2)
		&& dynamic_cast<BetaNode*>(&n3)) {

		static_cast<BetaNode*>(&n1)->addBetaPair(static_cast<BetaNode*>(&n3));
		static_cast<BetaNode*>(&n2)->addBetaPair(static_cast<BetaNode*>(&n3));

		static_cast<BetaNode*>(&n3)->setLeftConnection(&n1);
		static_cast<BetaNode*>(&n3)->setRightConnection(&n2);
	}
	//terminal - beta - beta --> coming soon ~!!

}

void NewReteGraph::processRete(int timeSlice)
{
	if (m_WMSet.getWMInputQueue()[0]->empty())
		return;

	vector<pair<Node*, int>> visitedMark;
	vector<Node*> pushedBeta;

	bool isDone = false;

	//activate all alpha
	for (int j = 0; j < alphaListIDDictionary.size(); j++) {

		//test on alpha
		static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[j]])->testAlphaAndSaveHere(m_WMSet.getWMInputQueue()[0], timeSlice);

			//activate the beta
			//searching all pair and push it
			for (int k = 0; k < static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[j]])->getAllPairs().size(); k++) {

				//check for duplicate
				bool isADuplicate = false;
				for (int l = 0; l < pushedBeta.size(); l++) {
					if (pushedBeta[l] == static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[j]])->getSinglePair(k)) {
						isADuplicate = true;
						break;
					}
				}
				if (!isADuplicate) {
					pushedBeta.push_back(static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[j]])->getSinglePair(k));
					visitedMark.push_back({ static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[j]])->getSinglePair(k), 0 });
				}
			}

			//break;
	}

	//vector<int> possible_match = {};

	//BFS based on Queue
	while (!pushedBeta.empty()) {
		if (!static_cast<BetaNode*>( static_cast<BetaNode*>(pushedBeta[0])->getLeftConnNode())->isEmptyResult()
			&& !static_cast<BetaNode*>(static_cast<BetaNode*>(pushedBeta[0])->getRightConnNode())->isEmptyResult()) {

			static_cast<BetaNode*>(pushedBeta[0])->processBetaNode(timeSlice);

			//Activate successor node
			for (int i = 0; i < static_cast<BetaNode*>(pushedBeta[0])->getAllPairs().size(); i++) {

				//Check to avoid duplication
				bool isDuplicate = false;
				for (int j = 0; j < pushedBeta.size(); j++) {
					if (static_cast<BetaNode*>(pushedBeta[0])->getSinglePair(i) == pushedBeta[j]) {
						isDuplicate = true;
						break;
					}
				}
				if (!isDuplicate)
					pushedBeta.push_back(static_cast<BetaNode*>(pushedBeta[0])->getSinglePair(i));
			}

			//Mark the current node in visited mark
			for (int i = 0; i < visitedMark.size(); i++) {
				if (visitedMark[i].first == pushedBeta[0]) {
					visitedMark[i].second++;

					//Evaluate visited mark
					if (visitedMark[i].second >= 3)
						isDone = true;
					break;
				}
			}
		}

		pushedBeta.erase(pushedBeta.begin());

		if (isDone)
			break;
	}
	int a = 0;
}

Node* NewReteGraph::findAlphaNode(string dataType)
{
	for (int i = 0; i < alphaListIDDictionary.size(); i++) {
		if(static_cast<AlphaNode*>(NodeList[alphaListIDDictionary[i]])->getAlphaDataType() == dataType)
			return NodeList[alphaListIDDictionary[i]];
	}
	return nullptr;
}

Node* NewReteGraph::findBetaNode(string product)
{
	for (int i = 0; i < betaListIDDictionary.size(); i++) {
		if (static_cast<BetaNode*>(NodeList[betaListIDDictionary[i]])->getProduct() == product)
			return NodeList[betaListIDDictionary[i]];
	}
	return nullptr;
}

void NewReteGraph::createWMSet(vector<string> inputName)
{
	//for (int i = 0; i < inputName.size(); i++) {
	m_WMSet.createInputQueue(inputName[0]);

	addAlphaReturnNode(inputName[0] + " == All");
	//}
}

vector<queue<EventPtr>*> NewReteGraph::getWMInputQueue()
{
	return m_WMSet.getWMInputQueue();
}

void NewReteGraph::printWMSet()
{
	m_WMSet.printInsisde();
}

void NewReteGraph::clearWM()
{
	m_WMSet.clearSet();
}

//Node* NewReteGraph::findAlphaNode(Node* tempNode)
//{
//	return NodeList[alphaListIDDictionary[i]];
//}
