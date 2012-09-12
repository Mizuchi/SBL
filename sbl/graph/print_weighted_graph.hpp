#ifndef _sbl_print_weighted_graph
#define _sbl_print_weighted_graph
#include<ostream>
#include<string>
#include"foredge.hpp"
#include"weighted_graph.hpp"
#include"../utility/lexical_cast.hpp"

namespace sbl {
template<class A, class B, class C, class D>
std::ostream &operator<<(std::ostream &os, WeightedGraphWrapper<A,B,C,D> wg) {
    struct {
        std::string operator()(size_t v, size_t len) const {
            AUTO(result, str(v));
            while (result.size() < len)
                result = " " + result;
            return result;
        }
    } str_width; //     struct
    for (size_t head = 0; head < wg.graph.number_of_nodes(); head++) {
        foredge(wg.graph, head, tail, edge) {
            os << str_width(edge, 4) << ": "
               << str_width(head, 3) << " --> "
               << str_width(tail, 3) << " ["
               << wg.getWeight(edge) << "]" << std::endl;
        }
    }
    return os;
}
} // namespace sbl;
#endif
