#include "RBTree.h"

RBTree::RBTree() {
    NIL = new Node{0, BLACK, nullptr, nullptr, nullptr};
    NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
}
RBTree::~RBTree() {
    destroy(root);
    delete NIL;
}
void RBTree::destroy(Node* x) {
    if (x == NIL) return;
    destroy(x->left);
    destroy(x->right);
    delete x;
}
RBTree::Node* RBTree::newNode(int key) {
    Node* n = new Node{key, RED, NIL, NIL, NIL};
    return n;
}
void RBTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}
void RBTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}
void RBTree::insert(int key) {
    Node* z = newNode(key);
    Node* y = NIL;
    Node* x = root;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else if (z->key > x->key) x = x->right;
        else {
            delete z;
            return;
        }
    }
    z->parent = y;
    if (y == NIL) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = NIL;
    z->color = RED;
    insertFixup(z);
}
void RBTree::insertFixup(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right; 
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left; 
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
    root->parent = NIL;
}
RBTree::Node* RBTree::findNode(int key) const {
    Node* x = root;
    while (x != NIL) {
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else return x;
    }
    return NIL;
}
bool RBTree::search(int key) const {
    return findNode(key) != NIL;
}
void RBTree::transplant(Node* u, Node* v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}
RBTree::Node* RBTree::treeMinimum(Node* x) const {
    while (x->left != NIL) x = x->left;
    return x;
}
RBTree::Node* RBTree::treeMaximum(Node* x) const {
    while (x->right != NIL) x = x->right;
    return x;
}
std::optional<int> RBTree::minimum() const {
    if (root == NIL) return std::nullopt;
    return treeMinimum(root)->key;
}

RBTree::Node* RBTree::successor(Node* x) const {
    if (x->right != NIL) return treeMinimum(x->right);

    Node* y = x->parent;
    while (y != NIL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}
bool RBTree::erase(int key) {
    Node* z = findNode(key);
    if (z == NIL) return false;
    Node* y = z;
    if (z->left != NIL && z->right != NIL) {
        y = successor(z);                
    }
    Node* x = (y->left != NIL) ? y->left : y->right;  
    x->parent = y->parent;
    if (y->parent == NIL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    if (y != z) {
        z->key = y->key;   
    }
    Color yOriginal = y->color;
    delete y;
    if (yOriginal == BLACK) {
        deleteFixup(x);
    }
    return true;
}
void RBTree::deleteFixup(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

std::optional<int> RBTree::maximum() const {
    if (root == NIL) return std::nullopt;
    return treeMaximum(root)->key;
}
void RBTree::maxColorDFS(Node* x, bool wantRed, std::optional<int>& best) const {
    if (x == NIL) return;
    maxColorDFS(x->left, wantRed, best);
    if ((wantRed && x->color == RED) || (!wantRed && x->color == BLACK)) {
        if (!best.has_value() || x->key > best.value()) best = x->key;
    }
    maxColorDFS(x->right, wantRed, best);
}
std::optional<int> RBTree::maxRed() const {
    if (root == NIL) return std::nullopt;
    std::optional<int> best;
    maxColorDFS(root, true, best);
    return best;
}
std::optional<int> RBTree::maxBlack() const {
    if (root == NIL) return std::nullopt;
    std::optional<int> best;
    maxColorDFS(root, false, best);
    return best;
}
void RBTree::inorderPrint() const {
    inorderPrint(root);
    std::cout << "\n";
}
void RBTree::inorderPrint(Node* x) const {
    if (x == NIL) return;
    inorderPrint(x->left);
    std::cout << x->key << (x->color == RED ? "(R) " : "(B) ");
    inorderPrint(x->right);
}