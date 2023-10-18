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

short day_of_week_order(st_date date)
{
    short a, y, m;
    a = (14 - date.month) / 12;
    y = date.year - a;
    m = date.month + (12 * a) - 2;
    // Gregorian:
    // //0:sun, 1:Mon, 2:Tue...etc

    return (date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string day_of_week_name(short day_of_week_order)
{
    string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    return days[day_of_week_order];
}

bool is_weekend(st_date date)
{
    short day_order = day_of_week_order(date);
    return (day_order == 5 || day_order == 6);
}

bool is_business_day(st_date date)
{
    return !is_weekend(date);
}

short calculate_vacation_days(st_date date1, st_date date2)
{
    short days_counter = 0;

    while (is_date1_before_date2(date1, date2))
    {
        if (is_business_day(date1))
            days_counter++;

        date1 = increase_date_by_on_day(date1);
    }
    return days_counter;
}

int main()
{
    cout << "Vacation Starts:\n";
    st_date date1 = read_full_date();

    cout << "Vacation ends:\n";
    st_date date2 = read_full_date();

    cout << "\nVacation from: " << day_of_week_name(day_of_week_order(date1)) << ", "
         << date1.day << "/" << date1.month << "/" << date1.year;
    cout << "\nVacation to  : " << day_of_week_name(day_of_week_order(date2)) << ", "
         << date2.day << "/" << date2.month << "/" << date2.year;

    cout << "\n\nActual Vacation Days: " << calculate_vacation_days(date1, date2) << endl;
}

