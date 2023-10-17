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

s_date read_date()
{
    s_date date;

    date.day = read_day();
    date.month = read_month();
    date.year = read_year();

    return date;
}

bool is_date1_before_date2(s_date date1, s_date date2)
{
    return  (date1.year < date2.year) ?
        true : ((date1.year == date2.year) ?
            (date1.month < date2.month ?
                true : (date1.month == date2.month ?
                    date1.day < date2.day : false)) : false); 
}

int main()
{
    s_date date1 = read_date();
    s_date date2 = read_date();

    if (is_date1_before_date2(date1, date2))
        cout << "\nYes. Date1 is before date2.\n";
    else 
        cout << "\nNo. Date1 isn't before date2.\n";
}

