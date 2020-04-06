#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
	int SuperNodeID;
	Node(int id, string condition);
	//Node();
	virtual int getID() = 0;
	virtual string getType() = 0;

	string justCondition;
};

