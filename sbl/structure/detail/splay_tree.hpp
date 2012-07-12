#ifndef _sbl_splay_tree_base
#define _sbl_splay_tree_base
#include"rotate_tree.hpp"

namespace sbl {
namespace detail {

template<class NodePtr>
class SplayTreeNodeBase:public RotateTreeNodeBase<NodePtr> {
    protected:
        ~SplayTreeNodeBase() {}
};

template<class NodePtr, class GetNode, class Expand, class Update>
class SplayTreeBase: public RotateTreeBase<NodePtr, GetNode, Expand, Update> {
        // Bottom-Up Splay Tree
        // FAQ
        // Q: Why not use Top-Down Splay Tree?
        // A: There are three reasons.
        //    * Update and expand operator wipe out the performance advantages
        //    * The design of Top-Down is too complex (need 3 trees to splay)
        //    * Since we can not be allocated memory, we have no dummy node
    public:

        typedef RotateTreeBase<NodePtr, GetNode, Expand, Update> Base;
        typedef SplayTreeBase<NodePtr, GetNode, Expand, Update> Self;
        using Base::get_left;
        using Base::get_right;
        using Base::get_child;
        using Base::get_parent;
        using Base::link_left;
        using Base::link_right;
        using Base::link_child;
        using Base::set_parent;
        using Base::is_left;
        using Base::is_right;
        using Base::get_node;
        using Base::rotate;
        using Base::update;
        using Base::expand;

        /// splay t to the root
        static void splay(NodePtr t) {
            while (get_parent(t) != NULL) {
                assert(t != NULL);
                NodePtr y = get_parent(t);
                if (get_parent(y) == NULL) {
                    rotate(t);
                } else {
                    bool isZigZig = is_right(t) and is_right(y);
                    bool isZagZag = is_left(t) and is_left(y);
                    if (isZigZig or isZagZag) {
                        // zig-zig or zag-zag
                        rotate(y);
                        rotate(t);
                    } else {
                        // zig-zag or zag-zig
                        rotate(t);
                        rotate(t);
                    }
                }
            }
        }

        /// add a new node to root according compare.
        /// compare must given a NodePtr and return {-1, 0, 1}
        /// -1: current node bigger, to the left subtree
        /// 0: current node equal to x, to the left subtree
        /// 1: current node smaller, to the right subtree
        /// @return new root
        template<class Compare3way>
        static NodePtr add(NodePtr root, NodePtr node, Compare3way compare) {
            if (root == NULL)
                return node;
            assert(get_parent(root) == NULL);
            NodePtr current = root; ///< current node we focus
            while (true) {
                expand(current);
                int k = compare(current);
                if (k == -1 or k == 0) {
                    if (get_left(current) == NULL) {
                        link_left(current, node);
                        break;
                    }
                    current = get_left(current);
                } else {
                    if (get_right(current) == NULL) {
                        link_right(current, node);
                        break;
                    }
                    current = get_right(current);
                }
            }
            update(node);
            splay(node);
            return node;
        }

    private:
        template<int n>
        struct AlwaysReturn {
            int operator()(...) {
                return n;
            }
        };
    public:

        /// splay the leftmost node
        static NodePtr leftmost(NodePtr root) {
            return find(root, AlwaysReturn<-1>());
        }

        /// splay the rightmost node
        static NodePtr rightmost(NodePtr root) {
            return find(root, AlwaysReturn<1>());
        }

        /// delete the root
        /// @return new root
        static NodePtr del(NodePtr root) {
            if (root == NULL)
                return root;
            NodePtr left = get_left(root);
            NodePtr right = get_right(root);
            expand(root);

            // break left child
            link_left(root, NULL);
            set_parent(left, NULL);

            // break right child
            link_right(root, NULL);
            set_parent(right, NULL);

            if (left == NULL) {
                return right;
            } else {
                left = rightmost(left);
                assert(get_right(left) == NULL);
                link_right(left, right);
                update(left);
                return left;
            }
        }

        /// find a node according Compare3way compare.
        /// compare must given a NodePtr and return {-1, 0, 1}
        /// -1: to the left subtree
        /// 0: we found it !!! splay it to the root!
        /// 1: to the right subtree
        /// @return new root (the node we found)
        template<class Compare3way>
        static NodePtr find(NodePtr root, Compare3way compare) {
            if (root == NULL)
                return root;
            NodePtr current = root;
            while (true) {
                assert(current != NULL);
                expand(current);
                int k = compare(current);
                if (k == -1) {
                    if (get_left(current) == NULL)
                        break;
                    current = get_left(current);
                } else if (k == 1) {
                    if (get_right(current) == NULL)
                        break;
                    current = get_right(current);
                } else {
                    assert(k == 0 and "SplayTree:: 3way not in {-1,0,1}");
                    break;
                }
            }
            splay(current);
            return current;
        }
    protected:
        ~SplayTreeBase() {}

}; // class SplayTreeBase
} // namespace detail
} // namespace sbl
#endif
