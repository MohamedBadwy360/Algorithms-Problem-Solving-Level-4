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

short read_number_of_days()
{
    short days;
    cout << "How Many Days?\n";
    cin >> days;

    return days;
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

st_date increase_date_by_on_day(st_date date)
{
    if (is_last_day_in_month(date))
    {
        if (is_last_month_in_year(date.month))
        {
            date.day = 1;
            date.month = 1;
            date.year++;
        }
        else
        {
            date.day = 1;
            date.month++;
        }
    }
    else
    {
        date.day++;
    }

    return date;
}

st_date increase_date_by_x_days(short days, st_date date)
{
    for (short i = 1; i <= days; i++)
    {
        date = increase_date_by_on_day(date);
    }

    return date;
}

st_date increase_days_by_one_week(st_date date)
{
    for (short i = 1; i <= 7; i++)
    {
        date = increase_date_by_on_day(date);
    }

    return date;
}

st_date increase_date_by_x_weeks(short weeks, st_date date)
{
    for (short i = 1; i <= weeks; i++)
    {
        date = increase_days_by_one_week(date);
    }

    return date;
}

st_date increase_date_by_one_month(st_date date)
{
    if (date.month == 12)
    {
        date.month = 1;
        date.year++;
    }
    else
    {
        date.month++;
    }

    short days_number_in_month = number_of_days_in_month(date.month, date.year);
    if (date.day > days_number_in_month)
    {
        date.day = days_number_in_month;
    }

    return date;
}

st_date increase_date_by_x_month(short months, st_date date)
{
    for (short i = 1; i <= months; i++)
    {
        date = increase_date_by_one_month(date);
    }

    return date;
}

st_date increase_date_by_one_year(st_date date)
{
    date.year++;

    return date;
}

st_date increase_date_by_x_years(short years, st_date date)
{
    date.year += years;

    return date;
}

st_date increase_date_by_one_dacade(st_date date)
{
    date.year += 10;

    return date;
}

st_date increase_date_by_x_decades(short decades, st_date date)
{
    date.year += decades * 10;

    return date;
}

st_date increase_date_by_one_century(st_date date)
{
    date.year += 100;

    return date;
}

st_date increase_date_by_one_millennium(st_date date)
{
    date.year += 1000;

    return date;
}


int main()
{
    st_date date = read_full_date();

    date = increase_date_by_on_day(date);
    cout << "\n01. Adding one day is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_x_days(10, date);
    cout << "\n02. Adding 10 days is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_days_by_one_week(date);
    cout << "\n03. Adding one week is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_x_weeks(10, date);
    cout << "\n04. Adding 10 weeks is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_one_month(date);
    cout << "\n05. Adding one month is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_x_month(5, date);
    cout << "\n06. Adding 5 months is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_one_year(date);
    cout << "\n07. Adding one year is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_x_years(10, date);
    cout << "\n08. Adding 10 years is\t\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_one_dacade(date);
    cout << "\n09. Adding one decade is\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_x_decades(10, date);
    cout << "\n10. Adding 10 decades is\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_one_century(date);
    cout << "\n11. Adding one century is\t: " << date.day << "/" << date.month << "/" << date.year;

    date = increase_date_by_one_millennium(date);
    cout << "\n12. Adding one millennium is\t: " << date.day << "/" << date.month << "/" << date.year;

    system("pause>0");
    return 0;
}
