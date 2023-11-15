#include <iostream>
#include <sstream>

#include "RedBlackTree.h"
#include "List.h"
#include "Task.h"
#include "Assignee.h"
#include "AssigneeManager.h"
#include "TaskManager.h"
#include "taskManagementSystem.h"
using namespace std;

int main() {
	//Assignee a("Laraib", "Fatima", "Dha phase 2", "11/2/2002", "A001");
	//Assignee b("Daniyal", "Faraz", "I9", "14/11/2003", "A002");
	//Assignee c("Muhammad", "Shah", "Askari 14", "1/1/2003", "A003");
	//Assignee d("Muhammad", "Ali", "Dha phase 1", "11/2/2002", "A004");
	//Assignee e("Mukhtar", "Shah", "Dha phase 7", "1/2/2001", "A005");
	//Assignee f("Hammad", "Ali", "Askari 4", "1/10/2002", "A006");

	//Task t1(101, "Task A", 1, "A001");
	//Task t2(102, "Task B", 6, "A002");
	//Task t3(103, "Task C", 3, "A003");
	//Task t4(104, "Task A", 3, "A004");
	//Task t5(105, "Task B", 4, "A005");
	//Task t6(106, "Task C", 3, "A006");
	////AssigneeManager m;
	//TaskManager t;
	////m.printAssignees();
	//
	//stringstream ss;
	//t.addTask(t1);
	//t.addTask(t2);
	//t.addTask(t3);
	//t.addTask(t4);
	//t.addTask(t5);
	//t.addTask(t6);
	//t.display(ss);
	//cout << ss.str() << endl;;
	//ss.clear();
	//stringstream pp;
	//t.updatep(105, 3);
	//t.display(pp);
	//cout << pp.str() << endl;

	taskManagementSystem taskSystem;

	taskSystem.addAssignee("Waqas", "Khan", "I6", "2/12/2003");  //This should get A001
	taskSystem.addAssignee("Hur", "Hashim", "Dha phase 4", "1/1/2002"); // A002 and so on.
	taskSystem.addAssignee("Hasan", "Khan", "I9", "2/11/2003");
	// Add tasks with various priority levels
	taskSystem.addTask(101, "Implement Feature A", 2, "A001");
	taskSystem.addTask(102, "Fix Bug in Module B", 3, "A002");
	taskSystem.addTask(103, "Write Unit Tests", 1, "A003");

	// Capture the actual output
	std::stringstream actualOutput;
	taskSystem.searchTasksByPriorityRange(1, 2, actualOutput);

	// Define the expected output
	std::string expectedOutput = "Tasks within Priority Range (1 to 2):\n"
		"Task ID: 103, Description: Write Unit Tests, Priority: 1, Assignee: Hasan (A003)\n"
		"Task ID: 101, Description: Implement Feature A, Priority: 2, Assignee: Waqas(A001)\n";

	// Compare the actual output with the expected output and display "PASS" or "FAIL"
	cout << actualOutput.str() << endl;
	cout << expectedOutput << endl;
	return 0;
}