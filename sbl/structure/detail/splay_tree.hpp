#ifndef _sbl_splay_tree
#define _sbl_splay_tree

namespace sbl {
namespace detail {

template<class NodePtr>
struct SplayTreeNode {
    NodePtr left;   ///< left child
    NodePtr right;  ///< right child
    NodePtr parent; ///< parent node
    SplayTreeNode(): left(NULL), right(NULL), parent(NULL) {}
};


template<class NodePtr, class GetNode, class Expand, class Update>
class SplayTree {
        // Bottom-Up Splay Tree
        // FAQ
        // Q: Why not use Top-Down Splay Tree?
        // A: There are three reasons.
        //    * Update and expand operator wipe out the performance advantages
        //    * The design of Top-Down is too complex (need 3 trees to splay)
        //    * Since we can not be allocated memory, we have no dummy node
    public:
        /// get the node information from NodePtr
        static SplayTreeNode<NodePtr> &get_node(NodePtr a) {
            assert(a != NULL);
            return GetNode()(a);
        }

        /// get the child according index {0: left, 1: right}
        static NodePtr get_child(NodePtr a, size_t idx) {
            assert(idx == 0 or idx == 1);
            if (idx == 0)
                return get_left(a);
            else
                return get_right(a);
        }

        /// set the child according index {0: left, 1: right}
        static void set_child(NodePtr a, size_t idx, NodePtr b) {
            assert(idx == 0 or idx == 1);
            if (idx == 0)
                set_left(a, b);
            else
                set_right(a, b);
        }

        /// get left child
        static NodePtr get_left(NodePtr a) {
            if (a == NULL) return NULL;
            return get_node(a).left;
        }

        /// set left child
        static void set_left(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).left = b;
        }

        /// get right child
        static NodePtr get_right(NodePtr a) {
            if (a == NULL) return NULL;
            return get_node(a).right;
        }

        /// set right child
        static void set_right(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).right = b;
        }

        /// get parent
        static NodePtr get_parent(NodePtr a) {
            if (a == NULL)return NULL;
            return get_node(a).parent;
        }

        /// set parent
        static void set_parent(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).parent = b;
        }

        /// check if x is a right child
        static bool is_right(NodePtr x) {
            assert(x != NULL);
            NodePtr y = get_parent(x);
            if (y == NULL) return false;
            return get_right(y) == x;
        }

        /// check if x is a left child
        static bool is_left(NodePtr x) {
            return not is_right(x);
        }

        static void expand(NodePtr parent, NodePtr left, NodePtr right) {
            return Expand()(parent, left, right);
        }

        static void update(NodePtr parent, NodePtr left, NodePtr right) {
            return Update()(parent, left, right);
        }

        /// expand node x information to his children
        static void expand(NodePtr x) {
            expand(x, get_left(x), get_right(x));
        }

        /// update node x information from his children
        static void update(NodePtr x) {
            update(x, get_left(x), get_right(x));
        }

        /// swap x to her father
        static void rotate(NodePtr x) {
            NodePtr y = get_parent(x);
            if (get_parent(y) != NULL) {
                if (get_left(get_parent(y)) == y)
                    set_left(get_parent(y), x);
                else
                    set_right(get_parent(y), x);
            }
            set_parent(x, get_parent(y));
            size_t c = (get_left(y) == x) ? 0 : 1;
            set_child(y, c, get_child(x, 1 - c));
            set_parent(get_child(y, c), y);

            set_child(x, 1 - c, y);
            set_parent(y, x);

            update(y);
            update(x);
        }

        /// splay t to the root
        static void splay(NodePtr t) {
            while (get_parent(t) != NULL) {
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
        /// 0: current node equal to x, to the right subtree
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
                if (k == -1) {
                    if (get_left(current) == NULL) {
                        set_left(current, node);
                        set_parent(node, current);
                        break;
                    }
                    current = get_left(current);
                } else {
                    if (get_right(current) == NULL) {
                        set_right(current, node);
                        set_parent(node, current);
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
            set_left(root, NULL);
            set_parent(left, NULL);

            // break right child
            set_right(root, NULL);
            set_parent(right, NULL);

            if (left == NULL) {
                return right;
            } else {
                left = rightmost(left);
                assert(get_right(left) == NULL);
                set_right(left, right);
                set_parent(right, left);
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

}; // class SplayTree
} // namespace detail
} // namespace sbl
#endif
