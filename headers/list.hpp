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


        // typedef typename int size_type;//!!!!



        explicit list(const allocator_type& alloc = allocator_type());
        explicit list (unsigned int n, const value_type& val = value_type(),//!!!! size_type
                const allocator_type& alloc = allocator_type());

    private:

        class Node {
            public:
                T* ptrPrev;
                T* ptrNext;
                T data;
        };

        Node* _head;
        Node* _tail;
        unsigned int _size;



};


/**
 *  @brief  Creates a %list with no elements.
 *  @param  __a  An allocator object.
 */
template < class T, class Alloc>
list<T, Alloc>::list(const list<T, Alloc>::allocator_type& alloc) {
    (void)alloc;
    _size = 0;
    _head = NULL;
    _tail = NULL;
    std::cout << "Hey" << std::endl;
}

template < class T, class Alloc>
list<T, Alloc>::list (unsigned int n, const list<T, Alloc>::value_type& val,
                const list<T, Alloc>::allocator_type& alloc) {

    pointer ptr = alloc.allocate(n);
    alloc.construct(ptr, val);
    std::cout << "HALO!" << std::endl;
}














}



#endif