#pragma once

#include "iterator.hpp"
#include <limits>
#include <string>
#include <algorithm>

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

    private:

        pointer         _arr;
        size_type       _sz;
        size_type       _cap;
        allocator_type  _alloc;

    public:

        explicit vector (const allocator_type& alloc =
        allocator_type()) : _arr ( NULL ), _sz( 0 ), _cap( 0 ),
                            _alloc( alloc ) {}

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type())
                : _sz( n ), _cap( n ), _alloc( alloc ) {

            if ( n < 0 )
                throw std::length_error( "invalid size" );
            _arr = _alloc.allocate( _cap );
            for ( size_type i = 0; i < _sz; ++i ) {
                _arr[i] = val;
            }
        }
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) :
               _sz(0), _cap(0), _alloc(alloc) {
            _arr = _alloc.allocate(_cap);
            assign(first, last);
        }

        //copy
        vector(const vector& x) {
            if (this != &x) {
                _cap = x._cap;
                _sz = x._sz;
                _alloc = x.get_allocator();
                _arr = _alloc.allocate(x._cap);
                for (size_type i = 0; i < _sz; ++i) {
                    _arr[i] = x._arr[i];
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
        vector& operator= (const vector& x) {
            if (this != &x) {
                clear();
                _alloc.deallocate(_arr, _cap);
                _cap = x._cap;
                _sz = x._sz;
                _arr = _alloc.allocate(_cap);
                for (size_type i = 0; i < _sz; ++i) {
                    _arr[i] = x._arr[i];
                }
            }
            return *this;
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
        size_type max_size() const { return _alloc.max_size(); }

        void resize (size_type n, value_type val = value_type()) {

            if (n < _sz) {
                for (; _sz != n; )
                    pop_back();
            } else {
                if (_cap * 2 < n)
                    reserve(n);
                for (; _sz != n; )
                    push_back(val);
            }

        }
        size_type capacity() const { return _cap; }
        bool empty() const { return _sz == 0; }
        void reserve (size_type n) {

            if (n > _cap) {
                pointer tmp = _alloc.allocate( n );
                for ( size_type i = 0; i < _sz; ++i ) {
                    tmp[i] = _arr[i];
                }
                if ( _arr )
                    _alloc.deallocate( _arr, _cap );
                _cap = n;
                _arr = tmp;
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

            size_type dis = 0;

            for (iterator it = first; it != last; it++, dis++) {
                if (it == end())
                    throw std::length_error("out of range");
            }
            clear();
            reserve(dis);
            for (; first != last; ++first) {
                push_back(*first);
            }
        }

        void assign(size_type n, const value_type& val) {

            if (n < 0)
                throw std::length_error("invalid size");
            clear();
            reserve(n);
            for (size_type i = 0; i < n; ++i, _sz++)
                _arr[i] = val;
        }
        void push_back(const value_type& val) {

            if ( _cap == _sz ) {
                if ( !_cap )
                    reserve( 1 );
                else
                    reserve( 2 * _sz );
            }
            _arr[_sz] = val;
            ++_sz;
        }

        void pop_back() { _alloc.destroy(_arr + _sz); _sz--; }

        iterator    insert (iterator position, const value_type& val) {

            size_type i(0);
            for (iterator it = begin(); it != position; it++, i++);
            insert(position, 1, val);
            return iterator(_arr + i);
        }

        void        insert (iterator position, size_type n, const value_type&
        val) {
            size_type max_size = _sz + n;

            if (n >= _cap) {
                reserve(_cap + n);
                _sz = max_size;
            } else {
                for(; _sz != max_size; _sz++) {
                    if (_sz == _cap)
                        reserve(_cap * 2);
                }
            }
            int i(0);
            for (iterator it = begin(); it != position; it++, i++);

            for (int k = _sz - 1; k >= 0; --k) {
                if (k == i) {
                    for (; n > 0; --n, ++i)
                        _arr[i] = val;
                    return;
                }
                if (k - static_cast<int>(n) >= 0) {
                    _arr[k] = _arr[k - n];
                }
            }
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) {

            size_type dis(0);
            for (iterator it = first; it != last; it++, dis++);

            pointer tmp = _alloc.allocate(dis);
            bool res = true;
            size_type i = 0;
            for (;first != last; ++first, ++i) {
                try { tmp[i] = *first; }
                catch (...) { res = false; break; }
            }
            _alloc.deallocate(tmp, dis);
            if (!res)
                throw std::exception();

            size_type newSize = _sz + dis;
            if (dis >= _cap) {
                reserve(_cap + dis);
                _sz = newSize;
            } else {
                for (;_sz != newSize; _sz++) {
                    if (_sz == _cap)
                        reserve(_cap * 2);
                }
            }

            size_type dis2(0);
            for (iterator it = begin();it != position; it++, dis2++);
            size_type index = dis2 + dis - 1;
            for (size_type i = _sz - 1; i >= 0; --i) {
                if (i == index) {
                    for (; dis > 0; --dis, --i)
                        _arr[i] = *--last;
                    return;
                }
                _arr[i] = _arr[i - dis];
            }
        }

        iterator erase (iterator position) {
            size_type i(0);
            for (iterator it = begin() ; it != position; it++, i++);
            for (size_type k = i; k < _sz; ++k)
                _arr[k] = _arr[k + 1];
            _sz--;
            return position;
        }
        iterator erase (iterator first, iterator last) {

            size_type start(0);
            for (iterator it = begin(); it != first; it++, start++);

            size_type end(0);
            for (iterator it = begin(); it != last; it++, end++);

            size_type offset = end - start;

            _sz -= offset;
            for (size_type i = start; i < _sz; ++i)
                _arr[i] = _arr[i + offset];

            return _arr + start;
        }

        void swap(vector& x) {
            std::swap(_sz, x._sz);
            std::swap(_cap, x._cap);
            std::swap(_arr, x._arr);
            std::swap(_alloc, x._alloc);
        }
        void clear() {
            for (size_type i = 0; i < _sz; i++)
                _alloc.destroy(_arr + i);
            _sz = 0;
        }

        //allocator
        allocator_type          get_allocator() const { return _alloc; }


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

