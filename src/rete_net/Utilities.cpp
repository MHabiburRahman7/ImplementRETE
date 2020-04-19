#include "Utilities.h"

Utilities::Utilities()
{
}

vector<pair<string, string>> Utilities::tokenize(string temp)
{
	//example
	//If distance < 10000 and elevation > 12000 then danger_obj
	//will return:
	//1. pair<"alpha" , "distance < 10000">
	//2. pair<"alpha" , "elevation > 12000">
	//3. pair<"term" , "danger_obj">

	//if danger_obj and speed > 20000 then alert_obj
	//will return:
	//1. pair<"beta" , "danger_obj">
	//2. pair<"alpha" , "speed > 20000">>
	//3. pair<"term" , "alert_obj">

	vector<string> tempor;
	vector<pair<string, string>> conditionMade;

	tempor = {};
	conditionMade = {};

	char* str = (char*)malloc(500);
	strcpy(str, temp.c_str());
	// Returns first token  
	char* token = strtok(str, " ");
	int itt = 0;
	int ittMade = 0;

	if (itt == 0 && strcmp(ToUpper(token).c_str(), "IF") == 0) {
		itt++;
	}
	else if (itt == 0 && strcmp(ToUpper(token).c_str(), "IF") != 0) {
		return conditionMade;
	}

	// Keep printing tokens while one of the 
	// delimiters present in str[].
	while (token != NULL)
	{
		//printf("%s\n", token);
		token = strtok(NULL, " ");
		//strcpy(token, ToUpper(token).c_str());

		//considered alpha
		if (token == NULL) {
			string cond = {};
			//cout << "considered product " << tempor[0] << endl;
			conditionMade.push_back({ "Term", tempor[0] });
			break;
		}
		else if ((strcmp(ToUpper(token).c_str(), "AND") == 0
			|| strcmp(ToUpper(token).c_str(), "THEN") == 0
			|| strcmp(ToUpper(token).c_str(), "OR") == 0)
			&& tempor.size() > 1) {

			string cond = {};
			for (int i = 0; i < tempor.size(); i++) {
				cond += tempor[i];
				cond += " ";
			}
			//cout << "considered alpha " << cond << endl;

			conditionMade.push_back({ "Alpha", cond });

			tempor = {};
		}
		else if ((strcmp(ToUpper(token).c_str(), "AND") == 0
			|| strcmp(ToUpper(token).c_str(), "THEN") == 0
			|| strcmp(ToUpper(token).c_str(), "OR") == 0)
			&& tempor.size() == 1) {
			string cond = {};
			cond = tempor[0];
			//cout << "considered beta " << cond << endl;

			conditionMade.push_back({ "Beta", cond });

			tempor = {};
		}
		else if (itt > 0 && (strcmp(ToUpper(token).c_str(), "AND") != 0
			|| strcmp(ToUpper(token).c_str(), "OR") == 0
			|| (strcmp(ToUpper(token).c_str(), "THEN") != 0))) {
			tempor.push_back(token);
		}

		//Get OR/AND
		if ((strcmp(ToUpper(token).c_str(), "AND") == 0)
			|| (strcmp(ToUpper(token).c_str(), "OR") == 0)) {
			conditionMade.push_back({ "condition", ToUpper(token).c_str() });
		}
		/*if ((strcmp(ToUpper(token).c_str(), "&") == 0)) {
			conditionMade.push_back({ "condition", "AND" });
		}*/

		//token = strtok(NULL, " ");
		itt++;
	}

	return conditionMade;
}

vector<pair<string, string>> Utilities::tokenizeMoreDetail(string temp)
{
	vector<string> tempor = {};
	vector<pair<string, string>> conditionMade = {};

	char* str = (char*)malloc(500);
	strcpy(str, temp.c_str());
	// Returns first token  
	char* token = strtok(str, " ");
	int itt = 0;
	int ittMade = 0;

	//IF
	if (itt == 0 && strcmp(ToUpper(token).c_str(), "IF") == 0) {
		itt++;
		while (token != NULL)
		{
			token = strtok(NULL, " ");
			//considered alpha
			if (token == NULL && tempor.size() > 1) {
				string cond = {};
				for (int i = 0; i < tempor.size(); i++) {
					cond += tempor[i];
					cond += " ";
				}
				conditionMade.push_back({ "Alpha", cond });

				tempor = {};
				break;
			}
			else if (token == NULL && tempor.size() == 1) {

				//conditionMade.push_back({ "Beta", tempor[0] });
				//string exi = "exist";
				//int pos = tempor[0].find(exi);
				if (tempor[0].find("(") > 0 && tempor[0].find(")") > 0) {
					conditionMade.push_back({ "Alpha", tempor[0] });
				}
				else {
					conditionMade.push_back({ "Beta", tempor[0] });
				}

				tempor = {};
				break;
			}
			else if ((strcmp(ToUpper(token).c_str(), "AND") == 0
				|| strcmp(ToUpper(token).c_str(), "THEN") == 0
				|| strcmp(ToUpper(token).c_str(), "OR") == 0)
				&& tempor.size() > 1) {

				string cond = {};
				for (int i = 0; i < tempor.size(); i++) {
					cond += tempor[i];
					cond += " ";
				}
				conditionMade.push_back({ "Alpha", cond });

				tempor = {};
			}
			//Considered beta
			else if ((strcmp(ToUpper(token).c_str(), "AND") == 0
				|| strcmp(ToUpper(token).c_str(), "THEN") == 0
				|| strcmp(ToUpper(token).c_str(), "OR") == 0)
				&& tempor.size() == 1) {
				string cond = {};
				cond = tempor[0];
				//cout << "considered beta " << cond << endl;

				if (cond.find("(") > 0 && cond.find(")") > 0) {
					conditionMade.push_back({ "Alpha", cond });
				}
				else {
					conditionMade.push_back({ "Beta", cond });
				}

				tempor = {};
			}
			else if (itt > 0 && (strcmp(ToUpper(token).c_str(), "AND") != 0
				|| strcmp(ToUpper(token).c_str(), "OR") == 0
				|| (strcmp(ToUpper(token).c_str(), "THEN") != 0))) {
				tempor.push_back(token);
			}
			//Get OR/AND
			if ((strcmp(ToUpper(token).c_str(), "AND") == 0)
				|| (strcmp(ToUpper(token).c_str(), "OR") == 0)) {
				conditionMade.push_back({ "condition", ToUpper(token).c_str() });
			}

			itt++;
		}
	}
	//FROM
	else if (itt == 0 && strcmp(ToUpper(token).c_str(), "FROM") == 0) {
		token = strtok(NULL, " ");
		conditionMade.push_back({ "Beta", token });
		//return conditionMade;
	}
	//THEN
	else if (itt == 0 && strcmp(ToUpper(token).c_str(), "THEN") == 0) {
		token = strtok(NULL, " ");
		conditionMade.push_back({ "Term", token });
		//return conditionMade;
	}
	else {
		string otherForm = token;
		token = strtok(NULL, " ");
		conditionMade.push_back({ ToUpper(otherForm), token });
		//return conditionMade;
	}
	return conditionMade;
}

string Utilities::ToUpper(string ori)
{
	for (int i = 0; i < ori.size(); i++) {
		ori[i] = toupper(ori[i]);
	}
	return ori;
}

string Utilities::ToLower(string ori)
{
	for (int i = 0; i < ori.size(); i++) {
		ori[i] = tolower(ori[i]);
	}
	return ori;
}
