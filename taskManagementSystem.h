#pragma once
#include <iostream>
#include <sstream>

#include "Assignee.h"
#include "Task.h"
#include "TaskManager.h"
#include "AssigneeManager.h"

class taskManagementSystem
{
private:
	AssigneeManager AM;
	TaskManager TM;
public:
	// Assignee functions;
	void addAssignee(string fname, string lname, string address, string dob); // adds a new assignee
	void displaybyID(stringstream& ss, const string& id); // display assignee by id
	void displaybyname(stringstream& ss, const string& fname, const string& lname); // display assignee by name
	void AssigneeWithNoTask(stringstream& ss); // display assignee with no tasks
	void ShiftTask(const string& id1, const string& id2); // shift tasks of assignee with id1 to assignee with id2
	void DeleteAssignee(const string& id); // delete the assignee with id -> id.
	void DisplayAssignee(stringstream& ss); // display in order of assignee with respect to ids and show whole assignee
	void AssigneeInOrder(stringstream& ss); // display in order of assignee with respect to ids and in format -> id (color)
	
	
	// Task functions;
	void addTask(const int& taskId, const string& description, const int& priority, const string& assigneeId); // add the task to the system
	void updateTaskPriority(const int& taskId, const int& newPriority); // update the priority of the task with id taskId
	void findHighestPriorityTask(stringstream& ss); // finds the highest priority task
	void findTasksByAssignee(const string& assigneeId, stringstream& ss); // find all tasks of the assignee with the id assigneeId
	void countTotalTasks(stringstream& ss); // finds the total tasks in the system
	void completeTask(const int& taskId); // marks the task with taskId as completed
	void displayCompletedTasks(stringstream& ss); // displays all the completed tasks
	void searchTasksByPriorityRange(const int& p1, const int& p2, stringstream& ss); // finds all the tasks with the priority in the range p1 and p2 inclusive
	void PrintTreeInorder(stringstream& ss); // display the inorder traversal of the tasks with format -> id (color)
	void deleteTask(const int& taskId); // delete the task with the id taskId
	void printTaskQueue(stringstream& ss); // display in order of tasks with respect to priority and show whole task

};

void taskManagementSystem::addAssignee(string fname, string lname, string address, string dob) 
{
	Assignee newAssignee(fname, lname, address, dob);
	AM.addAssignee(newAssignee);
}

void taskManagementSystem::displaybyID(stringstream& ss, const string& id)
{
	Assignee assignee = AM.getAssigneeById(id);
	ss << assignee;
}

void taskManagementSystem::displaybyname(stringstream& ss, const string& fname, const string& lname)
{
	AM.getAssigneeByName(ss, fname, lname);
}

void taskManagementSystem::AssigneeWithNoTask(stringstream& ss)
{
	AM.getAssigneeWithNoTask(ss);
}

void taskManagementSystem::DeleteAssignee(const string& id)
{
	AM.deleteAssignee(id);
}

void taskManagementSystem::DisplayAssignee(stringstream& ss)
{
	AM.getAssignees(ss);
}

void taskManagementSystem::AssigneeInOrder(stringstream& ss)
{
	AM.printAssignees(ss);
}

void taskManagementSystem::addTask(const int& taskId, const string& description, const int& priority, const string& assigneeId)
{
	Task newTask(taskId, description, priority, assigneeId);
	TM.addTask(newTask);
	AM.assignTask(newTask, newTask.getAssignee());
}

void taskManagementSystem::updateTaskPriority(const int& taskId, const int& newPriority)
{
	TM.updateTaskPriority(taskId, newPriority, AM);
}

void taskManagementSystem::printTaskQueue(stringstream& ss)
{
	TM.showAllTasks(ss, AM);
}

void taskManagementSystem::findHighestPriorityTask(stringstream& ss)
{
	Task task = TM.findHighestPriorityTask();
	ss << "Highest Priority Task: ";
	ss << task;
	Assignee assignee = AM.getAssigneeById(task.getAssignee());
	ss << ", Assignee: " << assignee.getFname() << " (" << assignee.getId() << ")\n";
}

void taskManagementSystem::findTasksByAssignee(const string& assigneeId, stringstream& ss)
{
	Assignee assignee = AM.getAssigneeById(assigneeId);
	ss << "Tasks Assigned to \"" << assignee.getFname() << " (" << assigneeId << ")\":\n";
	TM.findTaskByAssignee(ss, assigneeId, assignee.getFname());
}

void taskManagementSystem::countTotalTasks(stringstream& ss)
{
	ss << "Total Tasks in the System: " << TM.getTotalTasks() << "\n";
}

void taskManagementSystem::completeTask(const int& taskId)
{
	TM.completeTask(taskId);
}

void taskManagementSystem::displayCompletedTasks(stringstream& ss)
{
	ss << "Completed Tasks:\n";
	TM.displayAllCompleted(ss, AM);
}

void taskManagementSystem::searchTasksByPriorityRange(const int& p1, const int& p2, stringstream& ss)
{
	ss << "Tasks within Priority Range (" << p1 <<  " to " << p2 << "):\n";
	TM.searchForTaskByPriorityRange(p1, p2, ss, AM);
}

void taskManagementSystem::PrintTreeInorder(stringstream& ss)
{
	TM.printTasks(ss);
}

void taskManagementSystem::deleteTask(const int& taskId)
{
	TM.deleteTask(taskId, AM);
}


