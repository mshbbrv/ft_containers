#pragma once

#include "Vector.hpp"

namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack {

    public:
        typedef	Container									container_type;
        typedef typename Container::value_type				value_type;
        typedef typename Container::size_type				size_type;

        explicit stack(const Container &cont = Container()) : _container(cont)
        {}
        stack(const stack &x) : _container (x._container) {};
        ~stack() {};
        stack& operator=(const stack &x) {
            if (this != &x)
                _container = x._container;
            return *this;
        }
        bool empty() const { return _container.empty(); }
        size_type size() const { return _container.size(); }
        value_type top()	{ return _container.back(); }
        const value_type top() const	{ return _container.back(); }
        void push(const value_type &value) { _container.push_back(value); }
        void pop() { _container.pop_back(); }

    private:
        container_type _container;

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