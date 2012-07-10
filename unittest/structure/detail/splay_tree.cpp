#include"../../../sbl/structure/detail/splay_tree.hpp"
#include<gtest/gtest.h>
#include<deque>

namespace ST {
struct Node {
    sbl::detail::SplayTreeNode<Node *> node;
    int value;
    Node(int _): value(_) {}
    int print() const {
        return value;
    }
};
struct GetNode {
    sbl::detail::SplayTreeNode<Node *> &operator()(Node *a) const {
        return a->node;
    }
};
struct Nothing {
    void operator()(...) {}
};
struct Compare3way {
    int store;
    Compare3way(int _): store(_) {}
    int operator()(Node *root) {
        if (store == root->value)return 0;
        if (store < root->value)return -1;
        if (store > root->value)return +1;
        assert(false);
    }
};

void walk(Node *p) {
    if (p) {
        Node *left = p->node.left;
        Node *right = p->node.right;
        if (left) {
            EXPECT_LE(left->value, p->value);
            EXPECT_EQ(left->node.parent, p);
            walk(left);
        }
        if (right) {
            EXPECT_GE(right->value, p->value);
            EXPECT_EQ(right->node.parent, p);
            walk(right);
        }
    }
}
}


//#include<acml/json.hpp>
//#include<acml/acml.hpp>
//ACML_REGISTER_HANDLE(ST::Node *, visitor, value) {
//    if (value) {
//        visitor(value->value, "value");
//        if (value->node.left) {
//            assert(value->node.left->node.parent == value);
//            visitor(value->node.left, "left");
//        }
//        if (value->node.right) {
//            assert(value->node.right->node.parent == value);
//            visitor(value->node.right, "right");
//        }
//    }
//}

TEST(structure, splay_tree) {
    using namespace ST;
    using namespace std;
    typedef ST::Node *NodePtr;
    ::sbl::detail::SplayTree<NodePtr, GetNode, Nothing, Nothing> st;
    for (int i = 0; i < 100; i++) {
        NodePtr root = NULL;
        std::deque<ST::Node> t;
        for (int i = 0; i <= 200; i++) {
            int value = rand();
            t.push_back(value);
            root = st.add(root, &t.back(), Compare3way(value));
            walk(root);
        }
    }
};
