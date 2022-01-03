#pragma once
#include <string>

template <class T>
class RBTree {

private:

    Node<T> *_root;
    Node<T> _sentinel;
    size_t  _size;

public:

    RBTree() {
        _sentinel.key = NULL;
        _sentinel.parent = NULL;
        _sentinel.right = &_sentinel;
        _sentinel.left = &_sentinel;
        _sentinel.color = BLACK;
        _root = &_sentinel;
    }
    ~RBTree() {};

    void rotateLeft(Node<T> *x) {
        Node<T> *y = x->right;

        x->right = y->left;const_iterator
        if (y->left != &_sentinel)  y->left->parent = x;
        if (y != &_sentinel) y->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
        } else {
            _root = y;
        }
        y->left = x;
        if ( x != &_sentinel ) x->parent = y;
    }

    void rotateRight(Node<T> *x) {
        Node<T> *y = x->left;

        x->left = y->right;
        if ( y->right != &_sentinel) y->right->parent = x;
        if ( y != &_sentinel ) y->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
        } else {
            _root = y;
        }
        y->right = x;
        if (x != &_sentinel ) x->parent = y;
    }

    void insertFixup(Node<T> *x) {
        while (x != _root && x->parent->color == RED) {
            if (x->parent == x->parent->parent->left) {
                Node<T> *y = x->parent->parent->right;
                if (y->color == RED) {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->right) {
                        x = x->parent;
                        rotateLeft(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rotateRight(x->parent->parent);
                }
            } else {
                Node<T> *y = x->parent->parent->left;
                if (y->color == RED) {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        rotateRight(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rotateLeft(x->parent->parent);
                }
            }
        }
        _root->color = BLACK;
    }

    void deleteFixup(Node<T> *x) {
        while (x != _root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node<T> *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft (x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight (w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    rotateLeft (x->parent);
                    x = _root;
                }
            } else {
                Node<T> *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight (x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == RED) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft (w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight (x->parent);
                    x = _root;
                }
            }
        }
        x->color = BLACK;
    }

    int deleteNode(Node<T> *z) {
        Node<T> *x, *y;

        if (!z || z == &_sentinel) return 0;

        if (z->left == &_sentinel || z->right == &_sentinel) {
            y = z;
        } else {
            y = z->right;
            while (y->left != &_sentinel)
                y = y->left;
        }

        if (y->left != &_sentinel)
            x = y->left;
        else
            x = y->right;

        x->parent = y->parent;
        if (y->parent)
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        else
            _root = x;
        if (y != z) {
            z->key = y->key;
        }

        if (y->color == BLACK)
            deleteFixup (x);
        _sentinel.parent = getLast();
        _sentinel.begin = getBegin();
        _size--;
        delete y;
        return 1;
    }

    Node<T>* getBegin() {
        Node<T>* tmp = _root;
        while (tmp->left != &_sentinel) {
            tmp = tmp->left;
        }
        return tmp;
    }

    Node<T>* getLast() {
        Node<T>* tmp = _root;
        while (tmp->right != &_sentinel) {
            tmp = tmp->right;
        }
        return tmp;
    }

    Node<T>* getEnd() {
        Node<T>* tmp = _root;
        while (tmp->right != &_sentinel) {
            tmp = tmp->right;
        }
        return tmp->right;
    }

};