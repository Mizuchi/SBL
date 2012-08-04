#include"../../sbl/utility/complex.hpp"
#include"../../sbl/utility/float.hpp"
#include<gtest/gtest.h>
#include<complex>

TEST(Complex, FloatBase) {
    using namespace sbl;
    Complex<Float> a(-3.5, 2);
    EXPECT_EQ(a.real(), -3.5);
    EXPECT_EQ(a.imag(), 2);
    EXPECT_EQ(-3.5, real(a));
    EXPECT_EQ(2, imag(a));
}

TEST(Complex, FloatMul) {
    using namespace sbl;
    {
        Complex<Float> a(2, 1), b(3, 1);
        EXPECT_EQ(a * b, Complex<Float>(5, 5));
        EXPECT_EQ(real(a * b), 5);
        EXPECT_EQ(imag(a * b), 5);
    }
    {
        Complex<int> a(2, 1), b(3, 1);
        EXPECT_EQ(a * b, Complex<int>(5, 5));
        EXPECT_EQ(real(a * b), 5);
        EXPECT_EQ(imag(a * b), 5);
    }
}

TEST(Complex, FloatDiv) {
    using namespace sbl;
    {
        Complex<Float> a(7, 1), b(3, 4);
        EXPECT_EQ(a / b, Complex<Float>(1, -1));
        a.real(-1);
        a.imag(1);
        b.real(2);
        b.imag(1);
        EXPECT_EQ(a * b / Complex<Float>(0, -1), Complex<Float>(-1, -3));
    }
}

TEST(Complex, Arg) {
    using namespace sbl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(arg(Complex<double>(i - 1, j - 1)),
                      arg(std::complex<double>(i - 1, j - 1)));
}

TEST(Complex, Abs) {
    using namespace sbl;
    for (int n = 0; n < 10; n++) {
        int i = sqrt(rand()), j = sqrt(rand());
        EXPECT_EQ(abs(Complex<double>(i - 1, j - 1)),
                  abs(std::complex<double>(i - 1, j - 1)));
    }
}

TEST(Complex, Polar) {
    using namespace sbl;
    for (size_t i = 0; i < 100; i++) {
        Complex<Float> a(sqrt(rand()), sqrt(rand()));
        EXPECT_EQ(a, sbl::polar(abs(a), arg(a)));
    }
}

TEST(Complex, assign) {
    using namespace sbl;
    {
        Complex<Float> a(1.7, 2.5), b(3.3, -2.5);
        a += b;
        EXPECT_EQ(a, 5);
        EXPECT_EQ(5, a);
    }
    {
        Complex<Float> a(1.7, 2.5), b(3.3, -2.5);
        a -= conj(b);
        EXPECT_EQ(a, -1.6);
        EXPECT_EQ(-1.6, a);
    }
    {
        Complex<int> a(2, 1), b(3, 1);
        a *= b;
        EXPECT_EQ(a, Complex<int>(5, 5));
        EXPECT_EQ(real(a), 5);
        EXPECT_EQ(imag(a), 5);
        a /= 5;
        EXPECT_EQ(a, Complex<int>(1, 1));
        EXPECT_EQ(real(a), 1);
        EXPECT_EQ(imag(a), 1);
    }
    {
        Complex<Float> mycomplex;
        mycomplex = 10.0;   // 10
        mycomplex += 2.0;   // 12
        mycomplex -= Complex<Float>(2.0,-1.0);	//  10+i
        mycomplex = mycomplex + 10.0 ; // 20+i
        EXPECT_EQ(mycomplex, Complex<Float>(20.0,1.0));
    }
}
