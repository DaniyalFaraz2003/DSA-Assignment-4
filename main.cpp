#include <iostream>
#include <sstream>

#include "RedBlackTree.h"
#include "List.h"
#include "Task.h"
#include "Assignee.h"
#include "AssigneeManager.h"
using namespace std;

int main() {
	Assignee a("Laraib", "Fatima", "Dha phase 2", "11/2/2002", "A001");
	Assignee b("Daniyal", "Faraz", "I9", "14/11/2003", "A002");
	Assignee c("Muhammad", "Ali", "Askari 14", "1/1/2003", "A003");
	Assignee d("Muhammad", "Shah", "Dha phase 1", "11/2/2002", "A004");
	Assignee e("Mukhtar", "Shah", "Dha phase 7", "1/2/2001", "A005");
	Assignee f("Hammad", "Ali", "Askari 4", "1/10/2002", "A006");

	Task t1(102, "Fix Bug in Module B", 2, "A001");
	Task t2(103, "Write Unit Tests", 1, "A003");
	Task t3(101, "Implement Feature A", 3, "A002");
	AssigneeManager m;
	m.addAssignee(a);
	m.addAssignee(b);
	m.addAssignee(c);
	m.addAssignee(d);
	m.addAssignee(e);
	m.addAssignee(f);
	//m.printAssignees();
	
	m.assignTask(t1, "A001");
	m.assignTask(t2, "A001");
	m.assignTask(t3, "A002");

	
	stringstream ss;
	return 0;
}