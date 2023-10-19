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
    cout << "\nEnter Start Date: \n\n";
    period.start_date = read_full_date();
    cout << "Enter End Date: \n\n";
    period.end_date = read_full_date();

    return period;
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

bool is_date_within_period(st_date date, st_period period)
{
    if (!is_date1_before_date2(date, period.start_date) && !is_date1_after_date2(date, period.end_date))
        return true;
    else
        return false;
}

int main()
{
    std::cout << "Enter Period:\n";
    st_period period = read_period();

    cout << "Enter a date: \n";
    st_date date = read_full_date();

    if (is_date_within_period(date, period))
        cout << "Yes. It is within the period.\n";
    else 
        cout << "No. It isn't within the period.\n";
}

