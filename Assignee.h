#pragma once
#ifndef ASSIGNEE_H
#define ASSIGNEE_H

#include <iostream>
#include <sstream>
#include "Task.h"
#include "List.h"
using namespace std;


class Assignee
{
private:
	string id, fname, lname, address, DOB;
	ArrayBasedList<Task> tasklist;
public:
	Assignee(string fname = "", string lname = "", string address = "", string dob = "", string id = "") {
		this->fname = fname;
		this->lname = lname;
		this->address = address;
		this->DOB = dob;
		this->id = id; 
	}
	string getName() { return fname + " " + lname; }
	string getFname() { return fname; }
	string getLname() { return lname; }
	string getAddress() { return address; }
	string getDob() { return DOB; }
	string getId() { return id; }

	Task getLastTask() {
		if (!tasklist.empty()) {
			return tasklist.back();
		}
		return Task();
	}
	void removeLastTask() {
		if (!tasklist.empty()) {
			tasklist.pop();
		}
	}
	bool noTasksAssigned() { return tasklist.empty(); }
	void assignTask(const Task& t) { 
		if (!searchTask(t))
			tasklist.push(t); 
	}
	void removeTask(const Task& t) {
		if (!searchTask(t)) return;
		int i;
		for (i = 0; i < tasklist.getSize(); i++) {
			if (tasklist[i] == t) break;
		}
		tasklist.deleteItem(i);
	}
	bool searchTask(const Task& t) {
		for (int i = 0; i < tasklist.getSize(); i++) {
			if (tasklist[i] == t) return true;
		}
		return false;
	}
	void printTasks() {
		for (int i = 0; i < tasklist.getSize(); i++) {
			cout << tasklist[i] << endl;
		}
	}

	friend ostream& operator<<(ostream& out, Assignee& a) {
		out << "Name: " << a.getName() << ", Address: " << a.getAddress() << ", DOB: " << a.getDob() << ", Assignee ID: " << a.getId() << "\n";
		return out;
	}
	friend stringstream& operator<<(stringstream& ss, Assignee& a) {
		ss << "Name: " << a.getName() << ", Address: " << a.getAddress() << ", DOB: " << a.getDob() << ", Assignee ID: " << a.getId() << "\n";
		return ss;
	}

	bool operator<(const Assignee& other) { return this->id < other.id; }
	bool operator>(const Assignee& other) { return this->id > other.id; }
	bool operator==(const Assignee& other) { return this->id == other.id; }
	bool operator<=(const Assignee& other) { return *this < other || *this == other; }
	bool operator>=(const Assignee& other) { return *this > other || *this == other; }

	bool operator<(const string& id) { return this->id < id; }
	bool operator>(const string& id) { return this->id > id; }
	bool operator==(const string& id) { return this->id == id; }
	bool operator<=(const string& id) { return *this < id || *this == id; }
	bool operator>=(const string& id) { return *this > id || *this == id; }
};

#endif // !ASSIGNEE_H