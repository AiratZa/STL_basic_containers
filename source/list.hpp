//
// Created by Great Drake on 1/9/21.
//

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <cstdlib>
# include <iostream>

#include "details/allocator_traits_wrapper.hpp"
#include "details/meta_programming.hpp"

namespace ft {


    // INSIDE REALIZTION STARTS


    namespace details {

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
            void _relinkElementsBefore(_ListNodeBase * const __first,
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

            static void _swapNodeBases(_ListNodeBase& first, _ListNodeBase& second) {
                _ListNodeBase* tmpFirst = first._ptrNext;

                first._ptrNext = second._ptrNext;
                second._ptrNext = tmpFirst;

                (first._ptrNext)->_ptrPrev = &first;
                (second._ptrNext)->_ptrPrev = &second;

                tmpFirst = first._ptrPrev;

                first._ptrPrev = second._ptrPrev;
                second._ptrPrev = tmpFirst;

                (first._ptrPrev)->_ptrNext = &first;
                (second._ptrPrev)->_ptrNext = &second;
            }


            void _reverse()
            {
                _ListNodeBase* tmp = this;
                do
                {
                    std::swap(tmp->_ptrNext, tmp->_ptrPrev);
                    // Old next node is now prev.
                    tmp = tmp->_ptrPrev;
                }
                while (tmp != this);
            }

        };

        struct _ListNodeHeader : public _ListNodeBase {
            _ListNodeHeader() : _size(0) {
                _initHead();
            }

            void _initHead() {
                this->_ptrPrev = this->_ptrNext = this;
                this->_size = 0;
            }
            std::size_t _size;

        private:
            _ListNodeBase* _getBasePtr() { return this; };
        };

        template < typename value_type >
        struct _ListNode : public _ListNodeBase {
            _ListNode() : _ListNodeBase(), _data(value_type()) {

            }

            value_type _data;
            value_type* _getDataPtr() { return &_data; };
            value_type const* _getDataPtr() const { return &_data; };
        };

        template <typename value_type, typename Alloc>
        class _ListBase {
        protected:

            typedef typename alloc_traits_wrapper<Alloc>::template
            rebind<value_type>::other				_VT_alloc_type;
            typedef alloc_traits_wrapper<_VT_alloc_type>	_VT_alloc_traits;
            typedef typename _VT_alloc_traits::template
            rebind<_ListNode<value_type> >::other _Node_alloc_type;
            typedef alloc_traits_wrapper<_Node_alloc_type> _Node_alloc_traits;

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
                return _distanceBetweenNodeBases(_base._node._ptrNext, &(_base._node));
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
                _base._node._size = _base._node._size - _n;
            }

            void _setSize(std::size_t _n) {
                _base._node._size = _n;
            }

            std::size_t _getSize(void) const{
                return _base._node._size;
            }

        public:
            typedef Alloc allocator_type;

            _Node_alloc_type& getNodeAllocator() { return this->_base; };
            const _Node_alloc_type& getNodeAllocator() const { return this->_base; };

            _ListBase()  { };

            _ListBase(const _Node_alloc_type& _allocator) : _base(_allocator) { };

            void _clearAllNodes() {
                typedef _ListNode<value_type>  _Node;
                details::_ListNodeBase* __cur = _base._node._ptrNext;
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










        // CUSTOM ITERATORS STARTS

        template<class VT >
        struct _ListIterator
        {
            typedef _ListIterator<VT>		_Self;
            typedef details::_ListNode<VT>			_Node;

            typedef std::ptrdiff_t				difference_type;
            typedef std::bidirectional_iterator_tag	iterator_category;
            typedef VT				value_type;
            typedef VT*				pointer;
            typedef VT&				reference;

            // The only member points to the %list element.
            details::_ListNodeBase* _nodeBase;


            _ListIterator() : _nodeBase() { }

            explicit _ListIterator(details::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };

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
            typedef const details::_ListNode<VT>			_Node;
            typedef _ListIterator<VT>			iterator;

            typedef std::ptrdiff_t				difference_type;
            typedef std::bidirectional_iterator_tag	iterator_category;
            typedef VT				value_type;
            typedef const VT*				pointer;
            typedef const VT&				reference;

            // The only member points to the %list element.
            const details::_ListNodeBase* _nodeBase;

            _ListConstIterator() : _nodeBase() { }

            explicit _ListConstIterator(const details::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };

            explicit _ListConstIterator(const iterator& _it) : _nodeBase(_it._nodeBase) { };

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




    }
    // INSIDE REALIZTION ENDS




    // LIST ITSELF STARTS

    template < class T, class Alloc = std::allocator <T> >
class list : protected details::_ListBase<T, Alloc> {
    typedef typename details::_ListBase<T, Alloc> _Base;

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

        typedef details::_ListIterator<value_type> iterator;
        typedef details::_ListConstIterator< const value_type> const_iterator;
        typedef std::reverse_iterator< details::_ListIterator<value_type> > reverse_iterator;
        typedef std::reverse_iterator< details::_ListConstIterator<const value_type> > const_reverse_iterator;

    protected:
        typedef typename details::_ListNode<value_type> _Node;

    using details::_ListBase<value_type , allocator_type >::_allocateListNode;
    using details::_ListBase<value_type , allocator_type >::_deallocateListNode;
    using details::_ListBase<value_type , allocator_type >::_incrementSize;
    using details::_ListBase<value_type , allocator_type >::_decrementSize;
    using details::_ListBase<value_type , allocator_type >::_base; //AllocatorObject


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
        template<typename _Integer>
        void
        _initialize_dispatch(_Integer __n, _Integer __x, ft::details::true_type)
        { _fill_with_given_value(static_cast<size_type>(__n), __x); }

        template<typename InputIterator>
        void
        _initialize_dispatch(InputIterator first, InputIterator last,
                               ft::details::false_type)
        {
            for (; first != last; ++first)
                    push_back(*first);
        }

    public:

// Constructors

        // default (1)
        explicit list (const allocator_type& alloc = allocator_type()) : _Base(_Node_alloc_type(alloc)) { };

        // fill (2)
        explicit list (size_type n, const value_type& val = value_type(),
                       const allocator_type& alloc = allocator_type()) : _Base(_Node_alloc_type(alloc)) {
            _fill_with_given_value(n, val);
        }

        // range (3)
        template <class InputIterator>
        list (InputIterator first, InputIterator last,
              const allocator_type& alloc = allocator_type())
                : _Base(_Node_alloc_type(alloc))
        {
            // Check whether it's an integral type.  If so, it's not an iterator.
            typedef typename ft::details::is_integer<InputIterator>::type Integral;
            _initialize_dispatch(first, last, Integral());
        }

        // copy (4)
        list (const list& x) : _Base(_Node_alloc_traits::_S_select_on_copy(x.getNodeAllocator()))
        { _initialize_dispatch(x.begin(), x.end(), ft::details::false_type()); }


//Destructor

        //All destruction inside ListBase
        ~list() { };


//Iterators

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

        size_type size() const { return _Base::_getSize(); };

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
            _decrementSize(1);
            (_it._nodeBase)->_unlink();
            _Node* _tmp = static_cast<_Node*>(_it._nodeBase);
            value_type* __val = _tmp->_getDataPtr();
            _VT_alloc_type(_base).destroy(__val);//destructs an object in allocated storage
            _deallocateListNode(_tmp);
        }

        void _fill_with_assignation(size_type __n, const value_type& __val)
        {
            iterator __i = begin();
            for (; __i != end() && __n > 0; ++__i, --__n)
                *__i = __val;
            if (__n > 0)
                insert(end(), __n, __val);
            else
                erase(__i, end());
        }


        template<typename _Integer>
        void
        _assign_dispatch(_Integer __n, _Integer __val, ft::details::true_type)
        { this->_fill_with_assignation(__n, __val); }

        // Called by the range assign to implement [23.1.1]/9
        template<typename InputIterator>
        void
        _assign_dispatch(InputIterator first, InputIterator last,
                         ft::details::false_type) {

            iterator __curFirst1 = begin();
            iterator __curLast1 = end();
            for (; __curFirst1 != __curLast1 && first != last;
                   ++__curFirst1, (void)++first)
                *__curFirst1 = *first;
            if (first == last)
                erase(__curFirst1, __curLast1); //erase elements if given range shorter or equal to current size(begin - end range)
            else
                insert(__curLast1, first, last);
        }



    public:

        // range (1)
        // In the range version (1), the new contents are elements constructed from each of the elements in the range between first and last, in the same order.

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last) {
            // Check whether it's an integral type.  If so, it's not an iterator.
            typedef typename ft::details::is_integer<InputIterator>::type Integral;
            _assign_dispatch(first, last, Integral());

        }

        // fill (2)
        void assign (size_type n, const value_type& val) {
            _fill_with_assignation(n, val);
        }

        void push_front (const value_type& val) {
            _insertValueToIterator(begin(), val);
        }

        void pop_front() {
            this->_eraseInIteratorPos(begin());
        }

        void push_back (const value_type& val) {
            _insertValueToIterator(end(), val);
        }

        void pop_back() {
            iterator tmpEnd = this->end();
            --tmpEnd;
            this->_eraseInIteratorPos(tmpEnd);
        }

        //The container is extended by inserting new elements before the element at the specified position.

        // Returns An iterator that points to the first of the newly inserted elements.
        //single element (1)
        iterator insert (iterator position, const value_type& val) {
            _Node* _ptr = _createNode(val);
            _ptr->_link(position._nodeBase);
            _incrementSize(1);
            return iterator (_ptr);
        }

        //fill (2)
        void insert (iterator position, size_type n, const value_type& val) {
            list _tmpList(n, val, _base);
            splice(position, _tmpList);
        }

        //range (3)
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last) {
            list _tmpList(first, last, _base);
            splice(position, _tmpList);
        }

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


        void swap (list& x) {
            details::_ListNodeBase::_swapNodeBases((this->_base)._node,
                                                     x._base._node);

            size_t x_size = x.size();
            x._setSize(this->size());
            this->_setSize(x_size);

            _Node_alloc_traits::_S_on_swap(_base,
                                           x._base);
        }


    private:
        iterator _findBorderIteratorToResize(size_type& _newSize)
        {
            iterator iter;
            size_type curLen = 0;
            for (iter = begin(); iter != end() && curLen < _newSize; ++iter, ++curLen)
                ;
            _newSize -= curLen;
            return iter;
        }

    public:

        void resize (size_type n, value_type val = value_type()) {
            iterator iter = _findBorderIteratorToResize(n);//returns iterator that consider current length and end of list ofc
            // and change 'n' (newSize) value
            if (n > 0) {
                insert(end(), n, val);
            } else {
                erase(iter, end());
            }
        }


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

        // Moves the elements from [first,last) before position.
        void
        _transfer(iterator position, iterator first, iterator last)
        { position._nodeBase->_relinkElementsBefore(first._nodeBase, last._nodeBase); }

//Operations

    public:

        //entire list (1)
        //The first version (1) transfers all the elements of x into the container.
        void splice (iterator position, list& x) {
            if (!x.empty()) {
                (position._nodeBase)->_relinkElementsBefore(x.begin()._nodeBase, x.end()._nodeBase);

                this->_incrementSize(x.size());
                x._Base::_setSize(0);
            }
        }

        //single element (2)
        //The second version (2) transfers only the element pointed by i from x into the container.
        void splice (iterator position, list& x, iterator i) {
            iterator __j = i;
            ++__j;
            if (position == i || position == __j)
                return;
            (position._nodeBase)->_relinkElementsBefore(i._nodeBase, __j._nodeBase);

            this->_incrementSize(1);
            x._decrementSize(1);
        }

        //element range (3)
        //The third version (3) transfers the range [first,last) from x into the container.
        void splice (iterator position, list& x, iterator first, iterator last) {
            if (first != last)
            {
                size_t __n = _Base::_distanceBetweenNodeBases(first._nodeBase, last._nodeBase);
                this->_incrementSize(__n);
                x._decrementSize(__n);

                (position._nodeBase)->_relinkElementsBefore(first._nodeBase, last._nodeBase);
            }
        }

        // Remove elements with specific value
        void remove (const value_type& val) {
            iterator it = this->begin();
            iterator ite = this->end();

            iterator tmp;

            while (it != ite) {
                tmp = it;
                ++tmp;
                if (*it == val) {
                    this->_eraseInIteratorPos(it);
                }
                it = tmp;
            }
        }

        // Remove elements fulfilling condition
        template <class Predicate>
        void remove_if (Predicate pred) {
            iterator it = this->begin();
            iterator ite = this->end();

            iterator tmp;

            while (it != ite) {
                tmp = it;
                ++tmp;
                if (pred(*it)) {
                    this->_eraseInIteratorPos(it);
                }
                it = tmp;
            }
        }


        void unique() {
            iterator _first = begin();
            iterator _last = end();

            iterator _next = _first;
            while (++_next != _last)
            {
                if (*_first == *_next) {
                    this->_eraseInIteratorPos(_next);
                } else {
                    _first = _next;
                }

                _next = _first;
            }
        }

        template <class BinaryPredicate>
        void unique (BinaryPredicate binary_pred) {
            iterator _first = begin();
            iterator _last = end();

            iterator _next = _first;
            while (++_next != _last)
            {
                if (binary_pred(*_first, *_next)) {
                    this->_eraseInIteratorPos(_next);
                } else {
                    _first = _next;
                }

                _next = _first;
            }
        }



        // (1)
        void merge (list& x)
        {
            if (this != std::addressof(x))
            {
                iterator first1 = begin();
                iterator last1 = end();
                iterator first2 = x.begin();
                iterator last2 = x.end();
                const size_t orig_size = x.size();
                try
                {
                        while (first1 != last1 && first2 != last2)
                        if (*first2 < *first1)
                        {
                            iterator next = first2;
                            _transfer(first1, first2, ++next);
                            first2 = next;
                        }
                        else
                        ++first1;
                        if (first2 != last2)
                            _transfer(last1, first2, last2);

                        this->_incrementSize(x._getSize());
                        x._setSize(0);
                }
                catch(...)
                {
                    const size_t dist = std::distance(first2, last2);
                    this->_incrementSize(orig_size - dist);
                    x._setSize(dist);
                    throw;
                }
            }
        }

        // (2)
        template <class Compare>
        void merge (list& x, Compare comp)
        {
            if (this != std::addressof(x))
            {
                iterator first1 = begin();
                iterator last1 = end();
                iterator first2 = x.begin();
                iterator last2 = x.end();
                const size_t orig_size = x.size();
                try
                {
                    while (first1 != last1 && first2 != last2)
                        if (comp(*first2, *first1))
                        {
                            iterator next = first2;
                            _transfer(first1, first2, ++next);
                            first2 = next;
                        }
                        else
                            ++first1;
                    if (first2 != last2)
                        _transfer(last1, first2, last2);

                    this->_incrementSize(x._getSize());
                    x._setSize(0);
                }
                catch(...)
                {
                    const size_t dist = std::distance(first2, last2);
                    this->_incrementSize(orig_size - dist);
                    x._setSize(dist);
                    throw;
                }
            }
        }

        void sort()
        {
            // Do nothing if the list has length 0 or 1.
            if (this->_base._node._ptrNext != &this->_base._node
                && this->_base._node._ptrNext->_ptrNext != &this->_base._node)
            {
                list carry;
                list tmp[64];
                list * fill = tmp;
                list * counter;
                try
                {
                    do
                    {
                        carry.splice(carry.begin(), *this, begin());

                        for(counter = tmp;
                            counter != fill && !counter->empty();
                            ++counter)
                        {
                            counter->merge(carry);
                            carry.swap(*counter);
                        }
                        carry.swap(*counter);
                        if (counter == fill)
                            ++fill;
                    }
                    while ( !empty() );

                    for (counter = tmp + 1; counter != fill; ++counter)
                        counter->merge(*(counter - 1));
                    swap( *(fill - 1) );
                }
                catch(...)
                {
                    this->splice(this->end(), carry);
                    for (int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
                        this->splice(this->end(), tmp[i]);
                    throw;
                }
            }
        }


        template <class Compare>
        void sort (Compare comp)
        {
            // Do nothing if the list has length 0 or 1.
            if (this->_base._node._ptrNext != &this->_base._node
                && this->_base._node._ptrNext->_ptrNext != &this->_base._node)
            {
                list carry;
                list tmp[64];
                list * fill = tmp;
                list * counter;
                try
                {
                    do
                    {
                        carry.splice(carry.begin(), *this, begin());

                        for(counter = tmp;
                            counter != fill && !counter->empty();
                            ++counter)
                        {
                            counter->merge(carry, comp);
                            carry.swap(*counter);
                        }
                        carry.swap(*counter);
                        if (counter == fill)
                            ++fill;
                    }
                    while ( !empty() );

                    for (counter = tmp + 1; counter != fill; ++counter)
                        counter->merge(*(counter - 1), comp);
                    swap(*(fill - 1));
                }
                catch(...)
                {
                    this->splice(this->end(), carry);
                    for (int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
                        this->splice(this->end(), tmp[i]);
                    throw;
                }
            }
        }

        void reverse()
        { this->_base._node._reverse(); }


        allocator_type get_allocator() const
        { return allocator_type(_Base::getNodeAllocator()); }


    };



// relational operators (list)
    template <class T, class Alloc>
    bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        typedef typename list<T, Alloc>::const_iterator const_iterator;

        const_iterator it1 = lhs.begin();
        const_iterator it2 = rhs.begin();

        const_iterator ite1 = lhs.end();
        const_iterator ite2 = rhs.end();

        while (it1 != ite1 && it2 != ite2 && *it1 == *it2)
        {
            ++it1;
            ++it2;
        }
        return it1 == ite1 && it2 == ite2;
    }

    template <class T, class Alloc>
    bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    //// The elements are compared using operator<
    template <class T, class Alloc>
    bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                            rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return !( rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return !( lhs < rhs);
    }


    /* This is an overload of the generic algorithm swap that improves its performance by mutually transferring
     * ownership over their assets to the other container (i.e., the containers exchange references to their data,
     * without actually performing any element copy or movement): It behaves as if x.swap(y) was called.
    */
    template <class T, class Alloc>
    void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
        x.swap(y);
    }


}//namespace ft



#endif
