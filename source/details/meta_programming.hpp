//
// Created by airat on 05.06.2021.
//

#ifndef FT_CONTAINERS_META_PROGRAMMING_HPP
#define FT_CONTAINERS_META_PROGRAMMING_HPP

namespace ft {
    namespace details {
        // Define a nested type if some predicate holds.
        template<bool, typename>
        struct enable_if
        { };

        template<typename T>
        struct enable_if<true, T>
        { typedef T type; };

        struct true_type { };
        struct false_type { };

        // Compare for equality of types.
        template<typename, typename>
        struct are_same
        {
            enum { value = 0 };
            typedef false_type type;
        };

        template<typename T>
        struct are_same<T, T>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<typename T>
        struct is_integer
        {
            enum { value = 0 };
            typedef false_type type;
        };

        // Thirteen specializations (yes there are eleven standard integer
        // types; <em>long long</em> and <em>unsigned long long</em> are
        // supported as extensions).  Up to four target-specific __int<N>
        // types are supported as well.
        template<>
        struct is_integer<bool>
        {
            enum { value = 1 };
            typedef true_type type;
        };



    }
}


#endif //FT_CONTAINERS_META_PROGRAMMING_HPP
