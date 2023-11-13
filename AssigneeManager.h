#pragma once
#include <iostream>
#include <sstream>
#include "Assignee.h"
#include "List.h"
#include "RedBlackTree.h"

using namespace std;

class AssigneeManager
{
private:
	RedBlackTree<Assignee> tree;
public:
	Assignee getAssigneeById(string id) {
		if (tree.exists(id)) {
			return tree.search(id)->data;
		}
		return Assignee();
	}
	void addAssignee(const Assignee& a) {
		if (!tree.exists(a)) {
			tree.insertNode(a);
		}
	}
	void getAssigneeByName(stringstream& in, string fname, string lname) {
		ArrayBasedList<Assignee> res;
		tree.getTreeData(res);
		for (int i = 0; i < res.getSize(); i++) {
			if (fname == res[i].getFname() && lname == res[i].getLname()) {
				Assignee a = res[i];
				in << a;
			}
		}
	}
	void getAssigneeWithNoTask(stringstream& in) {
		ArrayBasedList<Assignee> res;
		tree.getTreeData(res);
		for (int i = 0; i < res.getSize(); i++) {
			if (res[i].noTasksAssigned()) {
				Assignee a = res[i];
				in << a;
			}
		}
	}
	void assignTask(const Task& t, string id) {
		if (tree.exists(id)) {
			tree.search(id)->data.assignTask(t);
		}
	}
	void disAssignTask(const Task& t, string id) {
		if (tree.exists(id)) {
			tree.search(id)->data.removeTask(t);
		}
	}
	void deleteAssignee(const string& id) {
		if (tree.exists(id)) {
			if (tree.search(id)->data.noTasksAssigned()) {
				Assignee temp("", "", "", "", id);
				tree.deleteNode(temp);
			}
		}
	}
	void shiftTasks(string from, string to) {
		if (!tree.exists(from) || !tree.exists(to)) return;
		Node<Assignee>* fromAssignee = tree.search(from);
		Node<Assignee>* toAssignee = tree.search(to);
		while (!fromAssignee->data.noTasksAssigned()) {
			Task t = fromAssignee->data.getLastTask();
			fromAssignee->data.removeLastTask();
			toAssignee->data.assignTask(t);
		}
	}
	void printAssignees() {
		tree.displayAssignee();
	}
};
