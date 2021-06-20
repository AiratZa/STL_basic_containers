//
// Created by airat on 14.06.2021.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_PARTS_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_PARTS_HPP

namespace ft {

    namespace details {

        enum RB_tree_color {
            RED = false,
            BLACK = true
        };

        template<typename Key_compare>
        struct Rb_tree_key_compare
        {
            Key_compare		key_compare_;

            Rb_tree_key_compare()
                    : key_compare_() { }

            Rb_tree_key_compare(const Key_compare& comp)
                    : key_compare_(comp) { }
        };


        struct Rb_tree_node_base
        {
            typedef Rb_tree_node_base*          Base_ptr;
            typedef const Rb_tree_node_base*    Const_Base_ptr;

            RB_tree_color color;
            Base_ptr parent;
            Base_ptr left;
            Base_ptr right;

            static Base_ptr minimum_(Base_ptr x) {
                while (x->left != 0)
                    x = x->left;
                return x;
            }

            static Const_Base_ptr minimum_(Const_Base_ptr x) {
                while (x->left != 0)
                    x = x->left;
                return x;
            }

            static Base_ptr maximum_(Base_ptr x) {
                while (x->right != 0)
                    x = x->right;
                return x;
            }

            static Const_Base_ptr maximum_(Const_Base_ptr x) {
                while (x->right != 0)
                    x = x->right;
                return x;
            }

        };

        struct Rb_tree_header
        {
            Rb_tree_node_base	header;
            std::size_t         node_count; // Keeps track of size of tree.

            Rb_tree_header()
            {
                header.color = RED;
                reset_();
            }

            void move_data_(Rb_tree_header& from)
            {
                header.color = from.header.color;
                header.parent = from.header.parent;
                header.left = from.header.left;
                header.right = from.header.right;
                header.parent->parent = &header;
                node_count = from.node_count;

                from.reset_();
            }

            void reset_()
            {
                header.parent = 0;
                header.left = &header;
                header.right = &header;
                node_count = 0;
            }
        };


        template<typename Val>
        struct Rb_tree_node : public Rb_tree_node_base
        {
            typedef Rb_tree_node<Val>* Link_type;

            Val value_field;

            Val* valptr_()
            { return std::__addressof(value_field); }

            const Val* valptr_() const
            { return std::__addressof(value_field); }
        };



        Rb_tree_node_base* Rb_tree_increment(Rb_tree_node_base* x) throw ();
        const Rb_tree_node_base* Rb_tree_increment(const Rb_tree_node_base* x) throw ();
        Rb_tree_node_base* Rb_tree_decrement(Rb_tree_node_base* x) throw ();
        const Rb_tree_node_base* Rb_tree_decrement(const Rb_tree_node_base* x) throw ();

    }
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_PARTS_HPP
