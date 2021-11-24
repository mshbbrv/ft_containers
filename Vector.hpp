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
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef value_type& reference;
        typedef value_type& const_reference;
        typedef std::size_t size_type;

        //iterator

        typedef std::iterator<iterator> iterator;
        typedef std::iterator<const_iterator> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //construct

        explicit                vector (const allocator_type& alloc = allocator_type());
        explicit                vector (size_type n, const value_type& val = value_type(),
                                        const allocator_type& alloc = allocator_type());
        template <class InputIterator>
                                vector (InputIterator first, InputIterator last,
                                        const allocator_type& alloc = allocator_type());

        //copy
        constexpr               vector(const vector& x);

        //destroy
        constexpr               ~vector();

        //operator=
        vector&                 operator= (const vector& x);

        // iterators
        iterator                begin();
        const_iterator          begin() const;
        iterator                end();
        const_iterator          end() const;
        reverse_iterator        rbegin();
        const_reverse_iterator  rbegin() const;
        reverse_iterator        rend();
        const_reverse_iterator  rend() const;

        // capacity
        size_type               size() const;
        size_type               max_size() const;
        void                    resize (size_type n, value_type val = value_type());
        size_type               capacity() const;
        bool                    empty() const;
        void                    reserve (size_type n);

        // element access
        reference               operator[](size_type n);
        const_reference         operator[](size_type n) const;
        reference               at(size_type n);
        const_reference         at(size_type n) const;
        reference               front();
        const_reference         front() const;
        reference               back();
        const_reference         back() const;


        // modifiers
        template <class InputIterator>
                void            assign (InputIterator first, InputIterator last);
        void                    assign (size_type n, const value_type& val);
        void                    push_back (const value_type& val);
        void                    pop_back();
        iterator                insert (iterator position, const value_type& val);
        void                    insert (iterator position, size_type n, const value_type& val);
        template <class InputIterator>
                void            insert (iterator position, InputIterator first, InputIterator last);
        iterator                erase (iterator position);
        iterator                erase (iterator first, iterator last);

        void                    swap (vector& x);
        void                    clear();

        //allocator
        allocator_type          get_allocator() const;

        //non-member
        template <class T, class Alloc>
                bool            operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
        template <class T, class Alloc>
                bool            operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
        template <class T, class Alloc>
                bool            operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
        template <class T, class Alloc>
                bool            operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
        template <class T, class Alloc>
                bool            operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
        template <class T, class Alloc>
                bool            operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
        template <class T, class Alloc>
                void            swap (vector<T,Alloc>& x, vector<T,Alloc>& y);


    private:

    };

}

