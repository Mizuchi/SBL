#include"../../sbl/utility/datetime.hpp"
#include<gtest/gtest.h>


TEST(datetime, base) {
    using namespace sbl;
    using namespace gregorianCalendar;
    EXPECT_EQ(days_between_two_dates(8, 8, 2008, 9, 9, 2008), 32);
    EXPECT_EQ(days_between_two_dates(8, 8, 2008, 8, 8, 2008), 0);
    EXPECT_EQ(days_between_two_dates(8, 8, 2008, 9, 8, 2008), 1);
    EXPECT_EQ(days_between_two_dates(1, 1, 1695, 1, 1, 1705), 3652);
    EXPECT_EQ(days_between_two_dates(1, 1, 1694, 1, 1, 1705), 4017);
    EXPECT_EQ(days_between_two_dates(1, 1, 1694, 1, 1, 1704), 3651);
    EXPECT_EQ(days_between_two_dates(1, 1, 1595, 1, 1, 1605), 3653);
    EXPECT_EQ(days_between_two_dates(1, 1, 1594, 1, 1, 1605), 4018);
    EXPECT_EQ(days_between_two_dates(1, 1, 1594, 1, 1, 1604), 3652);

    // Neil Armstrong
    EXPECT_EQ(days_between_two_dates(5, 8, 1930, 25, 8, 2012), 29971);

    // Steve Jobs
    EXPECT_EQ(days_between_two_dates(24, 2, 1955, 5, 10, 2011), 20677);

    // Napoleon
    EXPECT_EQ(days_between_two_dates(15, 8, 1769, 5, 5, 1821), 18890);
}
