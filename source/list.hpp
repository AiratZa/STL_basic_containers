//
// Created by Great Drake on 1/9/21.
//

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <cstdlib>
# include <iostream>

#include "allocator_trairs_wrapper.hpp"

namespace ft {


    // INSIDE REALIZTION STARTS


    namespace __detail {


        struct _ListNodeBase {
            _ListNodeBase* _ptrPrev;
            _ListNodeBase* _ptrNext;

            void _link(_ListNodeBase* _ptr) {
                this->_ptrNext = _ptr;
                this->_ptrPrev = _ptr->_ptrPrev;
                _ptr->_ptrPrev->_ptrNext = this;
                _ptr->_ptrPrev = this;
            }


            void _unlink(void) {
                _ListNodeBase* const _nextNode = this->_ptrNext;
                _ListNodeBase* const _prevNode = this->_ptrPrev;

                _nextNode->_ptrPrev = _prevNode;
                _prevNode->_ptrNext = _nextNode;
            }

            // Moves the elements from [first,last) before position.
            void _relinkElementsIteratorBefore(_ListNodeBase * const __first,
            _ListNodeBase * const __last)
            {
                if (this != __last)
                {
                    // Remove [first, last) from its old position. (forward relinking)
                    __last->_ptrPrev->_ptrNext  = this;
                    __first->_ptrPrev->_ptrNext = __last;
                    this->_ptrPrev->_ptrNext    = __first;

                    // Splice [first, last) into its new position. (backward relinking)
                    _ListNodeBase* const __tmp = this->_ptrPrev;
                    this->_ptrPrev                = __last->_ptrPrev;
                    __last->_ptrPrev              = __first->_ptrPrev;
                    __first->_ptrPrev             = __tmp;
                }
            }


        };

        struct _ListNodeHeader : public _ListNodeBase {
            _ListNodeHeader() : _size(0) {
                _initHead();
            }

            void _initHead() {
                this->_ptrPrev = this->_ptrNext = this;
            }
            std::size_t _size;

        private:
            _ListNodeBase* _getBasePtr() { return this; };
        };

        template < typename value_type >
        struct _ListNode : _ListNodeBase {
            value_type _data;
            value_type* _getDataPtr() { return std::addressof(_data); };
            value_type const* _getDataPtr() const { return std::addressof(_data); };
        };

        template <typename value_type, typename Alloc>
        class _ListBase {
        protected:

            typedef typename __custom::alloc_traits_wrapper<Alloc>::template
            rebind<value_type>::other				_VT_alloc_type;
            typedef __custom::alloc_traits_wrapper<_VT_alloc_type>	_VT_alloc_traits;
            typedef typename _VT_alloc_traits::template
            rebind<_ListNode<value_type> >::other _Node_alloc_type;
            typedef __custom::alloc_traits_wrapper<_Node_alloc_type> _Node_alloc_traits;

            static std::size_t _distanceBetweenNodeBases(const _ListNodeBase* _first, const _ListNodeBase* _second) {
                std::size_t count = 0;
                while (_first != _second) {
                    _first = _first->_ptrNext;
                    ++count;
                }
                return count;
            }

            struct _ListNodeAllocation : public _Node_alloc_type {

                _ListNodeHeader _node;

                _ListNodeAllocation() : _Node_alloc_type () { };
                _ListNodeAllocation(const _Node_alloc_type& _allocator) : _Node_alloc_type(_allocator) { };

            };

            _ListNodeAllocation _base;

            std::size_t _Base_get_size() { return 0; };



            std::size_t _countNodes() const {
                return _distanceBetweenNodeBases(_base._node._ptrNext, std::addressof(_base._node));
            }

            typename _Node_alloc_traits::pointer _allocateListNode() {
                return  _Node_alloc_traits::allocate(_base, 1);
            };

            void _deallocateListNode(typename _Node_alloc_traits::pointer _ptr) {
                return  _Node_alloc_traits::deallocate(_base, _ptr, 1);
            };

            void _incrementSize(std::size_t _n) {
                _base._node._size += _n;
            }

            void _decrementSize(std::size_t _n) {
                _base._node._size += _n;
            }

            void _setSize(std::size_t _n) {
                _base._node._size = _n;
            }

        public:
            typedef Alloc allocator_type;

//            _Node_alloc_type& getNodeAllocator() { return this->_base; };
//            const _Node_alloc_type& getNodeAllocator() const { return this->_base; };

            _ListBase()  { };

            _ListBase(const _Node_alloc_type& _allocator) : _base(_allocator) { };

            void _clearAllNodes() {
                typedef _ListNode<value_type>  _Node;
                __detail::_ListNodeBase* __cur = _base._node._ptrNext;
                while (__cur != &_base._node)
                {
                    _Node* __tmp = static_cast<_Node*>(__cur);
                    __cur = __tmp->_ptrNext;
                    value_type* __val = __tmp->_getDataPtr();
                    _VT_alloc_type(_base).destroy(__val);//destructs an object in allocated storage
                    _deallocateListNode(__tmp);
                }
            }

            ~_ListBase() {
                _clearAllNodes();
            };

            void _BaseInit() {
                (this->_base)._node._initHead();
            }

        };


    }
    // INSIDE REALIZTION ENDS



    // CUSTOM ITERATORS STARTS

    template<class VT >
struct _ListIterator
{
    typedef _ListIterator<VT>		_Self;
    typedef __detail::_ListNode<VT>			_Node;

    typedef std::ptrdiff_t				difference_type;
    typedef std::bidirectional_iterator_tag	iterator_category;
    typedef VT				value_type;
    typedef VT*				pointer;
    typedef VT&				reference;

    // The only member points to the %list element.
    __detail::_ListNodeBase* _nodeBase;


    _ListIterator() : _nodeBase() { }

    explicit _ListIterator(__detail::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };

    _Self
    _getIteratorCopy() const
    { return *this; }

    reference
    operator*() const
    { return *(static_cast<_Node*>(_nodeBase)->_getDataPtr()); }

    pointer
    operator->() const
    { return *(static_cast<_Node*>(_nodeBase)->_getDataPtr());  }

    _Self&
    operator++()
    {
        _nodeBase = _nodeBase->_ptrNext;
        return *this;
    }

    _Self
    operator++(int)
    {
        _Self __tmp = *this;
        _nodeBase = _nodeBase->_ptrNext;
        return __tmp;
    }

    _Self&
    operator--()
    {
        _nodeBase = _nodeBase->_ptrPrev;
        return *this;
    }

    _Self
    operator--(int)
    {
        _Self __tmp = *this;
        _nodeBase = _nodeBase->_ptrPrev;
        return __tmp;
    }

    friend bool
    operator==(const _Self& __x, const _Self& __y)
    { return __x._nodeBase == __y._nodeBase; }

    friend bool
    operator!=(const _Self& __x, const _Self& __y)
    { return __x._nodeBase != __y._nodeBase; }


};


    template<class VT >
    struct _ListConstIterator
    {
        typedef _ListConstIterator<VT>		_Self;
        typedef const __detail::_ListNode<VT>			_Node;
        typedef _ListIterator<VT>			iterator;

        typedef std::ptrdiff_t				difference_type;
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef VT				value_type;
        typedef const VT*				pointer;
        typedef const VT&				reference;

        // The only member points to the %list element.
        const __detail::_ListNodeBase* _nodeBase;

    _ListConstIterator() : _nodeBase() { }

    explicit _ListConstIterator(const __detail::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };

    explicit _ListConstIterator(const iterator& _it) : _nodeBase(_it._nodeBase) { };

//        iterator
//        _M_const_cast() const
//        { return iterator(const_cast<__detail::_ListNodeBase*>(_nodeBase)); }

    reference
    operator*() const
    { return (*(static_cast<_Node*>(_nodeBase)->_getDataPtr())); }

    pointer
    operator->() const
    { return static_cast<_Node*>(_nodeBase)->_getDataPtr();  }

    _Self&
    operator++()
    {
        _nodeBase = _nodeBase->_ptrNext;
        return *this;
    }

    _Self
    operator++(int)
    {
        _Self __tmp = *this;
        _nodeBase = _nodeBase->_ptrNext;
        return __tmp;
    }

    _Self&
    operator--()
    {
        _nodeBase = _nodeBase->_ptrPrev;
        return *this;
    }

    _Self
    operator--(int)
    {
        _Self __tmp = *this;
        _nodeBase = _nodeBase->_ptrPrev;
        return __tmp;
    }

    friend bool
    operator==(const _Self& __x, const _Self& __y)
    { return __x._nodeBase == __y._nodeBase; }

    friend bool
    operator!=(const _Self& __x, const _Self& __y)
    { return __x._nodeBase != __y._nodeBase; }


};

    // CUSTOM ITERATORS ENDS


    // LIST ITSELF STARTS

    template < class T, class Alloc = std::allocator <T> >
class list : protected __detail::_ListBase<T, Alloc> {
    typedef typename __detail::_ListBase<T, Alloc> _Base;

    typedef typename _Base::_VT_alloc_type _VT_alloc_type;
    typedef typename _Base::_VT_alloc_traits _VT_alloc_traits;
    typedef typename _Base::_Node_alloc_type _Node_alloc_type;
    typedef typename _Base::_Node_alloc_traits _Node_alloc_traits;

    public:
        typedef T value_type;

        typedef Alloc allocator_type;
        typedef typename _VT_alloc_traits::reference reference;
        typedef typename _VT_alloc_traits::const_reference const_reference;
        typedef typename _VT_alloc_traits::pointer pointer;
        typedef typename _VT_alloc_traits::const_pointer const_pointer;

        typedef typename std::ptrdiff_t difference_type;
        typedef typename std::size_t size_type;

        typedef _ListIterator<value_type> iterator;
        typedef _ListConstIterator< const value_type> const_iterator;
        typedef std::reverse_iterator<_ListIterator<value_type>> reverse_iterator;
        typedef std::reverse_iterator<_ListConstIterator<const value_type>> const_reverse_iterator;

    protected:
        typedef typename __detail::_ListNode<value_type> _Node;

    using __detail::_ListBase<value_type , allocator_type >::_allocateListNode;
    using __detail::_ListBase<value_type , allocator_type >::_deallocateListNode;
    using __detail::_ListBase<value_type , allocator_type >::_incrementSize;
    using __detail::_ListBase<value_type , allocator_type >::_decrementSize;
    using __detail::_ListBase<value_type , allocator_type >::_base; //AllocatorObject


        _Node* _createNode(const value_type& _val) {
            _Node* _ptr = _allocateListNode();
            try
            {
                _VT_alloc_type _allocator(_base);
                _allocator.construct(_ptr->_getDataPtr(), _val);
            }
            catch(...)
            {
                _deallocateListNode(_ptr);
                throw;
            }
            return _ptr;
        }

    private:
        list() { };

    public:
        //1. default
        explicit list (const allocator_type& alloc = allocator_type()) : _Base(_Node_alloc_type(alloc)) { };

        //2. fill
        explicit list (size_type n, const value_type& val = value_type(),
                       const allocator_type& alloc = allocator_type()) : _Base(_Node_alloc_type(alloc)) {
            _fill_with_given_value(n, val);
        }


        //All destruction inside ListBase
        ~list() { };


        iterator begin() {
            return iterator (((this->_base)._node._ptrNext));
        }

        const_iterator begin() const {
            return const_iterator ((this->_base)._node._ptrNext);
        }

        iterator end() {
            return iterator (&(this->_base)._node);
        }

        const_iterator end() const {
            return const_iterator (&(this->_base)._node);
        }

        reverse_iterator rbegin() {
            return reverse_iterator (end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator (end());
        }

        reverse_iterator rend() {
            return reverse_iterator (begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator (begin());
        }


// Capacity:

        size_type size() const { return this->_countNodes(); };

        bool empty() const {
                return ((this->_base)._node._ptrNext == &(this->_base)._node);
            }

        size_type max_size() const {
            return _Node_alloc_traits::max_size(this->_base); //returns the largest supported allocation size
        }

//Element access:

        // front Returns a reference to the first element in the list container.
        // Calling this function on an empty container causes undefined behavior.

        reference front() {
            return *(this->begin());
        }

        const_reference front() const {
            return *(this->begin());
        }

        // back Returns a reference to the last element in the list container.
        //Calling this function on an empty container causes undefined behavior.

        reference back() {
            iterator tmp = end();
            --tmp;
            return *tmp;
        }

        const_reference back() const {
            const_iterator tmp = end();
            --tmp;
            return *tmp;
        }


//Modifiers:





    private:

        void _insertValueToIterator(iterator _it, const value_type& _val) {
            _Node* _ptr = _createNode(_val);
            _ptr->_link(_it._nodeBase);
            _incrementSize(1);
        }

        // Erases element at position given
        void _eraseInIteratorPos(iterator _it) {
            _decrementSize(-1);
            (_it._nodeBase)->_unlink();
            _Node* _tmp = static_cast<_Node*>(_it._nodeBase);
            value_type* __val = _tmp->_getDataPtr();
            _VT_alloc_type(_base).destroy(__val);//destructs an object in allocated storage
            _deallocateListNode(_tmp);
        }

    public:

        void push_front (const value_type& val) {
            _insertValueToIterator(begin(), val);
        }

        void push_back (const value_type& val) {
            _insertValueToIterator(end(), val);
        }

        //The container is extended by inserting new elements before the element at the specified position.

        // Returns An iterator that points to the first of the newly inserted elements.
        //single element (1)
        iterator insert (iterator position, const value_type& val) {
            _Node* _ptr = _createNode(val);
            _ptr->_link(position._nodeBase);
            _decrementSize(1);
            return iterator (_ptr);
        }

        //fill (2)
        void insert (iterator position, size_type n, const value_type& val) {
            size_type tmp = 0;
            iterator iterTmp = position;

            while (tmp < n) {
                iterTmp = insert(iterTmp, val);
                tmp++;
            }
        }

        //range (3) todo 1
//        template <class InputIterator>
//        void insert (iterator position, InputIterator first, InputIterator last) {
//            iterator tmpIt;
//
//            while (first != last) {
//                tmpIt = this->insert(position, first)
//            }
//        }





        // Removes from the list container either a single element (position) or a range of elements ([first,last)).

        iterator erase (iterator position) {
            iterator retIt = iterator((position._nodeBase)->_ptrNext);
            this->_eraseInIteratorPos(position);
            return retIt;
        }

        iterator erase (iterator first, iterator last) {
            while (first != last) {
                first = erase(first);
            }
            return first;
        }


    private:
        const_iterator _findBorderIteratorToResize(size_type& _newSize) const
        {
            const_iterator iter;
            size_type curLen = 0;
            for (iter = begin(); iter != end() && curLen < _newSize; ++iter, ++curLen)
                ;
            _newSize -= curLen;
            return iter;
        }

    public:

        void resize (size_type n, value_type val = value_type()) {
            const_iterator iter = _findBorderIteratorToResize(n);//returns iterator that consider current length and end of list ofc
            // and change 'n' (newSize) value
            if (n > 0) {
                insert(end(), n, val);
            } else {
                erase(iter, end());
            }
        }



//TODO
// test splice
// test resize
// finish and test third type of insert





        void clear() {
            _Base::_clearAllNodes();
            _Base::_BaseInit();
        }

        private:
            void _fill_with_given_value(size_type _n, const value_type& _val) {
                for( ; _n; --_n ) {
                    this->push_back(_val);
                }
            }




//Operations

    private:

        // To implement the splice (and merge) bits of N1599.
        void
        _throw_if_non_equal_allocators(list& __x)
        {
            if (std::__alloc_neq<typename _Base::_Node_alloc_type>::_S_do_it(this->_base, __x.base))
                abort();
        }

    public:

        //entire list (1)
        //The first version (1) transfers all the elements of x into the container.
        void splice (iterator position, list& x) {
            if (!x.empty()) {
                _throw_if_non_equal_allocators(x);

                (position._nodeBase)->_relinkElementsIteratorBefore(x.begin(), x.end());

                this->_incrementSize(x.size());
                _Base::_setSize(0);
            }
        }

        //single element (2)
        //The second version (2) transfers only the element pointed by i from x into the container.
        void splice (iterator position, list& x, iterator i) {
            iterator __j = i;
            ++__j;
            if (position == i || position == __j)
                return;

            if (this != std::__addressof(x))
                _throw_if_non_equal_allocators(x);

            (position._nodeBase)->_relinkElementsIteratorBefore(i, __j);

            this->_incrementSize(1);
            x._decrementSize(1);
        }

        //element range (3)
        //The third version (3) transfers the range [first,last) from x into the container.
        void splice (iterator position, list& x, iterator first, iterator last) {
            iterator tmpNext = first._nodeBase->_ptrNext;
            while (tmpNext != last)


            if (first != last)
            {
                if (this != std::__addressof(x))
                    _M_check_equal_allocators(x);

                size_t __n = _Base::_distanceBetweenNodeBases(first, last);
                this->_incrementSize(__n);
                x._decrementSize(__n);

                this->_M_transfer(position,
                                  first,
                                  last);
            }
        }




    };



/**
 *  @brief  Creates a %list with no elements.
 *  @param  __a  An allocator object.
 */
//    template < class T, class Alloc>
//    list<T, Alloc>::list(const list<T, Alloc>::allocator_type& alloc)
//            : _size(0), _allocator(alloc), _head(NULL), _tail(NULL) {
//                T* tmp = new T();
//                _end = new ListNode<value_type>(NULL, NULL, tmp);
//    }





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

    // LIST ITSELF ENDS




}//namespace ft








#endif
