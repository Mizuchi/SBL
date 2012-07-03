#ifndef _sbl_base
#define _sbl_base
#include<cassert>
#include<ctime>

namespace sbl {
#define TYPEOF     __typeof
#define AUTO(x, y) TYPEOF(y) x(y)
#define FOR(i, c)  for(AUTO(i, (c).begin()); i != (c).end(); ++i)
#define RFOR(i, c) for(AUTO(i, (c).end()); i-- != (c).begin();  )

/// Return run time for this thread in second.
static double spend_time() {
    return double(clock()) / CLOCKS_PER_SEC;
}
} // namespace sbl
#endif
