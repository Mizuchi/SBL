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

        static NodePtr get_child(NodePtr a, size_t idx) {
            assert(idx == 0 or idx == 1);
            if (idx == 0)
                return get_left(a);
            else
                return get_right(a);
        }
        static void set_child(NodePtr a, size_t idx, NodePtr b) {
            assert(idx == 0 or idx == 1);
            if (idx == 0)
                set_left(a, b);
            else
                set_right(a, b);
        }

        static NodePtr get_left(NodePtr a) {
            if (a == NULL) return NULL;
            return get_node(a).left;
        }

        static void set_left(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).left = b;
        }

        static NodePtr get_right(NodePtr a) {
            if (a == NULL) return NULL;
            return get_node(a).right;
        }

        static void set_right(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).right = b;
        }

        static NodePtr get_parent(NodePtr a) {
            if (a == NULL)return NULL;
            return get_node(a).parent;
        }

        static void set_parent(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).parent = b;
        }

        static bool is_right(NodePtr x) {
            assert(x != NULL);
            NodePtr y = get_parent(x);
            if (y == NULL) return false;
            return get_right(y) == x;
        }

        static bool is_left(NodePtr x) {
            assert(x != NULL);
            NodePtr y = get_parent(x);
            if (y == NULL) return false;
            return get_left(y) == x;
        }

        static void expand(NodePtr x, NodePtr l, NodePtr r) {
            return Expand()(x, l, r);
        }

        static void update(NodePtr x, NodePtr l, NodePtr r) {
            //cout << "===============================" << endl;
            //std::cout << ::acml::json::dumps(x) << std::endl;
            //std::cout << ::acml::json::dumps(l) << std::endl;
            //std::cout << ::acml::json::dumps(r) << std::endl;
            //cout << "===============================" << endl;
            return Update()(x, l, r);
        }

        static void expand(NodePtr x) {
            expand(x, get_left(x), get_right(x));
        }

        static void update(NodePtr x) {
            update(x, get_left(x), get_right(x));
        }

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

        template<int n>
        struct AlwaysReturn {
            int operator()(...) {
                return n;
            }
        };

        static NodePtr leftmost(NodePtr root) {
            return find(root, AlwaysReturn<1>());
        }

        static NodePtr rightmost(NodePtr root) {
            return find(root, AlwaysReturn<1>());
        }

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
                left = leftmost(left);
                assert(get_right(left) == NULL);
                set_right(left, right);
                set_parent(right, left);
                update(left);
                return left;
            }
        }

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
