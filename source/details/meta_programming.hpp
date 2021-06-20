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


        template<>
        struct is_integer<bool>
        {
            enum { value = 1 };
            typedef true_type type;
        };


        template<>
        struct is_integer<char>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<signed char>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<unsigned char>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<wchar_t>
        {
            enum { value = 1 };
            typedef true_type type;
        };


        template<>
        struct is_integer<short>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<unsigned short>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<int>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<unsigned int>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<long>
        {
            enum { value = 1 };
            typedef is_integer type;
        };

        template<>
        struct is_integer<unsigned long>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<long long>
        {
            enum { value = 1 };
            typedef true_type type;
        };

        template<>
        struct is_integer<unsigned long long>
        {
            enum { value = 1 };
            typedef true_type type;
        };



    }
}


#endif //FT_CONTAINERS_META_PROGRAMMING_HPP
