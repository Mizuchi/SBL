
#include"../../sbl/graph/flow.hpp"
#include<gtest/gtest.h>

namespace graphCostFlow {
struct GetCapacity {
    std::vector<size_t> capacity;
    size_t operator()(size_t edge) const {
        if (edge < capacity.size())
            return capacity[edge];
        else
            return 0;
    }
    void set(size_t edge, size_t value) {
        if (edge >= capacity.size())
            capacity.resize(edge + 1, 0);
        capacity[edge] = value;
    }
}; // struct GetCapacity

struct FlowKeeper {
    std::vector<size_t> flow;
    struct GetFlow {
        std::vector<size_t> &flow;
        GetFlow(std::vector<size_t> &_): flow(_) {}
        size_t operator()(size_t edge) const {
            if (edge < flow.size())
                return flow[edge];
            else
                return 0;
        }
    }; //     struct GetFlow
    struct SetFlow {
        std::vector<size_t> &flow;
        SetFlow(std::vector<size_t> &_): flow(_) {}
        void operator()(size_t edge, size_t value) {
            if (edge >= flow.size())
                flow.resize(edge + 1, 0);
            flow[edge] = value;
        }

    }; //     struct SetFlow
    GetFlow flow_getter() {
        return GetFlow(flow);
    }
    SetFlow flow_setter() {
        return SetFlow(flow);
    }
}; // struct GetFlow


}

TEST(graph, cost_flow) {
    using namespace graphCostFlow;
    // CLRS 2nd edition P.643
    sbl::AdjacencyList graph;
    FlowKeeper keeper;
    GetCapacity cap, cost;

#define addedge(i, j, b, c)                \
    do {                                   \
        AUTO(edge, graph.add_edge(i, j));  \
        cap.set(edge, c);                  \
        cost.set(edge, b);                 \
    } while(false)

    addedge(0, 1, 4, 15);
    addedge(0, 2, 2, 15);
    addedge(0, 3, 6, 10);

    addedge(2, 1, 5, 5);
    addedge(2, 3, 1, 10);

    addedge(1, 4, 5, 10);
    addedge(2, 4, 8, 10);
    addedge(3, 4, 5, 10);

#undef addedge

    sbl::minimum_cost_flow(graph, cap, keeper.flow_getter(), keeper.flow_setter(), cost, 0, 4);

    std::map<size_t, int> nodeInOut;

    size_t allCost = 0;

    for (size_t head = 0; head < graph.number_of_nodes(); head++) {
        foredge(graph, head, tail, index) {
            size_t flow = keeper.flow_getter()(index);
            EXPECT_LE(flow, cap(index));
            nodeInOut[head] -= flow;
            nodeInOut[tail] += flow;
            allCost += flow * cost(index);
        }
    }

    EXPECT_EQ(nodeInOut[0], -30);
    EXPECT_EQ(nodeInOut[1], 0);
    EXPECT_EQ(nodeInOut[2], 0);
    EXPECT_EQ(nodeInOut[3], 0);
    EXPECT_EQ(nodeInOut[4], 30);
    EXPECT_EQ(allCost, 285);
}
