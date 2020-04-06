#pragma once
#include <iostream>
#include <vector>

//#include "AlphaNode.h"
//#include "BetaNode.h"
//#include "GraphOrNet.h"

using namespace std;

class Utilities
{
public:
	//vector<AlphaNode> testAlpha;
	//vector<BetaNode> testBeta;

	Utilities();

	//tokenizing
	static vector<pair<string, string>> tokenize(string temp);

	static string ToUpper(string ori);
	static string ToLower(string ori);
};

