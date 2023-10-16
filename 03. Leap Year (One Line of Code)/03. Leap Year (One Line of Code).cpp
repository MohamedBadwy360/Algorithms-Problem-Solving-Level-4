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

int main()
{
    if (is_leap_year(read_year()))
        cout << "Yes. It is leap\n";
    else
        cout << "No. It isn't leap\n";
}

