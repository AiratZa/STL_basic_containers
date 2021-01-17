//
// Created by airat on 17.01.2021.
//

#ifndef STACK_HPP
# define STACK_HPP

#include "list.hpp"

namespace ft {

    // STACK ITSELF STARTS

    template <class T, class Container = list<T> >
    class stack {

    template <class VT, class Ctnr>
    friend bool operator== (const stack<VT,Ctnr>& lhs, const stack<VT,Ctnr>& rhs);

    template <class VT, class Ctnr>
    friend bool operator< (const stack<VT,Ctnr>& lhs, const stack<VT,Ctnr>& rhs);

    public:
//// Member types
        typedef T value_type;
        typedef Container container_type;
        typedef typename std::size_t size_type;

//// Member functions

// Constructor(s)

        explicit stack (const container_type& ctnr = container_type())
            : ctnr(ctnr) { }

// Other member functions

        bool empty() const {
            return ctnr.empty();
        }

        size_type size() const {
            return ctnr.size();
        }

        value_type& top() {
            return ctnr.back();
        }
        const value_type& top() const {
            return ctnr.back();
        }

        void push (const value_type& val) {
            ctnr.push_back(val);
        }

        void pop() {
            ctnr.pop_back();
        }

    private:
        container_type ctnr;

    };

// relational operators (stack)

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.ctnr == rhs.ctnr;
}

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs == rhs);
}

template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.ctnr < rhs.ctnr;
}

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !( rhs < lhs );
}

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return rhs < lhs;
}

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !( lhs < rhs);
}


}//namespace ft



#endif
