#ifndef _sbl_stl_printer
#define _sbl_stl_printer
#include"../base.hpp"
#include<list>
#include<deque>
#include<iostream>
#include<set>
#include<map>
namespace sbl {
// XXX: using namespace std is not a good idea
using namespace std;
typedef ostream &ost;
#define OHEAD template<class T> ost operator<<
#define THEAD template<class T1, class T2> ost operator<<

THEAD(ost os, pair<T1, T2> a) {
    return os << a.first << ": " << a.second;
}
template<class T>
ost sbl_printer(ost os, const T &a, const string &sp = ", ") {
    if (a.empty()) return os;
    os << "<" << a.size() << ">" << sp;
    FOR(i, a) {
        if (i != a.begin()) os << sp;
        os << *i;
    }
    return os;
}
OHEAD(ost os, const vector<T> &a) {
    os << '[';
    sbl_printer(os, a);
    return os << ']';
}
OHEAD(ost os, const set<T> &a) {
    os << "(";
    sbl_printer(os, a);
    return os << ")";
}
THEAD(ost os, const map<T1, T2> &a) {
    os << "{";
    sbl_printer(os, a);
    return os << "}";
}
OHEAD(ost os, const vector<vector<T> > &a) {
    os << '[';
    sbl_printer(os, a, "\n");
    return os << ']';
}

OHEAD(ost os, const list<T> &a) {
    os << "[";
    sbl_printer(os, a);
    return os << "]";
}
OHEAD(ost os, const deque<T> &a) {
    os << "[";
    sbl_printer(os, a);
    return os << "]";
}
OHEAD(ost os, const multiset<T> &a) {
    os << "(";
    sbl_printer(os, a);
    return os << ")";
}
THEAD(ost os, const multimap<T1, T2> &a) {
    os << "{";
    sbl_printer(os, a);
    return os << "}";
}
#undef OHEAD
#undef THEAD
} // namespace sbl
#endif
