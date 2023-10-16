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
    
    unsigned short arr_numbers[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (month == 2) ? (is_leap_year(year) ? 29 : 28) : arr_numbers[month - 1];
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