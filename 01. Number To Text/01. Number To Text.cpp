#include <string>
#include <iostream>

using namespace std;

int read_number(string message)
{
    float number = 0;
    cout << message << endl;
    cin >> number;

    while (cin.fail())
    {
        // user didn't input a number 
        cin.clear();		// clear input 

        // ignore all input line 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Invalid Number. " << message << endl;
        cin >> number;
    }

    return number;
}

string number_to_text(int number)
{
    if (number == 0)
        return "";
    else if (number >= 1 && number <= 19)
    {
        string arr[] = { "", "One", "Two", "Three", "Four", "Five",
            "Six", "Seven", "Eight", "Nine", "Ten",
            "Eleven", "Twelve", "Thirteen", "Fourteen",
            "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

        return arr[number] + " ";

    }

    else if (number >= 20 && number <= 99)
    {
        string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty",
            "Sixty", "Seventy", "Eighty", "Ninety" };

        return arr[number / 10] + " " + number_to_text(number % 10);
    }

    else if (number >= 100 && number <= 199)
    {
        return "One Hundred " + number_to_text(number % 100);
    }

    else if (number >= 200 && number <= 999)
    {
        return number_to_text(number / 100) + "Hundreds " + number_to_text(number % 100);
    }

    else if (number >= 1000 && number <= 1999)
    {
        return "One Thousand " + number_to_text(number % 1000);
    }

    else if (number >= 2000 && number <= 999999)
    {
        return number_to_text(number / 1000) + "Thousands " + number_to_text(number % 1000);
    }

    else if (number >= 1000000 && number <= 1999999)
    {
        return "One Million " + number_to_text(number % 1000000);
    }

    else if (number >= 2000000 && number <= 999999999)
    {
        return number_to_text(number / 1000000) + "Millions " + number_to_text(number % 1000000);
    }

    else if (number >= 1000000000 && number <= 1999999999)
    {
        return "One Billion " + number_to_text(number % 1000000000);
    }

    else if (number >= 2000000000)
    {
        return number_to_text(number / 1000000000) + "Billions " + number_to_text(number % 1000000000);
    }
}

int main()
{
    cout << number_to_text(read_number("Enter a number: ")) << endl;
}

