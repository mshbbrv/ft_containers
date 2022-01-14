#pragma once

namespace ft {

    enum Color { BLACK, RED };

    template<class T>
    struct Node {

        T*          data;
        Node<T>*    begin;
        Node<T>*    parent;
        Node<T>*    right;
        Node<T>*    left;
        Color       color;
        bool        nil;
    };
}