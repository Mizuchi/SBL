#ifndef _sbl_leftist_tree
#define _sbl_leftist_tree
#include<algorithm>
#include<functional>
#include<memory>

namespace sbl {
template < class T,
         class Compare = std::less<T>,
         class Allocator = std::allocator<T> >
class LeftistTree {
        // http://en.wikipedia.org/wiki/Leftist_tree
    private:

        Compare comp;
        struct Node {

            const T value;
            std::size_t nullPathLength;
            Node *leftChild, *rightChild;

            Node(const T &a): value(a), nullPathLength(0),
                leftChild(0), rightChild(0) {}

            std::size_t left_length() const {
                if (leftChild == NULL) return 0;
                return leftChild->nullPathLength;
            }
            std::size_t right_length() const {
                if (rightChild == NULL) return 0;
                return rightChild->nullPathLength;
            }
        } *root;
        typename Allocator::template rebind<Node>::other alloc;

        /// merge two node
        Node *bind(Node *a, Node *b) {
            if (a == NULL) return b;
            if (b == NULL) return a;

            // This was a max height biased leftist tree.
            // For the sake of convenience we let a->value bigger.
            if (comp(a->value, b->value))
                std::swap(a, b);

            a->rightChild = bind(a->rightChild, b);

            if (a->left_length() < a->right_length())
                // left null path length is shorter
                std::swap(a->leftChild, a->rightChild);

            a->nullPathLength = a->right_length() + 1;
            return a;
        }

        void del(Node *p) {
            if (p == 0) return;
            del(p->leftChild);
            del(p->rightChild);
            alloc.destroy(p);
            alloc.deallocate(p, 1);
        }

    public:
        LeftistTree() : root(0) {}

        ~LeftistTree() {
            clear();
        }
        void clear() {
            del(root);
            root = 0;
        }

        void push(const T &a) {
            Node *p = alloc.allocate(1);
            alloc.construct(p, a);
            root = bind(root, p);
        }

        const T &top() const {
            return root->value;
        }

        void pop() {
            Node *p = root;
            root = bind(root->leftChild, root->rightChild);
            alloc.destroy(p);
            alloc.deallocate(p, 1);
        }

        void merge(LeftistTree &a) {
            root = bind(root, a.root);
            a.root = 0;
        }
};
} // namespace sbl

#endif
