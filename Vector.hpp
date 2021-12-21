#pragma once

#include "Iterator.hpp"
//#include <iterator>
//#include <vector>
//#include <string>

namespace ft {

    template<class T, class Allocator = std::allocator<T> >
    class vector {

    public:

        // types
        typedef T                                       value_type;
        typedef Allocator                               allocator_type;
        typedef value_type&                             reference;
        typedef value_type&                             const_reference;
        typedef std::size_t                             size_type;
        typedef T*                                      pointer;
        typedef const T*                                const_pointer;
        typedef std::ptrdiff_t                          difference_type;

        //iterator
        typedef ft::iterator<T*> 						iterator;
        typedef ft::iterator<const T*>				    const_iterator;
        typedef ft::reverse_iterator<iterator> 			reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
        //construct

        explicit vector (const allocator_type& alloc =
                allocator_type()) : _arr ( 0 ), _sz( 0 ), _cap( 0 ),
                                    _alloc( alloc ) {}

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type())
                         : _sz( n ), _cap( n ), _alloc( alloc ) {

            if ( n < 0 )
                throw std::length_error( "invalid size" );
            _arr = _alloc.allocate( _cap );
            for ( size_t i = 0; i < _sz; ++i ) {
                _alloc.construct( (_arr + i), val );
            }
        }
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) :
                _arr(0), _alloc(alloc), _sz(0), _cap(0) {
            _arr = _alloc.allocate(0);
            assign(first, last);
        };

        //copy
        vector(const vector& x) {
            if (this != &x) {
                _cap = x._cap;
                _sz = x._sz;
                _alloc = x._alloc;
                _arr = _alloc.allocate(_cap);
                for (size_t i = 0; i < _sz; ++i) {
                    _alloc.construct((_arr + i), *(x._arr + i));
                }
            }
        }

        //destroy
        ~vector() {
            if (_arr)
                clear();
            _alloc.deallocate(_arr, _cap);
        };

        //operator=
        vector&                 operator= (const vector& x) {
            if (this != &x) {
                clear();
                _alloc.deallocate(_arr, _cap);
                _cap = x._cap;
                _sz = x._sz;
                _alloc = x._alloc;
                _arr = _alloc.allocate(_cap);
                for (size_t i = 0; i < _sz; ++i) {
                    _alloc.construct((_arr + i), *(x._arr + i));
                }
            }
        }

        // iterators
        iterator                begin() { return iterator(_arr); }
        const_iterator          begin() const { return const_iterator(_arr); }
        iterator                end() { return iterator( _arr + _sz ); }
        const_iterator          end() const {
            return const_iterator( _arr + _sz ); }
        reverse_iterator        rbegin() {
            return reverse_iterator( iterator(_arr + _sz - 1) ); }
        const_reverse_iterator  rbegin() const {
            return reverse_iterator( const_iterator(_arr + _sz - 1) ); }
        reverse_iterator        rend() {
            return reverse_iterator( iterator(_arr - 1) ); }
        const_reverse_iterator  rend() const {
            return reverse_iterator( const_iterator(_arr - 1) ); }

        // capacity
        size_type size() const { return _sz; }
        size_type max_size() const { return (size_type(~0) / sizeof(value_type)); }
        void resize (size_type n, value_type val = value_type()) {
            if (n > _cap) {
                reserve( n );
            }
            for ( size_type i = _sz; i < n; i++ )
                _alloc.construct( _arr + i, val );
            if (n < _sz) {
                _sz = n;
            }

        }
        size_type capacity() const { return _cap; }
        bool empty() const { return _sz == 0; }
        void reserve (size_type n) {

            if (n > _cap) {
                pointer tmp = _alloc.allocate(n);
                for (size_type i = 0; i < _sz; ++i) {
                    _alloc.construct(tmp + i, *(_arr + i));
                    _alloc.destroy(_arr + i);
                }
                _alloc.deallocate(_arr, _cap);
                _arr = tmp;
                _cap = n;
            }
        }

        // element access
        reference       operator[](size_type n) { return _arr[n]; }
        const_reference operator[](size_type n) const { return _arr[n]; }
        reference at(size_type n) {

            if (n >= _sz)
                throw std::out_of_range("out of range");
            return _arr[n];
        }
        const_reference at(size_type n) const {

            if (n >= _sz)
                throw std::out_of_range("out of range");
            return _arr[n];
        }
        reference       front()         { return *_arr; }
        const_reference front() const   { return *_arr; }
        reference       back()          { return _arr[_sz - 1]; }
        const_reference back() const    { return _arr[_sz - 1]; }


        // modifiers
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) {

            clear();
            insert(begin(), first, last);
        }
        void assign(size_type n, const value_type& val) {

            if (n < 0)
                throw std::length_error("invalid size");
            clear();
            insert(begin(), n, val);
        }
        void push_back(const value_type& val) {

            if ( _cap == _sz )
                reserve( 2 * _sz );
            insert(end(), val);

        }
        void pop_back() { _alloc.destroy(_arr + --_sz); }

        iterator    insert (iterator position, const value_type& val) {

            size_type pos = 0;
            iterator first = begin();
            for (;first != position; first++, pos++);

            if (_sz + 1  > _cap)
                reserve(_sz >= 0 && _sz + 1 <= 8 ? _sz + 1 : _sz * 2);
            _sz++;
            for (size_type j = _sz - 1; j > pos; j--)
                _arr[j] = _arr[j - 1];
            _arr[pos] = val;
            return iterator(_arr + pos);
        }
        void        insert (iterator position, size_type n, const value_type&
        val) {
            while(n--)
                position = insert(position, val);
        }
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) {

            for (; first != last; first++, position++)
                position = insert( position, *first );
        }

        iterator erase (iterator position) {

            iterator ret(position);

            while (position != end() - 1) {
                *position = *(position + 1);
                position++;
            }
            _sz--;
            return ret;
        }
        iterator erase (iterator first, iterator last) {

            while (first != last)
                erase(--last);
            return last;
        }

        void swap(vector& x) {
            size_type size = _sz;
            _sz = x._sz;
            x._sz = size;

            allocator_type alloc = _alloc;
            _alloc = x._alloc;
            x._alloc = alloc;

            size_type cap = _cap;
            _cap = x._cap;
            x._cap = cap;

            pointer arr = _arr;
            _arr = x._arr;
            x._arr = arr;
        }
        void clear() {
            for (size_type i = 0; i < _sz; i++) {
                _alloc.destroy(_arr + i);
            }
            _sz = 0;
        }

        //allocator
        allocator_type          get_allocator() const { return _alloc; }


    private:

        T*              _arr;
        size_t          _sz;
        size_t          _cap;
        allocator_type  _alloc;

    };

    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return lhs == rhs;};
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return lhs != rhs;};
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return lhs < rhs;};
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return lhs <= rhs;};
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return lhs > rhs;};
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return lhs >= rhs;};

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}

