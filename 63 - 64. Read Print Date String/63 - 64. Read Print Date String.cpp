#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct st_date
{
    short year;
    short month;
    short day;
};

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

string join_string(vector <string>& words, string delim = " ")
{
    string sentence = "";

    for (string& word : words)
    {
        sentence += word + delim;
    }

    return (sentence.substr(0, sentence.length() - delim.length()));
}

string read_date_string(string message)
{
    string date_string;
    cout << message;
    cin >> date_string;

    return date_string;
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

string date_to_string(st_date date)
{
    return to_string(date.day)+ "/" + to_string(date.month) + "/" + to_string(date.year);
}

int main()
{
    string date_string = read_date_string("\nEnter date dd/mm/yyyy:");

    st_date date = string_to_date(date_string);

    cout << "\nDay  : " << date.day << endl;
    cout << "Month: " << date.month << endl;
    cout << "Year : " << date.year << endl;

    cout << "\nDate String: " << date_to_string(date) << endl;
}

