#include <iostream>

using namespace std;

struct st_date
{
    short year;
    short month;
    short day;
};

bool is_date1_before_date2(st_date date1, st_date date2)
{
    return  (date1.year < date2.year) ?
        true : ((date1.year == date2.year) ?
            (date1.month < date2.month ?
                true : (date1.month == date2.month ?
                    date1.day < date2.day : false)) : false);
}

bool is_date1_equal_date2(st_date date1, st_date date2)
{
    return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
}

bool is_date1_after_date2(st_date date1, st_date date2)
{
    return (!is_date1_before_date2(date1, date2) && !is_date1_equal_date2(date1, date2));
}

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

int main()
{
    st_date date1 = read_full_date();
    st_date date2 = read_full_date();

    if (is_date1_after_date2(date1, date2))
        cout << "\nYes. Date1 is after date2.\n";
    else
        cout << "\nNo. Date1 isn't after date2.\n";
}

