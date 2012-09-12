#include<vector>
#include<numeric>
#include<gtest/gtest.h>
#include"../../sbl/graph/adjacency_list.hpp"
#include"../../sbl/utility/functional.hpp"
#include"../../sbl/graph/shortest_path_tree.hpp"
#include<iostream>
using namespace std;

struct GetCostFromVectorMST {
    std::vector<size_t> cost;
    void add(size_t x) {
        cost.push_back(x);
    }
    size_t operator()(size_t i) const {
        return cost[i];
    }
};

TEST(graph, minimum_spanning_tree) {
    using namespace sbl;
    AdjacencyList a;
    GetCostFromVectorMST getter;

#define addedge(s, t, c) a.add_edge((s), (t)); getter.add((c));
    addedge(1, 2, 4);
    addedge(1, 8, 9); // different from CLRS

    addedge(2, 1, 4);
    addedge(2, 3, 8);
    addedge(2, 8, 11);

    addedge(3, 2, 8);
    size_t f4 = addedge(3, 4, 7);
    addedge(3, 6, 4);
    size_t f9 = addedge(3, 9, 2);
    addedge(4, 3, 7);
    size_t f5 = addedge(4, 5, 9);
    addedge(4, 6, 14);

    addedge(5, 4, 9);
    addedge(5, 6, 10);

    addedge(6, 4, 14);
    addedge(6, 5, 10);
    addedge(6, 3, 4);
    addedge(6, 7, 2);

    addedge(7, 6, 2);
    addedge(7, 8, 1);
    addedge(7, 9, 6);

    addedge(8, 1, 9);
    addedge(8, 2, 11);
    addedge(8, 7, 1);
    addedge(8, 9, 7);

    addedge(9, 7, 6);
    addedge(9, 8, 7);
    addedge(9, 3, 2);
#undef addedge

    AUTO(wg, MAKE3(WeightedGraphWrapper, a, getter, Second()));

    AUTO(ans, MAKE1(ShortestPathTree, wg));
    ans.run(1, -1, false);
    EXPECT_FALSE(ans.in_tree(0));
    int all = 0;
    for (int i = 1; i < 10; i++) 
        all += ans.get_sum_of_weights(i);

    // If get 28, you may need to keep in mind that 
    // prim is a little a bit different with dijkstra.
    // You can not relax a node which is already in path tree.
    EXPECT_EQ(all, 0 + 4 + 8 + 7 + 9 + 4 + 2 + 1 + 2);

    EXPECT_EQ(ans.get_sum_of_weights(4), 7);
    EXPECT_EQ(ans.get_father(4), 3);
    EXPECT_EQ(ans.get_edge_to_father(4), f4);

    EXPECT_EQ(ans.get_sum_of_weights(5), 9);
    EXPECT_EQ(ans.get_father(5), 4);
    EXPECT_EQ(ans.get_edge_to_father(5), f5);

    EXPECT_EQ(ans.get_sum_of_weights(9), 2);
    EXPECT_EQ(ans.get_father(9), 3);
    EXPECT_EQ(ans.get_edge_to_father(9), f9);
}
