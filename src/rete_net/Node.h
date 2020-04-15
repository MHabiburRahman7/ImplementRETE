#pragma once

#include <iostream>
#include <vector>

#include <queue>
#include "../execution/EventProcess.h"

using namespace std;

class Node
{
public:
	int SuperNodeID;
	Node(int id, string condition);
	//Node();
	virtual int getID() = 0;
	virtual string getType() = 0;
	virtual bool isEmptyResult() = 0;

	string justCondition;
};

