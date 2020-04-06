#include "BetaNode.h"

BetaNode::BetaNode()
	: Node(BaseNodeID, tempComingCondition)
{
}

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
			if (leftSource == "")
				leftSource += token;
			else {
				leftSource += " ";
				leftSource += token;
			}
		}
		else if (itt == 1) {
			thisCondition = token;
			itt++;
		}
		else if (itt == 2) {
			if (rightSource == "")
				rightSource += token;
			else {
				rightSource += " ";
				rightSource += token;
			}
		}
		else if (itt == 3) {
			thisProduct = token;
		}
		token = strtok(NULL, " ");
		//}
	}

	//leftSource = token;
	//while (token != NULL)
	//{
	//	//printf("%s\n", token);
	//	token = strtok(NULL, " ");
	//	if (itt == 0)
	//		thisCondition = token;
	//	else if (itt == 1)
	//		rightSource = token;
	//	else if (itt == 3)
	//		thisProduct = token;
	//	itt++;
	//}
}

string BetaNode::getType()
{
	return "Beta";
}

int BetaNode::getID()
{
	return id;
}

int BetaNode::testBetaNode(vector<pair<int, int>> WME, vector<pair<int, int>> WME1)
{
	if (!leftSourceBool || !rightSourceBool)
		return -1;
	//previous codes
	/*
	if (leftSourceBool && rightSourceBool) {
		for (int i = 0; i < WME.size(); i++) {
			for (int j = i; j < WME1.size(); j++) {
				if (WME[i].first == WME1[j].first)
					testRes.push_back({ WME[i].first, thisProduct });
			}
		}
	}
	*/
	//join marking method
	/*
	if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "AND") {
		for (int i = 0; i < WME.size(); i++) {
			//AND condition
			if (WME[i].first == WME1[i].first)
				testRes.push_back({ WME[i].first, thisProduct });
			else
				testRes.push_back({ -1, "0" });
		}
	}else if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "OR") {
		for (int i = 0; i < WME.size(); i++) {
			if (WME[i].first != -1 || WME1[i].first != -1)
				testRes.push_back({ WME[i].first, thisProduct });
			else
				testRes.push_back({ -1,"0" });
		}
	}*/

	//Ordered join method
	int it1 = 0, it2 = 0, itt = 0;
	if (Utilities::ToUpper(thisCondition) == "AND") {

		if (WME.size() == 0 || WME1.size() == 0)
			return 0;

		while (1) {
			if (WME[it1].first == WME1[it2].first) {
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
			}
		}
	}
	else if (Utilities::ToUpper(thisCondition) == "OR") {

		if (WME.size() == 0) {
			for (int i = 0; i < WME1.size(); i++)
				testRes.push_back({ WME1[i].first, thisProduct });

			return 0;
		}
		else if (WME1.size() == 0) {
			for (int i = 0; i < WME.size(); i++)
				testRes.push_back({ WME[i].first, thisProduct });

			return 0;
		}

		while (1) {
			if (it1 == WME.size() && it2 == WME1.size())
				break;

			if (it1 == WME.size()) {
				testRes.push_back({ WME1[it2].first, thisProduct });
				if (it2 < WME1.size())
					it2++;
				continue;
			}
			if (it2 == WME1.size()) {
				testRes.push_back({ WME[it1].first, thisProduct });
				if (it1 < WME.size())
					it1++;
				continue;
			}


			if (WME[it1].first == WME1[it2].first) {

				testRes.push_back({ WME[it1].first, thisProduct });

				if (it1 < WME.size())
					it1++;
				if (it2 < WME1.size())
					it2++;

				continue;
			}

			if (WME[it1].first > WME1[it2].first&& it2 < WME1.size()) {
				testRes.push_back({ WME1[it2].first, thisProduct });
				it2++;
				continue;
			}
			else {
				testRes.push_back({ WME[it1].first, thisProduct });
				it1++;
				continue;
			}

			if (WME[it1].first < WME1[it2].first && it1 < WME.size()) {
				testRes.push_back({ WME[it1].first, thisProduct });
				it1++;
				continue;
			}
			else {
				testRes.push_back({ WME1[it2].first, thisProduct });
				it2++;
				continue;
			}

		}
	}

	return 0;
}

int BetaNode::testBetaNode(vector<pair<int, string>> WME, vector<pair<int, int>> WME1)
{
	if (!leftSourceBool || !rightSourceBool)
		return -1;

	//previous code
	/*
	if (leftSourceBool && rightSourceBool) {
		for (int i = 0; i < WME.size(); i++) {
			for (int j = i; j < WME1.size(); j++) {
				if (WME[i].first == WME1[j].first)
					testRes.push_back({ WME[i].first, thisProduct });
			}
		}
	}*/

	//join marking method
	/*
	if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "AND") {
		for (int i = 0; i < WME.size(); i++) {
			//And condition
			if (WME[i].first == WME1[i].first)
				testRes.push_back({ WME[i].first, thisProduct });
			else
				testRes.push_back({ -1, "0" });
		}
	}
	else if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "OR") {
		for (int i = 0; i < WME.size(); i++) {
			if (WME[i].first != -1 || WME1[i].first != -1)
				testRes.push_back({ WME[i].first, thisProduct });
			else
				testRes.push_back({ -1,"0" });
		}
	}*/

	//Ordered join method
	int it1 = 0, it2 = 0, itt = 0;
	if (Utilities::ToUpper(thisCondition) == "AND") {

		if (WME.size() == 0 || WME1.size() == 0)
			return 0;

		while (1) {
			if (WME[it1].first == WME1[it2].first) {
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
			}
		}
	}
	else if (Utilities::ToUpper(thisCondition) == "OR") {

		if (WME.size() == 0) {
			for (int i = 0; i < WME1.size(); i++)
				testRes.push_back({ WME1[i].first, thisProduct });

			return 0;
		}
		else if (WME1.size() == 0) {
			for (int i = 0; i < WME.size(); i++)
				testRes.push_back({ WME[i].first, thisProduct });

			return 0;
		}

		while (1) {
			if (it1 == WME.size() && it2 == WME1.size())
				break;

			if (it1 == WME.size()) {
				testRes.push_back({ WME1[it2].first, thisProduct });
				if (it2 < WME1.size())
					it2++;
				continue;
			}
			if (it2 == WME1.size()) {
				testRes.push_back({ WME[it1].first, thisProduct });
				if (it1 < WME.size())
					it1++;
				continue;
			}


			if (WME[it1].first == WME1[it2].first) {

				testRes.push_back({ WME[it1].first, thisProduct });

				if (it1 < WME.size())
					it1++;
				if (it2 < WME1.size())
					it2++;

				continue;
			}

			if (WME[it1].first > WME1[it2].first&& it2 < WME1.size()) {
				testRes.push_back({ WME1[it2].first, thisProduct });
				it2++;
				continue;
			}
			else {
				testRes.push_back({ WME[it1].first, thisProduct });
				it1++;
				continue;
			}

			if (WME[it1].first < WME1[it2].first && it1 < WME.size()) {
				testRes.push_back({ WME[it1].first, thisProduct });
				it1++;
				continue;
			}
			else {
				testRes.push_back({ WME1[it2].first, thisProduct });
				it2++;
				continue;
			}

		}
	}

	return 0;
}

int BetaNode::testBetaNode(vector<pair<int, string>> WME, vector<pair<int, string>> WME1)
{
	if (!leftSourceBool || !rightSourceBool)
		return -1;
	//Previous code
	/*
	if (leftSourceBool && rightSourceBool) {
		for (int i = 0; i < WME.size(); i++) {
			for (int j = i; j < WME1.size(); j++) {
				if (WME[i].first == WME1[j].first)
					testRes.push_back({ WME[i].first, thisProduct });
			}
		}
	}*/
	//join marking method
	/*
	if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "AND") {
		for (int i = 0; i < WME.size(); i++) {
			//And Condition
			if (WME[i].first == WME1[i].first)
				testRes.push_back({ WME[i].first, thisProduct });
			else
				testRes.push_back({ -1,"0" });
		}
	}
	else if (leftSourceBool && rightSourceBool && Utilities::ToUpper(thisCondition) == "OR") {
		for (int i = 0; i < WME.size(); i++) {
			if (WME[i].first != -1 || WME1[i].first != -1)
				testRes.push_back({ WME[i].first, thisProduct });
			else
				testRes.push_back({ -1,"0" });
		}
	}*/

	//Ordered join method
	int it1 = 0, it2 = 0, itt = 0;
	if (Utilities::ToUpper(thisCondition) == "AND") {

		if (WME.size() == 0 || WME1.size() == 0)
			return 0;

		while (1) {
			if (WME[it1].first == WME1[it2].first) {
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
			}
		}
	}
	else if (Utilities::ToUpper(thisCondition) == "OR") {

		if (WME.size() == 0) {
			for (int i = 0; i < WME1.size(); i++)
				testRes.push_back({ WME1[i].first, thisProduct });

			return 0;
		}
		else if (WME1.size() == 0) {
			for (int i = 0; i < WME.size(); i++)
				testRes.push_back({ WME[i].first, thisProduct });

			return 0;
		}

		while (1) {
			if (it1 == WME.size() && it2 == WME1.size())
				break;

			if (it1 == WME.size()) {
				testRes.push_back({ WME1[it2].first, thisProduct });
				if (it2 < WME1.size())
					it2++;
				continue;
			}
			if (it2 == WME1.size()) {
				testRes.push_back({ WME[it1].first, thisProduct });
				if (it1 < WME.size())
					it1++;
				continue;
			}


			if (WME[it1].first == WME1[it2].first) {

				testRes.push_back({ WME[it1].first, thisProduct });

				if (it1 < WME.size())
					it1++;
				if (it2 < WME1.size())
					it2++;

				continue;
			}

			if (WME[it1].first > WME1[it2].first&& it2 < WME1.size()) {
				testRes.push_back({ WME1[it2].first, thisProduct });
				it2++;
				continue;
			}
			else {
				testRes.push_back({ WME[it1].first, thisProduct });
				it1++;
				continue;
			}

			if (WME[it1].first < WME1[it2].first && it1 < WME.size()) {
				testRes.push_back({ WME[it1].first, thisProduct });
				it1++;
				continue;
			}
			else {
				testRes.push_back({ WME1[it2].first, thisProduct });
				it2++;
				continue;
			}

		}
	}

	return 0;
}

int BetaNode::addBetaPair(BetaNode* pair)
{
	int isExist = checkBeta(pair);
	if (isExist == 1)
		return 1;
	else {
		listOfBetaPair.push_back(pair);
		return 1;
	}

	return -1;
}

int BetaNode::checkBeta(BetaNode* pair)
{
	for (int i = 0; i < listOfBetaPair.size(); i++) {
		if (listOfBetaPair[i] == pair)
			return 1;
	}
	return 0;
}

int BetaNode::addBetaPairInNode(BetaNode* pair)
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

int BetaNode::ClearConnection()
{
	//betaPair = NULL;
	leftSourceBool = false;
	rightSourceBool = false;
	terminalPair = NULL;
	return 1;
}

int BetaNode::ResetNode()
{
	ClearConnection();
	testRes = {};
	listOfBetaPair = {};
	return 0;
}
