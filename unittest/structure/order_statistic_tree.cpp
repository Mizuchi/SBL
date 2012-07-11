#include<gtest/gtest.h>
#include<list>
#include<iostream>
//#include<acml/json.hpp>
//#include<acml/acml.hpp>

//#define private public
//#define protected public
//using namespace std;
#include"../../sbl/structure/order_statistic_tree.hpp"

struct NodeOST {
   sbl::OrderStatisticTreeNode<NodeOST *> node;
   int value;
   NodeOST(int _): value(_) {}
};

struct CompareOST {
    bool operator()(NodeOST *a, NodeOST *b) const {
        return a->value < b->value;
    }
};

struct GetNodeOST {
   sbl::OrderStatisticTreeNode<NodeOST *> &
   operator()(NodeOST *a) const {
       return a->node;
   }
};

//ACML_REGISTER_HANDLE(NodeOST *, visitor, value) {
//   if (value) {
//       visitor(value->value, "value");
//       visitor(value->node.size, "size");
//       if (value->node.left) {
//           assert(value->node.left->node.parent == value);
//           visitor(value->node.left, "left");
//       }
//       if (value->node.right) {
//           assert(value->node.right->node.parent == value);
//           visitor(value->node.right, "right");
//       }
//   }
//}

TEST(structure, OrderStatisticTree) {
   std::list<NodeOST> p;
   sbl::OrderStatisticTree<NodeOST *, GetNodeOST, CompareOST> tree;
   p.push_back(3), tree.insert(&p.back());
   p.push_back(5), tree.insert(&p.back());
   p.push_back(2), tree.insert(&p.back());
   p.push_back(8), tree.insert(&p.back());
   p.push_back(6), tree.insert(&p.back());
   NodeOST x(3);
   EXPECT_EQ(tree.biggest()->value, 8);
   EXPECT_EQ(tree.at(2)->value, 5);
   EXPECT_EQ(tree.find(&x)->value, 3);
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
