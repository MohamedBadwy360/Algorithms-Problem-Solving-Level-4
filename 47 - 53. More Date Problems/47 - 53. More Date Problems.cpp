#include <iostream>

using namespace std;

struct st_date
{
    short year;
    short month;
    short day;
};

short day_of_week_order(st_date date)
{
    short a, y, m;
    a = (14 - date.month) / 12;
    y = date.year - a;
    m = date.month + (12 * a) - 2;
    // Gregorian:
    // //0:sun, 1:Mon, 2:Tue...etc

    return (date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string day_of_week_name(short day_of_week_order)
{
    string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    return days[day_of_week_order];
}

st_date get_system_date()
{
    st_date date;

    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    date.day = now.tm_mday;
    date.month = now.tm_mon + 1;
    date.year = now.tm_year + 1900;

    return date;
}

bool is_leap_year(short year)
{
    //return ((year % 400 == 0) ? true : ((year % 100 == 0) ? false : ((year % 4 == 0) ? true : false)));

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

short number_of_days_in_month(short month, short year)
{
    if (month < 1 || month > 12)
        return 0;

    short arr_numbers[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (month == 2) ? (is_leap_year(year) ? 29 : 28) : arr_numbers[month - 1];
}

short number_of_days_in_year(short year)
{
    return is_leap_year(year) ? 366 : 365;
}

short number_of_days_from_the_beginning_of_year(st_date date)
{
    short sum = date.day;

    for (short i = 1; i < date.month; i++)
    {
        sum += number_of_days_in_month(i, date.year);
    }

    return sum;
}

bool is_end_of_week(st_date date)
{
    return (day_of_week_order(date) == 6);
}

bool is_weekend(st_date date)
{
    short day_order = day_of_week_order(date);
    return (day_order == 5 || day_order == 6);
}

bool is_business_day(st_date date)
{
    return !is_weekend(date);
}

short days_until_end_of_week(st_date date)
{
    return (6 - day_of_week_order(date));
}

short days_until_end_of_month(st_date date)
{
    return (number_of_days_in_month(date.month, date.year) - date.day);
}

short days_until_end_of_year(st_date date)
{
    return (number_of_days_in_year(date.year) - number_of_days_from_the_beginning_of_year(date));
}


int main()
{
    st_date date = get_system_date();

    short day_order = day_of_week_order(date);
    cout << "Today is " << day_of_week_name(day_order) << ", " << date.day << "/" << date.month << "/" << date.year;

    // ============================================

    cout << "\n\nIs it end of week?\n";
    if (is_end_of_week(date))
        cout << "Yes. It is end of week.\n";
    else
        cout << "No. It isn't end of week.\n";

    // ============================================

    cout << "\nIs it Weekend?\n";
    if (is_weekend(date))
        cout << "Yes. It is weekend.\n";
    else
        cout << "No. It isn't weekend.\n";

    // ============================================

    cout << "\nIs it business day?\n";
    if (is_business_day(date))
        cout << "Yes. It is business day.\n";
    else
        cout << "No. It isn't business day.\n";

    // ============================================

    cout << "\nDays until end of week: " << days_until_end_of_week(date) << endl;
    cout << "Days until end of month: " << days_until_end_of_month(date) << endl;
    cout << "Days until end of year: " << days_until_end_of_year(date) << endl;
}
