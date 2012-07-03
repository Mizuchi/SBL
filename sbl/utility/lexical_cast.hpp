#ifndef _sbl_lexical_cast
#define _sbl_lexical_cast
#include<string>
#include<sstream>
#include<stdexcept>

namespace sbl {

/// General literal text conversions, 
/// such as an int represented as a string, or vice-versa.
template<class T1, class T2>
T1 lexical_cast(const T2 &a) {
    std::stringstream s;
    T1 b;
    if ((s << a) and (s >> b)) return b;
    // Shouldn't reach here
    assert(false);
}

/// Convert anything to string
template<class T>
std::string str(const T& a) {
    // Do not overload this function, just specialize.
    // http://www.gotw.ca/publications/mill17.htm
    return lexical_cast<std::string>(a);
}
} // namespace sbl
#endif
