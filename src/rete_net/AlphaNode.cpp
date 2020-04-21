#include "AlphaNode.h"

int AlphaNode::getID()
{
	return id;
}

string AlphaNode::getType()
{
	return "Alpha";
}


AlphaNode::AlphaNode(int id_given, string condition, string wmNum) : Node(id_given, condition)
{
	wmNumber = wmNum;
	int itt = 0;

	id = id_given;

	char* str = (char*)malloc(100);
	strcpy(str, condition.c_str());
	// Returns first token  
	char* token = strtok(str, " ");
	string s(token);
	
	int open = s.find("(");
	int close = s.find(")");
	if (open > 0 && close > 0) {

		thisDataType = s.substr(0, open);
		if (Utilities::ToUpper(thisDataType) == "EXIST") {
			thisVarLimit = s.substr(open + 1, close - open - 1);
			thisCondition = "==";
		}
		else if (Utilities::ToUpper(thisDataType) == "COUNT") {
			while (token != NULL)
			{
				//printf("%s\n", token);
				token = strtok(NULL, " ");
				if (itt == 0)
					thisCondition = token;
				else if (itt == 1)
					thisVarLimit = token;
				itt++;
			}
		}

		additionalStr = s.substr(open + 1, close - open - 1);
	}
	else {
		// Keep printing tokens while one of the 
		// delimiters present in str[].
		thisDataType = token;
		while (token != NULL)
		{
			//printf("%s\n", token);
			token = strtok(NULL, " ");
			if (itt == 0)
				thisCondition = token;
			else if (itt == 1)
				thisVarLimit = token;
			itt++;
		}
	}
}

string AlphaNode::getAlphaDataType()
{
	return thisDataType;
}

string AlphaNode::getCondition()
{
	return thisCondition;
}

string AlphaNode::getVarLimit()
{
	return thisVarLimit;
}

string AlphaNode::getWmName()
{
	return wmNumber;
}

Node* AlphaNode::getSinglePair(int i)
{
	return listOfBetaPairsInNode[i];
}

vector<Node*> AlphaNode::getAllPairs()
{
	return listOfBetaPairsInNode;
}

queue<EventPtr>* AlphaNode::getEvRes()
{
	return EventResult;
}

void AlphaNode::setWindow(int len, int slide)
{
	winLen = len;
	winSlide = slide;
}

void AlphaNode::refreshEvent(queue<EventPtr> &eventQueue){
	long long curr = Utils::getTime();
	while (!eventQueue.empty() && eventQueue.front()->getTime() + winLen < curr) {
		eventQueue.pop();
	}
}

void AlphaNode::setWindowLiyang(int len, int slide)
{
	winLen = len;
	winSlide = slide;

	//set sliding windows with Exist() operator.
	vector<Window*> windowList;
	//for (string inputStreamName : inputStreams) {//生成这么多的win和existOp是不合理的，需要修改
	NaiveTimeSlidingWindow* win = new NaiveTimeSlidingWindow(winLen);
	win->setTimeSliding(winSlide);
	if (additionalStr.size() > 0) {
		ExistOp* existOp = new ExistOp(additionalStr);//operator
		win->setStatefulOperator(existOp);
		windowList.push_back(win);//vector
	}
	else {
		ExistOp* existOp = new ExistOp(thisVarLimit);//operator
		win->setStatefulOperator(existOp);
		windowList.push_back(win);//vector
	}

	alphaWindowList = windowList;
	//}
}

int AlphaNode::checkExistPair(Node* pairs)
{
	for (int i = 0; i < listOfBetaPairsInNode.size(); i++) {
		if (listOfBetaPairsInNode[i] == pairs)
			return 1;
	}

	return 0;
}

int AlphaNode::addBetaPair(Node* pair)
{
	int isExist = checkExistPair(pair);
	if (isExist)
		return 1;
	else {
		//listOfBetaPairs.push_back(pair);
		listOfBetaPairsInNode.push_back(pair);
		return 1;
	}
	return -1;
}

void AlphaNode::testAlphaAndSaveHere(vector<pair<int, int>> test_cases)
{
	//testRes = {};
	int limit = atoi(thisVarLimit.c_str());

	int cases = -1;
	// 0 -> equal less
	// 1 -> equal more
	// 2 -> less
	// 3 -> more
	if (thisCondition == "<=")
		cases = 0;
	else if (thisCondition == ">=")
		cases = 1;
	else if (thisCondition == "<")
		cases = 2;
	else if (thisCondition == ">")
		cases = 3;

	for (int i = 0; i < test_cases.size(); i++) {
		if (cases == 0 && test_cases[i].second <= limit) {
			//testRes.push_back(test_cases[i]);
		}
		else if (cases == 1 && test_cases[i].second >= limit) {
			//testRes.push_back(test_cases[i]);
		}
		else if (cases == 2 && test_cases[i].second < limit) {
			//testRes.push_back(test_cases[i]);
		}
		else if (cases == 3 && test_cases[i].second > limit) {
			//testRes.push_back(test_cases[i]);
		}
		//In case join-marking is implemented
		/*else {
			testRes.push_back({ -1, 0 });
		}*/
	}
}

bool AlphaNode::testDataType(string condition_test)
{
	if (strcmp(condition_test.c_str(), thisCondition.c_str()) != 0)
		return false;
	else
		return true;
}

int AlphaNode::ResetNode()
{
	//testRes = {};
	//listOfBetaPairs = {};
	listOfBetaPairsInNode = {};
	//betaPair = NULL;
	return 1;
}

int AlphaNode::ClearResults()
{
	while (!EventResult->empty()) {
		EventResult->pop();
	}
	return 1;
}

void AlphaNode::testAlphaAndSaveHere(queue<EventPtr>* inputQueue, int TimeSlice)
{
	ClearResults();
	queue<EventPtr> inputQueue_local = *inputQueue;
	//auto itt_local = inputQueue_local.front();

	bool isAbleToProcess = false;

	if (winLen > 0 && winSlide > 0) {
		refreshEvent(inputQueue_local);
	}
	
	float limit = atof(thisVarLimit.c_str());

	if (limit == 0) {//its not a integer val
		int cases = -1;
		if (thisCondition == "=" || thisCondition == "==")
			cases = 0;
		else if (thisCondition == "!=")
			cases = 1;

		int timeSlice_i = TimeSlice;
		while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
			//EventPtr originalFrontEvent = inputQueue_local->front();
			EventPtr originalFrontEvent = inputQueue_local.front();

			if (thisVarLimit == "All") {
				EventResult->push(originalFrontEvent);
			}
			//else if (cases == 0 && thisDataType == "exist" && Utilities::ToUpper(thisDataType) == Utilities::ToUpper(thisVarLimit)) {
			else if (cases == 0 && thisDataType == "exist" && wmNumber == thisVarLimit) {
				if (winLen > 0 && winSlide > 0) {
					long long curr = Utils::getTime();
					if (originalFrontEvent->getTime() + winLen < curr)
						EventResult->push(originalFrontEvent);
				}else
					EventResult->push(originalFrontEvent);
			}
			else if (cases == 0 && originalFrontEvent->getString(thisDataType) == thisVarLimit) {
				//testRes.push_back(test_cases[i]);
				EventResult->push(originalFrontEvent);
			}
			else if (cases == 1 && originalFrontEvent->getString(thisDataType) != thisVarLimit) {
				EventResult->push(originalFrontEvent);
			}

			inputQueue_local.pop();
			//itt_local+=1;
			timeSlice_i--;
		}
	}
	else {
		int cases = -1;
		// 0 -> equal less
		// 1 -> equal more
		// 2 -> less
		// 3 -> more
		if (thisCondition == "<=")
			cases = 0;
		else if (thisCondition == ">=")
			cases = 1;
		else if (thisCondition == "<")
			cases = 2;
		else if (thisCondition == ">")
			cases = 3;
		else if (thisCondition == "==")
			cases = 4;
		
		if (Utilities::ToUpper(thisDataType) == "COUNT") {
			int timeSlice_i = TimeSlice;
			if (cases == 0) {
				while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
					EventPtr originalFrontEvent = inputQueue_local.front();

					if (inputQueue_local.size() <= limit)
						EventResult->push(originalFrontEvent);

					timeSlice_i--;
					inputQueue_local.pop();
				}
			}
			else if (cases == 1) {
				while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
					EventPtr originalFrontEvent = inputQueue_local.front();

					if (inputQueue_local.size() >= limit)
						EventResult->push(originalFrontEvent);

					timeSlice_i--;
					inputQueue_local.pop();
				}
			}
			else if (cases == 2) {
				while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
					EventPtr originalFrontEvent = inputQueue_local.front();

					if (inputQueue_local.size() < limit)
						EventResult->push(originalFrontEvent);

					timeSlice_i--;
					inputQueue_local.pop();
				}
			}
			else if (cases == 3) {
				while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
					EventPtr originalFrontEvent = inputQueue_local.front();
					
					if(inputQueue_local.size() > limit)
						EventResult->push(originalFrontEvent);
					
					timeSlice_i--;
					inputQueue_local.pop();
				}
			}
			else if (cases == 4) {
				while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
					EventPtr originalFrontEvent = inputQueue_local.front();

					if (inputQueue_local.size() == limit)
						EventResult->push(originalFrontEvent);

					timeSlice_i--;
					inputQueue_local.pop();
				}
			}
		}

		int timeSlice_i = TimeSlice;
		while (!inputQueue_local.empty() && timeSlice_i > 0) {//current input queue is not empty.
			EventPtr originalFrontEvent = inputQueue_local.front();

			if (cases == 0 && originalFrontEvent->getFloat(thisDataType) <= limit) {
				EventResult->push(originalFrontEvent);
			}
			else if (cases == 1 && originalFrontEvent->getFloat(thisDataType) >= limit) {
				EventResult->push(originalFrontEvent);
			}
			else if (cases == 2 && originalFrontEvent->getFloat(thisDataType) < limit) {
				EventResult->push(originalFrontEvent);
			}
			else if (cases == 3 && originalFrontEvent->getFloat(thisDataType) > limit) {
				EventResult->push(originalFrontEvent);
			}
			else if (cases == 4 && originalFrontEvent->getFloat(thisDataType) == limit) {
				EventResult->push(originalFrontEvent);
			}

			inputQueue_local.pop();
			timeSlice_i--;
		}
	}
}

bool AlphaNode::isEmptyResult()
{
	if (EventResult == NULL || EventResult->size() == 0)
		return true;
	return false;
}
