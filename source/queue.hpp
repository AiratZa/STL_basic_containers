//
// Created by airat on 17.01.2021.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP


#include "list.hpp"

namespace ft {

    // QUEUE ITSELF STARTS

    /* queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out),
     * where elements are inserted into one end of the container and extracted from the other.
    */

    template <class T, class Container = list<T> >
    class queue {

        template <class VT, class Ctnr>
        friend bool operator== (const queue<VT,Ctnr>& lhs, const queue<VT,Ctnr>& rhs);

        template <class VT, class Ctnr>
        friend bool operator<  (const queue<VT,Ctnr>& lhs, const queue<VT,Ctnr>& rhs);


    public:
//// Member types
        typedef T value_type;
        typedef Container container_type;
        typedef typename std::size_t size_type;

//// Member functions

// Constructor(s)

        explicit queue (const container_type& ctnr = container_type())
            : ctnr(ctnr) { }

// Other member functions

        bool empty() const {
            return ctnr.empty();
        }

        size_type size() const {
            return ctnr.size();
        }

        value_type& front() {
            return ctnr.front();
        }

        const value_type& front() const {
            return ctnr.front();
        }

        value_type& back() {
            return ctnr.back();
        }

        const value_type& back() const {
            return ctnr.back();
        }

        void push (const value_type& val) {
            ctnr.push_back(val);
        }


        void pop() {
            ctnr.pop_front();
        }

    private:
        container_type ctnr;

    };

// relational operators (stack)

    template <class T, class Container>
    bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return lhs.ctnr = rhs.ctnr;
    }

    template <class T, class Container>
    bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return ! (lhs == rhs);
    }

    template <class T, class Container>
    bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return lhs.ctnr < rhs.ctnr;
    }

    template <class T, class Container>
    bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return rhs > lhs;
    }

    template <class T, class Container>
    bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
        return !( rhs < lhs );
    }

}//namespace ft



#endif //QUEUE_HPP
