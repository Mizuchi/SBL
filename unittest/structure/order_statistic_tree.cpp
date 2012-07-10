#include<gtest/gtest.h>
#include<list>
#include<iostream>
#include<acml/json.hpp>
#include<acml/acml.hpp>

using namespace std;
#include"../../sbl/structure/order_statistic_tree.hpp"

struct NodeOST {
   sbl::intrusive::OrderStatisticTreeNode<NodeOST *> node;
   int value;
   bool less_than(const NodeOST *x) const {
       return value < x->value;
   }
   NodeOST(int _): value(_) {}
};

struct GetNodeOST {
   sbl::intrusive::OrderStatisticTreeNode<NodeOST *> &
   operator()(NodeOST *a) const {
       return a->node;
   }
};

ACML_REGISTER_HANDLE(NodeOST *, visitor, value) {
   if (value) {
       visitor(value->value, "value");
       visitor(value->node.size, "size");
       if (value->node.node.left) {
           assert(value->node.node.left->node.node.parent == value);
           visitor(value->node.node.left, "left");
       }
       if (value->node.node.right) {
           assert(value->node.node.right->node.node.parent == value);
           visitor(value->node.node.right, "right");
       }
   }
}

TEST(structure, OrderStatisticTree) {
   std::list<NodeOST> p;
   sbl::intrusive::OrderStatisticTree<NodeOST *, GetNodeOST> tree;
   p.push_back(3), tree.insert(&p.back());
   p.push_back(5), tree.insert(&p.back());
   p.push_back(2), tree.insert(&p.back());
   p.push_back(8), tree.insert(&p.back());
   p.push_back(6), tree.insert(&p.back());
   //std::cout << ::acml::json::dumps(tree.root) << std::endl;
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
