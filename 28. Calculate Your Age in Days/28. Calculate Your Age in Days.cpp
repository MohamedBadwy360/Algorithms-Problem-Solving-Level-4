#include <iostream>
#include <ctime>

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

    cout << "Enter a  year: ";
    cin >> year;

    return year;
}

short read_month()
{
    short month;

    cout << "Enter a month: ";
    cin >> month;

    return month;
}

short read_day()
{
    short day;

    cout << "Enter a   day: ";
    cin >> day;

    return day;
}

st_date read_full_date()
{
    st_date date;

    date.day = read_day();
    date.month = read_month();
    date.year = read_year();
    cout << endl;

    return date;
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

short number_of_days_from_the_beginning_of_year(st_date date)
{
    short sum = date.day;

    for (short i = 1; i < date.month; i++)
    {
        sum += number_of_days_in_month(i, date.year);
    }

    return sum;
}

bool is_date1_before_date2(st_date date1, st_date date2)
{
    if (date1.year < date2.year)
        return true;
    else if (date1.year == date2.year)
    {
        if (date1.month < date2.month)
            return true;
        else if (date1.month == date2.month)
        {
            if (date1.day < date2.day)
                return true;
        }
    }
    else
        return false;
}

int difference_between_days(st_date date1, st_date date2, bool include_end_day = false)
{
    if (is_date1_before_date2(date1, date2))
    {
        if (date1.year == date2.year)
        {
            return number_of_days_from_the_beginning_of_year(date2)
                - number_of_days_from_the_beginning_of_year(date1)
                + include_end_day;
        }
        else
        {
            int remaining_days = number_of_days_in_year(date1.year)
                - number_of_days_from_the_beginning_of_year(date1)
                + number_of_days_from_the_beginning_of_year(date2);

            for (short i = date1.year + 1; i < date2.year; i++)
            {
                remaining_days += number_of_days_in_year(i);
            }

            return remaining_days + include_end_day;
        }
    }

    return -1;
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

int main()
{
    cout << "Please Enter Birthday: \n\n";
    st_date birth = read_full_date();
    st_date today_date = get_system_date();

    cout << "Your age is: " << difference_between_days(birth, today_date, true) << " days.\n";
}
