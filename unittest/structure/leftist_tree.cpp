#include<gtest/gtest.h>
#include"../../sbl/structure/leftist_tree.hpp"
#include<algorithm>
#include<vector>

struct NodeLT {
    sbl::LeftistTreeNode<NodeLT *> node;
    int value;
    NodeLT(int s): value(s) {}
};

struct CompareLT  {
    bool operator()(NodeLT *a, NodeLT *b) {
        return a->value < b->value;
    }
};

struct GetNodeLT {
    sbl::LeftistTreeNode<NodeLT *> &
    operator()(NodeLT* a) const {
        return a->node;
    }
};

TEST(structure, leftist_tree_intrusive) {
    sbl::LeftistTree<NodeLT *, GetNodeLT, CompareLT> a, b;
    NodeLT x[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    b.push(x + 5);
    b.push(x + 4);
    b.push(x + 2);
    a.push(x + 7);
    a.push(x + 3);
    a.push(x + 1);
    EXPECT_EQ(a.top(), x + 7);
    a.pop();
    EXPECT_EQ(a.top(), x + 3);
    a.merge(b);
    EXPECT_EQ(a.top(), x + 5);
    a.pop();
    EXPECT_EQ(a.top(), x + 4);
};
