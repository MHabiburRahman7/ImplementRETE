#pragma once
#include <iostream>
#include <vector>

#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstring>
#include <ctime>

#include <mutex>

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
	static vector<pair<string, string>> tokenizeMoreDetail(string temp);

	static long long getTime();

	static string ToUpper(string ori);
	static string ToLower(string ori);
};

