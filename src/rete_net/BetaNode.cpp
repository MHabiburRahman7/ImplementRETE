#include "BetaNode.h"

//BetaNode::BetaNode()
//	: Node(BaseNodeID, tempComingCondition)
//{
//}

BetaNode::BetaNode(int id_given, string condition)
	: Node(id_given, condition)
{
	int itt = 0;

	id = id_given;

	char* str = (char*)malloc(100);
	strcpy(str, condition.c_str());
	// Returns first token  
	char* token = strtok(str, " ");

	while (token != NULL) {
		if (Utilities::ToUpper(token) == "AND"
			|| Utilities::ToUpper(token) == "OR"
			|| Utilities::ToUpper(token) == "THEN")
		{
			itt++;
		}
		//else {
		if (itt == 0) {
			if (leftSourcePair.first == "") {
				//leftSource += token;
				leftSourcePair.first += token;
			}
			else {
				//leftSource += " ";
				//leftSource += token;
				leftSourcePair.first += " ";
				leftSourcePair.first += token;
			}
		}
		else if (itt == 1) {
			thisCondition = token;
			itt++;
		}
		else if (itt == 2) {
			if (rightSourcePair.first == "") {
				//rightSource += token;
				rightSourcePair.first += token;
			}
			else {
				//rightSource += " ";
				//rightSource += token;
				rightSourcePair.first += " ";
				rightSourcePair.first += token;
			}
		}
		else if (itt == 3) {
			thisProduct = token;
		}
		token = strtok(NULL, " ");
		//}
	}
}

string BetaNode::getType()
{
	return "Beta";
}

Node* BetaNode::getLeftConnNode()
{
	return leftSourcePair.second;
}

Node* BetaNode::getRightConnNode()
{
	return rightSourcePair.second;
}

string BetaNode::getLeftConnName()
{
	return leftSourcePair.first;
}

string BetaNode::getRightConnName()
{
	return rightSourcePair.first;
}



Node* BetaNode::getSinglePair(int i)
{
	return listOfBetaPairInNode[i];
}

vector<Node*> BetaNode::getAllPairs()
{
	return listOfBetaPairInNode;
}

int BetaNode::setLeftConnection(Node* node)
{
	if (leftSourcePair.second == NULL) {
		leftSourcePair.second = node;
		return 1;
	}
	else {
		return 0;
	}
	/*if (leftConnectionInNode == NULL){
		leftConnectionInNode = node;
		return 1;
	}
	else 
		return 0;*/
}

int BetaNode::setRightConnection(Node* node)
{
	if (rightSourcePair.second == NULL) {
		rightSourcePair.second = node;
		return 1;
	}
	else {
		return 0;
	}
	//if (rightConnectionInNode == NULL) {
	//	rightConnectionInNode = node;
	//	return 1;
	//}
	//else
	//	return 0;
}

int BetaNode::processBetaNode(int timeSlice)
{
	ClearResult();

	queue<EventPtr> left = *leftSourcePair.second->getEvRes();
	queue<EventPtr> right = *rightSourcePair.second->getEvRes();
	
	//Ordered join method
	//int it1 = 0, it2 = 0, itt = 0;
	if (Utilities::ToUpper(thisCondition) == "AND") {

		//EventPtr ev = left->front();
		if (left.size() == 0 || right.size() == 0)
			return 0;

		//auto leftItt = left->front();
		//auto leftEnd = left->back();
		//auto rightItt = right->front();
		//auto rightEnd = right->back();

		//it1 = leftItt->getId();
		//it2 = rightItt->getId();

		while (1) {
			if (left.size() == 0 && right.size() == 0)
				break;

			EventPtr frontLeftEvent = left.front();
			EventPtr frontRightEvent = right.front();
			//if ((static_cast<EventPtr*>(left).front())->getId() == ((EventPtr)right.front())->getId()) {
			if (frontLeftEvent->getId() == frontRightEvent->getId()) {
				//int c;
				EventResult->push(frontLeftEvent);
				if (left.size() > 0)
					left.pop();
				else
					right.pop();

				if (right.size() > 0)
					right.pop();
				else
					left.pop();
			}
			//else if (((EventPtr)left.front())->getId() > ((EventPtr)right.front())->getId()) {
			else if(frontLeftEvent->getId() > frontRightEvent->getId()){
				if (right.size() > 0)
					right.pop();
				else
					left.pop();
			}
			//else if (((EventPtr)left.front())->getId() < ((EventPtr)right.front())->getId()) {
			else if(frontLeftEvent->getId() < frontRightEvent->getId()){
				if (left.size() > 0)
					left.pop();
				else
					right.pop();
			}
			//itt++;

			if (left.size() == 1 && right.size() == 1) {
				//if (((EventPtr)left.front())->getId() == ((EventPtr)right.front())->getId())
				if(frontLeftEvent->getId() == frontRightEvent->getId())
					EventResult->push(frontLeftEvent);
				break;
			}

			//(EventPtr)left->front()->getId()
			/*if (WME[it1].first == WME1[it2].first) {
				testRes.push_back({ WME[it1].first, thisProduct });
				if (it1 + 1 < WME.size())
					it1++;
				else
					it2++;
				if (it2 + 1 < WME1.size())
					it2++;
				else it1++;
			}
			else if (WME[it1].first > WME1[it2].first) {
				if (it2 + 1 < WME1.size())
					it2++;
				else
					it1++;
			}
			else if (WME[it1].first < WME1[it2].first) {
				if (it1 + 1 < WME.size())
					it1++;
				else
					it2++;
			}
			itt++;

			if (WME[it1] == WME[WME.size() - 1] && WME1[it2] == WME1[WME1.size() - 1]) {
				if (WME[it1].first == WME1[it2].first)
					testRes.push_back({ WME[it1].first, thisProduct });
				break;
			}*/
		}
	}
	
	return 0;
}

bool BetaNode::isEmptyResult()
{
	if (EventResult == NULL || EventResult->size() == 0)
		return true;
	return false;
}

queue<EventPtr>* BetaNode::getEvRes()
{
	return EventResult;
}

string BetaNode::getProduct()
{
	return thisProduct;
}

int BetaNode::getID()
{
	return id;
}

//int BetaNode::testBetaNode(vector<pair<int, int>> WME, vector<pair<int, int>> WME1)
//{
//	if (!leftSourceBool || !rightSourceBool)
//		return -1;
//	//previous codes
//	/*
//	if (leftSourceBool && rightSourceBool) {
//		for (int i = 0; i < WME.size(); i++) {
//			for (int j = i; j < WME1.size(); j++) {
//				if (WME[i].first == WME1[j].first)
//					testRes.push_back({ WME[i].first, thisProduct });
//			}
//		}
//	}
//	*/
//	//join marking method
//	/*
//	if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "AND") {
//		for (int i = 0; i < WME.size(); i++) {
//			//AND condition
//			if (WME[i].first == WME1[i].first)
//				testRes.push_back({ WME[i].first, thisProduct });
//			else
//				testRes.push_back({ -1, "0" });
//		}
//	}else if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "OR") {
//		for (int i = 0; i < WME.size(); i++) {
//			if (WME[i].first != -1 || WME1[i].first != -1)
//				testRes.push_back({ WME[i].first, thisProduct });
//			else
//				testRes.push_back({ -1,"0" });
//		}
//	}*/
//
//	//Ordered join method
//	int it1 = 0, it2 = 0, itt = 0;
//	if (Utilities::ToUpper(thisCondition) == "AND") {
//
//		if (WME.size() == 0 || WME1.size() == 0)
//			return 0;
//
//		while (1) {
//			if (WME[it1].first == WME1[it2].first) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				if (it1 + 1 < WME.size())
//					it1++;
//				else
//					it2++;
//				if (it2 + 1 < WME1.size())
//					it2++;
//				else it1++;
//			}
//			else if (WME[it1].first > WME1[it2].first) {
//				if (it2 + 1 < WME1.size())
//					it2++;
//				else
//					it1++;
//			}
//			else if (WME[it1].first < WME1[it2].first) {
//				if (it1 + 1 < WME.size())
//					it1++;
//				else
//					it2++;
//			}
//			itt++;
//
//			if (WME[it1] == WME[WME.size() - 1] && WME1[it2] == WME1[WME1.size() - 1]) {
//				if (WME[it1].first == WME1[it2].first)
//					testRes.push_back({ WME[it1].first, thisProduct });
//				break;
//			}
//		}
//	}
//	else if (Utilities::ToUpper(thisCondition) == "OR") {
//
//		if (WME.size() == 0) {
//			for (int i = 0; i < WME1.size(); i++)
//				testRes.push_back({ WME1[i].first, thisProduct });
//
//			return 0;
//		}
//		else if (WME1.size() == 0) {
//			for (int i = 0; i < WME.size(); i++)
//				testRes.push_back({ WME[i].first, thisProduct });
//
//			return 0;
//		}
//
//		while (1) {
//			if (it1 == WME.size() && it2 == WME1.size())
//				break;
//
//			if (it1 == WME.size()) {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				if (it2 < WME1.size())
//					it2++;
//				continue;
//			}
//			if (it2 == WME1.size()) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				if (it1 < WME.size())
//					it1++;
//				continue;
//			}
//
//
//			if (WME[it1].first == WME1[it2].first) {
//
//				testRes.push_back({ WME[it1].first, thisProduct });
//
//				if (it1 < WME.size())
//					it1++;
//				if (it2 < WME1.size())
//					it2++;
//
//				continue;
//			}
//
//			if (WME[it1].first > WME1[it2].first&& it2 < WME1.size()) {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				it2++;
//				continue;
//			}
//			else {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				it1++;
//				continue;
//			}
//
//			if (WME[it1].first < WME1[it2].first && it1 < WME.size()) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				it1++;
//				continue;
//			}
//			else {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				it2++;
//				continue;
//			}
//
//		}
//	}
//
//	return 0;
//}

//int BetaNode::testBetaNode(vector<pair<int, string>> WME, vector<pair<int, int>> WME1)
//{
//	if (!leftSourceBool || !rightSourceBool)
//		return -1;
//
//	//previous code
//	/*
//	if (leftSourceBool && rightSourceBool) {
//		for (int i = 0; i < WME.size(); i++) {
//			for (int j = i; j < WME1.size(); j++) {
//				if (WME[i].first == WME1[j].first)
//					testRes.push_back({ WME[i].first, thisProduct });
//			}
//		}
//	}*/
//
//	//join marking method
//	/*
//	if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "AND") {
//		for (int i = 0; i < WME.size(); i++) {
//			//And condition
//			if (WME[i].first == WME1[i].first)
//				testRes.push_back({ WME[i].first, thisProduct });
//			else
//				testRes.push_back({ -1, "0" });
//		}
//	}
//	else if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "OR") {
//		for (int i = 0; i < WME.size(); i++) {
//			if (WME[i].first != -1 || WME1[i].first != -1)
//				testRes.push_back({ WME[i].first, thisProduct });
//			else
//				testRes.push_back({ -1,"0" });
//		}
//	}*/
//
//	//Ordered join method
//	int it1 = 0, it2 = 0, itt = 0;
//	if (Utilities::ToUpper(thisCondition) == "AND") {
//
//		if (WME.size() == 0 || WME1.size() == 0)
//			return 0;
//
//		while (1) {
//			if (WME[it1].first == WME1[it2].first) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				if (it1 + 1 < WME.size())
//					it1++;
//				else
//					it2++;
//				if (it2 + 1 < WME1.size())
//					it2++;
//				else it1++;
//			}
//			else if (WME[it1].first > WME1[it2].first) {
//				if (it2 + 1 < WME1.size())
//					it2++;
//				else
//					it1++;
//			}
//			else if (WME[it1].first < WME1[it2].first) {
//				if (it1 + 1 < WME.size())
//					it1++;
//				else
//					it2++;
//			}
//			itt++;
//
//			if (WME[it1] == WME[WME.size() - 1] && WME1[it2] == WME1[WME1.size() - 1]) {
//				if (WME[it1].first == WME1[it2].first)
//					testRes.push_back({ WME[it1].first, thisProduct });
//				break;
//			}
//		}
//	}
//	else if (Utilities::ToUpper(thisCondition) == "OR") {
//
//		if (WME.size() == 0) {
//			for (int i = 0; i < WME1.size(); i++)
//				testRes.push_back({ WME1[i].first, thisProduct });
//
//			return 0;
//		}
//		else if (WME1.size() == 0) {
//			for (int i = 0; i < WME.size(); i++)
//				testRes.push_back({ WME[i].first, thisProduct });
//
//			return 0;
//		}
//
//		while (1) {
//			if (it1 == WME.size() && it2 == WME1.size())
//				break;
//
//			if (it1 == WME.size()) {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				if (it2 < WME1.size())
//					it2++;
//				continue;
//			}
//			if (it2 == WME1.size()) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				if (it1 < WME.size())
//					it1++;
//				continue;
//			}
//
//
//			if (WME[it1].first == WME1[it2].first) {
//
//				testRes.push_back({ WME[it1].first, thisProduct });
//
//				if (it1 < WME.size())
//					it1++;
//				if (it2 < WME1.size())
//					it2++;
//
//				continue;
//			}
//
//			if (WME[it1].first > WME1[it2].first&& it2 < WME1.size()) {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				it2++;
//				continue;
//			}
//			else {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				it1++;
//				continue;
//			}
//
//			if (WME[it1].first < WME1[it2].first && it1 < WME.size()) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				it1++;
//				continue;
//			}
//			else {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				it2++;
//				continue;
//			}
//
//		}
//	}
//
//	return 0;
//}

//int BetaNode::testBetaNode(vector<pair<int, string>> WME, vector<pair<int, string>> WME1)
//{
//	if (!leftSourceBool || !rightSourceBool)
//		return -1;
//	//Previous code
//	/*
//	if (leftSourceBool && rightSourceBool) {
//		for (int i = 0; i < WME.size(); i++) {
//			for (int j = i; j < WME1.size(); j++) {
//				if (WME[i].first == WME1[j].first)
//					testRes.push_back({ WME[i].first, thisProduct });
//			}
//		}
//	}*/
//	//join marking method
//	/*
//	if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "AND") {
//		for (int i = 0; i < WME.size(); i++) {
//			//And Condition
//			if (WME[i].first == WME1[i].first)
//				testRes.push_back({ WME[i].first, thisProduct });
//			else
//				testRes.push_back({ -1,"0" });
//		}
//	}
//	else if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "OR") {
//		for (int i = 0; i < WME.size(); i++) {
//			if (WME[i].first != -1 || WME1[i].first != -1)
//				testRes.push_back({ WME[i].first, thisProduct });
//			else
//				testRes.push_back({ -1,"0" });
//		}
//	}*/
//
//	//Ordered join method
//	int it1 = 0, it2 = 0, itt = 0;
//	if (Utilities::ToUpper(thisCondition) == "AND") {
//
//		if (WME.size() == 0 || WME1.size() == 0)
//			return 0;
//
//		while (1) {
//			if (WME[it1].first == WME1[it2].first) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				if (it1 + 1 < WME.size())
//					it1++;
//				else
//					it2++;
//				if (it2 + 1 < WME1.size())
//					it2++;
//				else it1++;
//			}
//			else if (WME[it1].first > WME1[it2].first) {
//				if (it2 + 1 < WME1.size())
//					it2++;
//				else
//					it1++;
//			}
//			else if (WME[it1].first < WME1[it2].first) {
//				if (it1 + 1 < WME.size())
//					it1++;
//				else
//					it2++;
//			}
//			itt++;
//
//			if (WME[it1] == WME[WME.size() - 1] && WME1[it2] == WME1[WME1.size() - 1]) {
//				if (WME[it1].first == WME1[it2].first)
//					testRes.push_back({ WME[it1].first, thisProduct });
//				break;
//			}
//		}
//	}
//	else if (Utilities::ToUpper(thisCondition) == "OR") {
//
//		if (WME.size() == 0) {
//			for (int i = 0; i < WME1.size(); i++)
//				testRes.push_back({ WME1[i].first, thisProduct });
//
//			return 0;
//		}
//		else if (WME1.size() == 0) {
//			for (int i = 0; i < WME.size(); i++)
//				testRes.push_back({ WME[i].first, thisProduct });
//
//			return 0;
//		}
//
//		while (1) {
//			if (it1 == WME.size() && it2 == WME1.size())
//				break;
//
//			if (it1 == WME.size()) {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				if (it2 < WME1.size())
//					it2++;
//				continue;
//			}
//			if (it2 == WME1.size()) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				if (it1 < WME.size())
//					it1++;
//				continue;
//			}
//
//
//			if (WME[it1].first == WME1[it2].first) {
//
//				testRes.push_back({ WME[it1].first, thisProduct });
//
//				if (it1 < WME.size())
//					it1++;
//				if (it2 < WME1.size())
//					it2++;
//
//				continue;
//			}
//
//			if (WME[it1].first > WME1[it2].first&& it2 < WME1.size()) {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				it2++;
//				continue;
//			}
//			else {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				it1++;
//				continue;
//			}
//
//			if (WME[it1].first < WME1[it2].first && it1 < WME.size()) {
//				testRes.push_back({ WME[it1].first, thisProduct });
//				it1++;
//				continue;
//			}
//			else {
//				testRes.push_back({ WME1[it2].first, thisProduct });
//				it2++;
//				continue;
//			}
//
//		}
//	}
//
//	return 0;
//}

int BetaNode::addBetaPair(Node* pair)
{
	int isExist = checkBeta(pair);
	if (isExist == 1)
		return 1;
	else {
		listOfBetaPairInNode.push_back(pair);
		return 1;
	}

	return -1;
}

int BetaNode::checkBeta(Node* pair)
{
	for (int i = 0; i < listOfBetaPairInNode.size(); i++) {
		if (listOfBetaPairInNode[i] == pair)
			return 1;
	}
	return 0;
}

int BetaNode::ClearConnection()
{
	//betaPair = NULL;
	//leftSourceBool = false;
	//rightSourceBool = false;
	termPair.second = NULL;
	termPair.first = "";
	return 1;
}

int BetaNode::ResetNode()
{
	ClearConnection();
	//testRes = {};
	//EventResult;
	listOfBetaPairInNode = {};

	ClearResult();
	return 0;
}

int BetaNode::ClearResult()
{
	while (!EventResult->empty()) {
		EventResult->pop();
	}
	return 1;
}
