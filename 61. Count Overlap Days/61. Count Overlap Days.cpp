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

void swap_dates(st_date& date1, st_date& date2)
{
    st_date temp_date;

    temp_date.year = date1.year;
    temp_date.month = date1.month;
    temp_date.day = date1.day;

    date1.year = date2.year;
    date1.month = date2.month;
    date1.day = date2.day;

    date2.year = temp_date.year;
    date2.month = temp_date.month;
    date2.day = temp_date.day;
}

int difference_between_days(st_date date1, st_date date2, bool include_end_day = false)
{
    int days = 0;
    short swap_flag_value = 1;

    if (!is_date1_before_date2(date1, date2))
    { //Swap Dates 
        swap_dates(date1, date2);
        swap_flag_value = -1;
    }
    while (is_date1_before_date2(date1, date2))
    {
        days++;
        date1 = increase_date_by_on_day(date1);
    }
    return include_end_day ? ++days * swap_flag_value : days * swap_flag_value;
}

int period_length_in_days(st_period period, bool include_end_day = false)
{
    return difference_between_days(period.start_date, period.end_date, include_end_day);
}

bool is_period_overlap(st_period period1, st_period period2)
{
    if (is_date1_before_date2(period1.end_date, period2.start_date) || is_date1_before_date2(period2.end_date, period1.start_date))
        return false;
    else
        return true;
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

int overlap_days(st_period period1, st_period period2)
{
    int period1_length = period_length_in_days(period1, true);
    int period2_length = period_length_in_days(period2, true);
    int overlap_days = 0;

    if (!is_period_overlap(period1, period2))
        return 0;

    if (period1_length < period2_length)
    {
        while (is_date1_before_date2(period1.start_date, period1.end_date))
        {
            if (is_date_within_period(period1.start_date, period2))
                overlap_days++;

            period1.start_date = increase_date_by_on_day(period1.start_date);
        }
    }
    else
    {
        while (is_date1_before_date2(period2.start_date, period2.end_date))
        {
            if (is_date_within_period(period2.start_date, period1))
                overlap_days++;

            period2.start_date = increase_date_by_on_day(period2.start_date);
        }
    }

    return overlap_days;
}

int main()
{
    cout << "Period 1: \n";
    st_period period1 = read_period();
    cout << "====================\n";
    cout << "Period 2: \n";
    st_period period2 = read_period();

    cout << "Overlap days = " << overlap_days(period1, period2) << endl;
}