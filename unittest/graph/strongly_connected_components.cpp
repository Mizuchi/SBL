#include"../../sbl/graph/adjacency_list.hpp"
#include"../../sbl/graph/strongly_connected_components.hpp"
#include<vector>
#include<gtest/gtest.h>
using namespace sbl;

TEST(graph, strongly_connected_components) {
    AdjacencyList a;
    a.add_edge(1, 2);

    a.add_edge(2, 3);
    a.add_edge(2, 7);
    a.add_edge(2, 8);

    a.add_edge(3, 4);
    a.add_edge(3, 6);

    a.add_edge(4, 3);
    a.add_edge(4, 5);
    a.add_edge(5, 5);

    a.add_edge(6, 5);
    a.add_edge(6, 7);

    a.add_edge(7, 6);
    a.add_edge(8, 1);
    AUTO(ans, strongly_connected_components(a));

    EXPECT_EQ(ans[1], ans[2]);
    EXPECT_EQ(ans[1], ans[8]);
    EXPECT_NE(ans[1], ans[3]);
    EXPECT_EQ(ans[3], ans[4]);
    EXPECT_EQ(ans[6], ans[7]);
    EXPECT_NE(ans[3], ans[6]);
}
