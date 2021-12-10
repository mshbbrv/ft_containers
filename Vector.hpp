# include <iterator>

namespace ft {

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag         : public input_iterator_tag {};
    struct bidirectional_iterator_tag   : public forward_iterator_tag {};
    struct random_access_iterator_tag   : public bidirectional_iterator_tag {};

    template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator {

        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    template <class Iterator>
    struct iterator_traits {

        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    // Specialization
    template <class T>
    struct iterator_traits<T*> {

        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };


    template< class T >
    class RandomAccessIterator : public
            iterator<random_access_iterator_tag, T> {

    private:

    public:

    };



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

        //iterator

        typedef std::iterator<iterator> iterator;
        typedef std::iterator<const_iterator> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //construct

        explicit vector (const allocator_type& alloc =
                allocator_type()) : _arr ( nullptr ), _sz( 0 ), _cap( 0 ),
                                    _alloc( alloc ) {}

        explicit vector (size_type n, const value_type& val = value_type(),
                                        const allocator_type& alloc =
                                                allocator_type()) : _sz( n ),
                                                _cap( n ), _alloc( alloc ) {
            _arr = new value_type[n]();
            for (size_t i = 0; i < n; ++i) {
                _arr[i] = val;
            }
        }
        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0)
        : _sz(0), _cap(0), _arr(nullptr), _alloc(alloc) {
            ptrdiff_t len = last.operator->() - first.operator->();
            if (len < 0)
                throw std::length_error("vector");
            _sz = static_cast<size_type> (len);
            _cap = _sz;
            _arr = _alloc.allocate(_cap);
            for (size_type i = 0; i < _size; ++i){
                _alloc.construct(_arr + i, *first);
                first++;
            }
        }

        //copy
        constexpr               vector(const vector& x) : _arr(0),
        _sz(x._sz), _cap(x._cap), _alloc(x.get_allocator()){
            _arr = _alloc.allocate(x._cap);
            for (size_t i = 0; i < _sz; i++)
                _arr[i] = x._arr[i];
        }

        //destroy
        constexpr               ~vector() {
            clear();
        };

        //operator=
        vector&                 operator= (const vector& x) {
            if (this == &other)
                return *this;
            clear();
            _arr = new value_type[x._cap];
            _cap = x._cap;
            _sz = x._sz;
            assign( x.begin(), x.end() );
            return *this;
        }

        // iterators
        iterator                begin() { return iterator(_arr); }
        const_iterator          begin() const {
            return const_iterator(_arr); }
        iterator                end() {
            return iterator(&_arr[_sz]); }
        const_iterator          end() const {
            return const_iterator(&_arr[_sz]);
        }
        reverse_iterator        rbegin() {

            return reverse_iterator(&_arr[_sz - 1]);
        }
        const_reverse_iterator  rbegin() const {
            return reverse_iterator(&_arr[_sz - 1]);
        }
        reverse_iterator        rend() {
            return reverse_iterator(_arr - 1);
        }
        const_reverse_iterator  rend() const {
            return reverse_iterator(_arr - 1);
        }

        // capacity
        size_type size() const { return _sz; }
        size_type max_size() const { return _alloc.max_size(); }
        void resize (size_type n, value_type val = value_type()) {

            if (n < _sz) {
                while (_sz != n)
                    pop_back();
            } else {
                if (_cap * 2 < n)
                    reserve(n);
                while (_sz != n)
                    push_back(val);
            }
        }
        size_type capacity() const { return _cap; }
        bool empty() const { return !_sz; }
        void reserve ( size_type n ) {

            if (n > _cap) {
                T* tmp = allocator.allocate(size);
                for (size_t i = 0; i < _size; ++i)
                    tmp[i] = buffer[i];
                if (buffer) allocator.deallocate(buffer, _capacity);
                _capacity = size;
                buffer = tmp;
            }
        }

        // element access
        reference       operator[](size_type n) { return _arr[n]; }
        const_reference operator[](size_type n) const { return _arr[n]; }
        reference       at(size_type n) {

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
        void            assign (InputIterator first, InputIterator last) {

            clear();
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }
        void assign (size_type n, const value_type& val) {

            if (n < 0)
                throw std::out_of_range("out of range");
            clear();
            reserve(n);
            for (size_t i = 0; i < n; ++i, _size++)
                _arr[i] = val;
        }
        void                    push_back (const value_type& val) {
            if (_sz == _cap)
                (!_cap) ? reserve(1) : reserve(_cap * 2);
            _arr[_sz] = val;
            ++_sz;
        }
        void        pop_back() { _sz--; }
        iterator    insert (iterator position, const value_type&
        val) {

            int index = position - begin();
            insert(position, 1, val);
            return iterator(_arr + index);
        }
        void        insert (iterator position, size_type n, const value_type&
        val) {
            int index = position - begin();
            size_t max_size = _sz + n;

            if (n >= _cap) {
                reserve(_cap + n);
                 _sz = max_size;
            } else {
                while (_sz != max_size) {
                    if (_sz == _cap)
                        reserve(_cap * 2);
                    _sz++;
                }
            }
            for (int i = _sz; i >= 0; --i) {
                if (i == index) {
                    for (; n > 0; --n) {
                        _arr[i] = val;
                        return;
                    }
                }
                _arr[i] = _arr[i - n];
            }
        }
        template <class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
        void            insert (iterator position, InputIterator first,
                                InputIterator last) { }
        iterator                erase (iterator position) {

            int index = position - begin();
            for (size_t i = index; i < _sz; ++i) {
                _arr[i] = _arr[i + 1];
            }
            _sz--;
            return position;
        }
        iterator                erase (iterator first, iterator last) {

            int start = first - begin();
            int end = last - begin();
            int offset = end - start;

            _sz -= offset;
            for (size_t i = start; i < _sz; ++i) {
                _arr[i] = _arr[i + offset];
            }
            return _arr + start;
        }

        void                    swap (vector& x) {
            std::swap(_sz, x._sz);
            std::swap(_cap, x._cap);
            std::swap(_arr, x._arr);
            std::swap(_alloc, x._alloc);
        }
        void                    clear() {
            for (size_type i = 0; i < _sz; i++) {
                _alloc.destroy(_arr + i);
            }
            _sz = 0;
        }

        //allocator
        allocator_type          get_allocator() const { return _alloc; }

        //non-member
        template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
        }

        template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return (!(lhs == rhs));
        }

        template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return (!(rhs < lhs));
        }

        template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return (rhs < lhs);
        }

        template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
            return (!(lhs < rhs));
        }

        template <class T, class Alloc>
        void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
            vector<T,Alloc>	tmp(x);
            x = y;
            y = tmp;
        }

    private:

        T*              _arr;
        size_t          _sz;
        size_t          _cap;
        allocator_type  _alloc;

    };

}

