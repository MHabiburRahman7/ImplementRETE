#include <vector>
#include "../common/Event.h"
#include "../execution/ProcessRegister.h"
#include "../execution/Process.h"
#include "../spec/CQSpec.h"
#include "../expression/Predicate.h"
#include "../expression/OperatorPredicate.h"

#include "../expression/GreaterThanFloat.h"

#pragma once

class rete_test
{
public:
	rete_test() {};

	vector<EventPtr> event_vec;
	vector<CQProcess*> cqProc_vec;

	int add_CQProcess(CQProcess * cq);
	int add_event(EventPtr e);
	int build_rete();

	int getEvent(EventPtr* e);
};

