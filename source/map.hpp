//
// Created by airat on 17.01.2021.
//

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <utility>
#include "details/allocator_traits_wrapper.hpp"
#include "details/red_black_tree.hpp"

namespace ft {

    template < class Key,                                              // map::key_type
            class T,                                                   // map::mapped_type
            class Compare = std::less<Key>,                            // map::key_compare
            class Alloc = std::allocator<std::pair<const Key,T> > >    // map::allocator_type
    class map {

    public:
        typedef Key                     key_type;
        typedef T                       mapped_type;
        typedef std::pair<const Key,T>  value_type;
        typedef Compare                 key_compare;
        typedef Alloc                   allocator_type;

    private:

        typedef typename ft::details::alloc_traits_wrapper<Alloc>::template
                        rebind<value_type>::other Pair_alloc_type_;

        typedef ft::details::Rb_tree<key_type, value_type, std::_Select1st<value_type>,
                        key_compare, Pair_alloc_type_> Rb_tree_type_;

        typedef ft::details::alloc_traits_wrapper<Pair_alloc_type_> Alloc_traits_;

        Rb_tree_type_ tree_;

    public:
        typedef typename Alloc_traits_::reference		        reference;
        typedef typename Alloc_traits_::const_reference	        const_reference;
        typedef typename Alloc_traits_::pointer		            pointer;
        typedef typename Alloc_traits_::const_pointer	        const_pointer;
        typedef typename Rb_tree_type_::iterator		        iterator;
        typedef typename Rb_tree_type_::const_iterator	        const_iterator;
        typedef typename Rb_tree_type_::reverse_iterator        reverse_iterator;
        typedef typename Rb_tree_type_::const_reverse_iterator  const_reverse_iterator;
        typedef typename Rb_tree_type_::difference_type	        difference_type;
        typedef typename Rb_tree_type_::size_type		        size_type;

    // Constructors
        // empty (1)
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type())
                      : tree_(comp, Pair_alloc_type_(alloc)) { }

        // range (2)
        template <class InputIterator>
        map (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type())
             : tree_(comp, Pair_alloc_type_(alloc))
        {
            tree_.insert_range_unique(first, last);
        }

        // copy (3)
        map (const map& x)
            : tree_(x.tree_) { }

    // destructor
    ~map() { }

    // copy (1)
        map& operator= (const map& x)
        {
            tree_ = x.tree_;
            return *this;
        }

    // observers BEGIN

        class value_compare
            : public std::binary_function<value_type, value_type, bool>
        {
            friend class map<Key, T, Compare, Alloc>;
        protected:
            Compare comp;

            value_compare(Compare c)
                    : comp(c) { }

        public:
            bool operator()(const value_type& x, const value_type& y) const
            { return comp(x.first, y.first); }
        };

        key_compare key_comp() const
        { return tree_.key_comp();}

        value_compare value_comp() const
        { return value_compare(tree_.key_comp()); }

    // observers END

        iterator begin()
        { return tree_.begin(); }

        const_iterator begin() const
        { return tree_.begin(); }

        iterator end()
        { return tree_.end(); }

        const_iterator end() const
        { return tree_.end(); }

        reverse_iterator rbegin()
        { return tree_.rbegin(); }

        const_reverse_iterator rbegin() const
        { return tree_.rbegin(); }

        reverse_iterator rend()
        { return tree_.rend(); }

        const_reverse_iterator rend() const
        { return tree_.rend(); }


    // CAPACITY
        bool empty() const
        { return tree_.empty(); }

        size_type size() const
        { return tree_.size();}

        size_type max_size() const
        { return tree_.max_size();}


    // OPERATIONS

        iterator find (const key_type& k)
        { return tree_.find(k); }

        const_iterator find (const key_type& k) const
        { return tree_.find(k); }


        size_type count (const key_type& k) const
        { return tree_.find(k) == tree_.end() ? 0 : 1; }

        /**
         *  This functions return the first element of a subsequence of elements
         *  that matches the given key.  If unsuccessful they return an iterator
         *  pointing to the first element that has a greater value than given key
         *  or end() if no such element exists.
         */

        iterator lower_bound(const key_type& k)
        { return tree_.lower_bound(k); }


        const_iterator lower_bound(const key_type& k) const
        { return tree_.lower_bound(k); }


        iterator upper_bound (const key_type& k)
        { return tree_.upper_bound(k); }


        const_iterator upper_bound (const key_type& k) const
        { return tree_.upper_bound(k); }


        std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        { return tree_.equal_range(k); }

        std::pair<iterator,iterator>             equal_range (const key_type& k)
        { return tree_.equal_range(k); }


        mapped_type& operator[](const key_type& k)
        {
            iterator it = lower_bound(k);
            // it->first is greater than or equivalent to k.
            if (it == end() || key_comp()(k, (*it).first))
                it = insert(it, value_type(k, mapped_type()));
            return (*it).second;
        }

    // INSERT

        // single element (1)
        std::pair<iterator,bool> insert (const value_type& val)
        { return tree_.insert_unique(val); }

        // with hint (2)
        iterator insert (iterator position, const value_type& val)
        {
            return tree_.insert_unique(position, val);
        }

        // range (3)
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            return tree_.insert_range_unique(first, last);
        }

    // ERASE
        // (1)
        void erase (iterator position) {
            tree_.erase(position);
        }

        // (2)
        size_type erase (const key_type& k) {
            return tree_.erase(k);
        }

        // (3)
        void erase (iterator first, iterator last) {
            tree_.erase(first, last);
        }

    // SWAP

        void swap (map& x)
        { tree_.swap(x.tree_); }

    // CLEAR

        void clear()
        { tree_.clear(); }

    // GET_ALLOCATOR

        allocator_type get_allocator() const
        { return allocator_type(tree_.get_allocator()); }


        template<typename K1, typename T1, typename C1, typename A1>
        friend bool
        operator==(const map<K1, T1, C1, A1>&,
                   const map<K1, T1, C1, A1>&);

        template<typename K1, typename T1, typename C1, typename A1>
        friend bool
        operator<(const map<K1, T1, C1, A1>&,
                  const map<K1, T1, C1, A1>&);
    };



    template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator==(const map<Key, T, Compare, Alloc>& x,
               const map<Key, T, Compare, Alloc>& y)
    { return x.tree_ == y.tree_; }


    template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator<(const map<Key, T, Compare, Alloc>& x,
              const map<Key, T, Compare, Alloc>& y)
    { return x.tree_ < y.tree_; }

    /// Based on operator==
    template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator!=(const map<Key, T, Compare, Alloc>& x,
               const map<Key, T, Compare, Alloc>& y)
    { return !(x == y); }

    /// Based on operator<
    template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator>(const map<Key, T, Compare, Alloc>& x,
              const map<Key, T, Compare, Alloc>& y)
    { return y < x; }

    /// Based on operator<
    template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator<=(const map<Key, T, Compare, Alloc>& x,
               const map<Key, T, Compare, Alloc>& y)
    { return !(y < x); }

    /// Based on operator<
    template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator>=(const map<Key, T, Compare, Alloc>& x,
               const map<Key, T, Compare, Alloc>& y)
    { return !(x < y); }

    /// See std::map::swap().
    template<typename Key, typename T, typename Compare, typename Alloc>
    inline void
    swap(map<Key, T, Compare, Alloc>& x,
         map<Key, T, Compare, Alloc>& y)
    { x.swap(y); }



}//namespace ft

#endif
