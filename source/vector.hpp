//
// Created by airat on 20.03.2021.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <stdexcept>
#include <iterator>

#include "details/allocator_traits_wrapper.hpp"
#include "details/meta_programming.hpp"
#include "details/iterator.hpp"

namespace ft {


    // INSIDE REALIZTION STARTS

    namespace __details {


        template <typename value_type, typename Alloc>
        class _VectorBase {
        protected:

            typedef typename alloc_traits_wrapper<Alloc>::template
                                rebind<value_type>::other _VT_alloc_type;
            typedef typename alloc_traits_wrapper<_VT_alloc_type>::pointer pointer;

            struct _VectorBaseData {
                pointer _start;
                pointer _finish;
                pointer _end_of_storage;

                _VectorBaseData()
                        : _start(), _finish(), _end_of_storage() {}


                void _copy_data(_VectorBaseData const &other) {
                    _start = other._start;
                    _finish = other._finish;
                    _end_of_storage = other._end_of_storage;
                }

                void _swap_data(_VectorBaseData &other) {
                    _VectorBaseData __tmp;
                    __tmp._copy_data(*this);
                    _copy_data(other);
                    other._copy_data(__tmp);
                }
            };

            struct _VectorBaseCore
                    : public _VT_alloc_type, public _VectorBaseData
            {
                _VectorBaseCore() : _VT_alloc_type() {}

                _VectorBaseCore(_VT_alloc_type const &__a)
                        : _VT_alloc_type(__a) {}
            };


        public:
            typedef Alloc allocator_type;

            _VectorBaseCore core;

            _VT_alloc_type &get_VT_allocator() { return this->core; }

            const _VT_alloc_type &get_VT_allocator() const { return this->core; }

            allocator_type get_allocator() const { return allocator_type(get_VT_allocator()); }

        // pImpl constructors
            _VectorBase() {}

            _VectorBase(const allocator_type &__a)
                : core(__a) {}

            _VectorBase(std::size_t __n)
                :  core()
            { _create_storage(__n); }

            _VectorBase(std::size_t __n, const allocator_type &__a)
                : core(__a)
            { _create_storage(__n); }


            ~_VectorBase() {
                _deallocate(core._start,
                            core._end_of_storage - core._start);
            }


            pointer _allocate(std::size_t __n) {
                typedef alloc_traits_wrapper<_VT_alloc_type> _concrete_alloc;
                return __n != 0 ? _concrete_alloc::allocate(core, __n) : pointer();
            }

            void _deallocate(pointer __p, std::size_t __n) {
                typedef alloc_traits_wrapper<_VT_alloc_type> _concrete_alloc;
                if (__p)
                    _concrete_alloc::deallocate(core, __p, __n);
            }

            void _create_storage(std::size_t __n) {
                this->core._start = this->_allocate(__n);
                this->core._finish = this->core._start;
                this->core._end_of_storage = this->core._start + __n;
            }
        };

    };
    // INSIDE REALIZTION ENDS


    // VECTOR ITSELF STARTS

    template < class T, class Alloc = std::allocator <T> >
    class vector : protected __details::_VectorBase<T, Alloc> {

        typedef typename __details::_VectorBase<T, Alloc> _Base;
        typedef typename _Base::_VT_alloc_type _VT_alloc_type;
        typedef __details::alloc_traits_wrapper<_VT_alloc_type>	_VT_alloc_traits;

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename _VT_alloc_traits::reference reference;
        typedef typename _VT_alloc_traits::const_reference const_reference;
        typedef typename _VT_alloc_traits::pointer pointer;
        typedef typename _VT_alloc_traits::const_pointer const_pointer;

        typedef typename std::ptrdiff_t difference_type;
        typedef typename std::size_t size_type;

        typedef ft::details::NormalIterator<pointer, vector> iterator;
        typedef ft::details::NormalIterator<const_pointer, vector> const_iterator;
        typedef ft::details::reverse_iterator<iterator> reverse_iterator;
        typedef ft::details::reverse_iterator<const_iterator> const_reverse_iterator;
//


    public:

// Constructors

    // default (1)
    explicit vector (const allocator_type& alloc = allocator_type())
        : _Base(alloc)
    {
    };

    // fill (2)
    explicit vector (size_type n, const value_type& val = value_type(),
                     const allocator_type& alloc = allocator_type())
         : _Base(_check_init_len(n, alloc), alloc)
    {
        _fill_initialize(n, val);
    };


    // range (3)
    template <class InputIterator>
    vector (InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type()) {
        typedef typename ft::__details::is_integer<InputIterator>::type Integral;
        _initialize_dispatch(first, last, Integral());
    }

    // copy (4)
    vector (const vector& x) : _Base(x.size(),
                                     _VT_alloc_traits::_S_select_on_copy(x.get_VT_allocator())) {
        this->core._finish = _uninitialized_copy(x.begin(), x.end(), this->core._start);
    }

    ~vector()
    {
        for (pointer tmp = this->core._start; tmp != this->core._finish; ++tmp)
            _VT_alloc_traits::destroy(this->get_VT_allocator(), tmp);
    }


    // copy (1)
    vector& operator= (const vector& x) {
        if (std::__addressof(x) != this)
        {
            const size_type x_len = x.size();
            if (x_len > capacity())
            {
                pointer tmp = _allocate_and_copy(x_len, x.begin(), x.end());
                for (pointer tmp = this->core._start; tmp < this->core._finish; ++tmp)
                    _VT_alloc_traits::destroy(this->get_VT_allocator(), tmp);

                this->_deallocate(this->core._start,
                                  this->core._end_of_storage - this->core._start);
                this->core._start = tmp;
                this->core._end_of_storage = this->core._start + x_len;
            }
            else if (size() >= x_len)
            {
                iterator it = std::copy(x.begin(), x.end(), begin());
                for (iterator tmp = it; tmp != end(); ++tmp)
                    _VT_alloc_traits::destroy(this->get_VT_allocator(), *tmp);
            }
            else
            {
                std::copy(x.core._start, x.core._start + size(),
                          this->core._start);
                _uninitialized_copy_a(x.core._start + size(),
                                      x.core._finish,
                                      this->core._finish);
            }
            this->core._finish = this->core._start + x_len;
        }
    return *this;
    }


    size_type size() const {
        return size_type(this->core._finish - this->core._start);
    }

    size_type max_size() const{
        return _max_size(this->get_VT_allocator());
    }

//    void resize (size_type n, value_type val = value_type()) {
//        if (n > size())
//            _fill_insert(end(), n - size(), val);
//        else if (n < size())
//            _erase_at_end(this->core._start + n);
//    }

    size_type capacity() const {
        return size_type(this->core._end_of_storage - this->core._start);
    }


    // ITERATORS START

    iterator begin() {
        return iterator(this->core._start);
    }

    const_iterator begin() const {
        return const_iterator(this->core._start);
    }

    iterator end() {
        return iterator(this->core._finish);
    }

    const_iterator end() const {
        return const_iterator(this->core._finish);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }


    // ITERATORS END

    reference operator[] (size_type n) {
        return *(this->core._start + n);
    }

    const_reference operator[] (size_type n) const {
        return *(this->core._start + n);
    }


    void push_back(const value_type& val)
    {
        if (this->core._finish != this->core._end_of_storage)
        {
            _VT_alloc_traits::construct(this->core, this->core._finish, val);
            ++this->core._finish;
        }
        else
            _realloc_insert(end(), val);
    }


    void clear()
    { _erase_at_end(this->core._start); }

private:

    // Called by the first initialize_dispatch above and by the
    // vector(n,value,a) constructor.
    void _fill_initialize(size_type n, const value_type& value)
    {
        pointer tmp = this->core._start;
        try
        {
            for (int i = n; i > 0; --i, (void) ++tmp)
                _VT_alloc_traits::construct(this->get_VT_allocator(), tmp, value);
        }
        catch(...)
        {
            for (pointer i = this->core._start; i != tmp; ++i)
                _VT_alloc_traits::destroy(this->get_VT_allocator(), i);
            throw;
        }
        this->core._finish = this->core._start + n;
    }

    template<typename InputIterator>
    pointer _uninitialized_copy(InputIterator _first, InputIterator _last,
                           pointer _start)
    {
        pointer cur = _start;
        try
        {
            for (; _first != _last; ++_first, (void)++cur)
                _VT_alloc_traits::construct(this->get_allocator(), cur, *_first);
             return cur;
        }
        catch(...)
        {
            for (; _start != cur; ++_start)
                _VT_alloc_traits::destroy(this->get_allocator(), _start);
            throw;
        }
    }

    template<typename Integer>
    void _initialize_dispatch(Integer n, Integer value, ft::__details::true_type)
    {
        this->_core._start = _M_allocate(_check_init_len(
                static_cast<size_type>(n), this->get_VT_allocator()));
        this->core._end_of_storage =
                this->core._start + static_cast<size_type>(n);
        _fill_initialize(static_cast<size_type>(n), value);
    }

    template<typename InputIterator>
    void _initialize_dispatch(InputIterator first, InputIterator last,
                           ft::__details::false_type)
    {
        _range_initialize(first, last,
                          std::iterator_traits<InputIterator>::iterator_category());
    }

    // Called by the second initialize_dispatch above
    template<typename InputIterator>
    void
    _range_initialize(InputIterator first, InputIterator last,
                        std::input_iterator_tag)
    {
        try
        {
            for (; first != last; ++first)
                push_back(*first);
        }
        catch(...)
        {
            clear();
            throw;
        }
    }

    // Called by the second initialize_dispatch above
    template<typename ForwardIterator>
    void _range_initialize(ForwardIterator first, ForwardIterator last,
                        std::forward_iterator_tag)
    {
        const size_type n = std::distance(first, last);
        this->core._start = this->_allocate(_check_init_len(n, this->get_VT_allocator()));
        this->core._end_of_storage = this->core._start + n;
        this->core._finish = _uninitialized_copy(first, last, this->core._start);
    }

    void _realloc_insert(iterator position, const T& x)
    {
        const size_type len = _check_len(size_type(1), "vector::_M_realloc_insert");
        pointer old_start = this->core._start;
        pointer old_finish = this->core._finish;

        const size_type elems_before = position - begin();
        pointer new_start(this->_M_allocate(len));
        pointer new_finish(new_start);
        try
        {
            _VT_alloc_traits::construct(this->core,
                                        new_start + elems_before,
                                        x);
            new_finish = pointer();

            new_finish = _uninitialized_copy(old_start, position.base(), new_start);;
            ++new_finish;
            new_finish = _uninitialized_copy(position.base(), old_finish, new_finish);
        }
        catch(...)
        {
            if (!new_finish)
                _VT_alloc_traits::destroy(this->core,
                                          new_start + elems_before);
            else
            {
                for (pointer tmp = new_start; tmp != new_finish; ++tmp)
                    _VT_alloc_traits::destroy(this->get_allocator(), tmp);
            }
            _deallocate(new_start, len);
            throw;
        }
        for (pointer tmp = old_start; tmp != old_finish; ++tmp)
            _VT_alloc_traits::destroy(this->get_allocator(), tmp);

        _deallocate(old_start, this->core._end_of_storage - old_start);
        this->core._start = new_start;
        this->core._finish = new_finish;
        this->core._end_of_storage = new_start + len;
    }

        template<typename ForwardIterator>
        pointer _allocate_and_copy(size_type n,
                             ForwardIterator first, ForwardIterator last)
        {
            pointer result = this->_allocate(n);
            try
            {
                _uninitialized_copy_a(first, last, result);
                return result;
            }
            catch(...)
            {
                this->_deallocate(result, n);
                throw;
            }
        }

//    void _fill_insert(iterator position, size_type n, const value_type& x)
//    {
//        if (n != 0)
//        {
//            if (size_type(this->_M_impl._M_end_of_storage
//                          - this->_M_impl._M_finish) >= n)
//            {
//                value_type __x_copy = __x;
//
//                const size_type __elems_after = end() - __position;
//                pointer __old_finish(this->_M_impl._M_finish);
//                if (__elems_after > n)
//                {
//                    std::__uninitialized_move_a(this->_M_impl._M_finish - n,
//                                                this->_M_impl._M_finish,
//                                                this->_M_impl._M_finish,
//                                                _M_get_Tp_allocator());
//                    this->_M_impl._M_finish += n;
//                    _GLIBCXX_MOVE_BACKWARD3(__position.base(),
//                                            __old_finish - n, __old_finish);
//                    std::fill(__position.base(), __position.base() + n,
//                              __x_copy);
//                }
//                else
//                {
//                    this->_M_impl._M_finish =
//                            std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
//                                                          __n - __elems_after,
//                                                          __x_copy,
//                                                          _M_get_Tp_allocator());
//                    std::__uninitialized_move_a(__position.base(), __old_finish,
//                                                this->_M_impl._M_finish,
//                                                _M_get_Tp_allocator());
//                    this->_M_impl._M_finish += __elems_after;
//                    std::fill(__position.base(), __old_finish, __x_copy);
//                }
//            }
//            else
//            {
//                const size_type __len = _check_len(__n, "vector::_M_fill_insert");
//                const size_type __elems_before = __position - begin();
//                pointer __new_start(this->_M_allocate(__len));
//                pointer __new_finish(__new_start);
//                __try
//                {
//                    // See _M_realloc_insert above.
//                    std::__uninitialized_fill_n_a(__new_start + __elems_before,
//                                                  __n, __x,
//                                                  _M_get_Tp_allocator());
//                    __new_finish = pointer();
//
//                    __new_finish
//                            = std::__uninitialized_move_if_noexcept_a
//                            (this->_M_impl._M_start, __position.base(),
//                             __new_start, _M_get_Tp_allocator());
//
//                    __new_finish += __n;
//
//                    __new_finish
//                            = std::__uninitialized_move_if_noexcept_a
//                            (__position.base(), this->_M_impl._M_finish,
//                             __new_finish, _M_get_Tp_allocator());
//                }
//                catch(...)
//                {
//                    if (!__new_finish)
//                        std::_Destroy(__new_start + __elems_before,
//                                      __new_start + __elems_before + __n,
//                                      _M_get_Tp_allocator());
//                    else
//                        std::_Destroy(__new_start, __new_finish,
//                                      _M_get_Tp_allocator());
//                    _M_deallocate(__new_start, __len);
//                    throw;
//                }
//                std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
//                              _M_get_Tp_allocator());
//                _M_deallocate(this->_M_impl._M_start,
//                              this->_M_impl._M_end_of_storage
//                              - this->_M_impl._M_start);
//                this->_M_impl._M_start = __new_start;
//                this->_M_impl._M_finish = __new_finish;
//                this->_M_impl._M_end_of_storage = __new_start + __len;
//            }
//        }
//    }


// Internal erase functions follow.

    void _erase_at_end(pointer pos)
    {
        if (size_type n = this->core._finish - pos)
        {
            for (pointer tmp = pos; tmp != this->core._finish; ++tmp)
                _VT_alloc_traits::destroy(this->get_VT_allocator(), tmp);
            this->core._finish = pos;
        }
    }


    static size_type _max_size(const _VT_alloc_type& a)
    {
        const std::size_t diffmax
                = std::numeric_limits<difference_type>::max() / sizeof(T);
        const std::size_t allocmax = _VT_alloc_traits::max_size(a);
        return (std::min)(diffmax, allocmax);
    }

    // Called by constructors to check initial size.
    static size_type _check_init_len(size_type __n, const allocator_type& __a)
    {
        if (__n > _max_size(_VT_alloc_type (__a)))
            throw std::length_error(std::string("cannot create ft::vector larger than max_size()"));
        return __n;
    }

    size_type _check_len(size_type n, const char* str) const
    {
        if (max_size() - size() < n)
            throw std::length_error(std::string(str));

        const size_type len = size() + (std::max)(size(), n);
        return (len < size() || len > max_size()) ? max_size() : len;
    }

};


}//namespace ft


#endif //FT_CONTAINERS_VECTOR_HPP
