#include <iostream>

using namespace std;

struct st_date
{
    short year;
    short month;
    short day;
};

short read_year()
{
    short year;

    cout << "Enter a year: \n";
    cin >> year;

    return year;
}

short read_month()
{
    short month;

    cout << "Enter a month: \n";
    cin >> month;

    return month;
}

short read_day()
{
    short day;

    cout << "Enter a day: \n";
    cin >> day;

    return day;
}

st_date read_full_date()
{
    st_date date;

    date.day = read_day();
    date.month = read_month();
    date.year = read_year();

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

bool is_last_day_in_month(st_date date)
{
    return date.day == number_of_days_in_month(date.month, date.year);
}

bool is_last_month_in_year(short month)
{
    return (month == 12);
}

int main()
{
    st_date date = read_full_date();

    if (is_last_day_in_month(date))
        cout << "Yes. It is last day in month.\n";
    else
        cout << "No. It isn't last day in month.\n";

    if (is_last_month_in_year(date.month))
        cout << "Yes. It is last month in year.\n";
    else
        cout << "No. It isn't last month in year.\n";
}
