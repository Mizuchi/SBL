#include<gtest/gtest.h>
#include"../../sbl/structure/leftist_tree.hpp"
#include<algorithm>
#include<vector>

struct Node {
    sbl::LeftistTreeNode<Node*> node;
    bool compare(Node *other) {
        return value < other->value;
    }
    int value;
    Node(int s): value(s) {}
};

TEST(structure, leftist_tree_intrusive) {
    sbl::LeftistTree<Node *> a, b;
    Node x[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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
