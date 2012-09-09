#include"../../sbl/graph/adjacency_list.hpp"
#include<gtest/gtest.h>
#include<map>

TEST(graph, adjacency_list) {
    sbl::AdjacencyList a;
    a.add_edge(0, 1);
    sbl::AdjacencyList::Edge one_two = a.add_edge(1, 2);
    a.add_edge(1, 0);
    EXPECT_EQ(a.number_of_edges(), 3);
    EXPECT_EQ(a.number_of_nodes(), 2);
    std::map<size_t, size_t> index2tail;
    foredge(a, 1, tail, index) {
        index2tail[index] = tail;
    }
    EXPECT_EQ(index2tail.size(), 2);
    EXPECT_EQ(index2tail[1], 2);
    EXPECT_EQ(index2tail[2], 0);

    EXPECT_EQ(a.find_edges(0, 1).size(), 1);
    EXPECT_EQ(a.find_edges(1, 0).size(), 1);
    EXPECT_EQ(a.find_edges(1, 2).size(), 1);
    a.remove_edge(one_two);
    EXPECT_EQ(a.find_edges(0, 1).size(), 1);
    EXPECT_EQ(a.find_edges(1, 0).size(), 1);
    EXPECT_EQ(a.find_edges(1, 2).size(), 0);

    index2tail.clear();
    foredge(a, 1, tail, index) {
        index2tail[index] = tail;
    }
    EXPECT_EQ(index2tail.size(), 1);
    EXPECT_EQ(index2tail[2], 0);
    EXPECT_EQ(index2tail.count(1), 0);
}
