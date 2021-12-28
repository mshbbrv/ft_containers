#pragma once

#include "Node.hpp"
//#include "Utility.hpp"
//#include "Iterator.hpp"
//#include "Node.hpp"

namespace ft {

    template <class Key, class T, class Compare = std::less<Key>, class Alloc =
            std::allocator<std::pair<const Key, T> > >
    class map {
    public:

        // types
        typedef Key											key_type;
        typedef T											mapped_type;
        typedef ft::pair<const key_type, mapped_type>		value_type;
        typedef Compare										key_compare;
        typedef Alloc										allocator_type;
        typedef value_type&									reference;
        typedef const value_type&							const_reference;
        typedef value_type*                     			pointer;
        typedef const value_type*                   		const_pointer;

        //итераторы ?
        /*typedef ft::node_iterator<Node_<value_type>*, value_type>
                iterator;
        typedef ft::node_iterator<const Node_<value_type>*, value_type>					const_iterator;
        typedef ft::reverse_iterator<iterator>								reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
        typedef typename allocator_type::template rebind<Node_<value_type> >::other			allocator_rebind_node;
        typedef typename allocator_type::template rebind<Tree<value_type>
         >::other			allocator_rebind_tree;*/

        typedef std::size_t								size_type;
        typedef std::ptrdiff_t                          difference_type;

        typedef Node<value_type> node;
        typedef Node<value_type> *node_pointer;
        typedef Node<value_type> &node_reference;
        typedef typename allocator_type::template rebind<node>::other node_allocator;

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
        // ??
        node_allocator          _node_alloc;
        allocator_type 			_allocator;
        key_compare		 		_comp;
        size_type _size;

        node_pointer _root;
        node_pointer _end;
        node_pointer _begin;


        //инициализируем начало и конец
        void initMap() {
            _end = _node_alloc.allocate(1);
            _end->parent = 0;
            _end->left = 0;
            _end->right = 0;
            _end->data = NULL.allocate(0);
            _end->color = _BLACK;
            _begin = _node_alloc.allocate(1);
            _begin->parent = 0;
            _begin->left = 0;
            _begin->right = 0;
            _begin->data = _node_alloc.allocate(0);
            _begin->color = _BLACK;
        };

        void deleteNode(node_pointer node) {
            _allocator.destroy(node->data);
            _allocator.deallocate(node->data, 1);
            _allocator.deallocate(node, 1);
            _size--;
        };

        node_pointer getMaxFromIt(node_pointer node) {
            node_pointer tmp = node;
            for (; tmp && tmp->right; tmp = tmp->right);
            return tmp;
        };


    public:

        //construct
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type());

        //copy
        map (const map& x);

        //destroy
        ~map();

        //operator=
        map& operator= (const map& x);

        // iterators
        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;

        reverse_iterator rend();
        const_reverse_iterator rend() const;

        // capacity
        bool empty() const;
        size_type size() const;
        size_type max_size() const;

        // element access
        mapped_type& operator[] (const key_type& k);

        // modifiers
        pair<iterator,bool> insert (const value_type& val);
        iterator insert (iterator position, const value_type& val);
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last);

        void erase (iterator position);
        size_type erase (const key_type& k);
        void erase (iterator first, iterator last);

        void swap (map& x);

        void clear();

        // observers
        key_compare key_comp() const;
        value_compare value_comp() const;

        // operations
        iterator find (const key_type& k);
        const_iterator find (const key_type& k) const;

        size_type count (const key_type& k) const;

        iterator lower_bound (const key_type& k);
        const_iterator lower_bound (const key_type& k) const;

        iterator upper_bound (const key_type& k);
        const_iterator upper_bound (const key_type& k) const;

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
        pair<iterator,iterator>             equal_range (const key_type& k);

        // allocator

        allocator_type get_allocator() const;

    };
}