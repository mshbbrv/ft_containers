#pragma once

#include "iterator.hpp"
#include <limits>
#include <string>
#include <algorithm>

namespace ft {

    template <class Key, class T, class Compare = std::less<Key>, class Alloc =
            std::allocator<ft::pair<const Key, T> > >
    class map {

    public:

        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Alloc allocator_type;
        typedef Compare key_compare;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef const value_type *const_pointer;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef Node<value_type> node_type;
        typedef Node<value_type>* node_pointer;

        typedef ft::map_iterator<node_pointer, value_type>
                iterator;
        typedef ft::map_iterator<const node_pointer, value_type>
                const_iterator;
        typedef ft::reverse_map_iterator<node_pointer, value_type>
                reverse_iterator;
        typedef ft::reverse_map_iterator<const node_pointer, value_type>
                const_reverse_iterator;

        typedef typename allocator_type::template rebind<node_type>::other
                node_allocator;

        class value_compare : public std::binary_function<value_type, value_type, bool> {
        protected:
            key_compare _comp;
            value_compare(key_compare c) : _comp(c) {}
        public:
            bool operator()(const value_type& lhs, const value_type& rhs) const {
                return comp(lhs.first, rhs.first);
            }
        };

    private:

        allocator_type          _alloc;
        key_compare             _comp;
        node_allocator          _alloc_node;
        node_pointer            _root;
        node_type               _sen;
        size_type               _size;

        void _createTree() {

            _sen.data = NULL;
            _sen.begin = NULL;
            _sen.left = &_sen;
            _sen.right = &_sen;
            _sen.parent = NULL;
            _sen.color = BLACK;
            _sen.nil = true;
            _root = &_sen;
        }

        void _rotateLeft(node_pointer x) {
            node_pointer y = x->right;

            x->right = y->left;
            if (!y->left->nil)
                y->left->parent = x;
            if (!y->nil)
                y->parent = x->parent;
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
            if (!x->nil)
                x->parent = y;
        }

        void _rotateRight(node_pointer x) {
            node_pointer y = x->left;

            x->left = y->right;
            if (!y->right->nil)
                y->right->parent = x;
            if (!y->nil)
                y->parent = x->parent;
            if (x->parent) {
                if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
            } else {
                _root = y;
            }
            y->right = x;
            if (!x->nil)
                x->parent = y;
        }

        void _insertFixup(node_pointer x) {
            while (x != _root && x->parent->color == RED) {
                if (x->parent == x->parent->parent->left) {
                    node_pointer y = x->parent->parent->right;
                    if (y->color == RED) {
                        x->parent->color = BLACK;
                        y->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->right) {
                            x = x->parent;
                            _rotateLeft(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        _rotateRight(x->parent->parent);
                    }
                } else {
                    node_pointer y = x->parent->parent->left;
                    if (y->color == RED) {
                        x->parent->color = BLACK;
                        y->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->left) {
                            x = x->parent;
                            _rotateRight(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        _rotateLeft(x->parent->parent);
                    }
                }
            }
            _root->color = BLACK;
        }

        void _deleteFixup(node_pointer x) {
            while (x != _root && x->color == BLACK) {
                if (x == x->parent->left) {
                    node_pointer w = x->parent->right;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        _rotateLeft (x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK && w->right->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            _rotateRight (w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        _rotateLeft (x->parent);
                        x = _root;
                    }
                } else {
                    node_pointer w = x->parent->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        _rotateRight (x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    } else {
                        if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            _rotateLeft (w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->left->color = BLACK;
                        _rotateRight (x->parent);
                        x = _root;
                    }
                }
            }
            x->color = BLACK;
        }

        int _deleteNode(node_pointer z) {
            node_pointer x;
            node_pointer y;

            if (!z || z->nil)
                return 0;

            if (z->left->nil || z->right->nil) {
                y = z;
            } else {
                y = z->right;
                while (!y->left->nil)
                    y = y->left;
            }

            if (!y->left->nil)
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
                delete z->data;
                value_type *p = new value_type(*y->data);
                z->data = p;
            }

            if (y->color == BLACK)
                _deleteFixup (x);

            _sen.parent = _getLast();
            _sen.begin = _getBegin();
            _size--;
            delete y;
            return 1;
        }

        node_pointer _getBegin() {
            node_pointer tmp = _root;
            while (!tmp->left->nil) {
                tmp = tmp->left;
            }
            return tmp;
        }

        node_pointer _getLast() {
            node_pointer tmp = _root;
            while (!tmp->right->nil) {
                tmp = tmp->right;
            }
            return tmp;
        }

        node_pointer _getEnd() const {
            node_pointer tmp = _root;
            while (!tmp->right->nil) {
                tmp = tmp->right;
            }
            return tmp->right;
        }

        void _copyTree(node_pointer t) {
            if (!t->left->nil)
                _copyTree(t->left);
            if (!t->nil)
                insert(*t->data);
            if (!t->right->nil)
                _copyTree(t->right);
        }

        void _clearTree(node_pointer n) {
            if ( n->nil == false ) {
                if ( n->left->nil == false )
                    _clearTree( n->left );
                if ( n->right->nil == false)
                    _clearTree( n->right );
                _alloc.destroy( n->data );
                _alloc.deallocate( n->data, 1 );
                _alloc_node.deallocate( n, 1 );
                _size--;
            }
        }

        ft::pair<iterator, bool> _insertNode(node_pointer hint,
                                             const value_type& value) {
            node_pointer current;
            node_pointer parent;
            node_pointer x;

            current = hint;
            parent = 0;
            while (!current->nil) {
                if (value.first == current->data->first)
                    return ft::make_pair(current, false);
                parent = current;
                current = _comp(value.first, current->data->first) ?
                          current->left : current->right;
            }

            x = _alloc_node.allocate(1);
            x->data = _alloc.allocate(1);
            _alloc.construct(x->data, value);
            x->begin = NULL;
            x->parent = parent;
            x->left = &_sen;
            x->right = &_sen;
            x->color = RED;
            x->nil = false;

            if (parent) {
                if (_comp(value.first, parent->data->first))
                    parent->left = x;
                else
                    parent->right = x;
            } else {
                _root = x;
            }

            _insertFixup(x);

            if (x == _getLast())
                _sen.parent = x;
            if (x == _getBegin())
                _sen.begin = x;
            _size++;
            return ft::make_pair(x, true);
        }

    public:

        //construct
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
                _alloc(alloc), _comp(comp), _size(0) {
            _createTree();
        }

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0):
                _alloc(alloc), _comp(comp), _size(0) {
            _createTree();
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        //copy
        map(const map &x) : _alloc(x._alloc), _comp(x._comp), _size(x._size) {
            _createTree();
            _copyTree(x._root);
        }

        //destroy
        ~map() {
            _clearTree(_root);
        }

        //operator=
        map &operator=(const map &x) {
            if (this != &x) {
                _comp = x._comp;
                _alloc = x._alloc;
                _clearTree(_root);
                _copyTree( x._root );
            }
            return *this;
        }

        // iterators
        iterator begin() { return _getBegin(); }
        const_iterator begin() const { return _getBegin(); }

        iterator end() { return _getEnd(); }
        const_iterator end() const { return _getEnd(); }

        reverse_iterator rbegin() {
            return reverse_iterator(iterator(_getLast())); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(const_iterator(_getLast())); }

        reverse_iterator rend() {
            return reverse_iterator(iterator(_getEnd())); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(const_iterator(_getEnd())); }

        // capacity
        bool empty() const { return _size == 0; };
        size_type size() const { return _size; };
        size_type max_size() const {
            return (std::min((size_type)std::numeric_limits<std::ptrdiff_t>::max(),
                             std::numeric_limits<size_type>::max() /
                             (sizeof(node_type) + sizeof(mapped_type*))));

        }

        // element access
        mapped_type &operator[](const key_type &key) {
            return insert(ft::make_pair(key, T())).first->second;
        }

        // modifiers

        ft::pair<iterator, bool> insert(const value_type &val) {
            return _insertNode(_root, val);
        }

        iterator insert(iterator position, const value_type &val) {
            if (position == end()) {
                return _insertNode(_root, val).first;
            }
            else {
                if (position->first > val.first)
                {
                    iterator prev = position;
                    --prev;
                    while (prev != end() && prev->first >= val.first){
                        --position;
                        --prev;
                    }
                } else if (position->first < val.first) {
                    iterator next = position;
                    ++next;
                    while (next != end() && next->first <= val.first) {
                        ++position;
                        ++next;
                    }
                }
            }
            return _insertNode(position.base(), val).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        void erase(iterator position) {
            iterator tmp = position;
            _deleteNode(tmp.base());
        }
        
        size_type erase(const key_type &k) {
            return _deleteNode(find(k).base());
        }

        void erase(iterator first, iterator last) {
            iterator tmp;

            for (; first != last ;) {
                tmp = first++;
                _deleteNode(tmp.base());
            }
        }

        void swap(map &x) {
            node_pointer tmp = _root;
            _root = x._root;
            x._root = tmp;

            size_t size = _size;
            _size = x._size;
            x._size = size;
        }

        void clear() {
            _clearTree(_root);
            _createTree();
        }

        // observers
        key_compare key_comp() const { return _comp; }
        value_compare value_comp() const { return value_compare(_comp); }

        // operations
        iterator find(const key_type &k) {
            node_pointer current = _root;

            while (!current->nil) {
                if (k == current->data->first)
                    return (current);
                else
                    current = _comp(k, current->data->first) ? current->left :
                            current->right;
            }
            return end();
        }

        const_iterator find(const key_type &k) const {
            node_pointer current = _root;

            while (!current->nil) {
                if (k == current->data->first)
                    return (current);
                else
                    current = _comp(k, current->data->first) ? current->left :
                              current->right;
            }
            return end();
        }

        size_type count(const key_type& k) const {
            return (find(k) == end()) ? 0 : 1;
        }

        iterator lower_bound (const key_type& k) {
            node_pointer current = _root;

            while (!current->nil) {
                if (k == current->data->first)
                    return iterator(current);
                else {
                    if (_comp(k, current->data->first)) {
                        if (!current->left->nil)
                            current = current->left;
                        else
                            return iterator(current);
                    }
                    else {
                        if (!current->right->nil)
                            current = current->right;
                        else
                            return ++iterator(current);
                    }
                }
            }
            return end();
        }
        const_iterator lower_bound (const key_type& k) const {
            node_pointer current = _root;

            while (!current->nil) {
                if (k == current->data.first)
                    return const_iterator(current);
                else {
                    if (_comp(k, current->data.first)) {
                        if (!current->left->nil)
                            current = current->left;
                        else
                            return const_iterator(current);
                    }
                    else {
                        if (!current->right->nil)
                            current = current->right;
                        else
                            return ++const_iterator(current);
                    }
                }
            }
            return end();
        }

        iterator upper_bound (const key_type& k) {
            iterator tmp = lower_bound(k);

            return (tmp == end()) ? tmp : (_comp(k, tmp->first)) ? tmp : ++tmp;
        }
        const_iterator upper_bound (const key_type& k) const {
            const_iterator tmp = lower_bound(k);

            return (tmp == end()) ? tmp : (_comp(k, tmp->first)) ? tmp : ++tmp;
        }

        ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
            return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }
        ft::pair<iterator, iterator> equal_range (const key_type& k) {
            return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        // allocator

        allocator_type get_allocator() const { return _alloc; }

    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs == rhs);
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin()
                                          , rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs < rhs);
    }
}

