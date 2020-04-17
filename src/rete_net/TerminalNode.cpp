//#include "stdafx.h"
#include "TerminalNode.h"

int TerminalNode::getID()
{
	return thisId;
}

string TerminalNode::getType()
{
	return "Terminal";
}

bool TerminalNode::isEmptyResult()
{
	return false;
}

TerminalNode::TerminalNode(int id, string termName)
	: Node(id, termName)
{
	int itt = 0;
	thisId = id;

	char* str = (char*)malloc(100);
	strcpy(str, termName.c_str());
	// Returns first token  
	char* token = strtok(str, " ");

	prevBetaProduct = token;
	while (token != NULL)
	{
		//printf("%s\n", token);
		token = strtok(NULL, " ");
		if (itt == 1)
			term = token;
		itt++;
	}
}

void TerminalNode::addPair(Node* pair)
{
	//Duplicate check

	//Connect pair

}

int TerminalNode::checkPair(Node* pair)
{
	return 0;
}

queue<EventPtr>* TerminalNode::getEvRes()
{
	return nullptr;
}
