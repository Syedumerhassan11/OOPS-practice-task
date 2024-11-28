#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Base class Account
class Account {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;
    vector<string> transactionHistory;

public:
    Account(int accountNumber, string accountHolderName, double initialBalance)
        : accountNumber(accountNumber), accountHolderName(accountHolderName), balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactionHistory.push_back("Withdrew: $" + to_string(amount));
        } else {
            cout << "Insufficient balance. Withdrawal failed." << endl;
            transactionHistory.push_back("Failed Withdrawal Attempt: $" + to_string(amount));
        }
    }

    void displayAccountDetails() const {
        cout << fixed << setprecision(2);
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }

    void displayTransactionHistory() const {
        cout << "Transaction History for Account " << accountNumber << ":" << endl;
        for (const string& transaction : transactionHistory) {
            cout << "- " << transaction << endl;
        }
    }
};

// Derived class SavingsAccount
class SavingsAccount : public Account {
private:
    double interestRate; // Annual interest rate in percentage

public:
    SavingsAccount(int accountNumber, string accountHolderName, double initialBalance, double interestRate)
        : Account(accountNumber, accountHolderName, initialBalance), interestRate(interestRate) {}

    void calculateInterest() {
        double interest = (balance * interestRate) / 100.0;
        balance += interest;
        transactionHistory.push_back("Interest Earned: $" + to_string(interest));
    }

    void displayAccountDetails() const override {
        Account::displayAccountDetails();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Derived class CurrentAccount
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accountNumber, string accountHolderName, double initialBalance, double overdraftLimit)
        : Account(accountNumber, accountHolderName, initialBalance), overdraftLimit(overdraftLimit) {}

    void withdraw(double amount) override {
        if (balance - amount >= -overdraftLimit) {
            balance -= amount;
            transactionHistory.push_back("Withdrew: $" + to_string(amount));
        } else {
            cout << "Overdraft limit exceeded. Withdrawal failed." << endl;
            transactionHistory.push_back("Failed Withdrawal Attempt: $" + to_string(amount));
        }
    }

    void displayAccountDetails() const override {
        Account::displayAccountDetails();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
    }
};

// Main program
int main() {
    // Create a savings account
    SavingsAccount savings(1001, "Alice Johnson", 5000.00, 3.5);

    // Create a current account
    CurrentAccount current(2001, "Bob Smith", 2000.00, 1000.00);

    // Perform operations on the savings account
    savings.deposit(1000.00);
    savings.withdraw(2000.00);
    savings.calculateInterest();

    // Perform operations on the current account
    current.deposit(500.00);
    current.withdraw(2500.00); // Within overdraft limit
    current.withdraw(1000.00); // Exceeds overdraft limit

    // Display account details and transaction histories
    cout << "\nSavings Account Details:" << endl;
    savings.displayAccountDetails();
    savings.displayTransactionHistory();

    cout << "\nCurrent Account Details:" << endl;
    current.displayAccountDetails();
    current.displayTransactionHistory();

    return 0;
}

