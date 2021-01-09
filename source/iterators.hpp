//
// Created by Great Drake on 1/9/21.
//

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <memory>

template<class T >
class OwnInputIterator: public std::iterator< std::input_iterator_tag, T>
{
    template <class, class Alloc>
    friend class list;

private:
    OwnInputIterator(T* p) : _p(p) { };
public:
    OwnInputIterator(const OwnInputIterator &it) : _p(it._p) { };

    bool operator!=(OwnInputIterator const& other) const { return _p != other._p; };
    bool operator==(OwnInputIterator const& other) const { return _p == other._p; };
    typename OwnInputIterator::reference operator*() const {
        return *_p;
    };
    OwnInputIterator& operator++() { ++_p; return *this;}
private:
    T* _p;
    };

#endif //UNTITLED_ITERATORS_HPP













