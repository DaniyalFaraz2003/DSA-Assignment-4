#pragma once
#include <iostream>
#include <sstream>
#include "Assignee.h"
#include "List.h"
#include "RedBlackTree.h"

using namespace std;

class IdGenerator {
private:
	char currentLetter;
	int currentNum;
public:
	IdGenerator() {
		currentLetter = 'A';
		currentNum = 0;
	}
	string generateId() {
		if (currentNum == 999) {
			currentNum = 0;
			if (currentLetter == 'Z') currentLetter = 'A';
			else currentLetter++;
		}
		else currentNum++;
		char digit1 = '0' + (currentNum / 100);
		char digit2 = '0' + ((currentNum % 100) / 10);
		char digit3 = '0' + (currentNum % 10);
		string id = "";
		id += currentLetter; id += digit1; id += digit2; id += digit3;
		return id;
	}
};

class AssigneeManager
{
private:
	RedBlackTree<Assignee> tree;
	IdGenerator generator;
public:
	Assignee getAssigneeById(string id) {
		if (tree.exists(id)) {
			return tree.search(id)->data;
		}
		return Assignee();
	}
	void addAssignee(const Assignee& a) {
		Assignee assignee = a;
		const string id = generator.generateId();
		assignee.setId(id);
		if (!tree.exists(assignee)) {
			tree.insertNode(assignee);
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
	void assignTask(const Task t, string id) {
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
	void getAssignees(stringstream& ss) {
		ArrayBasedList<Assignee> res;
		tree.getTreeData(res);
		for (int i = 0; i < res.getSize(); i++) {
			Assignee assignee = res[i];
			ss << assignee;
		}
	}
	void printAssignees(stringstream& ss) {
		tree.displayAssignee(ss);
	}
};
