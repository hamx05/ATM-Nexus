#include "ATM.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string.h>
using namespace std;

// Function prototypes
void displayMainMenu();
void displayATMMenu();
void handleRegistration();
void handleLogin();
void handleDeposit(User& currentUser);
void handleWithdrawal(User& currentUser);
void handleTransfer(User& currentUser);
void clearScreen();
void waitForKeypress();

int main() {
    int choice;
    
    while (true) {
        displayMainMenu();
        cin >> choice;
        
        if (cin.fail()) { // handle char or any other invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid input. Please enter a number." << endl;
            waitForKeypress();
            continue;
        }
        
        switch (choice) {
            case 1:
                handleLogin();
                break;
            case 2:
                handleRegistration();
                break;
            case 3:
                cout<<"Thank you for using our ATM. Goodbye!" << endl;
                return 0;
            default:
                cout<<"Invalid choice. Please try again." << endl;
                waitForKeypress();
        }
    }
    
    return 0;
}

void displayMainMenu() {
    clearScreen();
    cout<<"===== WELCOME TO THE ATM SYSTEM =====" << endl;
    cout<<"1. Login" << endl;
    cout<<"2. Register" << endl;
    cout<<"3. Exit" << endl;
    cout<<"Enter your choice: ";
}

void displayATMMenu() {
    clearScreen();
    cout<<"===== ATM MENU =====" << endl;
    cout<<"1. Check Balance" << endl;
    cout<<"2. Deposit" << endl;
    cout<<"3. Withdraw" << endl;
    cout<<"4. Transfer" << endl;
    cout<<"5. Logout" << endl;
    cout<<"Enter your choice: ";
}

void handleRegistration() {
    clearScreen();
    cout<<"===== REGISTRATION =====" << endl;
    
    string username, password, confirmPassword;
    
    cout<<"Enter username: ";
    cin >> username;
    
    cout<<"Enter password: ";
    cin >> password;
    
    cout<<"Confirm password: ";
    cin >> confirmPassword;
    
    if (password != confirmPassword) {
        cout<<"Passwords do not match. Registration failed." << endl;
        waitForKeypress();
        return;
    }
    
    if (registerUser(username, password)) {
        cout<<"Registration successful! You can now login." << endl;
    } else {
        cout<<"Registration failed. Please try again." << endl;
    }
    
    waitForKeypress();
}

void handleLogin() {
    clearScreen();
    cout<<"===== LOGIN =====" << endl;
    
    string username, password;
    
    cout<<"Enter username: ";
    cin >> username;
    
    cout<<"Enter password: ";
    cin >> password;
    
    User currentUser;
    if (loginUser(username, password, currentUser)) {
        cout<<"Login successful! Welcome, " << currentUser.username << "!" << endl;
        waitForKeypress();
        
        int choice;
        bool loggedIn = true;
        
        while (loggedIn) {
            displayATMMenu();
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Invalid input. Please enter a number." << endl;
                waitForKeypress();
                continue;
            }
            
            switch (choice) {
                case 1: // Check Balance
                    clearScreen();
                    cout<<"Your current balance: Rs " << checkBalance(currentUser) << endl;
                    waitForKeypress();
                    break;
                case 2: // Deposit
                    handleDeposit(currentUser);
                    break;
                case 3: // Withdraw
                    handleWithdrawal(currentUser);
                    break;
                case 4: // Transfer
                    handleTransfer(currentUser);
                    break;
                case 5: // Logout
                    loggedIn = false;
                    cout<<"Logged out successfully." << endl;
                    waitForKeypress();
                    break;
                default:
                    cout<<"Invalid choice. Please try again." << endl;
                    waitForKeypress();
            }
        }
    } else {
        cout<<"Login failed. Invalid username or password." << endl;
        waitForKeypress();
    }
}

void handleDeposit(User& currentUser) {
    clearScreen();
    cout<<"===== DEPOSIT =====" << endl;
    
    double amount;
    cout<<"Enter amount to deposit: Rs ";
    cin >> amount;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid input. Please enter a valid amount." << endl;
        waitForKeypress();
        return;
    }
    
    if (deposit(currentUser, amount)) {
        cout<<"Deposit successful. New balance: Rs " << currentUser.balance << endl;
    }
    
    waitForKeypress();
}

void handleWithdrawal(User& currentUser) {
    clearScreen();
    cout<<"===== WITHDRAWAL =====" << endl;
    
    double amount;
    cout<<"Enter amount to withdraw: Rs ";
    cin >> amount;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid input. Please enter a valid amount." << endl;
        waitForKeypress();
        return;
    }
    
    if (withdraw(currentUser, amount)) {
        cout<<"Withdrawal successful. New balance: Rs " << currentUser.balance << endl;
    }
    
    waitForKeypress();
}

void handleTransfer(User& currentUser) {
    clearScreen();
    cout<<"===== TRANSFER =====" << endl;
    
    string receiverUsername;
    double amount;
    
    cout<<"Enter receiver's username: ";
    cin >> receiverUsername;
    
    cout<<"Enter amount to transfer: Rs ";
    cin >> amount;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid input. Please enter a valid amount." << endl;
        waitForKeypress();
        return;
    }
    
    if (transfer(currentUser, receiverUsername, amount)) {
        cout<<"Transfer successful. New balance: Rs " << currentUser.balance << endl;
    }
    
    waitForKeypress();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForKeypress() {
    cout<<"Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}