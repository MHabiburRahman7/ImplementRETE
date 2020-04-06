#pragma once
#include "ReteGraph.h"
#include "Utilities.h"
#include <iostream>

using namespace std;

class RETE_Process
{
public:

	static void addCQ(string input) {
		string finalTerm;

		vector<pair<string, string>> made;
		made = Utilities::tokenize(input);

		char* token;
		char* str = (char*)malloc(100);

		//This belong to beta and terminal
		if (made.size() == 2) {
			for (int i = 0; i < made.size(); i++) {
				//beta node
				if (i == 0) {
					finalTerm += made[i].second;
					finalTerm += " then ";
				}
				else {
					finalTerm += made[i].second;
				}
			}
			
			theGraph.addTerminal(finalTerm);

			int a;
		}
		//This belong to alpha-beta or beta-beta
		else if (made.size() > 2) {
			for (int i = 0; i < made.size(); i++) {

				if (i == 3) {
					finalTerm += "then ";
				}

				if (made[i].first == "Alpha") {
					//if alpha is exist

					//if alpha is not exist
					theGraph.addAlpha(made[i].second);

					finalTerm += made[i].second;
					finalTerm += " ";
				}
				else {
					finalTerm += made[i].second;
					finalTerm += " ";
				}
				token = strtok(str, " ");
			}
			
			theGraph.addBeta(finalTerm);
		}
	};

	static ReteGraph theGraph;

	
};

