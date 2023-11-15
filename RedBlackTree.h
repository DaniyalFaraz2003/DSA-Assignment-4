#pragma once

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include "Assignee.h"
#include "Task.h"
#include "List.h"
using namespace std;

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
    while (!(current -> l) -> isNil()) {
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

#endif // RED_BLACK_TREE_H