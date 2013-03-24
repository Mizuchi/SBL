#ifndef _sbl_vector_tree_impl
#define _sbl_vector_tree_impl
#include"detail/vector_tree.hpp"


namespace sbl {

template<class NodePtr>
class VectorTreeNode: public detail::VectorTreeNodeBase<NodePtr> {};

template<class NodePtr, class GetNode, class Expand, class Update>
class VectorTree: private detail::VectorTreeBase<NodePtr, GetNode, Expand, Update> {
    public:
        mutable NodePtr root;
        typedef detail::VectorTreeBase<NodePtr, GetNode, Expand, Update> Base;
        typedef VectorTree<NodePtr, GetNode, Expand, Update> Self;

        VectorTree(): root(NULL) {}

        /// @return n-th element
        NodePtr find_by_order(size_t n) {
            root = Base::find_by_order(root, n);
            return root;
        }

        /// insert a new node to position n
        void insert(size_t n, NodePtr newNode) {
            root = Base::insert(root, n, newNode);
        }

        /// insert new nodes to position n
        void insert(size_t n, NodePtr beg, NodePtr end) {
            if (beg == end)return;
            NodePtr p = end;
            do {
                --p;
                insert(n, p);
            } while (p != beg);
        }

        /// @return number of element
        size_t size()const {
            return Base::get_size(root);
        }

        /// replace a segment [l, r) to a given node
        NodePtr replace_segment(size_t l, size_t r, NodePtr newNode) {
            NodePtr oldNode;
            root = Base::replace_segment(root, l, r, newNode, &oldNode);
            return oldNode;
        }

        /// call(root of subtree in range [l, r))
        template<class Callable>
        void call_segment(size_t l, size_t r, Callable call) const {
            assert(l < r);
            root = Base::call_segment(root, l, r, call);
        }

        /// remove add element in range [l, r)
        NodePtr erase(size_t l, size_t r) {
            if (l == r) return NULL;
            return replace_segment(l, r, NULL);
        }
}; // class VectorTree
} // namespace sbl;

#endif
