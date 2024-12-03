#include <iostream>
#include <string>
#include <iomanip> // For formatting output

class Account
{
private:
    std::string accountHolder;
    std::string pin;
    double balance;

public:
    // Constructor
    Account(const std::string &name, const std::string &pinCode, double initialBalance)
        : accountHolder(name), pin(pinCode), balance(initialBalance) {}

    // Function to authenticate user
    bool authenticate(const std::string &enteredPin) const
    {
        return enteredPin == pin;
    }

    // Function to check balance
    double getBalance() const
    {
        return balance;
    }

    // Function to deposit money
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            std::cout << "Successfully deposited ₹" << amount << ".\n";
        }
        else
        {
            std::cout << "Invalid deposit amount!\n";
        }
    }

    // Function to withdraw money
    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            std::cout << "Successfully withdrew ₹" << amount << ".\n";
        }
        else if (amount > balance)
        {
            std::cout << "Insufficient balance!\n";
        }
        else
        {
            std::cout << "Invalid withdrawal amount!\n";
        }
    }

    // Function to display account details (for debugging or admin use)
    void displayAccountDetails() const
    {
        std::cout << "Account Holder: " << accountHolder << "\n";
        std::cout << "Balance: ₹" << std::fixed << std::setprecision(2) << balance << "\n";
    }
};

// Main ATM logic
void atmMenu(Account &account)
{
    int choice;
    do
    {
        std::cout << "\n--- ATM Menu ---\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cout << "Your current balance is: ₹"
                      << std::fixed << std::setprecision(2)
                      << account.getBalance() << "\n";
            break;
        }
        case 2:
        {
            double depositAmount;
            std::cout << "Enter the amount to deposit: ₹";
            std::cin >> depositAmount;
            account.deposit(depositAmount);
            break;
        }
        case 3:
        {
            double withdrawalAmount;
            std::cout << "Enter the amount to withdraw: ₹";
            std::cin >> withdrawalAmount;
            account.withdraw(withdrawalAmount);
            break;
        }
        case 4:
        {
            std::cout << "Thank you for using the ATM. Goodbye!\n";
            break;
        }
        default:
        {
            std::cout << "Invalid choice! Please try again.\n";
        }
        }
    } while (choice != 4);
}

int main()
{
    // Create an example account
    Account myAccount("John Doe", "1234", 5000.00);

    std::cout << "Welcome to the ATM!\n";

    // User authentication
    std::string enteredPin;
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts)
    {
        std::cout << "Enter your PIN: ";
        std::cin >> enteredPin;

        if (myAccount.authenticate(enteredPin))
        {
            std::cout << "Authentication successful!\n";
            atmMenu(myAccount);
            return 0;
        }
        else
        {
            std::cout << "Incorrect PIN. Try again.\n";
            attempts++;
        }
    }

    std::cout << "Too many incorrect attempts. Your account is locked.\n";
    return 1;
}
