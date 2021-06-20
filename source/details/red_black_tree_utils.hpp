//
// Created by airat on 14.06.2021.
//

#ifndef FT_CONTAINERS_RED_BLACK_TREE_UTILS_HPP
#define FT_CONTAINERS_RED_BLACK_TREE_UTILS_HPP

#include "red_black_tree_parts.hpp"

namespace ft {
    namespace details {

        static Rb_tree_node_base*
        local_Rb_tree_increment(Rb_tree_node_base* x) throw ()
        {
            if (x->right != 0)
            {
                x = x->right;
                while (x->left != 0)
                    x = x->left;
            }
            else
            {
                Rb_tree_node_base* y = x->parent;
                while (x == y->right)
                {
                    x = y;
                    y = y->parent;
                }
                if (x->right != y)
                    x = y;
            }
            return x;
        }


        static Rb_tree_node_base*
        local_Rb_tree_decrement(Rb_tree_node_base* x) throw ()
        {
            if (x->color == RED  &&   x->parent->parent == x)
                x = x->right;
            else if (x->left != 0)
            {
                Rb_tree_node_base* y = x->left;
                while (y->right != 0)
                    y = y->right;
                x = y;
            }
            else
            {
                Rb_tree_node_base* y = x->parent;
                while (x == y->left)
                {
                    x = y;
                    y = y->parent;
                }
                x = y;
            }
            return x;
        }


        Rb_tree_node_base* Rb_tree_increment(Rb_tree_node_base* x) throw ()
        {
            return local_Rb_tree_increment(x);
        }

        const Rb_tree_node_base* Rb_tree_increment(const Rb_tree_node_base* x) throw ()
        {
            return local_Rb_tree_increment(const_cast<Rb_tree_node_base*>(x));
        }

        Rb_tree_node_base* Rb_tree_decrement(Rb_tree_node_base* x) throw ()
        {
            return local_Rb_tree_decrement(x);
        }

        const Rb_tree_node_base* Rb_tree_decrement(const Rb_tree_node_base* x) throw ()
        {
            return local_Rb_tree_decrement(const_cast<Rb_tree_node_base*>(x));
        }


        static void
        local_Rb_tree_rotate_left(Rb_tree_node_base* const x,
                                  Rb_tree_node_base*& root)
        {
            Rb_tree_node_base* const y = x->right;

            x->right = y->left;
            if (y->left != 0)
                y->left->parent = x;
            y->parent = x->parent;

            if (x == root)
                root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        static void
        local_Rb_tree_rotate_right(Rb_tree_node_base* const x,
                                   Rb_tree_node_base*& root)
        {
            Rb_tree_node_base* const y = x->left;

            x->left = y->right;
            if (y->right != 0)
                y->right->parent = x;
            y->parent = x->parent;

            if (x == root)
                root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }

        void Rb_tree_insert_and_rebalance_(const bool          insert_left,
                                      Rb_tree_node_base* x,
                                      Rb_tree_node_base* p,
                                      Rb_tree_node_base& header) throw ()
        {
            Rb_tree_node_base *& root = header.parent;

            // Initialize fields in new node to insert.
            x->parent = p;
            x->left = 0;
            x->right = 0;
            x->color = RED;

            // Insert.
            // Make new node child of parent and maintain root, leftmost and
            // rightmost nodes.
            // N.B. First node is always inserted left.
            if (insert_left)
            {
                p->left = x; // also makes leftmost = x when p == &header

                if (p == &header)
                {
                    header.parent = x;
                    header.right = x;
                }
                else if (p == header.left)
                    header.left = x; // maintain leftmost pointing to min node
            }
            else
            {
                p->right = x;

                if (p == header.right)
                    header.right = x; // maintain rightmost pointing to max node
            }

            // Rebalance.
            while (x != root
                   && x->parent->color == RED)
            {
                Rb_tree_node_base* const xpp = x->parent->parent;

                if (x->parent == xpp->left)
                {
                    Rb_tree_node_base* const y = xpp->right;
                    if (y && y->color == RED)
                    {
                        x->parent->color = BLACK;
                        y->color = BLACK;
                        xpp->color = RED;
                        x = xpp;
                    }
                    else
                    {
                        if (x == x->parent->right)
                        {
                            x = x->parent;
                            local_Rb_tree_rotate_left(x, root);
                        }
                        x->parent->color = BLACK;
                        xpp->color = RED;
                        local_Rb_tree_rotate_right(xpp, root);
                    }
                }
                else
                {
                    Rb_tree_node_base* const y = xpp->left;
                    if (y && y->color == RED)
                    {
                        x->parent->color = BLACK;
                        y->color = BLACK;
                        xpp->color = RED;
                        x = xpp;
                    }
                    else
                    {
                        if (x == x->parent->left)
                        {
                            x = x->parent;
                            local_Rb_tree_rotate_right(x, root);
                        }
                        x->parent->color = BLACK;
                        xpp->color = RED;
                        local_Rb_tree_rotate_left(xpp, root);
                    }
                }
            }
            root->color = BLACK;
        }



        Rb_tree_node_base*
        Rb_tree_rebalance_for_erase_(Rb_tree_node_base* const z,
                                     Rb_tree_node_base& header) throw ()
        {
            Rb_tree_node_base *& root = header.parent;
            Rb_tree_node_base *& leftmost = header.left;
            Rb_tree_node_base *& rightmost = header.right;
            Rb_tree_node_base* y = z;
            Rb_tree_node_base* x = 0;
            Rb_tree_node_base* x_parent = 0;

            if (y->left == 0)     // z has at most one non-null child. y == z.
                x = y->right;     // x might be null.
            else
            if (y->right == 0)  // z has exactly one non-null child. y == z.
                x = y->left;    // x is not null.
            else
            {
                // z has two non-null children.  Set y to
                y = y->right;   //   z's successor.  x might be null.
                while (y->left != 0)
                    y = y->left;
                x = y->right;
            }
            if (y != z)
            {
                // relink y in place of z.  y is z's successor
                z->left->parent = y;
                y->left = z->left;
                if (y != z->right)
                {
                    x_parent = y->parent;
                    if (x) x->parent = y->parent;
                    y->parent->left = x;   // y must be a child of left
                    y->right = z->right;
                    z->right->parent = y;
                }
                else
                    x_parent = y;
                if (root == z)
                    root = y;
                else if (z->parent->left == z)
                    z->parent->left = y;
                else
                    z->parent->right = y;
                y->parent = z->parent;
                std::swap(y->color, z->color);
                y = z;
                // y now points to node to be actually deleted
            }
            else
            {                        // y == z
                x_parent = y->parent;
                if (x)
                    x->parent = y->parent;
                if (root == z)
                    root = x;
                else
                if (z->parent->left == z)
                    z->parent->left = x;
                else
                    z->parent->right = x;
                if (leftmost == z)
                {
                    if (z->right == 0)        // z->left must be null also
                        leftmost = z->parent;
                        // makes leftmost == _M_header if z == root
                    else
                        leftmost = Rb_tree_node_base::minimum_(x);
                }
                if (rightmost == z)
                {
                    if (z->left == 0)         // z->right must be null also
                        rightmost = z->parent;
                        // makes rightmost == _M_header if z == root
                    else                      // x == z->left
                        rightmost = Rb_tree_node_base::maximum_(x);
                }
            }
            if (y->color != RED)
            {
                while (x != root && (x == 0 || x->color == BLACK))
                    if (x == x_parent->left)
                    {
                        Rb_tree_node_base* w = x_parent->right;
                        if (w->color == RED)
                        {
                            w->color = BLACK;
                            x_parent->color = RED;
                            local_Rb_tree_rotate_left(x_parent, root);
                            w = x_parent->right;
                        }
                        if ((w->left == 0 ||
                             w->left->color == BLACK) &&
                            (w->right == 0 ||
                             w->right->color == BLACK))
                        {
                            w->color = RED;
                            x = x_parent;
                            x_parent = x_parent->parent;
                        }
                        else
                        {
                            if (w->right == 0
                                || w->right->color == BLACK)
                            {
                                w->left->color = BLACK;
                                w->color = RED;
                                local_Rb_tree_rotate_right(w, root);
                                w = x_parent->right;
                            }
                            w->color = x_parent->color;
                            x_parent->color = BLACK;
                            if (w->right)
                                w->right->color = BLACK;
                            local_Rb_tree_rotate_left(x_parent, root);
                            break;
                        }
                    }
                    else
                    {
                        // same as above, with right <-> left.
                        Rb_tree_node_base* w = x_parent->left;
                        if (w->color == RED)
                        {
                            w->color = BLACK;
                            x_parent->color = RED;
                            local_Rb_tree_rotate_right(x_parent, root);
                            w = x_parent->left;
                        }
                        if ((w->right == 0 ||
                             w->right->color == BLACK) &&
                            (w->left == 0 ||
                             w->left->color == BLACK))
                        {
                            w->color = RED;
                            x = x_parent;
                            x_parent = x_parent->parent;
                        }
                        else
                        {
                            if (w->left == 0 || w->left->color == BLACK)
                            {
                                w->right->color = BLACK;
                                w->color = RED;
                                local_Rb_tree_rotate_left(w, root);
                                w = x_parent->left;
                            }
                            w->color = x_parent->color;
                            x_parent->color = BLACK;
                            if (w->left)
                                w->left->color = BLACK;
                            local_Rb_tree_rotate_right(x_parent, root);
                            break;
                        }
                    }
                if (x) x->color = BLACK;
            }
            return y;
        }

    }
}

#endif //FT_CONTAINERS_RED_BLACK_TREE_UTILS_HPP
