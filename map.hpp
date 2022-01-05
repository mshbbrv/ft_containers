#pragma once

#include "iterator.hpp"

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
        typedef value_type *pointer;
        typedef value_type &reference;
        typedef const value_type *const_pointer;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef map_iterator<value_type> iterator;
        typedef const_map_iterator<value_type> const_iterator;
        typedef map_reverse_iterator<value_type> reverse_iterator;
        typedef map_reverse_iterator<const value_type> const_reverse_iterator;

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

        typename allocator_type::template rebind<Node<value_type>>::other _alloc_node;
        allocator_type      _alloc_value;
        key_compare         _comp;
        Node<value_type>*   _root;
        size_type           _size;
        Node<value_type>*   _end;
        Node<value_type>*   _begin;

        void _initTree() {
            _end = _alloc_node.allocate(1);
            _end->parent = NULL;
            _end->left = NULL;
            _end->right = NULL;
            _end->data = _alloc_value.allocate(0);
            _end->color = BLACK;
            _begin = _alloc_node.allocate(1);
            _begin->parent = NULL;
            _begin->left = NULL;
            _begin->right = NULL;
            _begin->data = _alloc_value.allocate(0);
            _begin->color = BLACK;
        }

        Node<value_type>* _createNode(value_type data) {
            Node<value_type>* newNode = _alloc_node.allocate(1);
            newNode->parent = NULL;
            newNode->right = NULL;
            newNode->left = NULL;
            newNode->color = RED;
            newNode->data = _alloc_value.allocate(1);
            _alloc_value.construct(newNode->data, data);
            _size++;
            return newNode;
        }

        void _deleteNode(Node<value_type>* node) {
            _alloc_value.destroy(node->data);
            _alloc_value.deallocate(node->data, 1);
            _alloc_node.deallocate(node, 1);
            _size--;
        }

        Node<value_type>* _getMax(Node<value_type>* node) {
            if (node && node->right)
                return _getMax(node->right);
            return (node);
        }

        Node<value_type>* _getMin(Node<value_type>* node) {
            if ( node && node->left )
                return _getMin( node->left );
            return (node);
        }

        Node<value_type>* _getUncle(Node<value_type>* node) {
            Node<value_type>* grandParent = getGrandParent(node);
            if (!grandParent)
                return NULL;
            if (_isOnLeft(node->parent))
                return grandParent->right;
            else
                return grandParent->left;
        }

        Node<value_type>* _getGrandParent(Node<value_type>* node) {
            if (node && node->parent)
                return node->parent->parent;
            return NULL;
        }

        void _relinkTreeEnd() {
            if (!_size)
                return;
            Node<value_type>* min = _getMin(_root);
            Node<value_type>* max = _getMax(_root);
            min->left = _begin;
            max->right = _end;
            _begin->parent = min;
            _end->parent = max;
        }

        void _rotation(Node<value_type>* node, Direction direction) {
            if (direction == LEFT) {
                Node<value_type>* pivot = node->right;
                node->right = pivot->left;
                if (pivot->left)
                    pivot->left->parent = node;
                pivot->parent = node->parent;
                if (!node->parent)
                    _root = pivot;
                else if (node == node->parent->left)
                    node->parent->left = pivot;
                else
                    node->parent->right = pivot;
                pivot->left = node;
                node->parent = pivot;
            }
            else if (direction == RIGHT) {
                Node<value_type>* pivot = node->left;
                node->left = pivot->right;
                if (pivot->right)
                    pivot->right->parent = node;
                pivot->parent = node->parent;
                if (!node->parent)
                    _root = pivot;
                else if (node == node->parent->left)
                    node->parent->left = pivot;
                else
                    node->parent->right = pivot;
                pivot->right = node;
                node->parent = pivot;
            }
        }

        bool _isOnLeft(Node<value_type>* node) {
            return node == node->parent->left;
        }

        void _standartBstInsertion(value_type val) {
            Node<value_type>* elem = _createNode(val);
            Node<value_type>* parent = nullptr;
            Node<value_type>* tmp = _root;
            while (tmp) {
                parent = tmp;
                if (!_comp(val.first, tmp->data->first))
                    tmp = tmp->right;
                else
                    tmp = tmp->left;
            }
            elem->parent = parent;
            if (!parent) {
                _root = elem;
                _root->color = BLACK;
                return;
            }
            else if (_comp(parent->data->first, val.first))
                parent->right = elem;
            else
                parent->left = elem;
            if (!elem->parent->parent)
                return;
            _rbInsertion(elem);
        }

        void _rbInsertion(Node<value_type>* tmp) {
            Node<value_type>* uncle;
            while (tmp->parent && tmp->parent->color == RED) {
                if (tmp->parent == tmp->parent->parent->right) {
                    uncle = tmp->parent->parent->left;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        tmp->parent->color = BLACK;
                        tmp->parent->parent->color = RED;
                        tmp = tmp->parent->parent;
                    }
                    else {
                        if (tmp == tmp->parent->left) {
                            tmp = tmp->parent;
                            _rotation(tmp, RIGHT);
                        }
                        tmp->parent->color = BLACK;
                        tmp->parent->parent->color = RED;
                        _rotation(tmp->parent->parent, LEFT);
                    }
                }
                else {
                    uncle = tmp->parent->parent->right;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        tmp->parent->color = BLACK;
                        tmp->parent->parent->color = RED;
                        tmp = tmp->parent->parent;
                    }
                    else {
                        if (tmp == tmp->parent->right) {
                            tmp = tmp->parent;
                            _rotation(tmp, LEFT);
                        }
                        tmp->parent->color = BLACK;
                        tmp->parent->parent->color = RED;
                        _rotation(tmp->parent->parent, RIGHT);
                    }
                }
                if (tmp == _root)
                    break;
            }
            _root->color = BLACK;
        }

        void _unlink() {
            if (_begin->parent)
                _begin->parent->left = nullptr;
            if (_end->parent)
                _end->parent->right = nullptr;
        }

        void _transplant(Node<value_type>* u, Node<value_type>* v) {
            if (u && !u->parent)
                _root = v;
            else if (_isOnLeft(u))
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v)
                v->parent = u->parent;
        }

        void _deleteFromTree(Node<value_type>* node) {
            Node<value_type>* y(node);
            Node<value_type>* x;
            int savedColor = y->color;
            if (!node->left) {
                x = node->right;
                _transplant(node, node->right);
            }
            else if (!node->right) {
                x = node->left;
                _transplant(node, node->left);
            }
            else {
                y = _getMin(node->right);
                savedColor = y->color;
                x = y->right;
                if (node == y->parent) {
                    if (x)
                        x->parent = y;
                }
                else {
                    _transplant(y, y->right);
                    y->right = node->right;
                    y->right->parent = y;
                }
                _transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
                y->color = node->color;
            }
            if (savedColor == BLACK)
                _fixTreeAfterDeletion(x);
            _deleteNode(node);
        }

        void _fixTreeAfterDeletion(Node<value_type>* x) {
            if (!x)
                return;
            while (x != _root and x->color == BLACK) {
                if (x == x->parent->left) {
                    Node<value_type>* w = x->parent->right;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        _rotation(x->parent, LEFT);
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK and w->right->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    }
                    else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            _rotation(w, RIGHT);
                            w = x->parent->right;
                        }
                        else {
                            w->color = x->parent->color;
                            w->parent->color = BLACK;
                            w->right->color = BLACK;
                            _rotation(x->parent, LEFT);
                            x = _root;
                        }
                    }
                }
                else {
                    Node<value_type>* w = x->parent->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->parent->color = RED;
                        _rotation(x->parent, RIGHT);
                        w = x->parent->left;
                    }
                    if (w->right->color == BLACK and w->left->color == BLACK) {
                        w->color = RED;
                        x = x->parent;
                    }
                    else {
                        if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            _rotation(w, LEFT);
                            w = x->parent->left;
                        }
                        else {
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->left->color = BLACK;
                            _rotation(x->parent, RIGHT);
                            x = _root;
                        }
                    }
                }
            }
            x->color = BLACK;
        }

    public:

        //construct
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
                _alloc_value(alloc), _comp(comp), _root(nullptr), _size(0) {
            _initTree();
        };

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0):
                _alloc_value(alloc), _comp(comp), _root(nullptr), _size(0) {
            _initTree();
            insert(first, last);
        };
        //copy
        map(const map &x) : _alloc_value(x._alloc_value), _comp(x._comp),
        _root(NULL), _size(x._size) {
            if (this == &x)
                return;
            *this = x;
        }

        //destroy
        virtual ~map() {
            clear();
            _alloc_value.destroy(_end->data);
            _alloc_value.destroy(_begin->data);
            _alloc_value.deallocate(_begin->data, 1);
            _alloc_value.deallocate(_end->data, 1);
            _alloc_node.destroy(_end);
            _alloc_node.destroy(_begin);
            _alloc_node.deallocate(_begin, 1);
            _alloc_node.deallocate(_end, 1);
        }

        //operator=
        map &operator=(const map &x) {
            clear();
            insert(x.begin(), x.end());
            return *this;
        }

        // iterators
        iterator begin() {
            if (!_size)
                return iterator(_end);
            return iterator(_begin->parent);
        }
        const_iterator begin() const {
            if (!_size)
                return const_iterator(_end);
            return const_iterator(_begin->parent);
        }

        iterator end() { return iterator(_end); }
        const_iterator end() const { return const_iterator(_end); }

        reverse_iterator rbegin() {
            if (!_size)
                return reverse_iterator(_begin);
            return reverse_iterator(_end->parent);
        }
        const_reverse_iterator rbegin() const {
            if (!_size)
                return const_reverse_iterator(_begin);
            return const_reverse_iterator(_end->parent);
        }

        reverse_iterator rend() { return reverse_iterator(_begin); };
        const_reverse_iterator rend() const { return const_reverse_iterator(_begin); };

        // capacity
        bool empty() const { return _size == 0; };
        size_type size() const { return _size; };
        size_type max_size() const { return _alloc_value.max_size() / 2; };

        // element access
        mapped_type &operator[](const key_type &key) {
            return insert(ft::make_pair(key, mapped_type())).first->second;
        }

        // modifiers

        ft::pair<iterator, bool> insert(const value_type &val) {
            iterator found = find(val.first);
            if (found != end()) {
                return ft::make_pair<iterator, bool>(found, false);
            }
            _unlink();
            _standartBstInsertion(val);
            _relinkTreeEnd();
            found = find(val.first);
            return ft::make_pair<iterator, bool>(found, true);
        }

        iterator insert(iterator position, const value_type &val) {
            (void) position;
            return insert(val).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) {
            for (; first != last; first++)
                insert(*first);
        }

        void erase(iterator position) {
            erase(position->first);
        }
        
        size_type erase(const key_type &k) {
            Node<value_type>* tmp = _root;
            _unlink();
            while (tmp) {
                if (k == tmp->data->first) {
                    _deleteFromTree(tmp);
                    _relinkTreeEnd();
                    return 1;
                }
                if (_comp(k, tmp->data->first))
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }
            _relinkTreeEnd();
            return 0;
        }

        void erase(iterator first, iterator last) {
            while(first != last){
                erase(first++);
            }
        }

        void swap(map &x) {
            Node<value_type>* tmp = this->_root;
            this->_root = x._root;
            x._root = tmp;

            tmp = this->_begin;
            this->_begin = x._begin;
            x._begin = tmp;

            tmp = this->_end;
            this->_end = x._end;
            x._end = tmp;

            size_t size = this->_size;
            this->_size = x._size;
            x._size = size;
        }

        void clear() {
            while (_size)
                erase(begin());
        }

        // observers
        key_compare key_comp() const { return _comp; }
        value_compare value_comp() const { return value_compare(_comp); }

        // operations
        iterator find(const key_type &k) {
            iterator it = begin();
            for (iterator ite = end(); it != ite && it->first != k; it++);
            return it;
        }
        const_iterator find(const key_type &k) const {
            const_iterator it = begin();
            for (const_iterator ite = end(); it != ite && it->first != k; it++);
            return it;
        }

        size_type count(const key_type& k) const {
            for (iterator it = begin(), ite = end(); it != ite; it++)
                if (it->first == k)
                    return 1;
            return 0;
        }

        iterator lower_bound (const key_type& k) {
            iterator it = begin();
            for (iterator ite = end(); it != ite && _comp(it->first, k); it++);
            return it;
        }
        const_iterator lower_bound (const key_type& k) const {
            const_iterator it = begin();
            for (const_iterator ite = end(); it != ite && _comp(it->first, k); it++);
            return it;
        }

        iterator upper_bound (const key_type& k) {
            iterator it = lower_bound(k);
            if (it != end())
                return ++it;
            return it;
        }
        const_iterator upper_bound (const key_type& k) const {
            const_iterator it = lower_bound(k);
            if (it != end())
                return ++it;
            return it;
        }

        ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
            return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }
        ft::pair<iterator, iterator> equal_range (const key_type& k) {
            return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        // allocator

        allocator_type get_allocator() const;

    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs == rhs);
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs > rhs);
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return rhs < lhs;
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
        return !(lhs < rhs);
    };

    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
        x.swap(y);
    };
}