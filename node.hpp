#pragma once

namespace ft {

    enum Color { BLACK, RED };
    enum Direction { RIGHT, LEFT };

    template<class T>
    struct Node {

        Node() : data(new T()), begin(NULL), parent(NULL), right(this),
                    left(this),  color(BLACK), nil(true) {}
        Node(const T& p) : data(new T(p)), begin(NULL), parent(NULL), right
        (this), left(this),  color(BLACK), nil(false) {}
        ~Node() { delete data; }
        T*          data;
        Node<T>*    begin;
        Node<T>*    parent;
        Node<T>*    right;
        Node<T>*    left;
        Color       color;
        bool        nil;
    };
}