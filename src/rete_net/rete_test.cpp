//#include "stdafx.h"
#include "rete_test.h"


int rete_test::add_CQProcess(CQProcess* cq)
{
	cqProc_vec.push_back(cq);

 	vector<string> attr, optname;

	attr = dynamic_cast<CQProcess*>(cq)->newAttrNames;
	optname = dynamic_cast<CQProcess*>(cq)->operatorNames;

	vector<Predicate *> pre, child;
	vector<Predicate> another_pre;

	string fieldName;
	float val;

	bool isOr = true;

	pre = cq->getPredicates();

	child = *pre[0]->getChildren();

	cout << "the class is: " << typeid(child[0]).name() << endl;

	if (typeid(pre[0]).name() == "And") {
		isOr = false;
	}

	for (int j = 0; j < child.size(); j++) {

		//Get the value
		if (dynamic_cast<GreaterThanFloat*>(child[j])) {
			fieldName = dynamic_cast<GreaterThanFloat*>(child[j])->getFieldName();
			val = dynamic_cast<GreaterThanFloat*>(child[j])->getPredicateValue();
		}
	}

	return 0;
}

int rete_test::add_event(EventPtr e)
{
	event_vec.push_back(e);
	return 1;
}

int rete_test::build_rete()
{
	//process rister
	ProcessRegister p;

	

	/*for (int i = 0; i < p.getAllCQ; i++) {
		p.getProcess[i];
	}*/
	


	return 0;
}

int rete_test::getEvent(EventPtr* e)
{

	return 0;
}
