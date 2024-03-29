#include<vector>
#include<gtest/gtest.h>
#include"../../sbl/graph/adjacency_list.hpp"
#include"../../sbl/graph/shortest_path_tree.hpp"

struct GetCostFromVector {
    std::vector<size_t> cost;
    void add(size_t x) {
        cost.push_back(x);
    }
    size_t operator()(size_t i) const{
        return cost[i];
    }
};

TEST(graph, shortest_path) {
    using namespace sbl;
    AdjacencyList a;
    GetCostFromVector getter;
#define addedge(s, t, c) a.add_edge((s), (t)); getter.add((c));
    addedge(0, 1, 10);
    addedge(0, 4, 5);

    addedge(1, 2, 1);
    addedge(1, 4, 2);

    addedge(2, 3, 4);
    addedge(3, 0, 7);
    addedge(3, 2, 6);

    addedge(4, 1, 3);
    addedge(4, 2, 9);
    addedge(4, 3, 2);
#undef addedge
    AUTO(weightedGraph, MAKE2(WeightedGraphWrapper, a, getter));
    {
    AUTO(ans, MAKE1(ShortestPathTree, weightedGraph));
    ans.run(0);

    EXPECT_EQ(ans.get_sum_of_weights(1), 8);
    EXPECT_EQ(ans.get_sum_of_weights(2), 9);
    EXPECT_EQ(ans.get_sum_of_weights(3), 7);
    EXPECT_EQ(ans.get_sum_of_weights(4), 5);
    }
    {
    AUTO(ans, MAKE1(ShortestPathTree, weightedGraph));
    ans.run(0, -1, true);

    EXPECT_EQ(ans.get_sum_of_weights(1), 8);
    EXPECT_EQ(ans.get_sum_of_weights(2), 9);
    EXPECT_EQ(ans.get_sum_of_weights(3), 7);
    EXPECT_EQ(ans.get_sum_of_weights(4), 5);
    }
}
