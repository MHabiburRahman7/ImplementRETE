#include "RETE_Process.h"

bool RETE_Process::isExist;

RETE_Process::RETE_Process()
{
	isExist = false;
}

void RETE_Process::resetAndClearGraph()
{
	theGraph.resetAndClearNet();
	isExist = false;
}

void RETE_Process::buildGraph()
{
	theGraph.buildCurrentAlphaBeta();
	isExist = true;
}

bool RETE_Process::process(int timeSlice)
{
	return false;
}

void RETE_Process::addCQ(list<string> input)
{
	//cannot handle list, lets go for vector
	vector<string> newInputForm;
	for (auto v : input) {
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

	//separate

	//main part
	string finalTerm;
	
	vector<pair<string, string>> made;
	made = Utilities::tokenize(newInputForm[0] + " " + newInputForm[2]);

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

		cqRete.addTerminal(finalTerm);

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
				cqRete.addAlpha(made[i].second);

				finalTerm += made[i].second;
				finalTerm += " ";
			}
			else {
				finalTerm += made[i].second;
				finalTerm += " ";
			}
			token = strtok(str, " ");
		}

		cqRete.addBeta(finalTerm);
	}
}
