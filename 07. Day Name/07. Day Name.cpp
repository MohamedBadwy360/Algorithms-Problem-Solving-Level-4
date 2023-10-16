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

unsigned short read_day()
{
    unsigned short day;

    cout << "Enter a day: \n";
    cin >> day;

    return day;
}

short day_of_week_order(unsigned short day, unsigned short month, unsigned short year)
{
    short a, y, m;
    a = (14 - month) / 12;
    y = year - a;
    m = month + (12 * a) - 2;
    // Gregorian:
    // //0:sun, 1:Mon, 2:Tue...etc

    return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string day_of_week_name(short day_of_week_order)
{
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    return days[day_of_week_order];
}

int main()
{
    unsigned short year = read_year();
    unsigned short month = read_month();
    unsigned short day = read_day();
    short day_order = day_of_week_order(day, month, year);

    cout << endl;
    cout << "Data     : " << day << "/" << month << "/" << year << endl;
    cout << "Day Order: " << day_order << endl;
    cout << "Day Name : " << day_of_week_name(day_order) << endl;
}
