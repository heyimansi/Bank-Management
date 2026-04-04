#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// -------------------- Color Functions --------------------
void Red() { cout << "\033[31m"; }
void Green() { cout << "\033[32m"; }
void Yellow() { cout << "\033[33m"; }
void Blue() { cout << "\033[34m"; }
void Magenta() { cout << "\033[35m"; }
void Cyan() { cout << "\033[36m"; }
void Reset() { cout << "\033[0m"; }

// -------------------- BankAccount Class --------------------
class Bankaccount {
private:
    string bank_name = "SBI";
    int Bankcode = 101;
    string account_holdername;
    string account_number;
    string account_password;
    string email;
    string Adharnumber;
    string phone_number;
    double balance;
    vector<string> transactionHistory;

public:
    void savefile();
    void loadfile();
    void Mainmenu();
    void create_account();
    void login_bankaccount();
    void deposit_money();
    void withdrawmoney();
    void check_balance();
    void account_details();
    void alltransactions_history();
};

// -------------------- File Handling --------------------
void Bankaccount::savefile() {
    ofstream file(account_number + ".txt");
    if (file.is_open()) {
        file << account_holdername << endl;
        file << account_number << endl;
        file << account_password << endl;
        file << email << endl;
        file << phone_number << endl;
        file << Adharnumber << endl;
        file << balance << endl;
        for (auto transaction : transactionHistory) {
            file << transaction << endl;
        }
        file.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}

void Bankaccount::loadfile() {
    ifstream file(account_number + ".txt");
    if (file.is_open()) {
        getline(file, account_holdername);
        getline(file, account_number);
        getline(file, account_password);
        getline(file, email);
        getline(file, phone_number);
        getline(file, Adharnumber);
        file >> balance;
        file.ignore();
        string transaction;
        while (getline(file, transaction)) {
            transactionHistory.push_back(transaction);
        }
        file.close();
    } else {
        cout << "Error file not opening" << endl;
    }
}

// -------------------- Main Menu --------------------
void Bankaccount::Mainmenu() {
    int choice;
    do {
        cout << "--------------------------------------------" << endl;
        cout << "Enter 1 for Deposit Money" << endl;
        cout << "Enter 2 for Withdraw Money" << endl;
        cout << "Enter 3 for Check Balance" << endl;
        cout << "Enter 4 for Account Details" << endl;
        cout << "Enter 5 for All Transactions History" << endl;
        cout << "Enter 6 for Logout" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("clear"); // Windows: use "cls"
        switch (choice) {
            case 1: deposit_money(); break;
            case 2: withdrawmoney(); break;
            case 3: check_balance(); break;
            case 4: account_details(); break;
            case 5: alltransactions_history(); break;
            case 6: cout << "Logging out..." << endl; break;
            default: cout << "Invalid choice. Please try again" << endl;
        }
    } while (choice != 6);
}

// -------------------- Account Creation --------------------
void Bankaccount::create_account() {
    Green();
    cout << "  Create Account    " << endl;
    cout << "-------------------" << endl;
    cout << "Enter Your Full Name: ";
    getline(cin, account_holdername);
    cout << "Enter Your Email ID: ";
    getline(cin, email);
    cout << "Enter Your Phone Number: ";
    getline(cin, phone_number);
    cout << "Enter Your AADHAR Number: ";
    getline(cin, Adharnumber);
    cout << "Enter Your Password: ";
    getline(cin, account_password);
    cout << "-------------------" << endl;
    Reset();

    balance = 500.0; // minimum balance

    ifstream file("State-Bank-Of-India.txt");
    if (file.is_open()) {
        file >> Bankcode;
        file.close();
    }
    ofstream output("State-Bank-Of-India.txt");
    if (output.is_open()) {
        output << Bankcode + 1;
        output.close();
    }

    account_number = bank_name + to_string(Bankcode);
    transactionHistory.push_back("Deposit: " + to_string(balance));

    Yellow();
    cout << "Account created successfully!" << endl;
    cout << "Account Number: " << account_number << endl;
    cout << "Account Password: " << account_password << endl;
    cout << "Minimum Balance: 500" << endl;
    cout << "-------------------" << endl;
    Reset();

    savefile();
}

// -------------------- Login --------------------
void Bankaccount::login_bankaccount() {
    string enteredAccountNumber;
    string enteredPassword;

    Blue();
    cout << "  Login Account  " << endl;
    cout << "-------------------" << endl;
    cout << "Enter Account Number: ";
    cin.ignore();
    getline(cin, enteredAccountNumber);

    account_number = enteredAccountNumber;
    ifstream file(account_number + ".txt");
    if (file.is_open()) {
        loadfile();
        cout << "Enter Password: ";
        getline(cin, enteredPassword);
        if (account_password == enteredPassword) {
            cout << "Login Successful" << endl;
            Mainmenu();
        } else {
            cout << "Invalid Password" << endl;
        }
        file.close();
    } else {
        cout << "Account Not Found" << endl;
    }
}

// -------------------- Deposit --------------------
void Bankaccount::deposit_money() {
    double amount;
    cout << "Enter Amount to Deposit: ";
    cin >> amount;
    cin.ignore();
    if (amount > 0) {
        balance += amount;
        transactionHistory.push_back("Deposit: " + to_string(amount));
        savefile();
        cout << "Deposit Successful" << endl;
        cout << "New Balance: " << balance << endl;
    } else {
        cout << "Invalid Amount!" << endl;
    }
}

// -------------------- Withdraw --------------------
void Bankaccount::withdrawmoney() {
    double amount;
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;
    cin.ignore();
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactionHistory.push_back("Withdraw: " + to_string(amount));
        savefile();
        cout << "Withdraw Successful" << endl;
        cout << "New Balance: " << balance << endl;
    } else {
        cout << "Invalid or Insufficient Balance!" << endl;
    }
}

// -------------------- Check Balance --------------------
void Bankaccount::check_balance() {
    cout << "Current Balance: " << balance << endl;
    cout << "-----------------------" << endl;
}

// -------------------- Account Details --------------------
void Bankaccount::account_details() {
    Magenta();
    cout << "|--------------------------------------|" << endl;
    cout << "|          STATE BANK OF INDIA         |" << endl;
    cout << "|--------------------------------------|" << endl;
    Blue();
    cout << "Account Holder Name  : " << account_holdername << endl;
    cout << "Account Number       : " << account_number << endl;
    cout << "Aadhar Number        : " << Adharnumber << endl;
    cout << "Email ID             : " << email << endl;
    cout << "Phone Number         : " << phone_number << endl;
    cout << "Current Balance      : " << balance << endl;
    cout << "---------------------------------------" << endl;
    Reset();
}

// -------------------- Transaction History --------------------
void Bankaccount::alltransactions_history() {
    cout << "Transaction History: " << endl;
    Yellow();
    cout << "-----------------------------------" << endl;
    cout << "Account Holder Name  : " << account_holdername << endl;
    cout << "Account Number       : " << account_number << endl;
    for (const auto &transaction : transactionHistory) {
        cout << transaction << endl;
    }
    cout << "-----------------------------------" << endl;
    Reset();
}

// -------------------- Main Function --------------------
int main() {
    Bankaccount Account;
    int choice;
    do {
        cout << "Welcome To State Bank Of INDIA" << endl;
        cout << "-------------------------------" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore();
        system("clear"); // Windows: use "cls"
        switch (choice) {
            case 1: Account.create_account(); break;
            case 2: Account.login_bankaccount(); break;
            case 3: cout << "Exiting..." << endl; break;
            default: cout << "Invalid Choice. Please try again." << endl;
        }
    } while (choice != 3);
    return 0;
}










































