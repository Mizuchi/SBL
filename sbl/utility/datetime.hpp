#ifndef _sbl_datetime
#define _sbl_datetime
#include<cassert>

namespace sbl {
namespace gregorianCalendar {

/// Check whether the date is suitable with gregorian calendar
/// In another word, whether the date after 15 October 1582.
/// Since Gregorian calendar is used after that,
/// use it before that date is not recommended.
static inline bool is_valid(int day, int month, int year) {
    if (year != 1582) return year > 1582;
    if (month != 10) return month > 10;
    return day >= 15;
}

/// @return whether a given year is leap year
static inline bool is_leap_year(int year) {
    return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0;
}

/// Given year and month, return how many days in that month.
static inline int days_of_month(int month, int year) {
    assert(month >= 1);
    assert(month <= 12);
    int daysOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(year))
        daysOfMonth[2] = 29;
    return daysOfMonth[month];
}

int __absolute_days(int day, int month, int year) {
    int leapYearCount = (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    int result = 365 * (year - 1) + leapYearCount;
    for (int i = 1; i < month; ++i)
        result += days_of_month(i, year);
    result += day;
    return result;
}

/// @return days between two dates.
static inline int days_between_two_dates(
    int day1, int month1, int year1,
    int day2, int month2, int year2
) {
    return __absolute_days(day2, month2, year2) -
           __absolute_days(day1, month1, year1);
}

} // namespace gregorianCalendar
} // namespace sbl
#endif
