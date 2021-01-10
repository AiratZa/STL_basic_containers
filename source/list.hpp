//
// Created by Great Drake on 1/9/21.
//

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

# include <iostream>





//template<typename _Alloc>
//struct __alloc_traits
//
//{
//    typedef _Alloc allocator_type;
//    typedef typename _Alloc::pointer                pointer;
//    typedef typename _Alloc::const_pointer          const_pointer;
//    typedef typename _Alloc::value_type             value_type;
//    typedef typename _Alloc::reference              reference;
//    typedef typename _Alloc::const_reference        const_reference;
//    typedef typename _Alloc::size_type              size_type;
//    typedef typename _Alloc::difference_type        difference_type;
//
//    static pointer
//    allocate(_Alloc& __a, size_type __n)
//    { return __a.allocate(__n); }
//
//    static void deallocate(_Alloc& __a, pointer __p, size_type __n)
//    { __a.deallocate(__p, __n); }
//
//    template<typename _Tp>
//    static void construct(_Alloc& __a, pointer __p, const _Tp& __arg)
//    { __a.construct(__p, __arg); }
//
//    static void destroy(_Alloc& __a, pointer __p)
//    { __a.destroy(__p); }
//
//    static size_type max_size(const _Alloc& __a)
//    { return __a.max_size(); }
//
//    static const _Alloc& _S_select_on_copy(const _Alloc& __a) { return __a; }
//
//    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
//    {
//        // _GLIBCXX_RESOLVE_LIB_DEFECTS
//        // 431. Swapping containers with unequal allocators.
//        std::__alloc_swap<_Alloc>::_S_do_it(__a, __b);
//    }
//
//    template<typename _Tp>
//    struct rebind
//    { typedef typename _Alloc::template rebind<_Tp>::other other; };
//};



namespace ft {


    namespace __detail {


        struct _ListNodeBase {
            _ListNodeBase* _ptrPrev;
            _ListNodeBase* _ptrNext;
        };

        struct _ListNodeHeader : public _ListNodeBase {
            _ListNodeHeader() {
                _initHead();
            }

            void _initHead() {
                this->_ptrPrev = this->_ptrNext = this;
            }

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

//            typedef typename __gnu_cxx::__alloc_traits<Alloc>::template
//            rebind<value_type>::other				_VT_alloc_type;
//            typedef __gnu_cxx::__alloc_traits<_VT_alloc_type>	_VT_alloc_traits;
//            typedef typename _VT_alloc_traits::template
//            rebind<_ListNode<value_type> >::other _Node_alloc_type;
//            typedef __gnu_cxx::__alloc_traits<_Node_alloc_type> _Node_alloc_traits;


            typedef typename Alloc::template
            rebind<value_type>::other				_VT_alloc_type;
            typedef _VT_alloc_type	_VT_alloc_traits;
            typedef typename _VT_alloc_traits::template
            rebind<_ListNode<value_type> >::other _Node_alloc_type;
            typedef _Node_alloc_type _Node_alloc_traits;


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
                return _distanceBetweenNodeBases(_base._node->_ptrNext, std::addressof(_base._node));
            }

            typename _Node_alloc_traits::pointer _allocateListNode() {
                return  _Node_alloc_traits::allocate(_base, 1);
            };

            void _deallocateListNode(typename _Node_alloc_traits::pointer _ptr) {
                return  _Node_alloc_traits::allocate(_base, _ptr, 1);
            };

        public:
            typedef Alloc allocator_type;

            _Node_alloc_type& getNodeAllocator() { return this->_base; };
            const _Node_alloc_type& getNodeAllocator() const { return this->_base; };

            _ListBase() { };

            _ListBase(const _Node_alloc_type& _allocator) : _base(_allocator) { };

            ~_ListBase() { };

            void _BaseInit() {
                (this->_base)._node._initHead();
            }

        };


    }


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

//        _Self
//        _M_const_cast() const _GLIBCXX_NOEXCEPT
//        { return *this; }

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
        typedef __detail::_ListNode<VT>			_Node;
        typedef _ListIterator<VT>			_Iterator;

        typedef std::ptrdiff_t				difference_type;
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef VT				value_type;
        typedef const VT*				pointer;
        typedef const VT&				reference;

        // The only member points to the %list element.
        const __detail::_ListNodeBase* _nodeBase;

    _ListConstIterator() : _nodeBase() { }

    explicit _ListConstIterator(__detail::_ListNodeBase* nodeBase) : _nodeBase(nodeBase) { };

//        _Self
//        _M_const_cast() const _GLIBCXX_NOEXCEPT
//        { return *this; }

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


        list() { };

//        explicit list(const allocator_type& alloc = allocator_type());
//        explicit list (size_type n, const value_type& val = value_type(),
//                       const allocator_type& alloc = allocator_type());
//
//        ~list();
//
//        size_type size() const;
//
//        void push_front (const value_type& val);
//        void push_back (const value_type& val);

//        iterator begin();
//        const_iterator begin() const;

//        iterator end();
//        const_iterator end() const;

//        reverse_iterator rbegin();
//        const_reverse_iterator rbegin() const;
//
//        reverse_iterator rend();
//        const_reverse_iterator rend() const;





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
//    list<T, Alloc>::list(list::size_type n, const value_type &val, const allocator_type &alloc)
//            : _size(0), _allocator(alloc), _head(NULL), _tail(NULL), _listNodeAllocator(list_node_allocator_type()) {
//        T* tmp = new T(_size);
//        _end = new ListNode<value_type>(NULL, NULL, tmp);
//
//        for (unsigned int i = 0; i < n; i++) {
//            this->push_back(val);
//        }
//    }
//
//
//    template<class T, class Alloc>
//    typename list<T, Alloc>::size_type list<T, Alloc>::size() const {
//        return this->_size;
//    }
//
//    template<class T, class Alloc>
//    void list<T, Alloc>::push_back(const value_type &val) {
//
//        pointer ptr = _allocator.allocate(1);
//        list_node_pointer ptrLN = _listNodeAllocator.allocate(1);
//        _allocator.construct(ptr, val);
//        _listNodeAllocator.construct(ptrLN, ListNode<value_type>(_tail, NULL, ptr));
//        if (_tail) {
//            _tail->_ptrNext = ptrLN;
//        }
//        _tail = ptrLN;
//        if (_head == NULL) {
//            _head = ptrLN;
//        }
//        increment_size();
//    }
//
//    template<class T, class Alloc>
//    void list<T, Alloc>::push_front(const value_type &val) {
//        pointer ptr = _allocator.allocate(1);
//        list_node_pointer ptrLN = _listNodeAllocator.allocate(1);
//        _allocator.construct(ptr, val);
//        _listNodeAllocator.construct(ptrLN, ListNode<value_type>(NULL, _head, ptr));
//        if (_head) {
//            _head->_ptrPrev = ptrLN;
//        }
//        _head = ptrLN;
//        if (_tail == NULL) {
//            _tail = ptrLN;
//        }
//        increment_size();
//    }

//    template<class T, class Alloc>
//    typename list<T, Alloc>::iterator list<T, Alloc>::begin() {
//        if (_head) {
//            return iterator(_head);
//        } else {
//            return iterator(_end);
//        }
//    }

//    template<class T, class Alloc>
//    typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const {
//        if (_head) {
//            return const_iterator(_head);
//        } else {
//            return const_iterator(_end);
//        }
//    }

//    template<class T, class Alloc>
//    typename list<T, Alloc>::iterator list<T, Alloc>::end() {
//        return iterator(_end->_data);
//    }
//
//    template<class T, class Alloc>
//    typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const {
//        return const_iterator(_end->_data);
//    }

//    template<class T, class Alloc>
//    list<T, Alloc>::~list() {
//        list_node_pointer tmp = _head;
//        for(unsigned int i = 0; i < _size; i++) {
//            list_node_pointer next = tmp->_ptrNext;
//            _allocator.destroy(tmp->_data);
//            _listNodeAllocator.destroy(tmp);
//            _allocator.deallocate(tmp->_data, 1);
//            _listNodeAllocator.deallocate(tmp, 1);
//            tmp = next;
//        }
//        delete _end->_data;
//        delete _end;
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

}








#endif
