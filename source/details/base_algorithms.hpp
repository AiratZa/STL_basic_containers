//
// Created by airat on 14.06.2021.
//

#ifndef FT_CONTAINERS_BASE_ALGORITHMS_HPP
#define FT_CONTAINERS_BASE_ALGORITHMS_HPP

#include "allocator_traits_wrapper.hpp"

namespace ft {
    namespace details {

        template< class BidirIt1, class BidirIt2 >
        BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
        {
            while (first != last) {
                *(--d_last) = *(--last);
            }
            return d_last;
        }


        template< class ForwardIt, class T >
        void fill(ForwardIt first, ForwardIt last, const T& value)
        {
            for (; first != last; ++first) {
                *first = value;
            }
        }

        template<typename ForwardIterator, typename Size, typename T,
                typename Allocator>
        ForwardIterator uninitialized_fill_n_a(ForwardIterator first, Size n,
                                               const T& x, Allocator& alloc)
        {
            ForwardIterator cur = first;
            typedef ft::details::alloc_traits_wrapper<Allocator> traits;
            try
            {
                for (; n > 0; --n, (void) ++cur)
                    traits::construct(alloc, std::addressof(*cur), x);
                return cur;
            }
            catch(...)
            {
                for (ForwardIterator tmp = first; tmp != cur; ++tmp)
                    traits::destroy(alloc, std::addressof(*tmp));
                throw;
            }
        }

        template<typename InputIterator, typename ForwardIterator,
                typename Allocator>
        ForwardIterator uninitialized_copy_a(InputIterator first, InputIterator last,
                                             ForwardIterator result, Allocator& alloc)
        {
            ForwardIterator cur = result;
            typedef ft::details::alloc_traits_wrapper<Allocator> traits;
            try
            {
                for (; first != last; ++first, (void)++cur)
                    traits::construct(alloc, std::addressof(*cur), *first);
                return cur;
            }
            catch(...)
            {
                for (ForwardIterator tmp = result; tmp != cur; ++tmp)
                    traits::destroy(alloc, std::addressof(*tmp));
                throw;
            }
        }

        template<typename ForwardIterator, typename Allocator>
        void Destroy(ForwardIterator first, ForwardIterator last,
                 Allocator& alloc)
        {
            typedef ft::details::alloc_traits_wrapper<Allocator> traits;
            for (; first != last; ++first)
                traits::destroy(alloc, std::addressof(*first));
        }


    }
}



#endif //FT_CONTAINERS_BASE_ALGORITHMS_HPP
