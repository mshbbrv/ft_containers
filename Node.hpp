#pragma once

namespace ft {

    enum Color { BLACK, RED };
    enum Direction { RIGHT, LEFT };

    template<class T>
    struct Node {

        T*          data;
        Node<T>*    parent;
        Node<T>*    right;
        Node<T>*    left;
        Color       color;
    };
}