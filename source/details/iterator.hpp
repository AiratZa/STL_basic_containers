//
// Created by airat on 05.06.2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include "meta_programming.hpp"

namespace ft {
    namespace details {

        template<typename Iterator>
        struct iterator_traits
        {
            typedef typename Iterator::iterator_category iterator_category;
            typedef typename Iterator::value_type        value_type;
            typedef typename Iterator::difference_type   difference_type;
            typedef typename Iterator::pointer           pointer;
            typedef typename Iterator::reference         reference;
        };

        template<typename Category, typename T, typename Distance = std::ptrdiff_t,
                typename Pointer = T*, typename Reference = T&>
        struct iterator
        {
            typedef Category  iterator_category;
            typedef T        value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
        };


        template<typename It>
        class reverse_iterator
                : public iterator<typename iterator_traits<It>::iterator_category,
                        typename iterator_traits<It>::value_type,
                        typename iterator_traits<It>::difference_type,
                        typename iterator_traits<It>::pointer,
                        typename iterator_traits<It>::reference>
        {
        protected:
            It current;

            typedef iterator_traits<It>		traits_type;

        public:
            typedef It					iterator_type;
            typedef typename traits_type::difference_type	difference_type;
            typedef typename traits_type::pointer		pointer;
            typedef typename traits_type::reference		reference;

            reverse_iterator() : current() { }

            explicit reverse_iterator(iterator_type x)
                : current(x) { }

            reverse_iterator(const reverse_iterator& x)
                    : current(x.current) { }

            /**
             *  A %reverse_iterator across other types can be copied if the
             *  underlying %iterator can be converted to the type of @c current.
            */
            template<typename Iter>
            explicit reverse_iterator(const reverse_iterator<Iter>& x)
                    : current(x.base()) { }

            /**
             *  @return  @c current, the %iterator used for underlying work.
            */
            iterator_type base() const
            { return current; }

            reference operator*() const
            {
                It tmp = current;
                return *--tmp;
            }

            /**
             *  @return  A pointer to the value at @c --current
            */
            pointer operator->() const
            {
                It tmp = current;
                --tmp;
                return _to_pointer(tmp);
            }

            reverse_iterator& operator++()
            {
                --current;
                return *this;
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                --current;
                return tmp;
            }

            reverse_iterator& operator--()
            {
                ++current;
                return *this;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                ++current;
                return tmp;
            }

            reverse_iterator operator+(difference_type n) const
            { return reverse_iterator(current - n); }

            reverse_iterator& operator+=(difference_type n)
            {
                current -= n;
                return *this;
            }

            reverse_iterator operator-(difference_type n) const
            { return reverse_iterator(current + n); }

            reverse_iterator& operator-=(difference_type n)
            {
                current += n;
                return *this;
            }

            reference operator[](difference_type n) const
            { return *(*this + n); }

        private:
            template<typename T>
            static T*
            _to_pointer(T* p)
            { return p; }

            template<typename T>
            static pointer
            _to_pointer(T t)
            { return t.operator->(); }
        };


// NORMAL_ITERATOR
        template<typename Iterator, typename Container>
        class NormalIterator
        {
        protected:
            Iterator _current;

            typedef std::iterator_traits<Iterator>		__traits_type;

        public:
            typedef Iterator					iterator_type;
            typedef typename __traits_type::iterator_category iterator_category;
            typedef typename __traits_type::value_type  	value_type;
            typedef typename __traits_type::difference_type 	difference_type;
            typedef typename __traits_type::reference 	reference;
            typedef typename __traits_type::pointer   	pointer;

            NormalIterator()
                    : _current(Iterator()) { }

            explicit
            NormalIterator(const Iterator& __i)
                    : _current(__i) { }


            // Allow iterator to const_iterator conversion
            template<typename _Iter>
            NormalIterator(const NormalIterator<_Iter,
                    typename ft::details::enable_if<(ft::details::are_same<_Iter, typename Container::pointer>::value),
                            Container>::type>& it)
                    : _current(it.base()) { }

            // Forward iterator requirements
            reference operator*() const
            { return *_current; }

            pointer operator->() const
            { return _current; }

            NormalIterator& operator++()
            {
                ++_current;
                return *this;
            }

            NormalIterator operator++(int)
            { return __normal_iterator(_current++); }

            // Bidirectional iterator requirements
            NormalIterator& operator--()
            {
                --_current;
                return *this;
            }

            NormalIterator operator--(int)
            { return NormalIterator(_current--); }

            // Random access iterator requirements
            reference operator[](difference_type __n) const
            { return _current[__n]; }

            NormalIterator& operator+=(difference_type __n)
            { _current += __n; return *this; }

            NormalIterator operator+(difference_type __n) const
            { return NormalIterator(_current + __n); }

            NormalIterator& operator-=(difference_type __n)
            { _current -= __n; return *this; }

            NormalIterator operator-(difference_type __n) const
            { return __normal_iterator(_current - __n); }

            const Iterator& base() const
            { return _current; }
        };

        template<typename Iterator, typename Container>
        inline bool
        operator!=(const NormalIterator<Iterator, Container>& lhs,
                   const NormalIterator<Iterator, Container>& rhs)
        { return lhs.base() != rhs.base(); }
    }
}




#endif //FT_CONTAINERS_ITERATOR_HPP
