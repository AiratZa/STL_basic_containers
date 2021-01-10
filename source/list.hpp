//
// Created by Great Drake on 1/9/21.
//

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

# include <iostream>



namespace ft {

//    #include "iterators.hpp"


    template < typename value_type >
    struct ListNode {
        ListNode() : _ptrPrev(NULL), _ptrNext(NULL), _data(NULL) { };
        ListNode(ListNode<value_type>* ptrPrev, ListNode<value_type>* ptrNext, value_type* data)
                : _ptrPrev(ptrPrev), _ptrNext(ptrNext), _data(data) { };
        ~ListNode() { };

        typedef typename std::allocator < ListNode<value_type> >  list_node_allocator_type;
        typedef typename std::allocator < ListNode<value_type> >::pointer  list_node_pointer;

        void setPrev(ListNode<value_type>* ptr) {
            _ptrPrev = ptr;
        }
        void setNext(ListNode<value_type>* ptr) {
            _ptrNext = ptr;
        }
        void setData(ListNode<value_type>* value) {
            _data = value;
        }
        list_node_pointer _ptrPrev;
        list_node_pointer _ptrNext;
        value_type* _data;
    };

    template<class T >
    class ListBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, T>
    {
        template <class, class Alloc>
        friend class list;

//        typedef ListNode<T>

    private:
        ListBidirectionalIterator(T* p) : _p(p) { };
    public:
        ListBidirectionalIterator(const ListBidirectionalIterator &it) : _p(it._p) { };

        bool operator!=(ListBidirectionalIterator const& other) const { return _p != other._p; };
        bool operator==(ListBidirectionalIterator const& other) const { return _p == other._p; };
        typename ListBidirectionalIterator::reference operator*() const {
            return *_p;
        };
        ListBidirectionalIterator& operator++() { ++_p; return *this;}
    private:
        T* _p;
    };

    template < class T, class Alloc = std::allocator <T> >
    class list {

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;


        typedef ListBidirectionalIterator<value_type> iterator;
        typedef ListBidirectionalIterator< const value_type> const_iterator;
//        typedef std::reverse_iterator<OwnInputIterator<value_type>> reverse_iterator;
//        typedef std::reverse_iterator<OwnInputIterator<const value_type>> const_reverse_iterator;



        typedef typename std::ptrdiff_t difference_type;
        typedef typename std::size_t size_type;



        explicit list(const allocator_type& alloc = allocator_type());
        explicit list (size_type n, const value_type& val = value_type(),
                       const allocator_type& alloc = allocator_type());

        ~list();

        size_type size() const;

        void push_front (const value_type& val);
        void push_back (const value_type& val);

        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;

//        reverse_iterator rbegin();
//        const_reverse_iterator rbegin() const;
//
//        reverse_iterator rend();
//        const_reverse_iterator rend() const;




    private:

        typedef typename std::allocator < ListNode<T> >  list_node_allocator_type;
        typedef typename std::allocator < ListNode<T> >::pointer  list_node_pointer;


        void increment_size(void)  { this->_size++; (*(_end->_data))++; }
        size_type _size;
        allocator_type _allocator;
        list_node_pointer _head;
        list_node_pointer _tail;
        list_node_pointer _end;
        list_node_allocator_type _listNodeAllocator;

    };



/**
 *  @brief  Creates a %list with no elements.
 *  @param  __a  An allocator object.
 */
    template < class T, class Alloc>
    list<T, Alloc>::list(const list<T, Alloc>::allocator_type& alloc)
            : _size(0), _allocator(alloc), _head(NULL), _tail(NULL) {
                T* tmp = new T();
                _end = new ListNode<value_type>(NULL, NULL, tmp);
    }

    template<class T, class Alloc>
    list<T, Alloc>::list(list::size_type n, const value_type &val, const allocator_type &alloc)
            : _size(0), _allocator(alloc), _head(NULL), _tail(NULL), _listNodeAllocator(list_node_allocator_type()) {
        T* tmp = new T(_size);
        _end = new ListNode<value_type>(NULL, NULL, tmp);

        for (unsigned int i = 0; i < n; i++) {
            this->push_back(val);
        }
    }


    template<class T, class Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::size() const {
        return this->_size;
    }

    template<class T, class Alloc>
    void list<T, Alloc>::push_back(const value_type &val) {

        pointer ptr = _allocator.allocate(1);
        list_node_pointer ptrLN = _listNodeAllocator.allocate(1);
        _allocator.construct(ptr, val);
        _listNodeAllocator.construct(ptrLN, ListNode<value_type>(_tail, NULL, ptr));
        if (_tail) {
            _tail->_ptrNext = ptrLN;
        }
        _tail = ptrLN;
        if (_head == NULL) {
            _head = ptrLN;
        }
        increment_size();
    }

    template<class T, class Alloc>
    void list<T, Alloc>::push_front(const value_type &val) {
        pointer ptr = _allocator.allocate(1);
        list_node_pointer ptrLN = _listNodeAllocator.allocate(1);
        _allocator.construct(ptr, val);
        _listNodeAllocator.construct(ptrLN, ListNode<value_type>(NULL, _head, ptr));
        if (_head) {
            _head->_ptrPrev = ptrLN;
        }
        _head = ptrLN;
        if (_tail == NULL) {
            _tail = ptrLN;
        }
        increment_size();
    }

    template<class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::begin() {
        if (_head) {
            return iterator(_head->_data);
        } else {
            return iterator(_end->_data);
        }
    }

    template<class T, class Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const {
        if (_head) {
            return const_iterator(_head->_data);
        } else {
            return const_iterator(_end->_data);
        }
    }

    template<class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::end() {
        return iterator(_end->_data);
    }

    template<class T, class Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const {
        return const_iterator(_end->_data);
    }

    template<class T, class Alloc>
    list<T, Alloc>::~list() {
        list_node_pointer tmp = _head;
        for(unsigned int i = 0; i < _size; i++) {
            list_node_pointer next = tmp->_ptrNext;
            _allocator.destroy(tmp->_data);
            _listNodeAllocator.destroy(tmp);
            _allocator.deallocate(tmp->_data, 1);
            _listNodeAllocator.deallocate(tmp, 1);
            tmp = next;
        }
//        delete _end->_data;
//        delete _end;
    }

//    template<class T, class Alloc>
//    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin() {
//        return reverse_iterator (end());
////        if (_tail) {
////            return reverse_iterator (_tail->_data);
////        } else {
////            return reverse_iterator(_end->_data);
////        }
//    }
//
//    template<class T, class Alloc>
//    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin() const {
//        return const_reverse_iterator (end());
////        if (_tail) {
////            return const_reverse_iterator(_tail->_data);
////        } else {
////            return const_reverse_iterator (_end->_data);
////        }
//    }
//
//    template<class T, class Alloc>
//    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend() {
//        return reverse_iterator(_end->_data);
//    }
//
//    template<class T, class Alloc>
//    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rend() const {
//        return const_reverse_iterator(_end->_data);
//    }

}

#endif
