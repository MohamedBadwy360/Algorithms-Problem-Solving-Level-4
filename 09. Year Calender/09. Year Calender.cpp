#include <iostream>

using namespace std;

short read_year()
{
    short year;

    cout << "Enter a year: \n";
    cin >> year;

    return year;
}

bool is_leap_year(short year)
{
    //return ((year % 400 == 0) ? true : ((year % 100 == 0) ? false : ((year % 4 == 0) ? true : false)));

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

string month_name(short month)
{
    string month_arr[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    return month_arr[month - 1];
}

short number_of_days_in_month(short month, short year)
{
    if (month < 1 || month > 12)
        return 0;

    short arr_numbers[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (month == 2) ? (is_leap_year(year) ? 29 : 28) : arr_numbers[month - 1];
}

short day_of_week_order(short day, short month, short year)
{
    short a, y, m;
    a = (14 - month) / 12;
    y = year - a;
    m = month + (12 * a) - 2;
    // Gregorian:
    // //0:sun, 1:Mon, 2:Tue...etc

    return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

void print_month_calendar(short month, short year)
{
    short current = day_of_week_order(1, month, year);
    int number_of_days = number_of_days_in_month(month, year);

    printf("\n  ______________ %s _______________\n\n", month_name(month).c_str());
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    short i = 0;
    for (i = 0; i < current; i++)
    {
        printf("     ");
    }

    for (short j = 1; j <= number_of_days; j++)
    {
        printf("%5d", j);

        if (++i == 7)
        {
            i = 0;
            cout << endl;
        }
    }

    printf("\n  __________________________________\n");
}

void print_year_calendar(short year)
{
    printf("\n  __________________________________\n\n");
    printf("\t    Calendar %d", year);
    printf("\n  __________________________________\n");

    for (short i = 1; i <= 12; i++)
    {
        print_month_calendar(i, year);
    }
}

int main()
{
    short year = read_year();

    print_year_calendar(year);
}
