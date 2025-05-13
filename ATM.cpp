#include "ATM.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

// file path for user database
const string USER_FILE = "users.txt";

// user management functions
bool registerUser(const string& username, const string& password) {
    // check if user already exists
    if (checkUserExists(username)) {
        cout<<"Username already exists. Please choose another one." << endl;
        return false;
    }
    
    // create new user
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.balance = 0.0;
    
    // save user to file
    return saveUser(newUser);
}

bool loginUser(const string& username, const string& password, User& currentUser) {
    vector<User> users = loadUsers();
    
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            currentUser = user;
            return true;
        }
    }
    
    return false;
}

bool checkUserExists(const string& username) {
    vector<User> users = loadUsers();
    
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    
    return false;
}

bool getUserByUsername(const string& username, User& user) {
    vector<User> users = loadUsers();
    
    for (const User& u : users) {
        if (u.username == username) {
            user = u;
            return true;
        }
    }
    
    return false;
}

// ------------------------------ Account operations ------------------------------
bool deposit(User& user, double amount) {
    if (amount <= 0) {
        cout<<"Invalid amount. Please enter a positive value." << endl;
        return false;
    }
    
    user.balance += amount;
    return updateUserBalance(user.username, user.balance);
}

bool withdraw(User& user, double amount) {
    if (amount <= 0) {
        cout<<"Invalid amount. Please enter a positive value." << endl;
        return false;
    }
    
    if (user.balance < amount) {
        cout<<"Insufficient funds. Your balance is Rs " << user.balance << endl;
        return false;
    }
    
    user.balance -= amount;
    return updateUserBalance(user.username, user.balance);
}

double checkBalance(const User& user) {
    return user.balance;
}

bool transfer(User& sender, const string& receiverUsername, double amount) {
    if (amount <= 0) {
        cout<<"Invalid amount. Please enter a positive value." << endl;
        return false;
    }
    
    if (sender.balance < amount) {
        cout<<"Insufficient funds. Your balance is Rs " << sender.balance << endl;
        return false;
    }
    
    User receiver;
    if (!getUserByUsername(receiverUsername, receiver)) {
        cout<<"Receiver not found. Please check the username." << endl;
        return false;
    }
    
    // update sender's balance
    sender.balance -= amount;
    if (!updateUserBalance(sender.username, sender.balance)) {
        return false;
    }
    
    // update receiver's balance
    receiver.balance += amount;
    return updateUserBalance(receiver.username, receiver.balance);
}

// ------------------------------ File operations ------------------------------
bool saveUser(const User& user) {
    vector<User> users = loadUsers();
    bool userExists = false;
    
    for (User& u : users) {
        if (u.username == user.username) {
            u = user;
            userExists = true;
            break;
        }
    }
    
    if (!userExists) {
        users.push_back(user);
    }
    
    ofstream file(USER_FILE);
    if (!file) {
        cout<<"Error opening file for writing." << endl;
        return false;
    }
    
    for (const User& u : users) {
        file << u.username << "," << u.password << "," << u.balance << endl;
    }
    
    file.close();
    return true;
}

vector<User> loadUsers() {
    vector<User> users;
    ifstream file(USER_FILE);
    
    if (!file) {
        // file doesn't exist yet, which is fine for a new system
        return users;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password, balanceStr;
        
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, balanceStr, ',');
        
        User user;
        user.username = username;
        user.password = password;
        user.balance = stod(balanceStr);
        
        users.push_back(user);
    }
    
    file.close();
    return users;
}

bool updateUserBalance(const string& username, double newBalance) {
    vector<User> users = loadUsers();
    
    for (User& user : users) {
        if (user.username == username) {
            user.balance = newBalance;
            
            ofstream file(USER_FILE);
            if (!file) {
                cout<<"Error opening file for writing." << endl;
                return false;
            }
            
            for (const User& u : users) {
                file << u.username << "," << u.password << "," << u.balance << endl;
            }
            
            file.close();
            return true;
        }
    }
    
    return false;
}