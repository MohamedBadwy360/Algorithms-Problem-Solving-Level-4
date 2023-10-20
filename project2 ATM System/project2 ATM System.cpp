#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const string file_name = "clients.txt";

enum en_main_menu
{
    en_quick_withdraw = 1, en_withdraw = 2, en_deposit = 3,
    en_check_balance = 4, en_logout = 5
};

struct st_client_data
{
    string account_number;
    string pin_code;
    string name;
    string phone;
    double account_balance = 0;
    bool mark_for_delete = false;
};


st_client_data current_client;
void show_main_menu();
void login();
st_client_data convert_line_data_to_record(string line, string delim);


string read_string(string message)
{
    string sentence;
    cout << message << endl;
    getline(cin >> ws, sentence);

    return sentence;
}

int read_amount(string message)
{
    int amount = -1;
    while (amount < 0)
    {
        cout << message;
        cin >> amount;
    }

    return amount;
}

short read_withdraw_option()
{
    short option = 0;
    cout << "\nChoose option to withdraw [1 - 8]: ";
    cin >> option;

    return option;
}

bool is_client_exist(string account_number, string file_name)
{
    string line;
    st_client_data client_data;

    fstream file;
    file.open(file_name, ios::in);

    while (getline(file, line))
    {
        client_data = convert_line_data_to_record(line, "#//#");
        if (client_data.account_number == account_number)
        {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

string convert_record_to_line(st_client_data client_data, string delim = "#//#")
{
    return (client_data.account_number + delim + client_data.pin_code + delim + client_data.name
        + delim + client_data.phone + delim + to_string(client_data.account_balance));
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

st_client_data convert_line_data_to_record(string line, string delim = "#//#")
{
    vector <string> line_data = split_string(line, delim);
    st_client_data client_data;

    client_data.account_number = line_data.at(0);
    client_data.pin_code = line_data.at(1);
    client_data.name = line_data.at(2);
    client_data.phone = line_data.at(3);
    client_data.account_balance = stod(line_data.at(4));

    return client_data;
}

void add_data_line_to_file(string file_name, string line_data)
{
    fstream file;
    file.open(file_name, ios::out | ios::app);

    while (file.is_open())
    {
        file << line_data << endl;

        file.close();
    }
}

vector<st_client_data> read_clients_data_from_file(string file_name)
{
    vector<st_client_data> v_clients_data;
    string line;
    st_client_data client_data;

    fstream file;
    file.open(file_name, ios::in);

    while (getline(file, line))
    {
        client_data = convert_line_data_to_record(line);
        v_clients_data.push_back(client_data);
    }

    file.close();

    return v_clients_data;
}

bool find_client_by_account_number(string account_number, vector<st_client_data> v_clients_data, st_client_data& client)
{
    for (st_client_data& c : v_clients_data)
    {
        if (c.account_number == account_number)
        {
            client = c;
            return true;
        }
    }

    return false;
}

void save_client_data_to_file(string file_name, vector<st_client_data> v_clients_data)
{
    fstream file;
    string line_data;

    file.open(file_name, ios::out);

    if (file.is_open())
    {
        for (st_client_data client : v_clients_data)
        {
            if (client.mark_for_delete == false)
            {
                line_data = convert_record_to_line(client);
                file << line_data << endl;
            }
        }

        file.close();
    }
}

short read_menu_option()
{
    short option = 0;
    cout << "Choose what you want to do: ";
    cin >> option;

    return option;
}

void go_back_to_main_menu()
{
    cout << "\n\nPress any key to go back to main menu...";
    system("pause>0");
    show_main_menu();
}

void show_exit_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tExit Program\n";
    cout << "-----------------------------------\n";
}

bool deposit(string account_number, int amount, vector <st_client_data>& v_clients_data)
{
    char answer = 'n';

    cout << "Are you sure you want to make this operation[Y/N]? ";
    cin >> answer;
    
    if (tolower(answer) == 'y')
    {
        for (st_client_data& c : v_clients_data)
        {
            if (c.account_number == account_number)
            {

                if (tolower(answer) == 'y')
                {
                    c.account_balance += amount;
                    current_client.account_balance = c.account_balance;
                    cout << "\nOperation is done Successfully.\n";
                    cout << "\nYour balance is " << c.account_balance;
                    save_client_data_to_file(file_name, v_clients_data);
                    return true;
                }
            }
        }
    }
    return false;
}

void show_deposit_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "-----------------------------------\n";

    vector <st_client_data> v_clients_data = read_clients_data_from_file(file_name);

    int amount = read_amount("Enter amount to deposit: ");

    deposit(current_client.account_number, amount, v_clients_data);
}

int get_quick_withdraw_amount(short quick_option)
{
    switch (quick_option)
    {
        case 1:
            return 20;
        case 2:
            return 50;
        case 3:
            return 100;
        case 4:
            return 200;
        case 5: 
            return 400;
        case 6:
            return 600;
        case 7:
            return 800;
        case 8:
            return 1000;
        default:
            return 0;
    }
}

void show_quick_withdraw_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tQuick Withdraw Screen\n";
    cout << "-----------------------------------\n";
    cout << "\t[1] 20 \t\t[2] 50" << endl;
    cout << "\t[3] 100 \t[4] 200" << endl;
    cout << "\t[5] 400 \t[6] 600" << endl;
    cout << "\t[7] 800 \t[8] 1000" << endl;
    cout << "-----------------------------------\n";

    vector <st_client_data> v_clients_data = read_clients_data_from_file(file_name);
    cout << "\nYour balance is " << current_client.account_balance;
    int amount = get_quick_withdraw_amount(read_withdraw_option());

    if (amount < current_client.account_balance)
        deposit(current_client.account_number, -amount, v_clients_data);
    else
        cout << "The amount exceeds the current balance.\n";
}

void show_withdraw_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "-----------------------------------\n";

    vector <st_client_data> v_clients_data = read_clients_data_from_file(file_name);
    cout << "\nYour balance is " << current_client.account_balance << endl;
    int amount = read_amount("\nEnter amount to withdraw: ");

    if (amount < current_client.account_balance)
        deposit(current_client.account_number, -amount, v_clients_data);
    else
        cout << "The amount exceeds the current balance.\n";
}

void show_check_balance()
{
    cout << "\n-----------------------------------\n";
    cout << "\tBalance Screen\n";
    cout << "-----------------------------------\n";

    cout << "\n\n\Balance = " << current_client.account_balance << endl << endl;
}

void perform_menu_option(en_main_menu option)
{
    switch (option)
    {
        case en_main_menu::en_quick_withdraw:
            system("cls");
            show_quick_withdraw_screen();
            go_back_to_main_menu();
            break;
        case en_main_menu::en_withdraw:
            system("cls");
            show_withdraw_screen();
            go_back_to_main_menu();
            break;
        case en_main_menu::en_deposit:
            system("cls");
            show_deposit_screen();
            go_back_to_main_menu();
            break;
        case en_main_menu::en_check_balance:
            system("cls");
            show_check_balance();
            go_back_to_main_menu();
            break;
        case en_main_menu::en_logout:
            system("cls");
            login();
            break;
    }
}

void show_main_menu()
{
    system("cls");

    cout << "======================================\n";
    cout << "\tATM Main Menu Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "======================================\n";

    perform_menu_option((en_main_menu)read_menu_option());
}

bool find_user_by_account_number_pincode(string account_number, string pincode, st_client_data& client)
{
    vector <st_client_data> v_clients = read_clients_data_from_file(file_name);

    for (st_client_data c : v_clients)
    {
        if (c.account_number == account_number && c.pin_code == pincode)
        {
            client = c;
            return true;
        }
    }

    return false;
}

bool load_client_data(string account_number, string pincode)
{
    if (find_user_by_account_number_pincode(account_number, pincode, current_client))
        return true;
    else
        return false;
}

void login()
{
    bool login_failed = false;
    string account_number, pincode;

    do
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen\n";
        cout << "-----------------------------------\n";

        if (login_failed)
            cout << "\nInvaid Username/Password.\n\n";

        cout << "Enter account number: ";
        getline(cin >> ws, account_number);
        cout << "Enter pincode: ";
        cin >> pincode;

        login_failed = !load_client_data(account_number, pincode);
    } while (login_failed);

    show_main_menu();
}

int main()
{
    cout << left;

    login();
    system("pause>0");

    return 0;
}