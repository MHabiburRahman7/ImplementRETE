#pragma once
#include <queue>
#include "../execution/EventProcess.h"
#include "../execution/Process.h"
#include <mutex>
#include <unordered_map>
#include "../execution/CEPProcess.h"
#include <set>

//#include "../rete_net/ReteGraph.h"
//#include "../rete_net/RETE_Process.h"

/*
To store the objects of Processing, including Event Filter, 
Event Capture, CQ and CEP. So it has functions to add, get and delete 
processing objects. All functions are decorated by static clause.
*/
class ProcessRegister {
	friend class ExecuteScheduler;
public:
	static void addProcess(Process* pro);
	static void removeProcess(string outputStreamName);
	static Process* getProcess(string outputStreamName);
	static set<Process*> allProcess();
	static EventProcess * getProcessOfEventFiltering();
	static bool isExist(Process* pro);

	static set<CEPProcess*> getCEPs();
	static vector<Process*>& getAllEventCapture();
	static vector<Process*>& getAllCQ();

	static void registerEventFilter(EventProcess* ep);

	//static void addProcessReteCQ();

	//----------------------------------------------------
	//Here comes Rete again . . .
	//static ReteGraph* rete_cq;

	// Well well, start from here man . . .
	// Remember only single RETE for CQ and single RETE for CEP
	// No more, no less 

private:
	static EventProcess *eventProcess;

	static set<Process*> processSet;
	//output stream name -> process
	static unordered_map<string, Process*> processMap;
	static vector<Process*> eventCaptureVec;
	static vector<Process*> cqVec;
	static set<CEPProcess*> cepSet;

	//lets treat the same;
	static vector<Process*> cqRete;
	//static Process* rete_cq;

public:
	static std::recursive_mutex mutexOfProcessRegister;//mutex lock among threads
};