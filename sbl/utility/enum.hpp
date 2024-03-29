#ifndef _sbl_enum
#define _sbl_enum
namespace sbl {
/// safe enum idiot
template<typename Def, typename Inner = typename Def::type>
class Enum : public Def {
    private:
        typedef typename Def::type type;
        Inner val;

    public:
        Enum(type v) : val(v) {}
        Inner underlying() const { return val; }

        bool operator< (const Enum &s) const { return val <  s.val; }
        bool operator> (const Enum &s) const { return val >  s.val; }
        bool operator<=(const Enum &s) const { return val <= s.val; }
        bool operator>=(const Enum &s) const { return val >= s.val; }
        bool operator==(const Enum &s) const { return val == s.val; }
        bool operator!=(const Enum &s) const { return val != s.val; }
}; // class Enum
} // namespace sbl
#endif
