#include <iostream>

using namespace std;

unsigned short read_year()
{
    unsigned short year;

    cout << "Enter a year: \n";
    cin >> year;

    return year;
}

unsigned short read_month()
{
    unsigned short month;

    cout << "Enter a month: \n";
    cin >> month;

    return month;
}

bool is_leap_year(unsigned short year)
{
    //return ((year % 400 == 0) ? true : ((year % 100 == 0) ? false : ((year % 4 == 0) ? true : false)));

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

unsigned short number_of_days_in_month(unsigned short year, unsigned short month)
{
    if (month < 1 || month > 12)
        return 0;
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else if (month == 2)
        return is_leap_year(year) ? 29 : 28;
    else
        return 30;
}

unsigned short number_of_hours_in_month(unsigned short year, unsigned short month)
{
    return number_of_days_in_month(year, month) * 24;
}

unsigned int number_of_minutes_in_month(unsigned short year, unsigned short month)
{
    return number_of_hours_in_month(year, month) * 60;
}

unsigned int number_of_seconds_in_month(unsigned short year, unsigned short month)
{
    return number_of_minutes_in_month(year, month) * 60;
}

int main()
{
    unsigned short year = read_year();
    unsigned short month = read_month();

    cout << "\nNumber of days     in month [" << month << "] is: " << number_of_days_in_month(year, month) << endl;
    cout << "Number of hours    in month [" << month << "] is: " << number_of_hours_in_month(year, month) << endl;
    cout << "Number of minutes  in month [" << month << "] is: " << number_of_minutes_in_month(year, month) << endl;
    cout << "Number of secondds in month [" << month << "] is: " << number_of_seconds_in_month(year, month) << endl;
}
