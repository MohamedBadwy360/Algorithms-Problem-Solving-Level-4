#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct st_date
{
    short year;
    short month;
    short day;
};

string replace_words(string sentence, string replaced_word, string replacing_word)
{
    short pos = sentence.find(replaced_word);

    while (pos != std::string::npos)
    {
        sentence.replace(pos, replaced_word.length(), replacing_word);

        pos = sentence.find(replaced_word);
    }

    return sentence;
}

string read_date_string(string message)
{
    string date_string;
    cout << message;
    getline(cin >> ws, date_string);

    return date_string;
}

vector<string> split_string(string sentence, string delim = " ")
{
    vector <string> words;
    short pos = 0;
    string word;

    while ((pos = sentence.find(delim)) != std::string::npos)
    {
        word = sentence.substr(0, pos);

        if (word != "")
            words.push_back(word);

        sentence.erase(0, pos + delim.length());
    }

    if (sentence != "")
        words.push_back(sentence);

    return words;
}

st_date string_to_date(string date_string)
{
    vector <string> v_date = split_string(date_string, "/");

    st_date date;

    date.day = stoi(v_date.at(0));
    date.month = stoi(v_date.at(1));
    date.year = stoi(v_date.at(2));

    return date;
}

string format_date(st_date date, string format = "dd/mm/yyyy")
{
    string date_string = "";

    date_string = replace_words(format, "dd", to_string(date.day));
    date_string = replace_words(date_string, "mm", to_string(date.month));
    date_string = replace_words(date_string, "yyyy", to_string(date.year));

    return date_string;
}

int main()
{
    string date_string = read_date_string("Enter date dd/mm/yyyy: ");
    st_date date = string_to_date(date_string);

    cout << "\n" << format_date(date) << endl;
    cout << "\n" << format_date(date, "mm/dd/yyyy") << endl;
    cout << "\n" << format_date(date, "yyyy/mm/dd") << endl;
    cout << "\n" << format_date(date, "yyyy/dd/mm") << endl;
    cout << "\n" << format_date(date, "dd-mm-yyyy") << endl;
    cout << "\n" << format_date(date, "mm-dd-yyyy") << endl;
    cout << "\n" << format_date(date, "Day: dd, Month: mm, Year: yyyy") << endl;
}
