#include"../../sbl/graph/flow.hpp"
#include<gtest/gtest.h>

namespace graphFlow {
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

TEST(graph, flow) {
    using namespace graphFlow;
    // CLRS 2nd edition P.643
    sbl::AdjacencyList graph;
    FlowKeeper keeper;
    GetCapacity cap;

    cap.set(graph.add_edge(0, 1), 16);
    cap.set(graph.add_edge(0, 2), 13);
    cap.set(graph.add_edge(1, 2), 10);
    cap.set(graph.add_edge(2, 1),  4);
    cap.set(graph.add_edge(1, 3), 12);
    cap.set(graph.add_edge(3, 2),  9);
    cap.set(graph.add_edge(2, 4), 14);
    cap.set(graph.add_edge(4, 3),  7);
    cap.set(graph.add_edge(3, 5), 20);
    cap.set(graph.add_edge(4, 5),  4);

    sbl::max_flow(graph, cap, keeper.flow_getter(), keeper.flow_setter(), 0, 5);

    std::map<size_t, int> nodeInOut;

    for (size_t head = 0; head < graph.number_of_nodes(); head++)
        foredge(graph, head, tail, index) {
        size_t flow = keeper.flow_getter()(index);
        EXPECT_LE(flow, cap(index));
        //if (flow) std::cout << head << " --> " << tail << ": " << flow << std::endl;
        nodeInOut[head] -= flow;
        nodeInOut[tail] += flow;
    }

    EXPECT_EQ(nodeInOut[0], -23);
    EXPECT_EQ(nodeInOut[1], 0);
    EXPECT_EQ(nodeInOut[2], 0);
    EXPECT_EQ(nodeInOut[3], 0);
    EXPECT_EQ(nodeInOut[4], 0);
    EXPECT_EQ(nodeInOut[5], 23);
}
