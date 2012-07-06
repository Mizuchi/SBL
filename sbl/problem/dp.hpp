#ifndef _sbl_dynamic_programming
#define _sbl_dynamic_programming

namespace sbl {
namespace dp {

/* -----------------------------------------------------------------------*/
/**
 * @brief Get the best decision.
 *
 * let opt[k] satisfy for all j, func(k, opt[k]) < func(k, j)
 * if opt array satisfy opt[0] < opt[1] < ... < opt[N],
 * We can get opt array in O(NlogN)
 *
 * limit func(i, j) in i1 <= i < i2, j1 <= j < j2.
 * for every i, when we find a answer, we will call opt[i] = j.
 *
 * @param i1 lower_bound i
 * @param i2 upper_bound i
 * @param j1 lower_bound j
 * @param j2 upper_bound j
 * @param opt assign opt[i]
 * @param f function
 */
/* -------------------------------------------------------------------------*/
template<class Opt, class Func, class Pred>
void get_opt(size_t i1, size_t i2,
             size_t j1, size_t j2,
             Opt &opt, const Func &f,
             const Pred &pred) {
    if (i1 >= i2) return;
    size_t m = (i1 + i2) / 2, k = j1;
    for (size_t j = j1 + 1; j < j2; j ++)
        if (pred(f(m, j), f(m, k))) k = j;
    opt[m] = k;
    get_opt(i1, m, j1, k + 1, opt, f, pred);
    get_opt(m + 1, i2, k, j2, opt, f, pred);
}

} // namespace dp
} // namespace sbl
#endif
