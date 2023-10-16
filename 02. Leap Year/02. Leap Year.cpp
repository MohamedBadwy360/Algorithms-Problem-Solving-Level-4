#include <iostream>

using namespace std;

bool leap_year(unsigned short year)
{
    if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    else
        return false;
}

unsigned short read_year()
{
    unsigned short year;

    cout << "Enter year: \n";
    cin >> year;

    return year;
}

int main()
{
    if (leap_year(read_year()))
        cout << "Yes. It is leap year.\n";
    else
        cout << "No. It isn't leap year.\n";

    return 0;
}

