#include <iostream>

using namespace std;

struct s_date
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

bool is_leap_year(short year)
{
    //return ((year % 400 == 0) ? true : ((year % 100 == 0) ? false : ((year % 4 == 0) ? true : false)));

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

short number_of_days_in_year(short year)
{
    return is_leap_year(year) ? 366 : 365;
}

short number_of_days_in_month(short month, short year)
{
    if (month < 1 || month > 12)
        return 0;

    short arr_numbers[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (month == 2) ? (is_leap_year(year) ? 29 : 28) : arr_numbers[month - 1];
}

short number_of_days_from_the_beginning_of_year(short day, short month, short year)
{
    short sum = day;

    for (short i = 1; i < month; i++)
    {
        sum += number_of_days_in_month(i, year);
    }

    return sum;
}

s_date date_from_day_order_of_year(short number_of_days, short year)
{
    s_date date;
    short remaining_days = number_of_days;

    short month_days = 0;

    date.year = year;
    date.month = 1;

    while (true)
    {
        month_days = number_of_days_in_month(date.month, year);

        if (remaining_days > month_days)
        {
            remaining_days -= month_days;
            date.month++;
        }
        else
        {
            date.day = remaining_days;
            break;
        }
    }
    return date;
}

s_date date_add_days(short day, short month, short year, short added_days)
{
    short remaining_days = number_of_days_from_the_beginning_of_year(day, month, year) + added_days;
    short year_days = 0;

    while (remaining_days > (year_days = number_of_days_in_year(year)))
    {
        remaining_days -= year_days;
        year++;
    }

    return date_from_day_order_of_year(remaining_days, year);
}

short read_number_of_days()
{
    short days;
    cout << "How Many Days?\n";
    cin >> days;

    return days;
}

int main()
{
    short year = read_year();
    short month = read_month();
    short day = read_day();
    short added_days = read_number_of_days();
    s_date date = date_add_days(day, month, year, added_days);


    cout << "Date after adding [" << added_days << "] is: ";
    cout << date.day << "/" << date.month << "/" << date.year << endl;
}

