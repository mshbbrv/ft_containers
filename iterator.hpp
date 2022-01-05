#pragma once
#include <string>
#include <stdexcept>
#include "node.hpp"

namespace ft {

    template <class Iter>
    struct iterator_traits {
    public:
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::const_pointer        const_pointer;
        typedef typename Iter::reference            reference;
        typedef typename Iter::const_reference      const_reference;
        typedef typename Iter::iterator_category    iterator_category;
    };

    template <typename T>
    struct iterator_traits<T*> {
    public:
        typedef T									value_type;
        typedef T*		    						pointer;
        typedef const T*							const_pointer;
        typedef T&									reference;
        typedef const T&    						const_reference;
        typedef std::ptrdiff_t			    		difference_type;
        typedef std::random_access_iterator_tag     iterator_category;
    };

    template <class T>
    class iterator {
    public:
        /*typedef T
        iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef typename iterator_traits<iterator_type>::const_pointer      const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::const_reference    const_reference;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::iterator_category
         iterator_category;*/

        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::ptrdiff_t difference_type;
    private:
        pointer _ptr;
    public:

        iterator() : _ptr(NULL) {}
        iterator(pointer ptr = 0) : _ptr(ptr) {}
        iterator(const iterator& x) {

            if (this != &x)
                *this = x;
        }
        iterator &operator=(const iterator& it) {
            if (this != &it) {
                _ptr = it._ptr;
            }
            return (*this);
        }
        iterator base() const { return _ptr; }
        ~iterator()	{};

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        iterator operator++(int)	{ iterator tmp(*this); _ptr++; return tmp; }
        iterator &operator++() { _ptr++; return *this; }

        iterator operator--(int) { iterator tmp(*this); _ptr--; return tmp; }
        iterator &operator--() { _ptr--; return *this; }

        iterator operator+(difference_type n) const { return iterator(_ptr + n); }
        difference_type operator+(iterator &n) { return (_ptr + n._ptr); }

        iterator operator-(difference_type n) const {
            return (iterator(_ptr -n));
        }
        difference_type operator-(iterator &n) {return (_ptr - n._ptr);	}

        bool operator<(const iterator& it) { return _ptr < it._ptr; }
        bool operator>(const iterator& it) { return _ptr > it._ptr; }
        bool operator<=(const iterator& it) { return _ptr <= it._ptr; }
        bool operator>=(const iterator& it) { return _ptr >= it._ptr; }
        bool operator==(const iterator& it) const { return _ptr == it._ptr; }
        bool operator!=(const iterator& it) const { return _ptr != it._ptr; }

        iterator	&operator-=(difference_type n) { _ptr -= n; return (*this); }
        iterator	&operator+=(difference_type n){ _ptr += n; return (*this); }

        reference operator[](difference_type val) const {
            return(_ptr[val]); }

        pointer getElement() const {return (_ptr);}
    };

    template <class T>
    class reverse_iterator {
    public:
        /*typedef T
        iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type
        value_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef typename iterator_traits<iterator_type>::const_pointer      const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::const_reference    const_reference;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
*/
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::ptrdiff_t difference_type;
    private:
        pointer _ptr;
    public:

        reverse_iterator(pointer ptr = 0) : _ptr(ptr) {}
        reverse_iterator(const reverse_iterator& x) {
            if (this != &x){
                _ptr = x._ptr;
            }
        }
        reverse_iterator &operator=(const reverse_iterator& it) {
            if (this != &it){
                _ptr = it._ptr;
            }
            return (*this);
        }
        ~reverse_iterator()	{};

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        reverse_iterator operator++(int)	{ reverse_iterator tmp(*this);
            _ptr--; return tmp; }
        reverse_iterator &operator++() { --_ptr; return *this; }

        reverse_iterator operator--(int) { reverse_iterator tmp(*this);
            _ptr++; return tmp; }
        reverse_iterator &operator--() { ++_ptr; return *this; }

        reverse_iterator operator+(difference_type n) const { return reverse_iterator
        (_ptr - n); }
        difference_type operator+(const reverse_iterator& it) const { return
        _ptr - it._ptr; }

        difference_type operator-(const reverse_iterator& it) const { return
        _ptr + it._ptr; }
        reverse_iterator operator-(difference_type n) const { return reverse_iterator
        (_ptr + n); }

        bool operator<(const reverse_iterator& it) const { return _ptr < it._ptr; }
        bool operator>(const reverse_iterator& it) const { return _ptr > it._ptr; }
        bool operator<=(const reverse_iterator& it) const { return _ptr <= it._ptr; }
        bool operator>=(const reverse_iterator& it) const { return _ptr >= it._ptr; }
        bool operator==(const reverse_iterator& it) const { return _ptr == it._ptr; }
        bool operator!=(const reverse_iterator& it) const { return _ptr != it._ptr; }

        reverse_iterator	&operator-=(difference_type n) { _ptr += n; return (*this); }
        reverse_iterator	&operator+=(difference_type n) { _ptr -= n; return (*this); }

        reference operator[](difference_type index) {
            return (*(_ptr + index));}
        pointer getElement() const {return (_ptr);}
    };

    template<class T>
    class map_iterator
            : public std::iterator<std::bidirectional_iterator_tag, T> {

    public:

        explicit map_iterator(Node<T>* ptr = NULL) : _it( ptr ) {};
        ~map_iterator() {};
        map_iterator(const map_iterator &it) {
            if (this != &it)
                *this = it;
        }
        map_iterator &operator=(const map_iterator &it) {
            if (this != &it)
                _it = it._it;
            return *this;
        }
        map_iterator operator++() {
            _getNext();
            return *this;
        }
        map_iterator operator++(int) {
            map_iterator tmp(*this);
            operator++();
            return tmp;
        }
        map_iterator operator--() {
            _getPrev();
            return *this;
        }
        map_iterator operator--(int) {
            map_iterator tmp(*this);
            operator--();
            return tmp;
        }
        bool operator==(const map_iterator &it) const { return _it == it._it; }
        bool operator!=(const map_iterator &it) const { return _it != it._it; }
        T &operator*() const { return *(_it->data); }
        T *operator->() const { return _it->data; }
        Node<T>* getNode() const { return _it; }

    private:

        Node<T>* _it;

        void _getNext() {
            if (_it->right)
                for (_it = _it->right; _it->left; _it = _it->left);
            else {
                for (; _it->parent && _it->parent->right == _it; _it = _it->parent);
                _it = _it->parent;
            }
        }
        void _getPrev() {
            if (_it->left)
                for (_it = _it->left; _it->right; _it = _it->right);
            else {
                for (; _it->parent && _it->parent->left == _it; _it =_it->parent);
                _it = _it->parent;
            }
        }
    };

    template<class T>
    class const_map_iterator
            : public std::iterator<std::bidirectional_iterator_tag, T> {

    public:

        explicit const_map_iterator(Node<T>* ptr = NULL) : _it( ptr ) {}
        ~const_map_iterator() {}
        const_map_iterator(const const_map_iterator &it) {
            if (this != &it)
                *this = it;
        }

        const_map_iterator &operator=(const const_map_iterator &it) {
            if (this != &it)
                _it = it._it;
            return *this;
        }

        const_map_iterator operator++() {
            _getNext();
            return *this;
        }
        const_map_iterator operator++(int) {
            const_map_iterator tmp(*this);
            operator++();
            return tmp;
        }
        const_map_iterator operator--() {
            _getPrev();
            return *this;
        }
        const_map_iterator operator--(int) {
            const_map_iterator tmp(*this);
            operator--();
            return tmp;
        }
        bool operator==(const const_map_iterator &it) const { return _it == it._it; }
        bool operator!=(const const_map_iterator &it) const { return _it != it._it; }
        const T &operator*() const { return *(_it->data); }
        const T *operator->() const { return _it->data; }
        Node<T>* getNode() const { return _it; }

    private:

        Node<T>* _it;

        void _getNext() {
            if (_it->right)
                for (_it = _it->right; _it->left; _it = _it->left);
            else {
                for (; _it->parent && _it->parent->right == _it; _it = _it->parent);
                _it = _it->parent;
            }
        }
        void _getPrev() {
            if (_it->left)
                for (_it = _it->left; _it->right; _it = _it->right);
            else {
                for (; _it->parent && _it->parent->left == _it; _it =_it->parent);
                _it = _it->parent;
            }
        }
    };

    template<class T>
    class map_reverse_iterator:
            public std::iterator<std::bidirectional_iterator_tag, T> {

    public:

        explicit map_reverse_iterator(Node<T>* ptr = NULL) : _it(ptr) {}
        virtual ~map_reverse_iterator() {}
        map_reverse_iterator(const map_reverse_iterator &it) {
            if (this == &it)
                return;
            *this = it;
        }
        map_reverse_iterator &operator=(const map_reverse_iterator &it) {
            _it = it._it;
            return *this;
        }
        map_reverse_iterator operator++() {
            _getPrev();
            return *this;
        }
        map_reverse_iterator operator++(int) {
            map_reverse_iterator tmp(*this);
            operator++();
            return tmp;
        }
        map_reverse_iterator operator--() {
            _getNext();
            return *this;
        }
        map_reverse_iterator operator--(int) {
            map_reverse_iterator tmp(*this);
            operator--();
            return tmp;
        }
        bool operator==(const map_reverse_iterator &it) const
        { return _it == it._it; }
        bool operator!=(const map_reverse_iterator &it) const
        { return _it != it._it; }
        T &operator*() const { return *(_it->data); }
        T *operator->() const { return _it->data; }
        Node<T>* getNode() { return _it; }

    private:
        Node<T>* _it;
        void _getNext() {
            if (_it->right)
                for (_it = _it->right; _it->left; _it = _it->left);
            else {
                for (; _it->parent && _it->parent->right == _it;
                    _it = _it->parent);
                _it = _it->parent;
            }
        }
        void _getPrev() {
            if (_it->left)
                for (_it = _it->left; _it->right; _it = _it->right);
            else {
                for (; _it->parent && _it->parent->left == _it;
                    _it = _it->parent);
                _it = _it->parent;
            }
        }
    };

    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

    template<class T, bool v>
    struct integral_constant {
        static const bool value = v;
        typedef T value_type;
        typedef integral_constant type;
        operator value_type() const { return value; }
    };

    template <class T> struct is_integral : public ft::integral_constant<T, false> {};
    template <> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char> : public ft::integral_constant<bool, true> {};
    template <> struct is_integral<signed char> : public integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char> : public integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t> : public integral_constant<bool, true> {};
    template <> struct is_integral<short> : public integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short> : public integral_constant<bool, true> {};
    template <> struct is_integral<int> : public integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int> : public integral_constant<bool, true> {};
    template <> struct is_integral<long> : public integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long> : public integral_constant<bool, true> {};
    template <> struct is_integral<long long> : public integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long> : public integral_constant<bool, true> {};


    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
        for (; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    }

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, BinaryPredicate p ) {
        for (; first1 != last1; ++first1, ++first2) {
            if (!p(*first1, *first2)) {
                return false;
            }
        }
        return true;
    }

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <class T1, typename T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;
        pair() : first(), second() {}
        pair(const first_type& a, const second_type& b) : first(a), second(b) {}
        template <class U, class V>
        pair(const pair<U, V>& p) : first(p.first), second(p.second) {}

        pair& operator=(pair const& p) {
            first = p.first;
            second = p.second;
            return *this;
        }
    };

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }
}