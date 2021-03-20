//
// Created by airat on 17.01.2021.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_HPP

#include "allocator_traits_wrapper.hpp"

namespace ft {

namespace __details {

    enum _RB_tree_color {
        _RED = false,
        _BLACK = true
    };

    struct _RB_tree_node_base
    {
        typedef _RB_tree_node_base* _Base_ptr;
        typedef const _RB_tree_node_base* _Const_Base_ptr;

        _RB_tree_color	_color;
        _Base_ptr		_parent;
        _Base_ptr		_left;
        _Base_ptr		_right;

//        static _Base_ptr
//        _S_minimum(_Base_ptr __x) _GLIBCXX_NOEXCEPT
//        {
//            while (__x->_M_left != 0) __x = __x->_M_left;
//            return __x;
//        }
//
//        static _Const_Base_ptr
//        _S_minimum(_Const_Base_ptr __x) _GLIBCXX_NOEXCEPT
//        {
//            while (__x->_M_left != 0) __x = __x->_M_left;
//            return __x;
//        }

//        static _Base_ptr
//        _S_maximum(_Base_ptr __x) _GLIBCXX_NOEXCEPT
//        {
//            while (__x->_M_right != 0) __x = __x->_M_right;
//            return __x;
//        }
//
//        static _Const_Base_ptr
//        _S_maximum(_Const_Base_ptr __x) _GLIBCXX_NOEXCEPT
//        {
//            while (__x->_M_right != 0) __x = __x->_M_right;
//            return __x;
//        }
    };

    // Helper type offering value initialization guarantee on the compare functor.
    template<typename key_compare>
    struct _RB_tree_key_compare
    {
        key_compare		_key_compare;

        _RB_tree_key_compare() : _key_compare() { }

        _RB_tree_key_compare(const key_compare& _comp)
                : _key_compare(_comp) { }

    };

    // Helper type to manage default initialization of node count and header.
    struct _RB_tree_header
    {
        _RB_tree_node_base	_header;
        std::size_t		_node_count; // Keeps track of size of tree.

        _Rb_tree_header()
        {
            _header._color = _RED;
            _reset();
        }

//        void
//        _M_move_data(_Rb_tree_header& __from)
//        {
//            _M_header._M_color = __from._M_header._M_color;
//            _M_header._M_parent = __from._M_header._M_parent;
//            _M_header._M_left = __from._M_header._M_left;
//            _M_header._M_right = __from._M_header._M_right;
//            _M_header._M_parent->_M_parent = &_M_header;
//            _M_node_count = __from._M_node_count;
//
//            __from._M_reset();
//        }

        void _reset()
        {
            _header._parent = 0;
            _header._left = &_header;
            _header._right = &_header;
            _node_count = 0;
        }
    };

    template<typename value_type>
    struct _RB_tree_node : public _RB_tree_node_base
    {
        typedef _Rb_tree_node<value_type>* _Link_type;

        value_type _data;

        value_type* _getDataPtr()
        { return &_data; }

        const value_type*  _getDataPtr() const
        { return &_data; }

    };


    template<typename _Key, typename _Val, typename _KeyOfValue,
            typename _Compare, typename _Alloc = allocator<_Val> >
    class _RB_tree
    {
        typedef typename alloc_traits_wrapper<_Alloc>::template
        rebind<_RB_tree_node<_Val> >::other _Node_allocator;

        typedef alloc_traits_wrapper<_Node_allocator> _Alloc_traits;

    protected:
        typedef _RB_tree_node_base* 		_Base_ptr;
        typedef const _RB_tree_node_base* 	_Const_Base_ptr;
        typedef _RB_tree_node<_Val>* 		_Link_type;
        typedef const _RB_tree_node<_Val>*	_Const_Link_type;

    public:
        typedef _Key 				key_type;
        typedef _Val 				value_type;
        typedef value_type* 			pointer;
        typedef const value_type* 		const_pointer;
        typedef value_type& 			reference;
        typedef const value_type& 		const_reference;
        typedef std::size_t 				size_type;
        typedef std::ptrdiff_t 			difference_type;
        typedef _Alloc 				allocator_type;






    };



}
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_HPP
