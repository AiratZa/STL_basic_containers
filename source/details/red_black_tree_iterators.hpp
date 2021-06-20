//
// Created by airat on 14.06.2021.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_ITERATORS_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_ITERATORS_HPP

#include "red_black_tree_parts.hpp"
#include "red_black_tree_utils.hpp"
#include <iterator>

namespace ft {
    namespace details {

        template<typename T>
        struct Rb_tree_iterator
        {
            typedef T  value_type;
            typedef T& reference;
            typedef T* pointer;

            typedef std::bidirectional_iterator_tag  iterator_category;
            typedef std::ptrdiff_t			         difference_type;

            typedef Rb_tree_iterator<T>		    Self;
            typedef Rb_tree_node_base::Base_ptr	Base_ptr;
            typedef Rb_tree_node<T>*            Link_type;

            Base_ptr node_;


            Rb_tree_iterator()
                    : node_() { }

            explicit
            Rb_tree_iterator(Base_ptr x)
                    : node_(x) { }

            reference
            operator*() const
            { return *static_cast<Link_type>(node_)->valptr_(); }

            pointer
            operator->() const
            { return static_cast<Link_type> (node_)->valptr_(); }

            Self& operator++()
            {
                node_ = Rb_tree_increment(node_);
                return *this;
            }

            Self operator++(int)
            {
                Self tmp = *this;
                node_ = Rb_tree_increment(node_);
                return tmp;
            }

            Self& operator--()
            {
                node_ = Rb_tree_decrement(node_);
                return *this;
            }

            Self operator--(int)
            {
                Self tmp = *this;
                node_ = Rb_tree_decrement(node_);
                return tmp;
            }

            friend bool operator==(const Self& x, const Self& y)
            { return x.node_ == y.node_; }

            friend bool operator!=(const Self& x, const Self& y)
            { return x.node_ != y.node_; }

        };

        template<typename T>
        struct Rb_tree_const_iterator
        {
            typedef T	        value_type;
            typedef const T&    reference;
            typedef const T*    pointer;

            typedef Rb_tree_iterator<T> iterator;

            typedef std::bidirectional_iterator_tag  iterator_category;
            typedef std::ptrdiff_t			         difference_type;

            typedef Rb_tree_const_iterator<T>		    Self;
            typedef Rb_tree_node_base::Const_Base_ptr	Base_ptr;
            typedef const Rb_tree_node<T>*			    Link_type;

            Base_ptr node_;

            Rb_tree_const_iterator()
                    : node_() { }

            explicit Rb_tree_const_iterator(Base_ptr x)
                    : node_(x) { }

            Rb_tree_const_iterator(const iterator& it)
                    : node_(it.node_) { }

            iterator const_cast_() const
            { return iterator(const_cast<typename iterator::Base_ptr>(node_)); }

            reference operator*() const
            { return *static_cast<Link_type>(node_)->valptr_(); }

            pointer operator->() const
            { return static_cast<Link_type>(node_)->valptr_(); }

            Self& operator++()
            {
                node_ = Rb_tree_increment(node_);
                return *this;
            }

            Self operator++(int)
            {
                Self tmp = *this;
                node_ = Rb_tree_increment(node_);
                return tmp;
            }

            Self& operator--()
            {
                node_ = Rb_tree_decrement(node_);
                return *this;
            }

            Self operator--(int)
            {
                Self tmp = *this;
                node_ = Rb_tree_decrement(node_);
                return tmp;
            }

            friend bool operator==(const Self& x, const Self& y)
            { return x.node_ == y.node_; }

            friend bool operator!=(const Self& x, const Self& y)
            { return x.node_ != y.node_; }

        };


    }
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_ITERATORS_HPP
