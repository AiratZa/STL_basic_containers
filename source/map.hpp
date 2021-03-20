//
// Created by airat on 17.01.2021.
//

#ifndef MAP_HPP
#define MAP_HPP

#include <utility>
#include "details/allocator_traits_wrapper.hpp"

namespace ft {

    // MAP ITSELF STARTS

    template < class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = less<Key>,                     // map::key_compare
            class Alloc = allocator<pair<const Key,T> > >    // map::allocator_type
    class map {

    public:
//// Member types
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type,mapped_type> value_type;

        typedef Compare key_compare;


        class value_compare
                : public std::binary_function<value_type, value_type, bool> {
            friend class map<Key, T, Compare, Alloc>;

            protected:
                Compare comp;

                value_compare(Compare c)
                        : comp(c) { }

            public:
                bool operator()(const value_type& _x, const value_type& _y) const
                { return comp(_x.first, _y.first); }
        };

        typedef Alloc allocator_type;

    private:
        /// This turns a red-black tree into a [multi]map.
        typedef typename __details::alloc_traits_wrapper<_Alloc>::template
        rebind<value_type>::other _Pair_alloc_type;

        typedef _RB_tree<key_type, value_type, _Select1st<value_type>,
        key_compare, _Pair_alloc_type> _RB_tree_type;

        /// The actual tree structure.
        _RB_tree_type _tree;

        typedef __custom::alloc_traits_wrapper<_Pair_alloc_type> _Alloc_traits;

    public:
        typedef typename _Alloc_traits::pointer		 pointer;
        typedef typename _Alloc_traits::const_pointer	 const_pointer;
        typedef typename _Alloc_traits::reference		 reference;
        typedef typename _Alloc_traits::const_reference	 const_reference;
        typedef typename _RB_tree_type::iterator		 iterator;
        typedef typename _RB_tree_type::const_iterator	 const_iterator;
        typedef typename _RB_tree_type::size_type		 size_type;
        typedef typename _RB_tree_type::difference_type	 difference_type;
        typedef typename _RB_tree_type::reverse_iterator	 reverse_iterator;
        typedef typename _RB_tree_type::const_reverse_iterator const_reverse_iterator;



//// Member functions

// Constructor(s)


        // empty (1)
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type())
              : : _tree(comp, _Pair_alloc_type(alloc)) { };

// Other member functions



    };

// relational operators (stack)

//    template <class T, class Container>
//    bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
//        return lhs.ctnr = rhs.ctnr;
//    }
//
//    template <class T, class Container>
//    bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
//        return ! (lhs == rhs);
//    }
//
//    template <class T, class Container>
//    bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
//        return lhs.ctnr < rhs.ctnr;
//    }
//
//    template <class T, class Container>
//    bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
//        return rhs > lhs;
//    }
//
//    template <class T, class Container>
//    bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
//        return rhs < lhs;
//    }
//
//    template <class T, class Container>
//    bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
//        return !( rhs < lhs );
//      }

}//namespace ft

#endif
