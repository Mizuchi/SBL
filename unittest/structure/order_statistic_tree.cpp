#include<gtest/gtest.h>
#include<list>
#include"../../sbl/structure/order_statistic_tree.hpp"

struct NodeOST {
   sbl::OrderStatisticTreeNode<NodeOST *> node;
   int value;
   bool less_than(const NodeOST *x) const {
       return value < x->value;
   }
   NodeOST(int _): value(_) {}
};

struct GetNodeOST {
   sbl::OrderStatisticTreeNode<NodeOST *> &
   operator()(NodeOST *a) const {
       return a->node;
   }
};

TEST(structure, OrderStatisticTree) {
   std::list<NodeOST> p;
   sbl::OrderStatisticTree<NodeOST *, GetNodeOST> tree;
   p.push_back(3), tree.insert(&p.back());
   p.push_back(5), tree.insert(&p.back());
   p.push_back(2), tree.insert(&p.back());
   p.push_back(8), tree.insert(&p.back());
   p.push_back(6), tree.insert(&p.back());
   NodeOST x(3);
   EXPECT_EQ(tree.at(2)->value, 5);
   EXPECT_EQ(tree.find(&x)->value, 3);
   EXPECT_EQ(tree.biggest()->value, 8);
   EXPECT_EQ(tree.bigger(&x)->value, 5);
   EXPECT_EQ(tree.smaller(&x)->value, 2);
   EXPECT_EQ(tree.bigger_count(&x), 3);
   EXPECT_EQ(tree.smaller_count(&x), 1);
   tree.erase(&x);

   EXPECT_EQ(tree.at(2)->value, 6);
   EXPECT_EQ(tree.biggest()->value, 8);
   EXPECT_EQ(tree.bigger(&x)->value, 5);
   EXPECT_EQ(tree.smaller(&x)->value, 2);
   EXPECT_EQ(tree.bigger_count(&x), 3);
   EXPECT_EQ(tree.smaller_count(&x), 1);
};
