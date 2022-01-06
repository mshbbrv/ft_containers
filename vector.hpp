#pragma once

#include "iterator.hpp"

namespace ft {

    template<class T, class Allocator = std::allocator<T> >
    class vector {

    public:

        // types
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::size_t                             size_type;
        typedef std::ptrdiff_t                          difference_type;

        //iterator
        typedef ft::iterator<value_type> 						iterator;
        typedef ft::iterator<const value_type>				    const_iterator;
        typedef ft::reverse_iterator<value_type> 			reverse_iterator;
        typedef ft::reverse_iterator<value_type>	const_reverse_iterator;

    private:

        T*              _arr;
        size_t          _sz;
        size_t          _cap;
        allocator_type  _alloc;

    public:

        //construct

        explicit vector (const allocator_type& alloc =
                allocator_type()) : _arr ( 0 ), _sz( 0 ), _cap( 0 ),
                                    _alloc( alloc ) {}

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type())
                         : _sz( n ), _cap( n ), _alloc( alloc ) {

            if ( n < 0 )
                throw std::length_error( "invalid size" );
            allocator = alloc;
            _capacity = _size = n;
            buffer = allocator.allocate(_capacity);
            for (size_t i = 0; i < count; ++i)
                buffer[i] = value;
            }
        }
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) :
               _alloc(alloc), _sz(0), _cap(0) {

            buffer = allocator.allocate(_capacity);
            assign(first, last);

        }

        //copy
        vector(const vector& x) : buffer(0), _capacity(other._capacity), _size(other._size), allocator(other.get_allocator()){
            buffer = allocator.allocate(x._capacity);
            for (size_t i = 0; i < _size; i++)
                buffer[i] = x.buffer[i];
        }

        //destroy
        ~vector() {

            clear();
            _alloc.deallocate(_arr, _cap);
        };

        //operator=
        vector&                 operator= (const vector& x) {
            if (this == &x)
                return *this;
            clear();
            allocator.deallocate(buffer, _capacity);
            _capacity = x._capacity;
            _size = x._size;
            buffer = allocator.allocate(_capacity);
            for (size_t i = 0; i < _size; ++i) {
                buffer[i] = other.buffer[i];
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
        size_type max_size() const { return (size_type(~0) / sizeof(value_type)); }
        void resize (size_type n, value_type val = value_type()) {
            if (n > max_size())
                throw std::length_error("len error");
            if (n < _sz){
                for (size_type i = _sz - n; i < n; i++)
                    _alloc.destroy(_arr + i);
            }
            else if (n > _sz){
                reserve(n);
                for (size_type i = _sz; i < n; i++)
                    _alloc.construct(_arr + i, val);
            }
            _sz = n;
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

            if (n >= _sz || n < 0)
                throw std::out_of_range("out of range");
            return _arr[n];
        }
        const_reference at(size_type n) const {

            if (n >= _sz || n < 0)
                throw std::out_of_range("out of range");
            return _arr[n];
        }
        reference       front()         { return *_arr; }
        const_reference front() const   { return *_arr; }
        reference       back()          { return (*(_arr + _sz - 1)); }
        const_reference back() const    { return (*(_arr + _sz - 1)); }


        // modifiers
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) {

            clear();
            ptrdiff_t  len = last.operator->() - first.operator->();
            if ((size_t)len > _cap)
                reserve(len);
            for (ptrdiff_t i = 0; i < len; i++){
                _alloc.construct(_arr + i, *first);
                first++;
            }
            _sz = static_cast<size_t>(len);
        }

        void assign(size_type n, const value_type& val) {

            if (n < 0)
                throw std::length_error("invalid size");
            clear();
            insert(begin(), n, val);
        }
        void push_back(const value_type& val) {

            if (_cap == 0){
                _arr = _alloc.allocate(1);
                _cap = 1;
                _sz = 1;
                _alloc.construct(_arr, val);
            }
            insert(end(), val);

        }
        void pop_back() { _alloc.destroy(_arr + (--_sz)); }

        iterator    insert (iterator position, const value_type& val) {

            if (_cap == 0){
                _cap = 1;
                _sz = 1;
                _arr = _alloc.allocate(1);
                _alloc.construct(_arr, val);
                return iterator(_arr);
            }
            pointer newArr = 0;
            size_type newPos = position.operator->() - _arr;
            size_type newCap;
            if (_sz + 1 > _cap)
                newCap = _cap * 2;
            else
                newCap = _cap;
            newArr = _alloc.allocate(newCap);
            size_type i = 0;
            for (; i < newPos; ++i){
                _alloc.construct(newArr + i, *(_arr + i));
            }
            _alloc.construct(newArr + newPos, val);
            i++;
            for (; i < _sz + 1; ++i){
                _alloc.construct(newArr + i, *(_arr + i - 1));
            }
            for (size_type k = 0; k < _sz; ++k)
                _alloc.destroy(_arr + k);
            _alloc.deallocate(_arr, _cap);
            _arr = newArr;
            _cap = newCap;
            _sz++;
            return (iterator(_arr + newPos));
        }

        void        insert (iterator position, size_type n, const value_type&
        val) {
            if (_cap == 0){
                _cap = n;
                _sz = n;
                _arr= _alloc.allocate(n);
                for (size_type i = 0; i < n; i++){
                    _alloc.construct((_arr + i), val);
                }
                return ;
            }
            pointer newArr = 0;
            size_type newPos = position.operator->() - _arr;
            size_type newCap;
            if (_sz + n > _cap)
                newCap = (_sz + n) * 2;
            else
                newCap = _cap;
            newArr = _alloc.allocate(newCap);
            size_type i = 0;
            for (; i < newPos; i++){
                _alloc.construct(newArr + i, *(_arr + i));
            }
            size_type j = 0;
            for (; j < n; ++j, ++i){
                _alloc.construct(newArr + j + newPos, val);
            }
            for (; i < _sz + n + 1; ++i){
                _alloc.construct(newArr + i, *(_arr + i - n));
            }
            j = 0;
            for (; j < _sz; ++j){
                _alloc.destroy(_arr + j);
            }
            _alloc.deallocate(_arr, _cap);
            _arr = newArr;
            _cap = newCap;
            _sz = _sz + n;
        }
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) {

            ptrdiff_t len = last - first;
            if (_cap == 0){
                _sz = len;
                _cap = len;
                _arr = _alloc.allocate(len);
                for (ptrdiff_t i = 0; i < len; i++){
                    _alloc.construct(_arr + i, *first);
                    first++;
                }
                return ;
            }
            size_type newPos = position.operator->() - _arr;
            size_type newCap;
            if (_sz + len > _cap){
                newCap = (_sz + len) * 2;
            }
            else
                newCap = _cap;
            pointer newArr = _alloc.allocate(newCap);
            size_type i = 0;
            for (; i < newPos; i++){
                _alloc.construct(newArr + i, *(_arr + i));
            }
            for (ptrdiff_t j = 0; j < len; ++j,++i){
                _alloc.construct(newArr + len + j, *first);
                first++;
            }
            for (; i < _sz + len + 1; ++i){
                _alloc.construct(newArr + i, *(_arr + i - len));
            }
            for (size_t k = 0; k < _sz; ++k){
                _alloc.destroy(_arr + k);
            }
            _alloc.deallocate(_arr, _cap);
            _arr = newArr;
            _cap = newCap;
            _sz = _sz + len;
        }

        iterator erase (iterator position) {

            size_type newPos = position.getElement() - _arr;
            for (; newPos < _sz; newPos++){
                _alloc.destroy(_arr + newPos);
                if (newPos + 1 < _sz)
                    _alloc.construct(_arr + newPos, *(_arr + newPos + 1));
            }
            _sz--;
            _alloc.destroy(_arr + (_sz - 1));
            return (iterator(position.getElement()));
        }
        iterator erase (iterator first, iterator last) {

            for (; first != last;){
                erase(--last);
            }
            return (iterator(last));
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

