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

        typedef ft::node_iterator<node_pointer, value_type>					iterator;
        typedef ft::node_iterator<const node_pointer, value_type>					const_iterator;
        typedef ft::reverse_iterator<iterator>								reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

        typedef typename allocator_type::template rebind<node_pointer>::other
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
        node_pointer            _nil;
        node_pointer            _root;
        size_type               _size;

        void _createNil() {
            _nil = _alloc_node.allocate(1);
            _nil->data = _alloc.allocate(0);
            _nil->parent = NULL;
            _nil->right = &_nil;
            _nil->left = &_nil;
            _nil->color = BLACK;
        }

        void _createTree() {
            _createNil();
            _root = &_nil;
        }

        void _rotateLeft(node_pointer x) {
            node_pointer y = x->right;

            x->right = y->left;
            if (y->left != _nil)
                y->left->parent = x;
            if (y != _nil)
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
            if (x != _nil)
                x->parent = y;
        }

        void _rotateRight(node_pointer x) {
            node_pointer y = x->left;

            x->left = y->right;
            if ( y->right != _nil)
                y->right->parent = x;
            if (y != _nil)
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
            if (x != _nil)
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
                            rotateLeft(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rotateRight(x->parent->parent);
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

        void _deleteFixup(node_pointer x) {
            while (x != _root && x->color == BLACK) {
                if (x == x->parent->left) {
                    node_pointer w = x->parent->right;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        rotateLeft (x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK && w->right->color == RED) {
                        w->color = BLACK;
                        x = x->parent;
                    } else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            rotateRight (w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        rotateLeft (x->parent);
                        x = _root;
                    }
                } else {
                    node_pointer w = x->parent->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        rotateRight (x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK) {
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

        int _deleteNode(node_pointer z) {
            node_pointer x;
            node_pointer y;

            if (!z || z == _nil)
                return 0;

            if (z->left == _nil || z->right == _nil) {
                y = z;
            } else {
                y = z->right;
                while (y->left != _nil)
                    y = y->left;
            }

            if (y->left != _nil)
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
                delete z->pair;
                value_type *p = new value_type(*y->pair);
                z->pair = p;
            }

            if (y->color == BLACK)
                deleteFixup (x);

            _nil->parent = _getLast();
            _size--;
            delete y;
            return 1;
        }

        node_pointer _getBegin() {
            node_pointer tmp = _root;
            while (tmp->left != _nil) {
                tmp = tmp->left;
            }
            return tmp;
        }

        node_pointer _getLast() {
            node_pointer tmp = _root;
            while (tmp->right != _nil) {
                tmp = tmp->right;
            }
            return tmp;
        }

        node_pointer _getEnd() {
            node_pointer tmp = _root;
            while (tmp->right != _nil) {
                tmp = tmp->right;
            }
            return tmp->right;
        }

        void _copyTree(node_pointer t) {
            if (t->left != _nil)
                fillTree(t->left);
            if (t != _nil)
                insert(*t->data);
            if (t->right != _nil)
                fillTree(t->right);
        }

        void _clearTree(node_pointer tmp) {
            if (tmp == _nil)
                return;
            if (tmp->left != _nil)
                clearTree(tmp->left);
            if (tmp->right != _nil)
                clearTree(tmp->right);
            _alloc_node.destroy(tmp);
            _alloc_node.deallocate(tmp, sizeof(node_type));
        }

        ft::pair<iterator, bool> _insertNode(node_pointer hint,
                                             const value_type& value) {
            node_type *current, *parent, *x;

            current = hint;
            parent = 0;
            while (!current->NIL) {
                if (value.first == current->pair->first)
                    return ft::make_pair(current, false);
                parent = current;
                current = _comp(value.first, current->pair->first) ?
                          current->left : current->right;
            }

            x = _alloc_node.allocate(sizeof(node_type));
            x->data = value;
            x->parent = parent;
            x->left = &_nil;
            x->right = &_nil;
            x->color = RED;

            if (parent) {
                if (_comp(value.first, parent->pair->first))
                    parent->left = x;
                else
                    parent->right = x;
            } else {
                _root = x;
            }

            _insertFixup(x);

            if (x == _getLast()) { _nil->parent = x; }
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
        map(const map &x) : _alloc(x._alloc), _comp(x._comp),
        _root(NULL), _size(x._size) {
            _copyTree(x._root);
        }

        //destroy
        virtual ~map() {
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
            return (std::min((size_type) std::numeric_limits<std::ptrdiff_t>::max(),
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
            return insertNode(position.base(), val).first;
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

            while (current != _nil) {
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

            while (current != _nil) {
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

            while (current != _nil) {
                if (k == current->data->first)
                    return iterator(current);
                else {
                    if (_comp(k, current->data->first)) {
                        if (current->left != _nil)
                            current = current->left;
                        else
                            return iterator(current);
                    }
                    else {
                        if (current->right != _nil)
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

            while (current != _nil) {
                if (k == current->data.first)
                    return const_iterator(current);
                else {
                    if (_comp(k, current->data.first)) {
                        if (current->left != _nil)
                            current = current->left;
                        else
                            return const_iterator(current);
                    }
                    else {
                        if (current->right != _nil)
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