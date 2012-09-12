#ifndef _sbl_weighted_graph
#define _sbl_weighted_graph

#include<cstddef>
#include<functional>
#include"../utility/type_traits.hpp"

namespace sbl {
template <
    class TGraph,
    class TGetWeight,
    class TPlus = std::plus<typename result_of<TGetWeight(std::size_t)>::type>,
    class TLess = std::less<typename result_of<TGetWeight(std::size_t)>::type>
> struct WeightedGraphWrapper {

    typedef TGraph Graph;
    typedef TGetWeight GetWeight;
    typedef TPlus Plus;
    typedef TLess Less;
    typedef typename result_of<GetWeight(std::size_t)>::type Weight;

    const Graph &graph;
    const GetWeight &getWeight;
    const Plus &plus;
    const Less &less;

    WeightedGraphWrapper(
        const Graph &iGraph,
        const GetWeight &iGetWeight,
        const Plus &iPlus = Plus(),
        const Less &iLess = Less()
    ): graph(iGraph), getWeight(iGetWeight), plus(iPlus), less(iLess) {}

}; // struct WeightedGraphWrapper

} // namespace sbl

#endif
