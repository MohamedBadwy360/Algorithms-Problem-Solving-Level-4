#include <iostream>

using namespace std;

bool is_leap_year(unsigned short year)
{
    //return ((year % 400 == 0) ? true : ((year % 100 == 0) ? false : ((year % 4 == 0) ? true : false)));

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

unsigned short read_year()
{
    unsigned short year;

    cout << "Enter year: \n";
    cin >> year;

    return year;
}

unsigned short number_of_days_in_year(unsigned short year)
{
    return is_leap_year(year) ? 366 : 365;
}

unsigned short number_of_hours_in_year(unsigned short year)
{
    return number_of_days_in_year(year) * 24;
}

unsigned int numebr_of_minutes_in_year(unsigned short year)
{
    return number_of_hours_in_year(year) * 60;
}

unsigned int number_of_seconds_in_year(unsigned short year)
{
    return numebr_of_minutes_in_year(year) * 60;
}

int main()
{
    unsigned short year = read_year();

    cout << "Number of days     in year [" << year << "] is: " << number_of_days_in_year(year) << endl;
    cout << "Number of hours    in year [" << year << "] is: " << number_of_hours_in_year(year) << endl;
    cout << "Number of minutes  in year [" << year << "] is: " << numebr_of_minutes_in_year(year) << endl;
    cout << "Number of secondds in year [" << year << "] is: " << number_of_seconds_in_year(year) << endl;
}
