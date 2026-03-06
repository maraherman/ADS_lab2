#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <optional>

class RBTree {
public:
    RBTree();
    ~RBTree();
    void insert(int key);
    bool erase(int key);
    bool search(int key) const;
    std::optional<int> minimum() const;
    std::optional<int> maximum() const;
    std::optional<int> maxRed() const;
    std::optional<int> maxBlack() const;
    void inorderPrint() const;

private:
    enum Color { RED, BLACK };
    struct Node {
        int key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
    };
    Node* root;
    Node* NIL; 
    void destroy(Node* x);
    Node* newNode(int key);
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void insertFixup(Node* z);
    void transplant(Node* u, Node* v);
    Node* treeMinimum(Node* x) const;
    Node* treeMaximum(Node* x) const;
    Node* successor(Node* x) const;
    Node* findNode(int key) const;
    void deleteFixup(Node* x);
    void inorderPrint(Node* x) const;
    void maxColorDFS(Node* x, bool wantRed, std::optional<int>& best) const;
};

#endif