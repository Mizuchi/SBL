#ifndef _sbl_base
#define _sbl_base
#include<cassert>
#include<utility>

namespace sbl {
using namespace std::rel_ops;
#define TYPEOF     __typeof
#define AUTO(x, y) TYPEOF(y) x(y)
#define FOR(i, c)  for(AUTO(i, (c).begin()); i != (c).end(); ++i)
#define RFOR(i, c) for(AUTO(i, (c).end()); i-- != (c).begin();  )
}
#endif // _sbl_base
