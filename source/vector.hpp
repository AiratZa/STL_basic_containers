//
// Created by airat on 20.03.2021.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

//# include <memory>
//# include <cstdlib>
//# include <iostream>

#include "details/allocator_traits_wrapper.hpp"

namespace ft {


    // INSIDE REALIZTION STARTS


    namespace __details {


        template <typename value_type, typename Alloc>
        class _VectorBase {
        protected:

            typedef typename alloc_traits_wrapper<Alloc>::template
                                rebind<value_type>::other _VT_alloc_type;
            typedef typename alloc_traits_wrapper<_VT_alloc_type>::pointer pointer;

            struct _VectorBaseData {
                pointer _start;
                pointer _finish;
                pointer _end_of_storage;

                _VectorBaseData()
                        : _start(), _finish(), _end_of_storage() {}


                void
                _copy_data(_VectorBaseData const &__x) {
                    _start = __x._start;
                    _finish = __x._finish;
                    _end_of_storage = __x._end_of_storage;
                }

                void
                _swap_data(_VectorBaseData &__x) {
                    // Do not use std::swap(_M_start, __x._M_start), etc as it loses
                    // information used by TBAA.
                    _VectorBaseData __tmp;
                    __tmp._copy_data(*this);
                    _copy_data(__x);
                    __x._copy_data(__tmp);
                }
            };

            struct _VectorBaseCore
                    : public _VT_alloc_type, public _VectorBaseData {
                _VectorBaseCore()
                        : _VT_alloc_type() {}

                _VectorBaseCore(_VT_alloc_type const &__a)
                        : _VT_alloc_type(__a) {}

            };


        public:
            typedef Alloc allocator_type;

            _VectorBaseCore core;

            _VT_alloc_type &get_VT_allocator() { return this->core; }

            const _VT_alloc_type &get_VT_allocator() const { return this->core; }

            allocator_type get_allocator() const { return allocator_type(get_VT_allocator()); }


            _VectorBase() {}

            _VectorBase(const allocator_type &__a)
                    : core(__a) {}


            _VectorBase(std::size_t __n)
                :  core()
            { _create_storage(__n); }

            _VectorBase(std::size_t __n,
                        const allocator_type &__a
                        )
                : core(__a)
            {_create_storage(__n);}


            ~_VectorBase() {
                _deallocate(core._start,
                              core._end_of_storage - core._start);
            }


            pointer _allocate(std::size_t __n) {
                typedef alloc_traits_wrapper<_VT_alloc_type> _concrete_alloc;
                return __n != 0 ? _concrete_alloc::allocate(core, __n) : pointer();
            }

            void _deallocate(pointer __p, std::size_t __n) {
                typedef alloc_traits_wrapper<_VT_alloc_type> _concrete_alloc;
                if (__p)
                    _concrete_alloc::deallocate(core, __p, __n);
            }

            void _create_storage(std::size_t __n) {
                this->core_alloc._start = this->_allocate(__n);
                this->core_alloc._finish = this->core_alloc._start;
                this->core_alloc._end_of_storage = this->core_alloc._start + __n;
            }
        };

    };
    // INSIDE REALIZTION ENDS



    // CUSTOM ITERATORS STARTS

//    template<class VT >
//    struct _ListIterator
//    {
//        typedef _ListIterator<VT>		_Self;
//        typedef __details::_ListNode<VT>			_Node;
//
//        typedef std::ptrdiff_t				difference_type;
//        typedef std::bidirectional_iterator_tag	iterator_category;
//        typedef VT				value_type;
//        typedef VT*				pointer;
//        typedef VT&				reference;
//
//        // The only member points to the %list element.
//        __details::_ListNodeBase* _nodeBase;
//
//
//        _ListIterator() : _nodeBase() { }
//
//        explicit _ListIterator(__details::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };
//
//        _Self
//        _getIteratorCopy() const
//        { return *this; }
//
//        reference
//        operator*() const
//        { return *(static_cast<_Node*>(_nodeBase)->_getDataPtr()); }
//
//        pointer
//        operator->() const
//        { return *(static_cast<_Node*>(_nodeBase)->_getDataPtr());  }
//
//        _Self&
//        operator++()
//        {
//            _nodeBase = _nodeBase->_ptrNext;
//            return *this;
//        }
//
//        _Self
//        operator++(int)
//        {
//            _Self __tmp = *this;
//            _nodeBase = _nodeBase->_ptrNext;
//            return __tmp;
//        }
//
//        _Self&
//        operator--()
//        {
//            _nodeBase = _nodeBase->_ptrPrev;
//            return *this;
//        }
//
//        _Self
//        operator--(int)
//        {
//            _Self __tmp = *this;
//            _nodeBase = _nodeBase->_ptrPrev;
//            return __tmp;
//        }
//
//        friend bool
//        operator==(const _Self& __x, const _Self& __y)
//        { return __x._nodeBase == __y._nodeBase; }
//
//        friend bool
//        operator!=(const _Self& __x, const _Self& __y)
//        { return __x._nodeBase != __y._nodeBase; }
//
//
//    };
//
//
//    template<class VT >
//    struct _ListConstIterator
//    {
//        typedef _ListConstIterator<VT>		_Self;
//        typedef const __details::_ListNode<VT>			_Node;
//        typedef _ListIterator<VT>			iterator;
//
//        typedef std::ptrdiff_t				difference_type;
//        typedef std::bidirectional_iterator_tag	iterator_category;
//        typedef VT				value_type;
//        typedef const VT*				pointer;
//        typedef const VT&				reference;
//
//        // The only member points to the %list element.
//        const __details::_ListNodeBase* _nodeBase;
//
//        _ListConstIterator() : _nodeBase() { }
//
//        explicit _ListConstIterator(const __details::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };
//
//        explicit _ListConstIterator(const iterator& _it) : _nodeBase(_it._nodeBase) { };
//
////        iterator
////        _M_const_cast() const
////        { return iterator(const_cast<__details::_ListNodeBase*>(_nodeBase)); }
//
//        reference
//        operator*() const
//        { return (*(static_cast<_Node*>(_nodeBase)->_getDataPtr())); }
//
//        pointer
//        operator->() const
//        { return static_cast<_Node*>(_nodeBase)->_getDataPtr();  }
//
//        _Self&
//        operator++()
//        {
//            _nodeBase = _nodeBase->_ptrNext;
//            return *this;
//        }
//
//        _Self
//        operator++(int)
//        {
//            _Self __tmp = *this;
//            _nodeBase = _nodeBase->_ptrNext;
//            return __tmp;
//        }
//
//        _Self&
//        operator--()
//        {
//            _nodeBase = _nodeBase->_ptrPrev;
//            return *this;
//        }
//
//        _Self
//        operator--(int)
//        {
//            _Self __tmp = *this;
//            _nodeBase = _nodeBase->_ptrPrev;
//            return __tmp;
//        }
//
//        friend bool
//        operator==(const _Self& __x, const _Self& __y)
//        { return __x._nodeBase == __y._nodeBase; }
//
//        friend bool
//        operator!=(const _Self& __x, const _Self& __y)
//        { return __x._nodeBase != __y._nodeBase; }
//
//
//    };

    // CUSTOM ITERATORS ENDS


    // VECTOR ITSELF STARTS

    template < class T, class Alloc = std::allocator <T> >
    class vector : protected __details::_VectorBase<T, Alloc> {
        typedef typename __details::_VectorBase<T, Alloc> _Base;
        typedef typename _Base::_VT_alloc_type _VT_alloc_type;
        typedef __details::alloc_traits_wrapper<_VT_alloc_type>	_VT_alloc_traits;

//        typedef typename _Base::_VT_alloc_traits _VT_alloc_traits;

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename _VT_alloc_traits::reference reference;
        typedef typename _VT_alloc_traits::const_reference const_reference;
        typedef typename _VT_alloc_traits::pointer pointer;
        typedef typename _VT_alloc_traits::const_pointer const_pointer;

        typedef typename std::ptrdiff_t difference_type;
        typedef typename std::size_t size_type;

//        typedef _VectorIterator<value_type> iterator;
//        typedef _VectorConstIterator< const value_type> const_iterator;
//        typedef std::reverse_iterator< _VectorIterator<value_type> > reverse_iterator;
//        typedef std::reverse_iterator< _VectorConstIterator<const value_type> > const_reverse_iterator;
//


    public:

// Constructors

        // default (1)
        explicit vector (const allocator_type& alloc = allocator_type()) { };

//        // fill (2)
//        explicit list (size_type n, const value_type& val = value_type(),
//                       const allocator_type& alloc = allocator_type()) : _Base(_Node_alloc_type(alloc)) {
//            _fill_with_given_value(n, val);
//        }
//
//        // range (3)
//        template <class InputIterator>
//        list (InputIterator first, InputIterator last,
//              const allocator_type& alloc = allocator_type())
//                : _Base(_Node_alloc_type(alloc))
//        {
//            // Check whether it's an integral type.  If so, it's not an iterator.
//            typedef typename std::__is_integer<InputIterator>::__type _Integral;
//            _initialize_dispatch(first, last, _Integral());
//        }
//
//        // copy (4)
//        list (const list& x) {
//
//        }


//Destructor

        //All destruction inside ListBase
        ~vector() { };


//Iterators

//        iterator begin() {
//            return iterator (((this->_base)._node._ptrNext));
//        }
//
//        const_iterator begin() const {
//            return const_iterator ((this->_base)._node._ptrNext);
//        }
//
//        iterator end() {
//            return iterator (&(this->_base)._node);
//        }
//
//        const_iterator end() const {
//            return const_iterator (&(this->_base)._node);
//        }
//
//        reverse_iterator rbegin() {
//            return reverse_iterator (end());
//        }
//
//        const_reverse_iterator rbegin() const {
//            return const_reverse_iterator (end());
//        }
//
//        reverse_iterator rend() {
//            return reverse_iterator (begin());
//        }
//
//        const_reverse_iterator rend() const {
//            return const_reverse_iterator (begin());
//        }


// Capacity:

//        size_type size() const { return _Base::_getSize(); };
//
//        bool empty() const {
//            return ((this->_base)._node._ptrNext == &(this->_base)._node);
//        }
//
//        size_type max_size() const {
//            return _Node_alloc_traits::max_size(this->_base); //returns the largest supported allocation size
//        }

//Element access:

        // front Returns a reference to the first element in the list container.
        // Calling this function on an empty container causes undefined behavior.

//        reference front() {
//            return *(this->begin());
//        }
//
//        const_reference front() const {
//            return *(this->begin());
//        }

        // back Returns a reference to the last element in the list container.
        //Calling this function on an empty container causes undefined behavior.

//        reference back() {
//            iterator tmp = end();
//            --tmp;
//            return *tmp;
//        }
//
//        const_reference back() const {
//            const_iterator tmp = end();
//            --tmp;
//            return *tmp;
//        }


//Modifiers:

    private:

//        void _insertValueToIterator(iterator _it, const value_type& _val) {
//            _Node* _ptr = _createNode(_val);
//            _ptr->_link(_it._nodeBase);
//            _incrementSize(1);
//        }

        // Erases element at position given
//        void _eraseInIteratorPos(iterator _it) {
//            _decrementSize(1);
//            (_it._nodeBase)->_unlink();
//            _Node* _tmp = static_cast<_Node*>(_it._nodeBase);
//            value_type* __val = _tmp->_getDataPtr();
//            _VT_alloc_type(_base).destroy(__val);//destructs an object in allocated storage
//            _deallocateListNode(_tmp);
//        }
//
//        void _fill_with_assignation(size_type __n, const value_type& __val)
//        {
//            iterator __i = begin();
//            for (; __i != end() && __n > 0; ++__i, --__n)
//                *__i = __val;
//            if (__n > 0)
//                insert(end(), __n, __val);
//            else
//                erase(__i, end());
//        }
//
//
//        template<typename _Integer>
//        void
//        _assign_dispatch(_Integer __n, _Integer __val, std::__true_type)
//        { this->_fill_with_assignation(__n, __val); }
//
//        // Called by the range assign to implement [23.1.1]/9
//        template<typename InputIterator>
//        void
//        _assign_dispatch(InputIterator first, InputIterator last,
//                         std::__false_type) {
//
//            iterator __curFirst1 = begin();
//            iterator __curLast1 = end();
//            for (; __curFirst1 != __curLast1 && first != last;
//                   ++__curFirst1, (void)++first)
//                *__curFirst1 = *first;
//            if (first == last)
//                erase(__curFirst1, __curLast1); //erase elements if given range shorter or equal to current size(begin - end range)
//            else
//                insert(__curLast1, first, last);
//        }



    public:

        // range (1)
        // In the range version (1), the new contents are elements constructed from each of the elements in the range between first and last, in the same order.

//        template <class InputIterator>
//        void assign (InputIterator first, InputIterator last) {
//            // Check whether it's an integral type.  If so, it's not an iterator.
//            typedef typename std::__is_integer<InputIterator>::__type _Integral;
//            _assign_dispatch(first, last, _Integral());
//
//        }
//
//        // fill (2)
//        void assign (size_type n, const value_type& val) {
//            _fill_with_assignation(n, val);
//        }
//
//        void push_front (const value_type& val) {
//            _insertValueToIterator(begin(), val);
//        }
//
//        void pop_front() {
//            this->_eraseInIteratorPos(begin());
//        }
//
//        void push_back (const value_type& val) {
//            _insertValueToIterator(end(), val);
//        }
//
//        void pop_back() {
//            iterator tmpEnd = this->end();
//            --tmpEnd;
//            this->_eraseInIteratorPos(tmpEnd);
//        }
//
//        //The container is extended by inserting new elements before the element at the specified position.
//
//        // Returns An iterator that points to the first of the newly inserted elements.
//        //single element (1)
//        iterator insert (iterator position, const value_type& val) {
//            _Node* _ptr = _createNode(val);
//            _ptr->_link(position._nodeBase);
//            _incrementSize(1);
//            return iterator (_ptr);
//        }
//
//        //fill (2)
//        void insert (iterator position, size_type n, const value_type& val) {
//            list _tmpList(n, val, _base);
//            splice(position, _tmpList);
//        }
//
//        //range (3)
//        template <class InputIterator>
//        void insert (iterator position, InputIterator first, InputIterator last) {
//            list _tmpList(first, last, _base);
//            splice(position, _tmpList);
//        }
//
//
//
//
//
//        // Removes from the list container either a single element (position) or a range of elements ([first,last)).
//
//        iterator erase (iterator position) {
//            iterator retIt = iterator((position._nodeBase)->_ptrNext);
//            this->_eraseInIteratorPos(position);
//            return retIt;
//        }
//
//        iterator erase (iterator first, iterator last) {
//            while (first != last) {
//                first = erase(first);
//            }
//            return first;
//        }
//
//
//        void swap (list& x) {
//            __details::_ListNodeBase::_swapNodeBases((this->_base)._node,
//                                                     x._base._node);
//
//            size_t x_size = x.size();
//            x._setSize(this->size());
//            this->_setSize(x_size);
//
//            _Node_alloc_traits::_S_on_swap(_base,
//                                           x._base);
//        }


    private:
//        iterator _findBorderIteratorToResize(size_type& _newSize)
//        {
//            iterator iter;
//            size_type curLen = 0;
//            for (iter = begin(); iter != end() && curLen < _newSize; ++iter, ++curLen)
//                ;
//            _newSize -= curLen;
//            return iter;
//        }

    public:

//        void resize (size_type n, value_type val = value_type()) {
//            iterator iter = _findBorderIteratorToResize(n);//returns iterator that consider current length and end of list ofc
//            // and change 'n' (newSize) value
//            if (n > 0) {
//                insert(end(), n, val);
//            } else {
//                erase(iter, end());
//            }
//        }
//
//
//        void clear() {
//            _Base::_clearAllNodes();
//            _Base::_BaseInit();
//        }

    private:
//        void _fill_with_given_value(size_type _n, const value_type& _val) {
//            for( ; _n; --_n ) {
//                this->push_back(_val);
//            }
//        }




//Operations

    private:

        // To implement the splice (and merge) bits of N1599.
//        void
//        _throw_if_non_equal_allocators(list& __x)
//        {
//            if (std::__alloc_neq<typename _Base::_Node_alloc_type>::_S_do_it(this->_base, __x._base))
//                abort();
//        }

    public:

        //entire list (1)
        //The first version (1) transfers all the elements of x into the container.
//        void splice (iterator position, list& x) {
//            if (!x.empty()) {
//                _throw_if_non_equal_allocators(x);
//
//                (position._nodeBase)->_relinkElementsBefore(x.begin()._nodeBase, x.end()._nodeBase);
//
//                this->_incrementSize(x.size());
//                x._Base::_setSize(0);
//            }
//        }
//
//        //single element (2)
//        //The second version (2) transfers only the element pointed by i from x into the container.
//        void splice (iterator position, list& x, iterator i) {
//            iterator __j = i;
//            ++__j;
//            if (position == i || position == __j)
//                return;
//
//            if (this != std::__addressof(x))
//                _throw_if_non_equal_allocators(x);
//
//            (position._nodeBase)->_relinkElementsBefore(i._nodeBase, __j._nodeBase);
//
//            this->_incrementSize(1);
//            x._decrementSize(1);
//        }
//
//        //element range (3)
//        //The third version (3) transfers the range [first,last) from x into the container.
//        void splice (iterator position, list& x, iterator first, iterator last) {
//            if (first != last)
//            {
//                if (this != std::__addressof(x))
//                    _throw_if_non_equal_allocators(x);
//
//                size_t __n = _Base::_distanceBetweenNodeBases(first._nodeBase, last._nodeBase);
//                this->_incrementSize(__n);
//                x._decrementSize(__n);
//
//                (position._nodeBase)->_relinkElementsBefore(first._nodeBase, last._nodeBase);
//            }
//        }
//
//        // Remove elements with specific value
//        void remove (const value_type& val) {
//            iterator it = this->begin();
//            iterator ite = this->end();
//
//            iterator tmp;
//
//            while (it != ite) {
//                tmp = it;
//                ++tmp;
//                if (*it == val) {
//                    this->_eraseInIteratorPos(it);
//                }
//                it = tmp;
//            }
//        }
//
//        // Remove elements fulfilling condition
//        template <class Predicate>
//        void remove_if (Predicate pred) {
//            iterator it = this->begin();
//            iterator ite = this->end();
//
//            iterator tmp;
//
//            while (it != ite) {
//                tmp = it;
//                ++tmp;
//                if (pred(*it)) {
//                    this->_eraseInIteratorPos(it);
//                }
//                it = tmp;
//            }
//        }
//
//
//        void unique() {
//            iterator _first = begin();
//            iterator _last = end();
//
//            iterator _next = _first;
//            while (++_next != _last)
//            {
//                if (*_first == *_next) {
//                    this->_eraseInIteratorPos(_next);
//                } else {
//                    _first = _next;
//                }
//
//                _next = _first;
//            }
//        }
//
//        template <class BinaryPredicate>
//        void unique (BinaryPredicate binary_pred) {
//            iterator _first = begin();
//            iterator _last = end();
//
//            iterator _next = _first;
//            while (++_next != _last)
//            {
//                if (binary_pred(*_first, *_next)) {
//                    this->_eraseInIteratorPos(_next);
//                } else {
//                    _first = _next;
//                }
//
//                _next = _first;
//            }
//        }
//
//
//
//        void sort() {
//
//        }
//
//
//        template <class Compare>
//        void sort (Compare comp) {
//
//        }




    };



// relational operators (list)
//    template <class T, class Alloc>
//    bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
//        typedef typename list<T, Alloc>::const_iterator const_iterator;
//
//        const_iterator it1 = lhs.begin();
//        const_iterator it2 = rhs.begin();
//
//        const_iterator ite1 = lhs.end();
//        const_iterator ite2 = rhs.end();
//
//        while (it1 != ite1 && it2 != ite2 && *it1 == *it2)
//        {
//            ++it1;
//            ++it2;
//        }
//        return it1 == ite1 && it2 == ite2;
//    }
//
//    template <class T, class Alloc>
//    bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
//        return !(lhs == rhs);
//    }
//
//    //// The elements are compared using operator<
//    template <class T, class Alloc>
//    bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
//        return std::lexicographical_compare(lhs.begin(), lhs.end(),
//                                            rhs.begin(), rhs.end());
//    }
//
//    template <class T, class Alloc>
//    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
//        return !( rhs < lhs);
//    }
//
//    template <class T, class Alloc>
//    bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
//        return (rhs < lhs);
//    }
//
//    template <class T, class Alloc>
//    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
//        return !( lhs < rhs);
//    }
//
//
//    /* This is an overload of the generic algorithm swap that improves its performance by mutually transferring
//     * ownership over their assets to the other container (i.e., the containers exchange references to their data,
//     * without actually performing any element copy or movement): It behaves as if x.swap(y) was called.
//    */
//    template <class T, class Alloc>
//    void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
//        x.swap(y);
//    }


}//namespace ft


#endif //FT_CONTAINERS_VECTOR_HPP
