#pragma once
#ifndef TASK_H
#define TASK_H

#include <iostream>
using namespace std;


class Task
{
private:
	string description, assigneeId;
	bool status; // 0 for not completed 1 for completed
	int priority, id;
public:
	Task(int id = 0, string description = "", int priority = 0, string assigneeId = "") {
		this->id = id;
		this->description = description;
		this->priority = priority;
		this->assigneeId = assigneeId;
		this->status = false;
	}
	string getDescription() const { return description; }
	int getPriority() const { return priority; }
	string getAssignee() const { return assigneeId; }
	int getId() const { return id; }
	bool getStatus() const { return status; }

	void setAssignee(string assignee) { this->assigneeId = assignee; }
	void setPriority(int p) { priority = p; }
	void setStatus(char c) { if (c == 'c') status = true; else status = false; }
	bool isCompleted() { return status; }

	friend ostream& operator<<(ostream& out, const Task& t) {
		out << "Task ID: " << t.id << ", Description: " << t.description << ", Priority: " << t.priority;
		return out;
	}

	bool operator==(const Task& other) {
		return this->id == other.id;
	}
};


#endif // !TASK_H