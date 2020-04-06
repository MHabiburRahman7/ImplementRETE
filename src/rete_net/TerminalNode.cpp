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

TerminalNode::TerminalNode(int id, string termName)
	: Node(BaseNodeID, tempComingCondition)
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
