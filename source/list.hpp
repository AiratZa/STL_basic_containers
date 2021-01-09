//
// Created by Great Drake on 1/9/21.
//

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

# include <iostream>

namespace ft {



    template < class T, class Alloc = std::allocator <T> >
    class list {

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename std::ptrdiff_t difference_type;
        typedef typename std::size_t size_type;



        explicit list(const allocator_type& alloc = allocator_type());
        explicit list (size_type n, const value_type& val = value_type(),
                       const allocator_type& alloc = allocator_type());

        ~list() {
            list_node_pointer tmp = _head;
            for(unsigned int i = 0; i < _size; i++) {
                list_node_pointer next = tmp->_ptrNext;
                _allocator.destroy(tmp->_data);
                _listNodeAllocator.destroy(tmp);
                _allocator.deallocate(tmp->_data, 1);
                _listNodeAllocator.deallocate(tmp, 1);
                tmp = next;
            }

        }

        size_type size() const;

        void push_back (const value_type& val);

    private:
        template < typename value_type >
        struct ListNode {
            ListNode() : _ptrPrev(NULL), _ptrNext(NULL), _data(NULL) { };
            ListNode(ListNode<value_type>* ptrPrev, ListNode<value_type>* ptrNext, value_type* data)
                    : _ptrPrev(ptrPrev), _ptrNext(ptrNext), _data(data) { };
            ~ListNode() { };

            typedef typename std::allocator < ListNode<T> >  list_node_allocator_type;
            typedef typename std::allocator < ListNode<T> >::pointer  list_node_pointer;

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

        typedef typename std::allocator < ListNode<T> >  list_node_allocator_type;
        typedef typename std::allocator < ListNode<T> >::pointer  list_node_pointer;
        void _allocate_n_contruct_chunk(const value_type &val);



        size_type _size;
        allocator_type _allocator;
        list_node_pointer _head;
        list_node_pointer _tail;
        list_node_allocator_type _listNodeAllocator;



    };


/**
 *  @brief  Creates a %list with no elements.
 *  @param  __a  An allocator object.
 */
    template < class T, class Alloc>
    list<T, Alloc>::list(const list<T, Alloc>::allocator_type& alloc)
            : _size(0), _allocator(alloc), _head(NULL), _tail(NULL) {
    }

    template<class T, class Alloc>
    list<T, Alloc>::list(list::size_type n, const value_type &val, const allocator_type &alloc)
            : _size(0), _allocator(alloc), _head(NULL), _tail(NULL), _listNodeAllocator(list_node_allocator_type()) {
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
        _size++;
    }













}



#endif
