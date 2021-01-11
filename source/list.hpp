//
// Created by Great Drake on 1/9/21.
//

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>

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

            void _plusToSize(std::size_t _n) {
                _base._node._size += _n;
            }

        public:
            typedef Alloc allocator_type;

//            _Node_alloc_type& getNodeAllocator() { return this->_base; };
//            const _Node_alloc_type& getNodeAllocator() const { return this->_base; };

            _ListBase()  { };

            _ListBase(const _Node_alloc_type& _allocator) : _base(_allocator) { };

            ~_ListBase() { };

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

//        _Self
//        _M_const_cast() const
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
    using __detail::_ListBase<value_type , allocator_type >::_plusToSize;
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


        size_type size() const { return this->_countNodes(); };

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




        void push_back (const value_type& val) {
            _insertValueToIterator(end(), val);
        }

    private:
        void _fill_with_given_value(size_type _n, const value_type& _val) {
            for( ; _n; --_n ) {
                this->push_back(_val);
            }
        }

        void _insertValueToIterator(iterator _it, const value_type& _val) {
            _Node* _ptr = _createNode(_val);
            _ptr->_link(_it._nodeBase);
            _plusToSize(1);
        }




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

    // LIST ITSELF ENDS




}//namespace ft








#endif
