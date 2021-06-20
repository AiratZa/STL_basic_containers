//
// Created by airat on 17.01.2021.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_HPP

#include "allocator_traits_wrapper.hpp"
#include "red_black_tree_parts.hpp"
#include "red_black_tree_iterators.hpp"
#include "iterator.hpp"

namespace ft {

namespace details {


    template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc = std::allocator<Val> >
    class Rb_tree
    {
        typedef typename ft::details::alloc_traits_wrapper<Alloc>::template
                                rebind<Rb_tree_node<Val> >::other Node_allocator;

        typedef ft::details::alloc_traits_wrapper<Node_allocator> Alloc_traits;

    protected:
        typedef Rb_tree_node_base* 		    Base_ptr;
        typedef const Rb_tree_node_base* 	Const_Base_ptr;
        typedef Rb_tree_node<Val>*   		Link_type;
        typedef const Rb_tree_node<Val>*	Const_Link_type;

    public:
        typedef Key 	    			key_type;
        typedef Val      				value_type;
        typedef value_type* 			pointer;
        typedef const value_type* 		const_pointer;
        typedef value_type& 			reference;
        typedef const value_type& 		const_reference;
        typedef std::size_t 			size_type;
        typedef std::ptrdiff_t 			difference_type;
        typedef Alloc 				    allocator_type;

    protected:
        template<typename Key_compare>
        struct Rb_tree_impl
                : public Node_allocator
                , public Rb_tree_key_compare<Key_compare>
                , public Rb_tree_header
        {
            typedef Rb_tree_key_compare<Key_compare> Base_key_compare;

            Rb_tree_impl()
                : Node_allocator() { }

            Rb_tree_impl(const Rb_tree_impl& x)
                    : Node_allocator(Alloc_traits::_S_select_on_copy(x))
                    , Base_key_compare(x.key_compare_)
            { }

            Rb_tree_impl(const Key_compare& comp, const Node_allocator& alloc)
                    : Node_allocator(alloc), Base_key_compare(comp)
            { }
        };

        Rb_tree_impl<Compare> impl_; // IMPL

        Base_ptr& root_()
        { return this->impl_.header.parent; }

        Const_Base_ptr root_() const
        { return this->impl_.header.parent; }

        Base_ptr& leftmost_()
        { return this->impl_.header.left; }

        Const_Base_ptr leftmost_() const
        { return this->impl_.header.left; }

        Base_ptr& rightmost_()
        { return this->impl_.header.right; }

        Const_Base_ptr rightmost_() const
        { return this->impl_.header.right; }

        Link_type begin_()
        { return static_cast<Link_type>(this->impl_.header.parent); }

        Const_Link_type begin_() const
        {
            return static_cast<Const_Link_type>
            (this->impl_.header.parent);
        }

        Base_ptr end_()
        { return &this->impl_.header; }

        Const_Base_ptr end_() const
        { return &this->impl_.header; }

        static const_reference S_value_(Const_Link_type x)
        { return *x->valptr_(); }

        static const Key& S_key_(Const_Link_type x)
        {
            return KeyOfValue()(*x->valptr_());
        }

        static Link_type S_left_(Base_ptr x)
        { return static_cast<Link_type>(x->left); }

        static Const_Link_type S_left_(Const_Base_ptr x)
        { return static_cast<Const_Link_type>(x->left); }

        static Link_type S_right_(Base_ptr x)
        { return static_cast<Link_type>(x->right); }

        static Const_Link_type S_right_(Const_Base_ptr x)
        { return static_cast<Const_Link_type>(x->right); }

        static const_reference S_value_(Const_Base_ptr x)
        { return *static_cast<Const_Link_type>(x)->valptr_(); }

        static const Key& S_key_(Const_Base_ptr x)
        { return S_key_(static_cast<Const_Link_type>(x)); }

        static Base_ptr minimum_(Base_ptr x)
        { return Rb_tree_node_base::minimum_(x); }

        static Const_Base_ptr minimum_(Const_Base_ptr x)
        { return Rb_tree_node_base::minimum_(x); }

        static Base_ptr maximum_(Base_ptr x)
        { return Rb_tree_node_base::maximum_(x); }

        static Const_Base_ptr maximum_(Const_Base_ptr x)
        { return Rb_tree_node_base::maximum_(x); }




    public:
        typedef Rb_tree_iterator<value_type>            iterator;
        typedef Rb_tree_const_iterator<value_type>            const_iterator;

        typedef ft::details::reverse_iterator<iterator>         reverse_iterator;
        typedef ft::details::reverse_iterator<const_iterator>   const_reverse_iterator;


        // Constructors / destructors

        Rb_tree() { }

        Rb_tree(const Compare& comp,
                 const allocator_type& alloc = allocator_type())
                : impl_(comp, Node_allocator(alloc)) { }

        Rb_tree(const Rb_tree& x)
                : impl_(x.impl_)
        {
            if (x.root_() != 0)
                root_() = copy_(x);
        }

        ~Rb_tree()
        { erase_(begin_()); }

        Rb_tree& operator=(const Rb_tree& x);

    private:

        struct Alloc_node
        {
                Alloc_node(Rb_tree& t)
                        : tree(t) { }

                template<typename Arg>
                Link_type operator()(const Arg& arg) const
                { return tree.create_node_(arg); }

            private:
                Rb_tree& tree;
        };

    public:

    // Accessors START
        Compare key_comp() const
        { return impl_.key_compare_; }

        iterator begin()
        { return iterator(this->impl_.header.left); }

        const_iterator begin() const
        { return const_iterator(this->impl_.header.left); }

        iterator end()
        { return iterator(&this->impl_.header); }

        const_iterator end() const
        { return const_iterator(&this->impl_.header); }

        reverse_iterator rbegin()
        { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }

        reverse_iterator rend()
        { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

    // Accessors FINISH
    public:
        Node_allocator& get_Node_allocator_()
        { return this->impl_; }

        const Node_allocator& get_Node_allocator_() const
        { return this->impl_; }

        allocator_type get_allocator() const
        { return allocator_type(get_Node_allocator_()); }



    protected:

        Link_type get_node_()
        { return Alloc_traits::allocate(get_Node_allocator_(), 1); }

        void put_node_(Link_type ptr)
        { Alloc_traits::deallocate(get_Node_allocator_(), ptr, 1); }

        void
        construct_node_(Link_type node, const value_type& x)
        {
            try
            { get_allocator().construct(node->valptr_(), x); }
            catch(...)
            {
                put_node_(node);
                throw;
            }
        }

        Link_type create_node_(const value_type& x)
        {
            Link_type tmp = get_node_();
            construct_node_(tmp, x);
            return tmp;
        }

        void destroy_node_(Link_type ptr)
        {
            get_allocator().destroy(ptr->valptr_());
        }

        void drop_node_(Link_type ptr)
        {
            destroy_node_(ptr);
            put_node_(ptr);
        }

        template<typename NodeGen>
        Link_type clone_node_(Const_Link_type x, NodeGen& node_gen)
        {
            Link_type tmp = node_gen(*x->valptr_());
            tmp->color = x->color;
            tmp->left = 0;
            tmp->right = 0;
            return tmp;
        }

    private:

        template<typename NodeGen>
        Link_type copy_(Const_Link_type x, Base_ptr p, NodeGen& node_gen)
        {
            // Structural copy. x and p must be non-null.
            Link_type top = clone_node_(x, node_gen);
            top->parent = p;

            try
            {
                if (x->right)
                    top->right = copy_(S_right_(x), top, node_gen);
                p = top;
                x = S_left_(x);

                while (x != 0)
                {
                    Link_type y = clone_node_(x, node_gen);
                    p->left = y;
                    y->parent = p;
                    if (x->right)
                        y->right = copy_(S_right_(x), y, node_gen);
                    p = y;
                    x = S_left_(x);
                }
            }
            catch(...)
            {
                erase_(top);
                throw;
            }
            return top;
        }

        template<typename NodeGen>
        Link_type copy_(const Rb_tree& x, NodeGen& gen)
        {
            Link_type root = copy_(x.begin_(), end_(), gen);
            leftmost_() = minimum_(root);
            rightmost_() = maximum_(root);
            impl_.node_count = x.impl_.node_count;
            return root;
        }

        Link_type copy_(const Rb_tree& x)
        {
            Alloc_node an(*this);
            return copy_(x, an);
        }

        void erase_(Link_type x)
        {
            // Erase without rebalancing.
            while (x != 0)
            {
                erase_(S_right_(x));
                Link_type y = S_left_(x);
                drop_node_(x);
                x = y;
            }
        }

        iterator lower_bound_(Link_type x, Base_ptr y, const Key& k)
        {
            while (x != 0)
                if (!impl_.key_compare_(S_key_(x), k))
                    y = x, x = S_left_(x);
                else
                    x = S_right_(x);
            return iterator(y);
        }


        const_iterator lower_bound_(Const_Link_type x, Const_Base_ptr y, const Key& k) const
        {
            while (x != 0)
                if (!impl_.key_compare_(S_key_(x), k))
                    y = x, x = S_left_(x);
                else
                    x = S_right_(x);
            return const_iterator(y);
        }

        iterator upper_bound_(Link_type x, Base_ptr y, const Key& key)
        {
            while (x != 0)
                if (impl_.key_compare_(key, S_key_(x)))
                    y = x, x = S_left_(x);
                else
                    x = S_right_(x);
            return iterator(y);
        }


        const_iterator upper_bound_(Const_Link_type x, Const_Base_ptr y, const Key& key) const
        {
            while (x != 0)
                if (impl_.key_compare(key, S_key_(x)))
                    y = x, x = S_left_(x);
                else
                    x = S_right_(x);
            return const_iterator(y);
        }


    public:

        bool empty() const
        { return impl_.node_count == 0; }

        size_type size() const
        { return impl_.node_count; }

        size_type max_size() const
        { return Alloc_traits::max_size(get_Node_allocator_()); }

    // LOWER BOUND

        iterator
        lower_bound(const key_type& k)
        { return lower_bound_(begin_(), end_(), k); }

        const_iterator
        lower_bound(const key_type& k) const
        { return lower_bound_(begin_(), end_(), k); }

    // UPPER BOUND
        iterator upper_bound(const key_type& key)
        { return upper_bound_(begin_(), end_(), key); }

        const_iterator upper_bound(const key_type& key) const
        { return upper_bound_(begin_(), end_(), key); }


    // Inserting helpers

        template<typename NodeGen>
        iterator insert_(Base_ptr x, Base_ptr p, const value_type& v, NodeGen& node_gen)
        {
            bool insert_left = (x != 0 || p == end_()
                                  || impl_.key_compare_(KeyOfValue()(v),
                                                            S_key_(p)));

            Link_type z = node_gen(v);

            Rb_tree_insert_and_rebalance_(insert_left, z, p,
                                          this->impl_.header);
            ++impl_.node_count;
            return iterator(z);
        }



        std::pair<Base_ptr, Base_ptr>
        get_insert_unique_pos_(const key_type& k)
        {
            typedef std::pair<Base_ptr, Base_ptr> Res;
            Link_type x = begin_();
            Base_ptr y = end_();
            bool comp_ = true;
            while (x != 0)
            {
                y = x;
                comp_ = impl_.key_compare_(k, S_key_(x));
                x = comp_ ? S_left_(x) : S_right_(x);
            }
            iterator it = iterator(y);
            if (comp_)
            {
                if (it == begin())
                    return Res(x, y);
                else
                    --it;
            }
            if (impl_.key_compare_(S_key_(it.node_), k))
                return Res(x, y);
            return Res(it.node_, 0);
        }

        std::pair<Base_ptr, Base_ptr>
        get_insert_hint_unique_pos_(const_iterator position,
                                    const key_type& k)
        {
            iterator pos = position.const_cast_();
            typedef std::pair<Base_ptr, Base_ptr> Res;

            // end()
            if (pos.node_ == end_())
            {
                if (size() > 0
                    && impl_.key_compare_(S_key_(rightmost_()), k))
                    return Res(0, rightmost_());
                else
                    return get_insert_unique_pos_(k);
            }
            else if (impl_.key_compare_(k, S_key_(pos.node_)))
            {
                // First, try before...
                iterator before = pos;
                if (pos.node_ == leftmost_()) // begin()
                    return Res(leftmost_(), leftmost_());
                else if (impl_.key_compare_(S_key_((--before).node_), k))
                {
                    if (S_right_(before.node_) == 0)
                        return Res(0, before.node_);
                    else
                        return Res(pos.node_, pos.node_);
                }
                else
                    return get_insert_unique_pos_(k);
            }
            else if (impl_.key_compare_(S_key_(pos.node_), k))
            {
                // ... then try after.
                iterator after = pos;
                if (pos.node_ == rightmost_())
                    return Res(0, rightmost_());
                else if (impl_.key_compare_(k, S_key_((++after).node_)))
                {
                    if (S_right_(pos.node_) == 0)
                        return Res(0, pos.node_);
                    else
                        return Res(after.node_, after.node_);
                }
                else
                    return get_insert_unique_pos_(k);
            }
            else
                // Equivalent keys.
                return Res(pos.node_, 0);
            return Res(pos.node_, 0);
        }


        // Insert
        std::pair<iterator, bool>
        insert_unique(const value_type& x)
        {
            typedef std::pair<iterator, bool> Res;
            std::pair<Base_ptr, Base_ptr> res = get_insert_unique_pos_(KeyOfValue()(x));

            if (res.second)
            {
                Alloc_node an(*this);
                return Res(insert_(res.first, res.second, x, an),
                                    true);
            }

            return Res(iterator(res.first), false);
        }


        template<typename NodeGen>
        iterator insert_unique(const_iterator position,
                                const Val& v,
                                NodeGen& node_gen)
        {
            std::pair<Base_ptr, Base_ptr> res = get_insert_hint_unique_pos_(position, KeyOfValue()(v));

            if (res.second)
                return insert_(res.first, res.second,
                               v, node_gen);
            return iterator(res.first);
        }

        iterator insert_unique(const_iterator pos, const value_type& x)
        {
            Alloc_node an(*this);
            return insert_unique(pos, x, an);
        }

        template<typename InputIterator>
        void insert_range_unique(InputIterator first, InputIterator last)
        {
            Alloc_node an(*this);
            for (; first != last; ++first)
                insert_unique(end(), *first, an);
        }

    // Erase

        void erase_aux_(const_iterator position)
        {
            Link_type y =
                    static_cast<Link_type>(Rb_tree_rebalance_for_erase_
                            (const_cast<Base_ptr>(position.node_),
                             this->impl_.header));
            drop_node_(y);
            --impl_.node_count;
        }

        void erase_aux_(const_iterator first, const_iterator last)
        {
            if (first == begin() && last == end())
                clear();
            else
                while (first != last)
                    erase_aux_(first++);
        }

        void erase(iterator position)
        { erase_aux_(position); }

        void
        erase(const_iterator position)
        { erase_aux_(position); }

        size_type erase(const Key& x)
        {
            std::pair<iterator, iterator> it = equal_range(x);
            const size_type old_size = size();
            erase_aux_(it.first, it.second);
            return old_size - size();
        }

        void erase(iterator first, iterator last)
        { erase_aux_(first, last); }

        void erase(const_iterator first, const_iterator last)
        { erase_aux_(first, last); }

        void erase(const key_type* first, const key_type* last)
        {
            while (first != last)
                erase(*first++);
        }

    // CLEAR

        void clear()
        {
            erase_(begin_());
            impl_.reset_();
        }


    // SWAP

        void swap(Rb_tree& other)
        {
            if (root_() == 0)
            {
                if (other.root_() != 0)
                    impl_.move_data_(other.impl_);
            }
            else if (other.root_() == 0)
                other.impl_.move_data_(impl_);
            else
            {
                std::swap(root_(),other.root_());
                std::swap(leftmost_(),other.leftmost_());
                std::swap(rightmost_(),other.rightmost_());

                root_()->parent = end_();
                other.root_()->parent = other.end_();
                std::swap(this->impl_.node_count, other.impl_.node_count);
            }
            // No need to swap header's color as it does not change.
            std::swap(this->impl_.key_compare_, other.impl_.key_compare_);

            Alloc_traits::_S_on_swap(get_Node_allocator_(),
                                      other.get_Node_allocator_());
        }


    // FIND

        iterator find(const key_type& key)
        {
            iterator it = lower_bound_(begin_(), end_(), key);
            return (it == end() || impl_.key_compare_(key, S_key_(it.node_))) ? end() : it;
        }


        const_iterator find(const key_type& key) const
        {
            const_iterator it = lower_bound_(begin_(), end_(), key);
             return (it == end() || impl_.key_compare_(key, S_key_(it.node_))) ? end() : it;
        }

    // EQUAL RANGE

        std::pair<iterator, iterator> equal_range(const key_type& key)
        {
            Link_type x = begin_();
            Base_ptr y = end_();
            while (x != 0)
            {
                if (impl_.key_compare_(S_key_(x), key))
                    x = S_right_(x);
                else if (impl_.key_compare_(key, S_key_(x)))
                    y = x, x = S_left_(x);
                else
                {
                    Link_type xu(x);
                    Base_ptr yu(y);
                    y = x, x = S_left_(x);
                    xu = S_right_(xu);
                    return std::pair<iterator,
                            iterator>(lower_bound_(x, y, key),
                                      upper_bound_(xu, yu, key));
                }
            }
            return std::pair<iterator, iterator>(iterator(y),
                                            iterator(y));
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
        {
            Const_Link_type x = begin_();
            Const_Base_ptr y = end_();
            while (x != 0)
            {
                if (impl_.key_compare_(S_key_(x), key))
                    x = S_right_(x);
                else if (impl_.key_compare_(key, S_key_(x)))
                    y = x, x = S_left_(x);
                else
                {
                    Const_Link_type xu(x);
                    Const_Base_ptr yu(y);
                    y = x, x = S_left_(x);
                    xu = S_right_(xu);
                    return std::pair<const_iterator,
                            const_iterator>(lower_bound_(x, y, key),
                                            upper_bound_(xu, yu, key));
                }
            }
            return std::pair<const_iterator, const_iterator>(const_iterator(y),
                                                        const_iterator(y));
        }



        friend bool
        operator==(const Rb_tree& x, const Rb_tree& y)
        {
            return x.size() == y.size()
                   && std::equal(x.begin(), x.end(), y.begin());
        }

        friend bool
        operator<(const Rb_tree& x, const Rb_tree& y)
        {
            return std::lexicographical_compare(x.begin(), x.end(),
                                                y.begin(), y.end());
        }

        friend bool
        operator!=(const Rb_tree& x, const Rb_tree& y)
        { return !(x == y); }

        friend bool
        operator>(const Rb_tree& x, const Rb_tree& y)
        { return y < x; }

        friend bool
        operator<=(const Rb_tree& x, const Rb_tree& y)
        { return !(y < x); }

        friend bool
        operator>=(const Rb_tree& x, const Rb_tree& y)
        { return !(x < y); }

    };




    template<typename Key, typename Val, typename KeyOfValue,
                typename Compare, typename Alloc>
    inline void swap(Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
                        Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
    { x.swap(y); }


}
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_HPP
