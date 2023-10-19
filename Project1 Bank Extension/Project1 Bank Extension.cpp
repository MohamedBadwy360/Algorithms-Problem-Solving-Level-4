#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct st_user
{
    string user_name;
    string password;
    int permission;
    bool mark_for_delete = false;
};

enum en_main_menu
{
    show_client_data = 1, add_new_client = 2, delete_client = 3,
    update_client = 4, find_client = 5, transactions = 6, manage_users = 7, logout = 8
};

enum en_transactions { deposit = 1, withdraw = 2, total_balances = 3, main_menu = 4 };

enum en_manage_users { list_users = 1, add_users = 2, delete_users = 3,
                       update_users = 4, find_users = 5, e_main_menu = 6};

enum en_permissions { p_all = -1, p_list_clients = 1, p_add_new_client = 2, p_delete_client = 4,
                      p_upadte_client = 8, p_find_client = 16, p_transactions = 32,
                      p_manage_users = 64};

struct st_client_data
{
    string account_number;
    string pin_code;
    string name;
    string phone;
    double account_balance = 0;
    bool mark_for_delete = false;
};


const string clients_file_name = "clients.txt";
const string users_file_name = "users.txt";
st_user current_user;


void show_main_menu();
st_client_data convert_line_data_to_record(string line, string delim);
void show_transactions_screen();
void show_manage_users_screen();
void login();

void access_denied_message()
{
    cout << "Access Denied.\n";
    cout << "You can not access this page.\n";
    cout << "Go back to main page.\n";
}

bool check_access_permission(en_permissions permissions)
{
    if (current_user.permission == en_permissions::p_all)
        return true;
    else if ((permissions & current_user.permission) == permissions)
        return true;
    else
        return false;
}

string read_string(string message)
{
    string sentence;
    cout << message << endl;
    getline(cin >> ws, sentence);

    return sentence;
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

st_client_data read_client_data()
{
    cout << "Please Enter Client Data: \n";

    st_client_data client_data;
    cout << "Enter Account Number: ";
    getline(cin >> ws, client_data.account_number); // will extract all white spaces

    while (is_client_exist(client_data.account_number, clients_file_name))
    {
        cout << "Client with account number (" << client_data.account_number << ") is found. Enter another account number: ";
        getline(cin >> ws, client_data.account_number);
    }

    cout << "Enter PinCode: ";
    getline(cin, client_data.pin_code);

    cout << "Enter Name: ";
    getline(cin, client_data.name);

    cout << "Enter Phone: ";
    getline(cin, client_data.phone);

    cout << "Enter Account Balance: ";
    cin >> client_data.account_balance;

    return client_data;
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

void print_client_data(st_client_data client_data)
{
    cout << "\nThe following is the extracted client data: \n\n";
    cout << "Account Number : " << client_data.account_number << endl;
    cout << "Pincode        : " << client_data.pin_code << endl;
    cout << "Name           : " << client_data.name << endl;
    cout << "Phone          : " << client_data.phone << endl;
    cout << "Account Balance: " << client_data.account_balance << endl;
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

void add_clients()
{
    st_client_data client;
    char add_more = 'Y';

    do
    {
        cout << "Adding New Client: \n\n";

        client = read_client_data();
        add_data_line_to_file(clients_file_name, convert_record_to_line(client));

        cout << "\nClient Add Successfully. Do you want to add more clients [Y/N] ?\n";
        cin >> add_more;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (add_more == 'Y' || add_more == 'y');
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

void print_header(vector<st_client_data> clients_data)
{
    cout << "\n\n\t\t\t\t\tClient List (" << clients_data.size() << ") Clients\n\n";
    cout << "_________________________________________________________________________________________________\n\n";
    cout << "|" << setw(15) << "Account Number" << "|" << setw(10) << "PinCode" << "|" <<
        setw(40) << "Client Name" << "|" << setw(15) << "Phone" << "|" << setw(10) << "Balance" << "|" << endl;
    cout << "_________________________________________________________________________________________________\n";
}

void print_record(st_client_data client_data)
{
    cout << "|" << setw(15) << client_data.account_number << "|" << setw(10)
        << client_data.pin_code << "|" << setw(40) << client_data.name
        << "|" << setw(15) << client_data.phone << "|" << setw(10)
        << client_data.account_balance << "|" << endl;
}

void show_clients_data()
{
    if (!check_access_permission(en_permissions::p_list_clients))
    {
        access_denied_message();
        return;
    }

    vector<st_client_data> clients_data = read_clients_data_from_file(clients_file_name);

    print_header(clients_data);

    for (st_client_data& client_data : clients_data)
    {
        print_record(client_data);
    }
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

bool mark_client_for_delete_by_account_number(string account_number, vector<st_client_data>& v_clients_data)
{
    for (st_client_data& client : v_clients_data)
    {
        if (client.account_number == account_number)
        {
            client.mark_for_delete = true;
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

bool delete_client_by_account_numebr(string account_number, vector<st_client_data>& v_clients_data)
{
    st_client_data client;
    char answer = 'n';

    if (find_client_by_account_number(account_number, v_clients_data, client))
    {
        print_client_data(client);

        cout << "Do you want to delete this client? ";
        cin >> answer;

        if (tolower(answer) != 'n')
        {
            mark_client_for_delete_by_account_number(account_number, v_clients_data);
            save_client_data_to_file(clients_file_name, v_clients_data);

            v_clients_data = read_clients_data_from_file(clients_file_name);
            cout << "Client is deleted successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "Client with account number (" << account_number << ") is not found.\n";
        return false;
    }
}

st_client_data change_client_record(string account_number)
{
    cout << "\nPlease Enter Updated Client Data: \n";

    st_client_data client_data;

    client_data.account_number = account_number;

    cout << "Enter PinCode: ";
    getline(cin >> ws, client_data.pin_code);

    cout << "Enter Name: ";
    getline(cin, client_data.name);

    cout << "Enter Phone: ";
    getline(cin, client_data.phone);

    cout << "Enter Account Balance: ";
    cin >> client_data.account_balance;

    return client_data;
}

bool Update_client_data(string account_number, vector<st_client_data>& v_clients_data)
{
    st_client_data client;
    char answer = 'n';

    if (find_client_by_account_number(account_number, v_clients_data, client))
    {
        print_client_data(client);

        cout << "Do you want to update this client data [Y/N]? ";
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            for (st_client_data& c : v_clients_data)
            {
                if (c.account_number == account_number)
                {
                    c = change_client_record(account_number);
                    break;
                }
            }

            save_client_data_to_file(clients_file_name, v_clients_data);

            cout << "\nClient Updated Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "Client with account number (" << account_number << ") is not found.\n";
        return false;
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

void go_back_to_transaction_menu()
{
    cout << "\n\nPress any key to go back to Transaction menu...";
    system("pause>0");
    show_transactions_screen();
}

void show_add_new_client_screen()
{
    if (!check_access_permission(en_permissions::p_add_new_client))
    {
        access_denied_message();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tAdd new client\n";
    cout << "-----------------------------------\n";

    add_clients();
}

void show_delete_client_screean()
{
    if (!check_access_permission(en_permissions::p_delete_client))
    {
        access_denied_message();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tDelete client data\n";
    cout << "-----------------------------------\n";

    string account_number = read_string("Enter Account Number: ");
    vector <st_client_data> v_clients_data = read_clients_data_from_file(clients_file_name);

    delete_client_by_account_numebr(account_number, v_clients_data);
}

void show_update_client_screen()
{
    if (!check_access_permission(en_permissions::p_upadte_client))
    {
        access_denied_message();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tUpdate client data\n";
    cout << "-----------------------------------\n";

    string account_number = read_string("Enter Account Number: ");
    vector <st_client_data> v_clients_data = read_clients_data_from_file(clients_file_name);

    Update_client_data(account_number, v_clients_data);
}

void show_find_client_screen()
{
    if (!check_access_permission(en_permissions::p_find_client))
    {
        access_denied_message();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tFind client\n";
    cout << "-----------------------------------\n";

    string account_number = read_string("Enter Account Number: ");
    vector <st_client_data> v_clients_data = read_clients_data_from_file(clients_file_name);
    st_client_data client;

    if (find_client_by_account_number(account_number, v_clients_data, client))
        print_client_data(client);
    else
        cout << "\nClient with (" << account_number << ") is not found.\n";
}

void show_logout_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tExit Program\n";
    cout << "-----------------------------------\n";
}

void deposit_money(string account_number, vector <st_client_data>& v_clients_data)
{
    double amount = 0;

    for (st_client_data& c : v_clients_data)
    {
        if (c.account_number == account_number)
        {
            print_client_data(c);
            cout << "\nPlease Enter Deposit Amount: ";
            cin >> amount;

            c.account_balance += amount;
            break;
        }
    }
    save_client_data_to_file(clients_file_name, v_clients_data);
    cout << "\nAmount is Deposited Successfully.\n";
}

void show_deposit_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "-----------------------------------\n";

    string account_number = read_string("Enter Account Number: ");
    st_client_data client;
    vector <st_client_data> v_clients_data = read_clients_data_from_file(clients_file_name);

    while (!find_client_by_account_number(account_number, v_clients_data, client))
    {
        cout << "Client with account number (" << account_number << ") is not found.\n";
        account_number = read_string("\nEnter Account Number: ");
    }

    deposit_money(account_number, v_clients_data);
}

void withdraw_money(string account_number, vector <st_client_data>& v_clients_data)
{
    double amount;

    for (st_client_data& c : v_clients_data)
    {
        if (c.account_number == account_number)
        {
            print_client_data(c);
            cout << "\nPlease Enter Withdraw Amount: ";
            cin >> amount;

            if (c.account_balance > amount)
            {
                c.account_balance -= amount;
                cout << "\nAmount is Withdrawed Successfully.\n";
                break;
            }
            else
            {
                while (amount > c.account_balance)
                {
                    cout << "There isn't enough money in the account. The amount is " << c.account_balance << endl;
                    cout << "\nPlease Enter Withdraw Amount: ";
                    cin >> amount;
                }

                c.account_balance -= amount;
                cout << "\nAmount is Withdrawed Successfully.\n";
                break;
            }
        }
    }

    save_client_data_to_file(clients_file_name, v_clients_data);
}

void show_withdraw_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "-----------------------------------\n";

    string account_number = read_string("Enter Account Number: ");
    st_client_data client;
    vector <st_client_data> v_clients_data = read_clients_data_from_file(clients_file_name);

    while (!find_client_by_account_number(account_number, v_clients_data, client))
    {
        cout << "Client with account number (" << account_number << ") is not found.\n";
        account_number = read_string("\nEnter Account Number: ");
    }

    withdraw_money(account_number, v_clients_data);
}

void show_total_balance()
{
    vector<st_client_data> clients_data = read_clients_data_from_file(clients_file_name);

    print_header(clients_data);

    double balance = 0;

    for (st_client_data& client_data : clients_data)
    {
        print_record(client_data);
        balance += client_data.account_balance;
    }

    cout << "\n\n\t\t\t\tTotal Balance = " << balance << endl << endl;
}

en_transactions read_transaction_option()
{
    short option;
    cout << "Enter Transaction: ";
    cin >> option;

    return en_transactions(option);
}

void perform_transactions_options(en_transactions transaction)
{
    switch (transaction)
    {
    case en_transactions::deposit:
        system("cls");
        show_deposit_screen();
        go_back_to_transaction_menu();
        break;
    case en_transactions::withdraw:
        system("cls");
        show_withdraw_screen();
        go_back_to_transaction_menu();
        break;
    case en_transactions::total_balances:
        system("cls");
        show_total_balance();
        go_back_to_transaction_menu();
        break;
    case en_transactions::main_menu:
        system("cls");
        show_main_menu();
        break;
    }
}

void show_transactions_screen()
{
    if (!check_access_permission(en_permissions::p_transactions))
    {
        access_denied_message();
        go_back_to_main_menu();
        return;
    }

    system("cls");

    cout << "======================================\n";
    cout << "\tTransactions Menu Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "======================================\n";

    perform_transactions_options(read_transaction_option());
}

st_user convert_line_to_user_record(string line, string delim = "#//#")
{
    vector <string> line_data = split_string(line, delim);
    st_user user_data;

    user_data.user_name = line_data.at(0);
    user_data.password = line_data.at(1);
    user_data.permission = stoi(line_data.at(2));

    return user_data;
}

string convert_user_record_to_line(st_user user, string delim = "#//#")
{
    return (user.user_name + delim + user.password + delim + to_string(user.permission));
}

vector <st_user> load_users_data_from_file(string file_name)
{
    vector<st_user> v_users_data;
    string line;
    st_user users_data;

    fstream file;
    file.open(file_name, ios::in);

    while (getline(file, line))
    {
        users_data = convert_line_to_user_record(line);
        v_users_data.push_back(users_data);
    }

    file.close();

    return v_users_data;
}

bool find_user_by_username_password(string user_name, string password, st_user& user)
{
    vector <st_user> v_users = load_users_data_from_file(users_file_name);

    for (st_user u : v_users)
    {
        if (u.user_name == user_name && u.password == password)
        {
            user = u;
            return true;
        }
    }

    return false;
}

bool load_user_data(string user_name, string password)
{
    if (find_user_by_username_password(user_name, password, current_user))
        return true;
    else
        return false;
}

en_manage_users read_manage_users_option()
{
    short option;
    cout << "Enter Manage Users Option: ";
    cin >> option;

    return en_manage_users(option);
}

void go_back_to_manage_users_menu()
{
    cout << "\n\nPress any key to go back to Manage Users menu...";
    system("pause>0");
    show_manage_users_screen();
}

void print_users_header(vector<st_user> v_users_data)
{
    cout << "\n\n\t\t\t\t\tUsers List (" << v_users_data.size() << ") User\n\n";
    cout << "________________________________________________________________________________\n\n";
    cout << "|" << setw(15) << "User Name" << "|" << setw(15) << "Password" << "|" <<
        setw(15) << "Permission" << "|" << endl;
    cout << "________________________________________________________________________________\n";
}

void print_user_record(st_user user)
{
    cout << "|" << setw(15) << user.user_name << "|" << setw(15)
        << user.password << "|" << setw(15) << user.permission
        << "|" << endl;
}

void show_users_data()
{
    vector<st_user> v_users_data = load_users_data_from_file(users_file_name);

    print_users_header(v_users_data);

    for (st_user& user : v_users_data)
    {
        print_user_record(user);
    }
}

bool is_user_exist(string user_name, string users_file_name)
{
    string line;
    st_user user;

    fstream file;
    file.open(users_file_name, ios::in);

    while (getline(file, line))
    {
        user = convert_line_to_user_record(line, "#//#");
        if (user.user_name == user_name)
        {
            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

int read_permission_to_set()
{
    int permissions = 0;
    char answer = 'n';

    cout << "Do you want to give user full access [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        return -1;

    cout << "\nDo you want to give access to?\n";
    cout << "\nShow client list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_list_clients;

    cout << "\nAdd client list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_add_new_client;

    cout << "\nDelete client list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_delete_client;

    cout << "\nUpdate client list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_upadte_client;

    cout << "\nFind client list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_delete_client;

    cout << "\nTransaction list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_transactions;

    cout << "\nManage users list [Y/N]? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions += en_permissions::p_manage_users;

    return permissions;
}

st_user read_user_data()
{
    cout << "Please Enter User Data: \n";

    st_user user;
    cout << "Enter User Name: ";
    getline(cin >> ws, user.user_name); // will extract all white spaces

    while (is_user_exist(user.user_name, users_file_name))
    {
        cout << "User with user name (" << user.user_name << ") is found. Enter another user name: ";
        getline(cin >> ws, user.user_name);
    }

    cout << "Enter Password: ";
    getline(cin, user.password);

    user.permission = read_permission_to_set();

    return user;
}

void add_new_user()
{
    st_user user;
    char add_more = 'Y';

    do
    {
        cout << "Adding New User: \n\n";

        user = read_user_data();
        add_data_line_to_file(users_file_name, convert_user_record_to_line(user));

        cout << "\nUser Add Successfully. Do you want to add more users [Y/N] ?\n";
        cin >> add_more;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (add_more == 'Y' || add_more == 'y');
}

void add_new_user_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New User Screen\n";
    cout << "-----------------------------------\n";

    add_new_user();
}

bool mark_user_for_delete_by_user_name(string user_name, vector<st_user>& v_users)
{
    for (st_user& user : v_users)
    {
        if (user.user_name == user_name)
        {
            user.mark_for_delete = true;
            return true;
        }

    }
    return false;
}

void save_user_data_to_file(string file_name, vector<st_user> v_users)
{
    fstream file;
    string line_data;

    file.open(file_name, ios::out);

    if (file.is_open())
    {
        for (st_user user : v_users)
        {
            if (user.mark_for_delete == false)
            {
                line_data = convert_user_record_to_line(user);
                file << line_data << endl;
            }
        }

        file.close();
    }
}

void print_user_data(st_user user)
{
    cout << "\nThe following is the extracted user data: \n\n";
    cout << "User name  : " << user.user_name << endl;
    cout << "password   : " << user.password << endl;
    cout << "Permissions: " << user.permission << endl;
}

bool find_user_by_username(string user_name, vector <st_user> v_users, st_user& user)
{
    for (st_user u : v_users)
    {
        if (u.user_name == user_name)
        {
            user = u;
            return true;
        }
    }

    return false;
}

bool delete_user_by_user_name(string user_name, vector<st_user>& v_users)
{
    if (user_name == "admin")
    { 
        cout << "\n\nYou cannot Delete This User.";
        return false; 
    }

    st_user user;
    char answer = 'n';

    if (find_user_by_username(user_name, v_users, user))
    {
        print_user_data(user);

        cout << "Do you want to delete this user [Y/N]? ";
        cin >> answer;

        if (tolower(answer) != 'n')
        {
            mark_user_for_delete_by_user_name(user_name, v_users);
            save_user_data_to_file(users_file_name, v_users);

            v_users = load_users_data_from_file(users_file_name);
            cout << "User is deleted successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nUser with user name (" << user_name << ") is not found.\n";
        return false;
    }
}

st_user change_user_record(string user_name)
{
    cout << "\nPlease Enter Updated Client Data: \n";

    st_user user;

    user.user_name = user_name;

    cout << "Enter Password: ";
    getline(cin >> ws, user.password);

    user.permission = read_permission_to_set();

    return user;
}

bool Update_user_data(string user_name, vector<st_user>& v_users)
{
    st_user user;
    char answer = 'n';

    if (find_user_by_username(user_name, v_users, user))
    {
        print_user_data(user);

        cout << "Do you want to update this user data [Y/N]? ";
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            for (st_user& u : v_users)
            {
                if (u.user_name == user_name)
                {
                    u = change_user_record(user_name);
                    break;
                }
            }

            save_user_data_to_file(users_file_name, v_users);

            cout << "\nUser Updated Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nUser with user name (" << user_name << ") is not found.\n";
        return false;
    }
}

void delete_user_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen\n";
    cout << "-----------------------------------\n";

    string user_name = read_string("Enter User Name: ");
    vector<st_user> v_users = load_users_data_from_file(users_file_name);

    delete_user_by_user_name(user_name, v_users);
}

void update_user_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Screen\n";
    cout << "-----------------------------------\n";

    string user_name = read_string("Enter User Name: ");
    vector <st_user> v_users = load_users_data_from_file(users_file_name);

    Update_user_data(user_name, v_users);
}

void find_user_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen\n";
    cout << "-----------------------------------\n";

    string user_name = read_string("Enter User Name: ");
    vector <st_user> v_users = load_users_data_from_file(users_file_name);
    st_user user;

    if (find_user_by_username(user_name, v_users, user))
        print_user_data(user);
    else
        cout << "\nUser with user name(" << user_name << ") is not found.\n";
}

void perform_manage_users_options(en_manage_users manage_option)
{
    switch (manage_option)
    {
        case en_manage_users::list_users:
            system("cls");
            show_users_data();
            go_back_to_manage_users_menu();
            break;
        case en_manage_users::add_users:
            system("cls");
            add_new_user_screen();
            go_back_to_manage_users_menu();
            break;
        case en_manage_users::delete_users:
            system("cls");
            delete_user_screen();
            go_back_to_manage_users_menu();
            break;
        case en_manage_users::update_users:
            system("cls");
            update_user_screen();
            go_back_to_manage_users_menu();
            break;
        case en_manage_users::find_users:
            system("cls");
            find_user_screen();
            go_back_to_manage_users_menu();
            break;
        case en_manage_users::e_main_menu:
            system("cls");
            show_main_menu();
            break;
    }
}

void show_manage_users_screen()
{
    if (!check_access_permission(en_permissions::p_manage_users))
    {
        access_denied_message();
        go_back_to_main_menu();
        return;
    }

    system("cls");

    cout << "======================================\n";
    cout << "\Manage Users Menu Screen\n";
    cout << "======================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "======================================\n";

    perform_manage_users_options(read_manage_users_option());
}

void perform_menu_option(en_main_menu option)
{
    switch (option)
    {
    case en_main_menu::show_client_data:
        system("cls");
        show_clients_data();
        go_back_to_main_menu();
        break;
    case en_main_menu::add_new_client:
        system("cls");
        show_add_new_client_screen();
        go_back_to_main_menu();
        break;
    case en_main_menu::delete_client:
        system("cls");
        show_delete_client_screean();
        go_back_to_main_menu();
        break;
    case en_main_menu::update_client:
        system("cls");
        show_update_client_screen();
        go_back_to_main_menu();
        break;
    case en_main_menu::find_client:
        system("cls");
        show_find_client_screen();
        go_back_to_main_menu();
        break;
    case en_main_menu::transactions:
        system("cls");
        show_transactions_screen();
        break;
    case en_main_menu::manage_users:
        system("cls");
        show_manage_users_screen();
        break;
    case en_main_menu::logout:
        system("cls");
        //show_logout_screen();
        login();
        break;
    }
}

void show_main_menu()
{
    system("cls");

    cout << "======================================\n";
    cout << "\tMain Menu Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Show Client Data.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "======================================\n";

    perform_menu_option((en_main_menu)read_menu_option());
}

void login()
{
    bool login_failed  = false;
    string user_name, password;

    do 
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen\n";
        cout << "-----------------------------------\n";

        if (login_failed)
            cout << "\nInvaid Username/Password.\n\n";

        cout << "Enter user name: ";
        cin >> user_name;
        cout << "Enter user password: ";
        cin >> password;

        login_failed = !load_user_data(user_name, password);
    } 
    while (login_failed);

    show_main_menu();
}

int main()
{
    cout << left;

    login();
    system("pause>0");

    return 0;
}