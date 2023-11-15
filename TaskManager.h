#pragma once
#include <iostream>
#include <sstream>
#include "List.h"
#include "Task.h"
#include "Assignee.h"
#include "RedBlackTree.h"
#include "AssigneeManager.h"
using namespace std;

class TaskManager
{
private:
	RedBlackTree<Task> tree;
	int fakeid = 0;
	int totalTasks = 0;
public:
	void addTask(const Task& t) {
		const Task updatedTask = Task(t.getId(), t.getDescription(), t.getPriority(), t.getAssignee(), ++fakeid);
		Node<Task>* existing = tree.search(t.getId());
		if (existing && !(existing->isNil())) {
			return;
		}
		tree.insertNode(t, 'p');
		totalTasks++;
	}
	void printTasks(stringstream& ss) {
		tree.displayTask(ss);
	}
	void completeTask(const int taskId) {
		Node<Task>* res = tree.search(taskId);
		if (!res->isNil()) {
			res->data.setStatus('c');
		}
	}
	Task findHighestPriorityTask() {
		return tree.findMaxPriority();
	}
	void findTaskByAssignee(stringstream& ss, const string& assignee, const string& assigneeName) {
		ArrayBasedList<Task> list;
		tree.getAllTasks(list);
		for (int i = 0; i < list.getSize(); i++) {
			if (list[i].getAssignee() == assignee) {
				Task t = list[i];
				ss << t << ", Assignee: " << assigneeName << " (" << assignee << ")\n";
			}
		}
	}
	void deleteTask(int taskId, AssigneeManager& AM) {
		Node<Task>* existing = tree.search(taskId);
		if (!existing || existing->isNil()) {
			return;
		}
		AM.disAssignTask(existing->data, existing->data.getAssignee());
		tree.deleteTask(taskId);
		totalTasks--;
		Node<Task>* node = tree.search(taskId);
		if (!node || node->tree->isNil()) tree.deleteTask(taskId);
	}
	void updateTaskPriority(const int taskId, const int newPriority, AssigneeManager& AM) {
		Task task = tree.search(taskId)->data;
		task.setPriority(newPriority);
		deleteTask(taskId, AM);
		AM.assignTask(task, task.getAssignee());
		addTask(task);
	}
	void clearCompletedTasks(AssigneeManager& AM) {
		ArrayBasedList<Task> list;
		tree.getAllTasks(list);
		for (int i = 0; i < list.getSize(); i++) {
			if (list[i].isCompleted()) {
				deleteTask(list[i].getId(), AM);
			}
		}
	}
	void displayAllCompleted(stringstream& ss, AssigneeManager& AM) {
		ArrayBasedList<Task> list;
		tree.getAllTasks(list);
		for (int i = 0; i < list.getSize(); i++) {
			if (list[i].isCompleted()) {
				Task t = list[i];
				Assignee assignee = AM.getAssigneeById(t.getAssignee());
				ss << t << ", Assignee: " << assignee.getFname() << " (" << assignee.getId() << ")\n";
			}
		}
	}
	void searchForTaskByPriorityRange(int p1, int p2, stringstream& ss, AssigneeManager& AM) {
		ArrayBasedList<Task> list;
		tree.getAllTasks(list);
		for (int i = 0; i < list.getSize(); i++) {
			if (list[i].getPriority() >= p1 && list[i].getPriority() <= p2) {
				Task t = list[i];
				Assignee assignee = AM.getAssigneeById(t.getAssignee());
				ss << t << ", Assignee: " << assignee.getFname() << " (" << assignee.getId() << ")\n";
			}
		}
	}
	void showAllTasks(stringstream& ss, AssigneeManager& AM) {
		ArrayBasedList<Task> list;
		tree.getAllTasks(list);
		for (int i = 0; i < list.getSize(); i++) {
			Task task = list[i];
			Assignee assignee = AM.getAssigneeById(task.getAssignee());
			ss << task << ", Assignee: " << assignee.getFname() << " (" << assignee.getId() << ")\n";
		}
	}


	int getTotalTasks() {
		return totalTasks;
	}
	
	// some helper functions for me;
	void del(int taskId) {
		Node<Task>* existing = tree.search(taskId);
		if (!existing || existing->isNil()) {
			return;
		}
		tree.deleteTask(taskId);
		totalTasks--;
		Node<Task>* node = tree.search(taskId);
		if (!node || node->tree->isNil()) tree.deleteTask(taskId);
	}
	void display (stringstream& ss) {
		ArrayBasedList<Task> list;
		tree.getAllTasks(list);
		for (int i = 0; i < list.getSize(); i++) {
			Task task = list[i];
			ss << task << '\n';
		}
	}
	void updatep(const int taskId, const int newPriority) {
		Task task = tree.search(taskId)->data;
		task.setPriority(newPriority);
		del(taskId);
		addTask(task);
	}
};