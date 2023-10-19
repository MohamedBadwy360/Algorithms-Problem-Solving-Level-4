#include <iostream>

using namespace std;

struct st_date
{
    short year;
    short month;
    short day;
};

struct st_period
{
    st_date start_date;
    st_date end_date;
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

st_period read_period()
{
    st_period period;
    cout << "\nStart Date: \n\n";
    period.start_date = read_full_date();
    cout << "End Date: \n\n";
    period.end_date = read_full_date();

    return period;
}

bool is_date1_before_date2(st_date date1, st_date date2)
{
    return  (date1.year < date2.year) ?
        true : ((date1.year == date2.year) ?
            (date1.month < date2.month ?
                true : (date1.month == date2.month ?
                    date1.day < date2.day : false)) : false);
}

bool is_period_overlap(st_period period1, st_period period2)
{
    if (is_date1_before_date2(period1.end_date, period2.start_date) || is_date1_before_date2(period2.end_date, period1.start_date))
        return false;
    else 
        return true;
}


int main()
{
    cout << "Period 1: \n";
    st_period period1 = read_period();
    cout << "====================\n";
    cout << "Period 2: \n";
    st_period period2 = read_period();

    if (is_period_overlap(period1, period2))
        cout << "Yes. It is overlapped.\n";
    else
        cout << "No. It isn't overlapped.\n";
}

