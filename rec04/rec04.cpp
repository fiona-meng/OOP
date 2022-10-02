/*
  rec04_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account{
    string account_name;
    int account_number;
};

// Task 2
// Define an Account class
class Accounts {
    friend ostream& operator << (ostream& os, const Accounts& account);
public:
    Accounts(const string& name, int number) : account_name(name),
    account_number(number) {}
    const string& get_name() const{ return account_name;}
    int get_number() const {return account_number;}
    
private:
    string account_name;
    int account_number;
};

// using getter
//ostream& operator << (ostream& os, const Accounts& account){
//    cout << account.get_name() <<
//    "  " << account.get_number() << endl;
//    return os;
//}

ostream& operator << (ostream& os, const Accounts& account);

// Task 3
// Define an Account and Transaction classes
class Transaction {
    friend ostream& operator << (ostream& os, const Transaction& transaction);
public:
    Transaction(const string& trans_type, int amount_money)
    : type(trans_type), amount(amount_money) {}
private:
    string type;
    int amount;
};

ostream& operator << (ostream& os, const Transaction& transaction);


class Account_3 {
    friend ostream& operator << (ostream& os, const Account_3& account_3);
public:
    Account_3(const string& name, int number_acoount)
    : account_name(name), account_number(number_acoount) {}
    void deposit(int amount) {
        balance = balance + amount;
        transaction_list.emplace_back("Deposit", amount);
    }
    void withdrawal(int amount) {
        if (balance > amount) {
            balance = balance - amount;
            transaction_list.emplace_back("Withdrawal", amount);
        } else {
            cout << "Account# " << account_number << " has only "
            << balance << ". " <<
            "Insufficient for withdrawal of " << amount << endl;
        }
    }
    int get_number() const { return account_number;}
private:
    string account_name;
    int account_number;
    vector<Transaction> transaction_list;
    int balance = 0;
};

ostream& operator << (ostream& os, const Account_3& account_3);
size_t find_account_number(int number, vector<Account_3>& account_list);

// Task 4
// Define an Account with a nested public Transaction class
class Account_4 {
    friend ostream& operator << (ostream& os, const Account_4& account_4);
    
public:
    Account_4(const string& name, int number_acoount)
    : account_name_4(name), account_number_4(number_acoount) {}
    void deposit(int amount) {
        balance_4 = balance_4 + amount;
        transaction_list_4.emplace_back("Deposit", amount);
    }
    void withdrawal(int amount) {
        if (balance_4 > amount) {
            balance_4 = balance_4 - amount;
            transaction_list_4.emplace_back("Withdrawal", amount);
        } else {
            cout << "Account# " << account_number_4 << " has only "
            << balance_4 << ". " <<
            "Insufficient for withdrawal of " << amount << endl;
        }
    }
    int get_number() const { return account_number_4;}
    
    class Transaction {
        friend ostream& operator <<
 (ostream& os, const Transaction& transaction);
    public:
        Transaction(const string& trans_type, int amount_money)
        : type_4(trans_type), amount_4(amount_money) {}
    private:
        string type_4;
        int amount_4;
    };
    
private:
    string account_name_4;
    int account_number_4;
    vector<Transaction> transaction_list_4;
    int balance_4 = 0;
};
ostream& operator << (ostream& os, const Account_4::Transaction& transaction);
ostream& operator << (ostream& os, const Account_4& account_4);


// Task 5
// Define an Account with a nested private Transaction class


 int main() {

    // Task 1: account as struct
    //      1a
     cout << "Task1a:\n";
     ifstream ifs("accounts.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     vector<Account> account_list;
     string name_1;
     int number_1;
     while(ifs >> name_1 >> number_1){
         Account new_account;
         new_account.account_name = name_1;
         new_account.account_number = number_1;
         account_list.push_back(new_account);
     }
     ifs.close();
     for (size_t index = 0; index < account_list.size(); index++){
         cout << account_list[index].account_name <<
         "  " << account_list[index].account_number << endl;
     }

    //      1b
     cout << "Task1b:\n";
     cout << "Filling vector of struct objects, using {} initialization:\n";
     account_list.clear();
     ifs.open("accounts.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     string name_2;
     int number_2;
     while(ifs >> name_2 >> number_2) {
         Account new_account_2{name_2, number_2};
         account_list.push_back(new_account_2);
     }
     ifs.close();
     for (size_t index = 0; index < account_list.size(); index++){
         cout <<  account_list[index].account_name <<
         "  " << account_list[index].account_number << endl;
     }

    //==================================
    // Task 2: account as class

    //      2a
     cout << "==============\n";
     cout << "\nTask2a:";
     cout << "\nFilling vector of class objects, using local class object:\n";
     vector<Accounts> accounts_list;
     ifs.open("accounts.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     string name_3;
     int number_3;
     while(ifs >> name_3 >> number_3){
         Accounts new_accounts(name_3, number_3);
         accounts_list.push_back(new_accounts);
     }
     ifs.close();
     for (size_t index = 0; index < accounts_list.size(); index++){
         cout << accounts_list[index].get_name() <<
         "  " << accounts_list[index].get_number() << endl;
     }

     cout << "\nTask2b:\n";
     cout << "output using output operator with getters\n";
     for (size_t index = 0; index < accounts_list.size(); index++){
         cout << accounts_list[index];
     }
    

     cout << "\nTask2c:\n";
     cout << "output using output operator as friend without getters\n";
     for (size_t index = 0; index < accounts_list.size(); index++){
         cout << accounts_list[index];
     }


     cout << "\nTask2d:\n";
     cout << "Filling vector of class objects," <<
     "using temporary class object:\n";
     ifs.open("accounts.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     string name_2d;
     int number_2d;
     vector<Accounts> accout_list_2d;
     while(ifs >> name_2d >> number_2d) {
         accout_list_2d.push_back(Accounts(name_2d, number_2d));
     }
     ifs.close();
     for (size_t index = 0; index < accout_list_2d.size(); index++){
         cout << accout_list_2d[index];
     }
     
     cout << "\nTask2e:\n";
     cout << "Filling vector of class objects, using emplace_back:\n";
     ifs.open("accounts.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     string name_2e;
     int number_2e;
     vector<Accounts> accout_list_2e;
     while(ifs >> name_2e >> number_2e) {
         accout_list_2e.emplace_back(name_2e, number_2e);
     }
     ifs.close();
     for (size_t index = 0; index < accout_list_2e.size(); index++){
         cout << accout_list_2e[index];
     }
    
     cout << "==============\n";
     cout << "\nTask 3:\nAccounts and Transaction:\n";
     ifs.open("transactions.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     string command;
     string accountName;
     int amount;
     int accountNumber;
     vector<Account_3> account_list_3;
     while(ifs >> command) {
         if (command == "Account"){
             ifs >> accountName >> accountNumber;
             account_list_3.emplace_back(accountName, accountNumber);
         } else if (command == "Deposit"){
             ifs >> accountNumber >> amount;
             size_t pos = find_account_number(accountNumber, account_list_3);
             account_list_3[pos].deposit(amount);
         } else if (command == "Withdraw"){
             ifs >> accountNumber >> amount;
             size_t pos = find_account_number(accountNumber, account_list_3);
             account_list_3[pos].withdrawal(amount);
         }
     }
     ifs.close();
     for (size_t index = 0; index < account_list_3.size(); index++){
         cout << account_list_3[index] << endl;
     }


     cout << "==============\n";
     cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
     ifs.open("transactions.txt");
     if(!ifs) {
         cerr << "Could not open the file.\n";
         exit(1);
     }
     string command_4;
     string accountName_4;
     int amount_4;
     int accountNumber_4;
     vector<Account_4> account_list_4;
     while(ifs >> command_4) {
         if (command_4 == "Account"){
             ifs >> accountName_4 >> accountNumber_4;
             account_list_4.emplace_back(accountName_4, accountNumber_4);
         } else if (command_4 == "Deposit"){
             ifs >> accountNumber_4 >> amount_4;
             for (size_t index = 0; index < account_list_4.size(); index++){
                 if (account_list_4[index].get_number() == accountNumber_4){
                     account_list_4[index].deposit(amount_4);
                 }
             }
         } else if (command_4 == "Withdraw"){
             ifs >> accountNumber_4 >> amount_4;
             for (size_t index = 0; index < account_list_4.size(); index++){
                 if (account_list_4[index].get_number() == accountNumber_4){
                     account_list_4[index].withdrawal(amount_4);
                 }
             }
         }
     }
     ifs.close();
     for (size_t index = 0; index < account_list_4.size(); index++){
         cout << account_list_4[index] << endl;
     }

     cout << "==============\n";
     cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
}

size_t find_account_number(int number, vector<Account_3>& account_list){
    for (size_t index = 0; index < account_list.size(); index++){
        if (account_list[index].get_number() == number) {
            return index;
        }
    }
    return account_list.size();
}


ostream& operator << (ostream& os, const Accounts& account){
    cout << account.account_name <<
    "  " << account.account_number << endl;
    return os;
}

ostream& operator << (ostream& os, const Transaction& transaction){
    cout << "     " << transaction.type <<
    "  " << transaction.amount << endl;
    return os;
}

ostream& operator << (ostream& os, const Account_3& account_3) {
    cout <<  account_3.account_name << "  " << account_3.account_number
    << ":" << endl;
    for (size_t index = 0; index < account_3.transaction_list.size();
         index++) {
        cout << account_3.transaction_list[index] << endl;
    }
    return os;
}

// Task 4
ostream& operator << (ostream& os, const Account_4::Transaction& transaction){
    cout << "     " << transaction.type_4 <<
    "  " << transaction.amount_4 << endl;
    return os;
}

ostream& operator << (ostream& os, const Account_4& account_4) {
    cout <<  account_4.account_name_4 << "  " << account_4.account_number_4
    << ":" << endl;
    for (size_t index = 0; index < account_4.transaction_list_4.size();
         index++) {
        cout << account_4.transaction_list_4[index] << endl;
    }
    return os;
}
