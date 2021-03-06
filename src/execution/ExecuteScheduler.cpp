#include "../stdafx.h"
#include "ExecuteScheduler.h"
#include <thread>
#include "../cqindex/ProcessRegisterForCQIndex.h"

//#include "../rete_net/rete_test.h"


priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*>,cmp > ExecuteScheduler::cq_pq;

priority_queue<Process_TriggerTime*, vector<Process_TriggerTime*>, cmp > ExecuteScheduler::cep_pq;

mutex ExecuteScheduler::mutexOfCQPriorityQueue;

mutex ExecuteScheduler::mutexOfCEPPriorityQueue;

void ExecuteScheduler::initialize() {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		buildGraph();
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

void ExecuteScheduler::buildGraph() {
	TopoGraph::setEventFilter(ProcessRegister::eventProcess);//add Event Filter processing

	NewReteGraph::createWMSet();

	for (Process* p : ProcessRegister::getAllEventCapture()) {//add Event Capture
		TopoGraph::addProcessUnitToGraph(p);
		//connect RETE
		TopoGraph::addRETEProcessUnitToGraph(p);
	}

	for (Process* p : ProcessRegister::getAllCQ()) {//add CQ
		TopoGraph::addProcessUnitToGraph(p);
		//connect RETE
		TopoGraph::addRETEProcessUnitToGraph(p);
	}

	for (Process* p: ProcessRegister::getCEPs()) {//add CEP
		TopoGraph::addProcessUnitToGraph(p);
	}

	//NewReteGraph::createWMSet({ "targetData" });

	//TopoGraph::addRETEProcessUnitToGraph(); //Register WMSet as the next output of EventProcess

	NewReteGraph::buildNetNode();

	buildTriggerTimePriorityQueue();
}

void ExecuteScheduler::rebuildGraph() {
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		TopoGraph::clear();
		for (Process * p : ProcessRegister::allProcess()) {
			p->removeAllDownStreamQueuesAndNames();
		}
		buildGraph();
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}

void ExecuteScheduler::runProcessQueue(){
	do {
		try {
			std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock

			//rete_test r;//---------------------------------------------------------------------------------------------------
			int itt = 0;
			//event filter
			for (auto iter = ProcessRegister::processSet.begin(); iter != ProcessRegister::processSet.end(); iter++){
				
				//if (dynamic_cast<CQProcess*>(*iter)) {
				//	//itt++;
				//	r.add_CQProcess(dynamic_cast<CQProcess*>(*iter));
				//}

				//change here?
				(*iter)->process(100);
			}

			//for Event Capture CQ and CEP because it require RETE ._.
			//NewReteGraph::printWMSet();
			NewReteGraph::processRete(100);


		}catch (std::logic_error& e) {
			std::cout << "[exception caught]\n";
		}
	} while (true);
}


void ExecuteScheduler::buildTriggerTimePriorityQueue() {
	try {
		std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfCEPPriorityQueue);
		while (!cep_pq.empty()) {//clear the priority queues
			delete cep_pq.top();
			cep_pq.pop();
		}
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}

	try {
		std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfCQPriorityQueue);
		while (!cq_pq.empty()) {
			delete cq_pq.top();
			cq_pq.pop();
		}
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
	
	try {
		std::lock_guard<std::recursive_mutex> lg(ProcessRegister::mutexOfProcessRegister);//mutex lock
		for (auto iter = ProcessRegister::processSet.begin(); iter != ProcessRegister::processSet.end(); iter++) {
			if (CEPProcess* cep = (CEPProcess*)dynamic_cast<CEPProcess*>(*iter)) {
				if (cep->windowList.size() > 0) {
					Process_TriggerTime* ptt = new Process_TriggerTime(cep, cep->windowList[0]->getWinSliding());
					try {
						std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfCEPPriorityQueue);
						cep_pq.push(ptt);
					}
					catch (std::logic_error& e) {
						std::cout << "[exception caught]\n";
					}
				}
			}else if (CQProcess * cq = (CQProcess*)dynamic_cast<CQProcess*>(*iter)) {
				if (cq->windowList.size() > 0) {
					Process_TriggerTime* ptt = new Process_TriggerTime(cq, cq->windowList[0]->getWinSliding());
					try {
						std::lock_guard<mutex> lg(ExecuteScheduler::mutexOfCQPriorityQueue);
						cq_pq.push(ptt);
					}
					catch (std::logic_error& e) {
						std::cout << "[exception caught]\n";
					}
				}
			}
		}
	}
	catch (runtime_error & e) {
		std::cout <<"Runtime error: " <<  e.what() << endl;
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]\n";
	}
}