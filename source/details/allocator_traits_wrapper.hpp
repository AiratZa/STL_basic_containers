//
// Created by airat on 11.01.2021.
//

#ifndef FT_CONTAINERS_ALLOCATOR_TRAITS_WRAPPER_HPP
#define FT_CONTAINERS_ALLOCATOR_TRAITS_WRAPPER_HPP

//#include <bits/allocator.h>

namespace ft {

namespace details {

    template<typename Alloc>
    struct alloc_traits_wrapper {
        typedef Alloc allocator_type;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;
        typedef typename Alloc::value_type value_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::size_type size_type;
        typedef typename Alloc::difference_type difference_type;

        static pointer
        allocate(Alloc &__a, size_type __n) { return __a.allocate(__n); }

        static void deallocate(Alloc &__a, pointer __p, size_type __n) { __a.deallocate(__p, __n); }

        template<typename VT>
        static void construct(Alloc &__a, pointer __p, const VT &__arg) { __a.construct(__p, __arg); }

        static void destroy(Alloc &__a, pointer __p) { __a.destroy(__p); }

        static size_type max_size(const Alloc &__a) { return __a.max_size(); }

        static const Alloc &_S_select_on_copy(const Alloc &__a) { return __a; }

        static void _S_on_swap(Alloc &a, Alloc &b) {
            // _GLIBCXX_RESOLVE_LIB_DEFECTS
            // 431. Swapping containers with unequal allocators.
            Alloc tmp = b;
            b = a;
            a = tmp;
        }

        template<typename VT>
        struct rebind {
            typedef typename Alloc::template rebind<VT>::other other;
        };
    };

    }
}

#endif //FT_CONTAINERS_ALLOCATOR_TRAITS_WRAPPER_HPP
