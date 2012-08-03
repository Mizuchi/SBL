#ifndef _sbl_nullptr
#define _sbl_nullptr
static const class {
    public:
        template<class T>
        inline operator T *() const {
            return 0;
        }
        template<class C, class T>
        inline operator T C::*() const {
            return 0;
        }
    private:
        void operator&() const;
} nullptr;
#endif
