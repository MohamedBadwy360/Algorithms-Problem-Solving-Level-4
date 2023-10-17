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

st_date read_date()
{
    st_date date;

    date.day = read_day();
    date.month = read_month();
    date.year = read_year();

    return date;
}

bool is_date1_equal_date2(st_date date1, st_date date2)
{
    return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
}

int main()
{
    st_date date1 = read_date();
    st_date date2 = read_date();

    if (is_date1_equal_date2(date1, date2))
        cout << "\nYes. Date1 is equal to date2.\n";
    else
        cout << "\nNo. Date1 isn't equal to date2.\n";
}