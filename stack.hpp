#pragma once

#include "vector.hpp"

namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack {

    public:
        typedef	Container									container_type;
        typedef typename Container::value_type				value_type;
        typedef typename Container::size_type				size_type;

        explicit stack(const Container &cont = Container()) : c(cont) {}
        stack(const stack &x) : c (x.c) {};
        ~stack() {};
        stack& operator=(const stack &x) {
            if (this != &x)
                c = x.c;
            return *this;
        }
        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        value_type top()	{ return c.back(); }
        const value_type top() const	{ return c.back(); }
        void push(const value_type &value) { c.push_back(value); }
        void pop() { c.pop_back(); }

    protected:
        container_type c;

    };

    template <class T, class Container>
    bool operator==(const stack<T,Container> &lhs, const stack<T,Container>
            &rhs)
    { return lhs._container == rhs._container; }

    template <class T, class Container>
    bool operator!=(const stack<T,Container> &lhs, const stack<T,Container>
            &rhs)
    { return lhs._container != rhs._container; }

    template <class T, class Container>
    bool operator<=(const stack<T,Container> &lhs,
            const stack<T,Container> &rhs)
    { return lhs._container <= rhs._container; }

    template <class T, class Container>
    bool operator>=(const stack<T,Container> &lhs,
            const stack<T,Container> &rhs)
    { return lhs._container >= rhs._container; }

    template <class T, class Container>
    bool operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    { return lhs._container < rhs._container; }

    template <class T, class Container>
    bool operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
    { return lhs._container > rhs._container; }
}