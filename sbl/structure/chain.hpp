#include"detail/chain.hpp"
#include<algorithm>
#include<iostream>
#include<vector>

namespace sbl {

/// @brief Chain is a vector like data structure which has log time complexity
/// for many operators.
template<class T, int features, class Hash = Empty>
class Chain {
    public:
        static const bool have_replace  = (features & chainFeatures::replace);
        static const bool have_reverse  = (features & chainFeatures::reverse);
        static const bool have_sum      = (features & chainFeatures::sum) or
                                          (features & chainFeatures::maxsum);
        static const bool have_top      = (features & chainFeatures::top);
        static const bool have_maxsum   = (features & chainFeatures::maxsum);
        static const bool have_lcp      = (features & chainFeatures::lcp);
    private:
        struct Node;
        struct GetNode;
        struct Expand;
        struct Update;
        template<bool _> struct Bool {};
        template<int _> struct Int {
            Int(...) {}
        };
        VectorTree<Node *, GetNode, Expand, Update> tree;
    private:
        typedef OrderStatisticSplayTree<Node *, GetNode, Expand, Update> Algorithm;
        struct SetReplaced {
            T value;
            SetReplaced(T v): value(v) {}
            void set_unreversed(...) {}
            void set_unreversed(Bool<true>, Node *p) {
                p->isReversed = false;
            }
            void set_sum(...) {}
            void set_sum(Bool<true>, Node *p, T value) {
                p->allSum = value * Algorithm::get_size(p);
            }
            void set_maxsum(...) {}
            void set_maxsum(Bool<true>, Node *p, T value) {
                p->maxSum = p->leftMaxSum = p->rightMaxSum
                                            = std::max(p->allSum, value);
            }
            void operator()(Node *p) {
                if (p != NULL) {
                    set_unreversed(p);
                    p->isReplaced = true;
                    p->replaceValue = value;
                    p->element = value;
                    set_sum(Bool<have_sum>(), p, value);
                    set_maxsum(Bool<have_maxsum>(), p, value);
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
        static void output_node(Node *ptr, size_t depth) {
            for (size_t i = 0; i < depth; i++)
                std::cerr << "    ";
            std::cerr << ptr->element << std::endl;
        }
        void output_tree() const {
            Node *root = tree.root;
            Algorithm::inorder_travel(tree.root, output_node);
        }
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
}; // struct Chain

template<class T, int features, class Hash>
struct Chain<T, features, Hash>::Node :
        conditional<have_replace, detail::ReplaceBase<T>, Int<0> >::type,
        conditional<have_reverse, detail::ReverseBase, Int<1> >::type,
        conditional<have_sum, detail::SumBase<T>, Int<2> >::type,
        conditional<have_top, detail::TopBase<T>, Int<3> >::type,
        conditional<have_maxsum, detail::MaxSumBase<T>, Int<4> >::type,
        conditional<have_lcp, detail::LCPBase<T>, Int<5> >::type,
        detail::VectorTreeNodeBase<Node *> {
    T element;
    Node(T value):
        conditional<have_replace, detail::ReplaceBase<T>, Int<0> >::type(value),
        conditional<have_reverse, detail::ReverseBase, Int<1> >::type(value),
        conditional<have_sum, detail::SumBase<T>, Int<2> >::type(value),
        conditional<have_top, detail::TopBase<T>, Int<3> >::type(value),
        conditional<have_maxsum, detail::MaxSumBase<T>, Int<4> >::type(value),
        conditional<have_lcp, detail::LCPBase<T>, Int<5> >::type(value),
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
            parent->isReplaced = false;
        }
    }
    void reverse_check(...) {}
    void reverse_check(Bool<true>, Node *parent, Node *left, Node *right) {
        if (parent->isReversed) {
            SetReversed s;
            s(left);
            s(right);
            parent->isReversed = false;
            Algorithm::swap_child(parent);
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
    void sum(...) {}
    void sum(Bool<true>) {
        parent->allSum = parent->element;
        if (left != NULL) parent->allSum += left->allSum;
        if (right != NULL) parent->allSum += right->allSum;
    }
    void replace(...) {}
    void reverse(...) {}
    void replace(Bool<true>) {
        parent->isReplaced = false;
        assert(not parent->isReplaced);
    }
    void reverse(Bool<true>) {
        parent->isReversed = false;
        assert(not parent->isReversed);
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
        parent->maxSum = parent->element;
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
        parent->leftMaxSum = parent->element;
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
        parent->rightMaxSum = parent->element;
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

    void update_all_maxsum(...) {}
    void update_all_maxsum(Bool<true>) {
        max_sum();
        max_left_sum();
        max_right_sum();
    }

    void operator()(Node *p, Node *l, Node *r) {
        parent = p, left = l, right = r;
        sum(Bool<have_sum>());
        replace(Bool<have_replace>());
        reverse(Bool<have_reverse>());
        update_all_maxsum(Bool<have_maxsum>());
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
    T &sum, &maxSum;
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
    T sum, maxSum;
    GetInfo<T, Node *> info(sum, maxSum);
    tree.call_segment(left, right, info);
    return sum;
}
template<class T, int features, class Hash>
T Chain<T, features, Hash>::max_sum(size_t left, size_t right) const {
    assert(left < right);
    T sum, maxSum;
    GetInfo<T, Node *> info(sum, maxSum);
    tree.call_segment(left, right, info);
    return maxSum;
}
} // namespace sbl
