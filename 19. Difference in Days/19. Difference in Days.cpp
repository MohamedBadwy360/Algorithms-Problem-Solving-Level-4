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

int main()
{
    st_date date1 = read_full_date();
    st_date date2 = read_full_date();

    cout << "Difference is: " << difference_between_days(date1, date2) << " days\n";
    cout << "Difference (including end day) is: " << difference_between_days(date1, date2, true) << " days\n";
}