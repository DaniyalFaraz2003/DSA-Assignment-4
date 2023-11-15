#pragma once

#include <iostream>
#include <sstream>
using namespace std;

template<class T>
class ArrayBasedList {
private:
	int size;
	int currentPtr;

	void increaseSize() {
		int n = size;
		size *= 2;
		T* temp = new T[size];
		for (int i = 0; i < n; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
public:
	T* arr;

	ArrayBasedList<T>() {
		size = 5;
		currentPtr = -1;
		arr = new T[size];
	}
	ArrayBasedList<T>(const ArrayBasedList<T>& other) {
		this->size = other.size;
		this->currentPtr = other.currentPtr;
		this->arr = new T[size];
		for (int i = 0; i < getSize(); i++) {
			this->arr[i] = other.arr[i];
		}
	}

	ArrayBasedList<T>& operator=(const ArrayBasedList<T>& other) {
		delete[] this->arr;
		this->size = other.size;
		this->currentPtr = other.currentPtr;
		this->arr = new T[size];
		for (int i = 0; i < getSize(); i++) {
			this->arr[i] = other.arr[i];
		}
		return *this;
	}

	bool empty() {
		return currentPtr == -1;
	}

	void push(T data) {
		if (currentPtr == size - 1) {
			increaseSize();
		}
		currentPtr++;
		arr[currentPtr] = data;
	}

	void popFront() {
		deleteItem(0);
	}

	T front() {
		if (!empty()) return arr[0];
		return T();
	}

	void pop() {
		if (empty()) {
			return;
		}
		currentPtr--;
	}

	T back() {
		return arr[currentPtr];
	}

	void insert(T data, int pos) {
		if ((pos > (currentPtr + 1)) || (pos < 0)) {
			return;
		}
		if (currentPtr == size - 1) {
			increaseSize();
		}
		currentPtr++;
		int i;
		for (i = currentPtr; i > pos; i--) {
			arr[i] = arr[i - 1];
		}
		arr[i] = data;
	}

	int getSize() {
		return currentPtr + 1;
	}

	void deleteItem(int pos) {
		if ((pos > (currentPtr + 1)) || (pos < 0) || empty()) {
			return;
		}
		for (int i = pos; i < currentPtr; i++) {
			arr[i] = arr[i + 1];
		}
		currentPtr--;
	}

	int search(T value) {
		for (int i = 0; i <= currentPtr; i++) {
			if (value == arr[i]) return i;
		}
		return -1;
	}

	friend ostream& operator<<(ostream& out, ArrayBasedList& l) {
		for (int i = 0; i <= l.currentPtr; i++) {
			out << l.arr[i] << " ";
		}
		out << endl;
		return out;
	}

	T operator[](int index) const {
		return arr[index];
	}

	~ArrayBasedList() {
		delete[] arr;
	}
};


class Task
{
private:
    string description, assigneeId;
    bool status; // 0 for not completed 1 for completed
    int priority, id;
    int fakeId;
public:
    Task(int id = 0, string description = "", int priority = 0, string assigneeId = "", int fakeId = 0) {
        this->id = id;
        this->description = description;
        this->priority = priority;
        this->assigneeId = assigneeId;
        this->status = false;
        this->fakeId = fakeId;
    }
    string getDescription() const { return description; }
    int getPriority() const { return priority; }
    string getAssignee() const { return assigneeId; }
    int getId() const { return id; }
    bool getStatus() const { return status; }
    int getFakeId() const { return fakeId; }
    void setAssignee(string assignee) { this->assigneeId = assignee; }
    void setPriority(int p) { priority = p; }
    void setStatus(char c) { if (c == 'c') status = true; else status = false; }
    bool isCompleted() { return status; }

    friend ostream& operator<<(ostream& out, const Task& t) {
        const string completed = t.status ? "Completed" : "Not Completed";
        out << "Task ID: " << t.id << ", Description: " << t.description << ", Priority: " << t.priority;
        return out;
    }

    bool operator==(const Task& other) {
        return this->id == other.id;
    }
    bool operator<(const Task& other) {
        return this->id < other.id;
    }
    bool operator>(const Task& other) {
        return this->id > other.id;
    }
};


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
    void setId(const string& id) {
        this->id = id;
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



template <class T>
class RedBlackTree;

template<class T>
struct Node {
    T data;
    Node* l, * r, * p;
    char c;
    Node<T>(T data, char c) : data(data), c(c), l(nullptr), r(nullptr), p(nullptr) {}
    virtual bool isNil() { return false; }
};
template<>
struct Node<Task> {
    Task data;
    Node* l, * r, * p;
    char c;
    RedBlackTree<Task>* tree;

    Node(Task data, char c) : data(data), c(c), l(nullptr), r(nullptr), p(nullptr), tree(nullptr) {}
    virtual bool isNil() { return false; }

};
template<class T>
struct NIL : public Node<T> {
    NIL(T data, char c) : Node<T>(data, c) {}
    bool isNil() { return true; }

};

template <class T>
class RedBlackTree {
private:
    Node<T>* root;
    void leftRotate(Node<T>* pivot);
    void rightRotate(Node<T>* pivot);
    void restructureInsert(Node<T>* n);
    void restructureDelete(Node<T>* n);
    void moveTree(Node<T>* t1, Node<T>* t2);
    Node<T>* replacementNode(Node<T>* n);
    void inorder(Node<T>* root);
    void getData(Node<T>* root, ArrayBasedList<T>& res);

    //All the specializations
    void inorderAssignee(Node<Assignee>* root, stringstream& ss);
    void inorderTask(Node<Task>* root, stringstream& ss);
    void shiftTask(Node<Task>* root, const string& id1, const string& id2);
    void getTaskData(Node<Task>* root, ArrayBasedList<Task>& res);

public:
    RedBlackTree();
    bool isNil() {
        return root == nullptr || root->isNil();
    }
    void insertNode(T data);
    void deleteNode(T data);
    bool exists(T data);
    void displayInorder();
    Node<T>* search(T data);
    void getTreeData(ArrayBasedList<T>& res);

    // All the specializations are here
    void getAllTasks(ArrayBasedList<Task>& res);
    void deleteTask(int taskId);
    Task findMaxPriority();
    Node<Task>* preOrderSearch(int id);
    void insertNode(const Task& data, char insertFactor);
    void displayAssignee(stringstream& ss);
    void displayTask(stringstream& ss);
    Node<Assignee>* search(string data);
    Node<Task>* search(const int taskId);
    bool exists(string data);
    void shiftTasks(const string id1, const string id2);
};
template<class T>
void RedBlackTree<T>::getData(Node<T>* root, ArrayBasedList<T>& res) {
    if (!root->isNil()) {
        if (root->l) getData(root->l, res);
        res.push(root->data);
        if (root->r) getData(root->r, res);
    }
}
template<class T>
RedBlackTree<T>::RedBlackTree() {
    root = new NIL<T>(T(), 'b');
}
template<class T>
void RedBlackTree<T>::leftRotate(Node<T>* pivot) {
    if (pivot->r == nullptr) return;
    Node<T>* temp = pivot->r;
    pivot->r = temp->l;
    if (temp->l != nullptr) {
        temp->l->p = pivot;
    }
    temp->p = pivot->p;
    if (pivot->p == nullptr) {
        root = temp;
    }
    else if (pivot == pivot->p->l) {
        pivot->p->l = temp;
    }
    else {
        pivot->p->r = temp;
    }
    temp->l = pivot;
    pivot->p = temp;
}
template<class T>
void RedBlackTree<T>::rightRotate(Node<T>* pivot) {
    if (pivot->l == nullptr) return;
    Node<T>* temp = pivot->l;
    pivot->l = temp->r;
    if (temp->r != nullptr) {
        temp->r->p = pivot;
    }
    temp->p = pivot->p;
    if (pivot->p == nullptr) {
        root = temp;
    }
    else if (pivot == pivot->p->l) {
        pivot->p->l = temp;
    }
    else {
        pivot->p->r = temp;
    }
    temp->r = pivot;
    pivot->p = temp;
}
template<class T>
void RedBlackTree<T>::insertNode(T data) {
    Node<T>* newNode = new Node<T>(data, 'r');
    newNode->l = new NIL<T>(T(), 'b');
    newNode->r = new NIL<T>(T(), 'b');
    Node<T>* prev = nullptr;
    Node<T>* current = root;
    while (!current->isNil()) {
        prev = current;
        if (newNode->data < current->data) {
            current = current->l;
        }
        else {
            current = current->r;
        }
    }
    newNode->p = prev;
    if (prev == nullptr) {
        delete root;
        root = newNode;
    }
    else if (newNode->data < prev->data) {
        delete prev->l;
        prev->l = newNode;
    }
    else {
        delete prev->r;
        prev->r = newNode;
    }
    restructureInsert(newNode);
}
template<>
void RedBlackTree<Task>::getAllTasks(ArrayBasedList<Task>& res)
{
    getTaskData(root, res);
}
template<>
void RedBlackTree<Task>::deleteTask(int taskId)
{
    Node<Task>* n = search(taskId);
    if (n == nullptr || n->isNil()) return;
    if (n->tree && !(n->tree->isNil())) {
        n->tree->deleteTask(taskId);
        if (n->tree->isNil()) {
            deleteTask(n->data.getId());
        }
        return;
    }

    Node<Task>* temp = n;
    char temp_c = temp->c;


    Node<Task>* x;
    if ((n->l)->isNil()) {
        delete n->l;
        x = n->r;
        moveTree(n, n->r);
    }
    else if ((n->r)->isNil()) {
        delete n->r;
        x = n->l;
        moveTree(n, n->l);
    }
    else {
        temp = n->l;
        while (!(temp->r)->isNil()) temp = temp->r;
        temp_c = temp->c;
        x = temp->l;
        delete temp->r;
        if (temp->p == n) {
            x->p = temp;
        }
        else {
            moveTree(temp, temp->l);
            temp->l = n->l;
            temp->l->p = temp;
        }

        moveTree(n, temp);
        temp->r = n->r;
        temp->r->p = temp;
        temp->c = n->c;

        delete n;
    }

    if (temp_c == 'b') {
        restructureDelete(x);
    }
}
template<>
Task RedBlackTree<Task>::findMaxPriority()
{
    if (root == nullptr) return Task();
    Node<Task>* current = root;
    while (!(current->l)->isNil()) {
        current = current->l;
    }
    if (current->tree) {
        current = current->tree->root;
        while (!(current->l)->isNil()) {
            current = current->l;
        }
    }
    return current->data;
}
template<>
Node<Task>* RedBlackTree<Task>::preOrderSearch(int id)
{
    if (root == nullptr) return nullptr;
    ArrayBasedList<Node<Task>*> st;
    st.push(root);
    while (!st.empty()) {
        Node<Task>* node = st.back();
        if (id == node->data.getId()) return node;
        else {
            st.pop();
            if (!(node->r->isNil())) {
                st.push(node->r);
            }
            if (!(node->l->isNil())) {
                st.push(node->l);
            }
        }
    }
    return nullptr;
}
template<>
Node<Task>* RedBlackTree<Task>::search(const int taskId)
{
    if (root == nullptr || root->isNil()) return nullptr;
    ArrayBasedList<Node<Task>*> st;
    st.push(root);
    while (!st.empty()) {
        Node<Task>* node = st.back();
        if (node->tree && !(node->tree->root->isNil())) {
            Node<Task>* innerNode = node->tree->preOrderSearch(taskId);
            if (innerNode && !(innerNode->isNil())) return node;
        }
        else if (node->data.getId() == taskId) return node;
        st.pop();
        if (!(node->r->isNil())) {
            st.push(node->r);
        }
        if (!(node->l->isNil())) {
            st.push(node->l);
        }
    }
    return nullptr;
}
template<>
void RedBlackTree<Task>::insertNode(const Task& data, char insertFactor) {
    Node<Task>* newNode = new Node<Task>(data, 'r');
    newNode->l = new NIL<Task>(Task(), 'b');
    newNode->r = new NIL<Task>(Task(), 'b');
    Node<Task>* prev = nullptr;
    Node<Task>* current = root;
    while (!current->isNil()) {
        prev = current;
        if (data.getPriority() < current->data.getPriority()) {
            current = current->l;
        }
        else if (data.getPriority() > current->data.getPriority()) {
            current = current->r;
        }
        else {
            if (current->tree != nullptr) {
                current->tree->insertNode(data);
            }
            else {
                current->tree = new RedBlackTree<Task>;
                current->tree->insertNode(current->data);
                current->tree->insertNode(data);
            }
            return;
        }
    }
    newNode->p = prev;
    if (prev == nullptr) {
        delete root;
        root = newNode;
    }
    else if (newNode->data.getPriority() < prev->data.getPriority()) {
        delete prev->l;
        prev->l = newNode;
    }
    else {
        delete prev->r;
        prev->r = newNode;
    }
    restructureInsert(newNode);
}
template<class T>
void RedBlackTree<T>::restructureInsert(Node<T>* n) {
    if (root == n) {
        n->c = 'b';
        return;
    }
    while (n->p && n->p->c == 'r') {
        if (n->p == n->p->p->l) {
            Node<T>* u = n->p->p->r;
            if (u->c == 'r') {
                n->p->c = 'b';
                u->c = 'b';
                n->p->p->c = 'r';
                n = n->p->p;
            }
            else if (n == n->p->r) {
                n = n->p;
                leftRotate(n);
            }
            else {
                n->p->c = 'b';
                n->p->p->c = 'r';
                rightRotate(n->p->p);
            }
        }
        else {
            Node<T>* u = n->p->p->l;
            if (u->c == 'r') {
                n->p->c = 'b';
                u->c = 'b';
                n->p->p->c = 'r';
                n = n->p->p;
            }
            else if (n == n->p->l) {
                n = n->p;
                rightRotate(n);
            }
            else {
                n->p->c = 'b';
                n->p->p->c = 'r';
                leftRotate(n->p->p);
            }
        }
    }
    root->c = 'b';
}
template<class T>
void RedBlackTree<T>::moveTree(Node<T>* t1, Node<T>* t2) {
    if (t1->p == nullptr) {
        root = t2;
    }
    else if (t1 == t1->p->l) {
        t1->p->l = t2;
    }
    else {
        t1->p->r = t2;
    }
    if (t2) t2->p = t1->p;
}
template<class T>
Node<T>* RedBlackTree<T>::replacementNode(Node<T>* n) {
    Node<T>* y = nullptr;
    if (n->l != nullptr)
    {
        y = n->l;
        while (y->r != nullptr)
            y = y->r;
    }
    else
    {
        y = n->r;
        while (y->l != nullptr)
            y = y->l;
    }
    return y;
}
template<class T>
void RedBlackTree<T>::deleteNode(T data) {
    Node<T>* n = search(data);
    if (n->isNil()) return;

    Node<T>* temp = n;
    char temp_c = temp->c;


    Node<T>* x;
    if ((n->l)->isNil()) {
        delete n->l;
        x = n->r;
        moveTree(n, n->r);
    }
    else if ((n->r)->isNil()) {
        delete n->r;
        x = n->l;
        moveTree(n, n->l);
    }
    else {
        temp = n->l;
        while (!(temp->r)->isNil()) temp = temp->r;
        temp_c = temp->c;
        x = temp->l;
        delete temp->r;
        if (temp->p == n) {
            x->p = temp;
        }
        else {
            moveTree(temp, temp->l);
            temp->l = n->l;
            temp->l->p = temp;
        }

        moveTree(n, temp);
        temp->r = n->r;
        temp->r->p = temp;
        temp->c = n->c;

        delete n;
    }

    if (temp_c == 'b') {
        restructureDelete(x);
    }

}
template<class T>
void RedBlackTree<T>::restructureDelete(Node<T>* node) {
    while (node != root && node->c == 'b') {
        if (node == node->p->l) {
            Node<T>* s = node->p->r;
            if (s->c == 'r') {
                s->c = 'b';
                node->p->c = 'r';
                leftRotate(node->p);
                s = node->p->r;
            }

            if (s->l->c == 'b' && s->r->c == 'b') {
                s->c = 'r';
                node = node->p;
            }
            else {
                if (s->r->c == 'b') {
                    s->l->c = 'b';
                    s->c = 'r';
                    rightRotate(s);
                    s = node->p->r;
                }

                s->c = node->p->c;
                node->p->c = 'b';
                s->r->c = 'b';
                leftRotate(node->p);
                node = root;
            }
        }
        else {
            Node<T>* s = node->p->l;
            if (s->c == 'r') {
                s->c = 'b';
                node->p->c = 'r';
                rightRotate(node->p);
                s = node->p->l;
            }

            if (s->r->c == 'b' && s->l->c == 'b') {
                s->c = 'r';
                node = node->p;
            }
            else {
                if (s->l->c == 'b') {
                    s->r->c = 'b';
                    s->c = 'r';
                    leftRotate(s);
                    s = node->p->l;
                }

                s->c = node->p->c;
                node->p->c = 'b';
                s->l->c = 'b';
                rightRotate(node->p);
                node = root;
            }
        }
    }
    node->c = 'b';
}
template<class T>
Node<T>* RedBlackTree<T>::search(T data) {
    Node<T>* current = root;
    while (!current->isNil()) {
        if (data > current->data) {
            current = current->r;
        }
        else if (data < current->data) {
            current = current->l;
        }
        else {
            return current;
        }
    }
    return current;
}
template<class T>
inline void RedBlackTree<T>::getTreeData(ArrayBasedList<T>& res)
{
    getData(root, res);
}
template<>
inline void RedBlackTree<Assignee>::displayAssignee(stringstream& ss)
{
    inorderAssignee(root, ss);
}
template<>
inline void RedBlackTree<Task>::displayTask(stringstream& ss) {
    inorderTask(root, ss);
}
template<>
Node<Assignee>* RedBlackTree<Assignee>::search(string data) {
    Node<Assignee>* current = root;
    while (!current->isNil()) {
        if (current->data < data) {
            current = current->r;
        }
        else if (current->data > data) {
            current = current->l;
        }
        else {
            return current;
        }
    }
    return current;
}
template<class T>
bool RedBlackTree<T>::exists(T data) {
    Node<T>* res = search(data);
    return !(res->isNil());
}
template<>
bool RedBlackTree<Assignee>::exists(string data) {
    Node<Assignee>* res = search(data);
    return !(res->isNil());
}
template<>
inline void RedBlackTree<Task>::shiftTasks(const string id1, const string id2)
{
    shiftTask(root, id1, id2);
}
template<>
inline void RedBlackTree<Task>::shiftTask(Node<Task>* root, const string& id1, const string& id2)
{
    if (!root->isNil()) {
        if (!(root->l)->isNil()) shiftTask(root->l, id1, id2);
        if (root->tree) {
            root->tree->shiftTask(root->tree->root, id1, id2);
        }
        else {
            if (root->data.getAssignee() == id1) root->data.setAssignee(id2);
        }
        if (!(root->r)->isNil()) shiftTask(root->r, id1, id2);
    }
}
template<class T>
void RedBlackTree<T>::inorder(Node<T>* root) {
    if (!root->isNil()) {
        if (!(root->l)->isNil()) inorder(root->l);
        string color = root->c == 'r' ? "red" : "black";
        cout << root->data << " (" << color << ")\n";
        if (!(root->r)->isNil()) inorder(root->r);
    }
}
template<>
void RedBlackTree<Assignee>::inorderAssignee(Node<Assignee>* root, stringstream& ss) {
    if (!root->isNil()) {
        if (!(root->l)->isNil()) inorderAssignee(root->l, ss);
        string color = root->c == 'r' ? "red" : "black";
        ss << root->data.getId() << " (" << color << ")\n";
        if (!(root->r)->isNil()) inorderAssignee(root->r, ss);
    }
}
template<>
void RedBlackTree<Task>::inorderTask(Node<Task>* root, stringstream& ss) {
    if (!root->isNil()) {
        if (!(root->l)->isNil()) inorderTask(root->l, ss);
        if (root->tree) {
            root->tree->inorderTask(root->tree->root, ss);
        }
        else {
            string color = root->c == 'r' ? "red" : "black";
            ss << root->data.getId() << " (" << color << ")\n";
        }
        if (!(root->r)->isNil()) inorderTask(root->r, ss);
    }
}
template<>
void RedBlackTree<Task>::getTaskData(Node<Task>* root, ArrayBasedList<Task>& res)
{
    if (!root->isNil()) {
        if (!(root->l)->isNil()) getTaskData(root->l, res);
        if (root->tree) {
            root->tree->getTaskData(root->tree->root, res);
        }
        else {
            res.push(root->data);
        }
        if (!(root->l)->isNil()) getTaskData(root->r, res);
    }
}
template<class T>
void RedBlackTree<T>::displayInorder() {
    inorder(root);
}

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
            if (list[i].isCompleted()) continue;
            Assignee assignee = AM.getAssigneeById(task.getAssignee());
            ss << task << ", Assignee: " << assignee.getFname() << " (" << assignee.getId() << ")\n";
        }
    }

    void shiftTasks(const string& id1, const string& id2) {
        tree.shiftTasks(id1, id2);
    }

    int getTotalTasks() {
        return totalTasks;
    }

    // some helper functions for me;
    // these are just for testing the class and functionality
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
    void display(stringstream& ss) {
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
void taskManagementSystem::ShiftTask(const string& id1, const string& id2)
{
    TM.shiftTasks(id1, id2);
    AM.shiftTasks(id1, id2);
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
    ss << "Tasks within Priority Range (" << p1 << " to " << p2 << "):\n";
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
