#include"detail/chain.hpp"
#include<algorithm>
#include<iostream>
#include<vector>

namespace sbl {

template<class T, int features, class Hash = Empty>
class Chain {
    public:
        static const bool have_replace  = features &chainFeatures::replace;
        static const bool have_reverse  = features &chainFeatures::reverse;
        static const bool have_sum      = features &chainFeatures::sum;
        static const bool have_top      = features &chainFeatures::top;
        static const bool have_maxsum   = features &chainFeatures::maxsum;
        static const bool have_lcp      = features &chainFeatures::lcp;
    private:
        struct Node;
        struct GetNode;
        struct Expand;
        struct Update;
        template<bool _> struct Bool {
            const static bool value = _;
        };
        template<int i> struct Int {
            Int(T value) {
                static_cast<void>(value);
            }
        };
        template<class Feature> struct Choose {
            typedef typename conditional <
            (Feature::feature &features) != 0,
            Feature, Int<Feature::feature>
            >::type type;
        }; // struct Choose
        VectorTree<Node *, GetNode, Expand, Update> tree;
    public:
        // metadata
        size_t size()const; // Untested
    public:
        // base
        void insert(size_t index, T value); // tested
        void erase(size_t left, size_t right); // tested
    public:
        // modify
        void replace(size_t left, size_t right, T value); // tested
        void reverse(size_t left, size_t right); // tested
    public:
        // query
        T sum(size_t left, size_t right)const; // tested
        T max_sum(size_t left, size_t right)const; // testsd
        T top(size_t left, size_t right)const; // TODO
        T lcp(size_t first, size_t second)const; // TODO
    private:
        typedef OrderStatisticSplayTree<Node *, GetNode, Expand, Update> Algorithm;
        struct SetReplaced {
            T value;
            SetReplaced(T v): value(v) {}
            void set_unreversed(...) {}
            void set_unreversed(Bool<true>, Node *p) {
                p->isReversed = false;
            }
            void operator()(Node *p) {
                if (p != NULL) {
                    set_unreversed(p);
                    p->isReplaced = true;
                    p->replaceValue = value;
                    p->element = value;
                    p->allSum = value * Algorithm::get_size(p);
                    p->maxSum = p->leftMaxSum = p->rightMaxSum
                                                = std::max(p->allSum, value);
                }
            }
        }; // struct SetReplaced

        struct SetReversed {
            SetReversed() {}
            void operator()(Node *p) {
                if (p != NULL) {
                    p->isReversed = not p->isReversed;
                    std::swap(p->leftMaxSum, p->rightMaxSum);
                }
            }
        }; // struct SetReversed
    public:
        void output_node(Node *ptr, size_t depth) {
            for (size_t i = 0; i < depth; i++)
                std::cerr << "    ";
            std::cerr << ptr->element << std::endl;
        }
        void output_tree() const {
            Node *root = tree.root;
            Algorithm::inorder_travel(tree.root, output_node);
        }
}; // struct Chain

template<class T, int features, class Hash>
struct Chain<T, features, Hash>::Node :
    public Choose<detail::ReplaceBase<T> >::type,
    public Choose<detail::ReverseBase >::type,
    public Choose<detail::SumBase<T> >::type,
    public Choose<detail::TopBase<T> >::type,
    public Choose<detail::MaxSumBase<T> >::type,
    public Choose<detail::LCPBase<T> >::type,
    public detail::VectorTreeNodeBase<Node *> {
    T element;
    Node(T value):
        Choose<detail::ReplaceBase<T> >::type(value),
        Choose<detail::ReverseBase >::type(value),
        Choose<detail::SumBase<T> >::type(value),
        Choose<detail::TopBase<T> >::type(value),
        Choose<detail::MaxSumBase<T> >::type(value),
        Choose<detail::LCPBase<T> >::type(value),
        element(value) {}
};
template<class T, int features, class Hash>
struct Chain<T, features, Hash>::GetNode {
    detail::VectorTreeNodeBase<Node *> &operator()(Node *a) const {
        return static_cast<detail::VectorTreeNodeBase<Node *> &>(*a);
    }
};

template<class T, int features, class Hash>
struct Chain<T, features, Hash>::Expand {
    void replace_check(...) {}
    void replace_check(Bool<true>, Node *parent, Node *left, Node *right) {
        if (parent->isReplaced) {
            SetReplaced s(parent->replaceValue);
            s(left);
            s(right);
        }
    }
    void reverse_check(...) {}
    void reverse_check(Bool<true>, Node *parent, Node *left, Node *right) {
        if (parent->isReversed) {
            Algorithm::swap_child(parent);
            SetReversed s;
            s(left);
            s(right);
            parent->isReversed = false;
        }
    }
    void operator()(Node *parent, Node *left, Node *right) {
        replace_check(Bool<have_replace>(), parent, left, right);
        reverse_check(Bool<have_reverse>(), parent, left, right);
    }
};

template<class T, int features, class Hash>
struct Chain<T, features, Hash>::Update {
    Node *parent, *left, *right;
    void sum() {
        parent->allSum = parent->element;
        if (left != NULL) parent->allSum += left->allSum;
        if (right != NULL) parent->allSum += right->allSum;
    }
    void replace(...) {}
    void reverse(...) {}
    void replace(Bool<true>) {
        parent->isReplaced = false;
    }
    void reverse(Bool<true>) {
        parent->isReversed = false;
    }
    void update_max(T &a, T b) {
        a = std::max(a, b);
    }
    bool has_left_child() {
        return left != NULL;
    }

    bool has_right_child() {
        return right != NULL;
    }
    void max_sum() {
        if (has_left_child()) {
            update_max(parent->maxSum, left->maxSum);
            update_max(parent->maxSum, left->rightMaxSum + parent->element);
        }
        if (has_right_child()) {
            update_max(parent->maxSum, right->maxSum);
            update_max(parent->maxSum, right->leftMaxSum + parent->element);
        }
        if (has_left_child() and has_right_child())
            update_max(parent->maxSum,
                       left->rightMaxSum + parent->element + right->leftMaxSum);
    }
    void max_left_sum() {
        if (has_left_child()) {
            parent->leftMaxSum = left->leftMaxSum;
            update_max(parent->leftMaxSum, left->allSum + parent->element);
            if (has_right_child())
                update_max(parent->leftMaxSum,
                           left->allSum + parent->element + right->leftMaxSum);
        } else if (has_right_child())
            update_max(parent->leftMaxSum,
                       parent->element + right->leftMaxSum);
    }
    void max_right_sum() {
        if (has_right_child()) {
            parent->rightMaxSum = right->rightMaxSum;
            update_max(parent->rightMaxSum, parent->element + right->allSum);
            if (has_left_child())
                update_max(parent->rightMaxSum,
                           left->rightMaxSum + parent->element + right->allSum);
        } else if (has_left_child())
            update_max(parent->rightMaxSum,
                       parent->element + left->rightMaxSum);
    }

    void operator()(Node *p, Node *l, Node *r) {
        parent = p, left = l, right = r;
        sum();
        replace(Bool<have_replace>());
        reverse(Bool<have_reverse>());
        parent->maxSum = parent->element;
        parent->leftMaxSum = parent->element;
        parent->rightMaxSum = parent->element;
        max_sum();
        max_left_sum();
        max_right_sum();
    }
};

template<class T, int features, class Hash>
size_t Chain<T, features, Hash>::size() const {
    return tree.size();
}
template<class T, int features, class Hash>
void Chain<T, features, Hash>::insert(size_t index, T value) {
    tree.insert(index, new Node(value));
}
template<class T, int features, class Hash>
void Chain<T, features, Hash>::erase(size_t left, size_t right) {
    assert(left <= right);
    if (left < right)
        tree.erase(left, right);
}


template<class T, int features, class Hash>
void Chain<T, features, Hash>::replace(size_t left, size_t right, T value) {
    assert(left <= right);
    if (left < right)
        tree.call_segment(left, right, SetReplaced(value));
}

template<class T, int features, class Hash>
void Chain<T, features, Hash>::reverse(size_t left, size_t right) {
    assert(left <= right);
    if (left < right)
        tree.call_segment(left, right, SetReversed());
}

template<class T, class NodePtr>
struct GetInfo {
    T &sum;
    T &maxSum;
    GetInfo(T &s, T &m): sum(s), maxSum(m) {}
    void operator()(NodePtr p) {
        assert(p != NULL);
        sum = p->allSum;
        maxSum = p->maxSum;
    }
}; // struct GetInfo

template<class T, int features, class Hash>
T Chain<T, features, Hash>::sum(size_t left, size_t right) const {
    if (left == right) return 0;
    assert(left < right);
    T sum;
    T maxSum;
    GetInfo<T, Node *> info(sum, maxSum);
    tree.call_segment(left, right, info);
    return sum;
}
template<class T, int features, class Hash>
T Chain<T, features, Hash>::max_sum(size_t left, size_t right) const {
    assert(left < right);
    T sum;
    T maxSum;
    GetInfo<T, Node *> info(sum, maxSum);
    tree.call_segment(left, right, info);
    return maxSum;
}
} // namespace sbl
