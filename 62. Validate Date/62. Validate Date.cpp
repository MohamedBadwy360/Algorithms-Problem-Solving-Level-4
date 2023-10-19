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

bool is_valid_date(st_date date)
{
    if (date.day < 1 || date.day > number_of_days_in_month(date.month, date.year))
        return false;
    else if (date.month < 1 || date.month > 12)
        return false;
    else
        return true;
}

int main()
{
    st_date date = read_full_date();

    if (is_valid_date(date))
        cout << "Yes. It is valid date.\n";
    else
        cout << "No. It isn't valid date.\n";
}
