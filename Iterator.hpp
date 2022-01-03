#pragma once
#include <string>
#include <stdexcept>

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
    private:
        T _ptr;
    public:
        typedef T											                iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef typename iterator_traits<iterator_type>::const_pointer      const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::const_reference    const_reference;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;

        //iterator() : _ptr(0) {}
        //iterator(pointer ptr = 0) : _ptr (ptr) {}
        iterator(T ptr = 0) : _ptr(ptr) {}
        template <class U>
        iterator(const iterator<U>& x) : _ptr(x.base()) {}
        T		base() const { return _ptr; }
        //iterator(const iterator& it) : _ptr(it._ptr) {}
        iterator &operator=(const iterator& it) {
            if (this != &it) {
                _ptr = it._ptr; }
            return *this; }
        ~iterator()	{};

        bool operator==(const iterator& it) const { return _ptr == it._ptr; }
        bool operator!=(const iterator& it) const { return _ptr != it._ptr; }

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return &(*_ptr); }

        iterator operator++(int)	{ iterator tmp(*this); _ptr++; return tmp; }
        iterator &operator++() { _ptr++; return *this; }

        iterator operator--(int) { iterator tmp(*this); _ptr--; return tmp; }
        iterator &operator--() { _ptr--; return *this; }

        iterator operator+(int n) const { return iterator(_ptr + n); }
        iterator operator+(const iterator& it) const { return _ptr + it._ptr; }

        iterator operator-(const iterator& it) const { return _ptr - it._ptr; }
        iterator operator-(int n) const { return iterator(_ptr - n); }

        bool operator<(const iterator& it) const { return _ptr < it._ptr; }
        bool operator>(const iterator& it) const { return _ptr > it._ptr; }
        bool operator<=(const iterator& it) const { return _ptr <= it._ptr; };
        bool operator>=(const iterator& it) const { return _ptr >= it._ptr; };

        iterator	&operator-=(int n) { _ptr -= n; return (*this); }
        iterator	&operator+=(int n){ _ptr += n; return (*this); }

        reference operator[](const unsigned int index) {
            return *_ptr[index]; }
    };

    template <class T>
    class reverse_iterator {
    private:
        T _ptr;
    public:
        typedef T											                iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type
        value_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef typename iterator_traits<iterator_type>::const_pointer      const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::const_reference    const_reference;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;

        reverse_iterator(T ptr = 0) : _ptr(ptr) {}
        template <class U>
        reverse_iterator(const reverse_iterator<U>& x) : _ptr(x.base()) {};
        iterator_type 		base() const		{ return _ptr; }
        reverse_iterator &operator=(const reverse_iterator& it) {
            if (this != &it) {
                _ptr = it._ptr; }
            return *this; }
        ~reverse_iterator()	{};

        bool operator==(const reverse_iterator& it) const { return _ptr == it._ptr; }
        bool operator!=(const reverse_iterator& it) const { return _ptr != it._ptr; }

        reference operator*() const { return *_ptr; }
        pointer operator->() const { return &(*_ptr); }

        reverse_iterator operator++(int)	{ reverse_iterator tmp(*this);
            _ptr--; return tmp; }
        reverse_iterator &operator++() { --_ptr; return *this; }

        reverse_iterator operator--(int) { reverse_iterator tmp(*this);
            _ptr++; return tmp; }
        reverse_iterator &operator--() { ++_ptr; return *this; }

        reverse_iterator operator+(int n) const { return reverse_iterator
        (_ptr - n); }
        reverse_iterator operator+(const reverse_iterator& it) const { return
        _ptr - it._ptr; }

        reverse_iterator operator-(const reverse_iterator& it) const { return
        _ptr + it._ptr; }
        reverse_iterator operator-(int n) const { return reverse_iterator
        (_ptr + n); }

        bool operator<(const reverse_iterator& it) const { return _ptr < it._ptr; }
        bool operator>(const reverse_iterator& it) const { return _ptr > it._ptr; }
        bool operator<=(const reverse_iterator& it) const { return _ptr <= it._ptr; };
        bool operator>=(const reverse_iterator& it) const { return _ptr >= it._ptr; };

        reverse_iterator	&operator-=(int n) { _ptr += n; return (*this); }
        reverse_iterator	&operator+=(int n) { _ptr -= n; return (*this); }

        reference operator[](const unsigned int index) {
            return *_ptr[index]; }
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
        T1 first;
        T2 second;
        pair() : first(), second() {}
        pair(T1 const& t1, T2 const& t2) : first(t1), second(t2) {}

        template <class U1, class U2>
        pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

        pair& operator=(pair const& p) {
            first = p.first;
            second = p.second;
            return *this;
        }

        void swap(pair& p) {
            swap(first,  p.first);
            swap(second, p.second);
        }
    };

    template<class T1, class T2>
    pair<T1, T2>
    make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }
}