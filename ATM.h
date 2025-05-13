#ifndef ATM_H
#define ATM_H

#include <string>
#include <vector>
using namespace std;

struct User {
    string username;
    string password;
    double balance;
};

// User management functions
bool registerUser(const string& username, const string& password);
bool loginUser(const string& username, const string& password, User& currentUser);
bool checkUserExists(const string& username);
bool getUserByUsername(const string& username, User& user);

// Account operations
bool deposit(User& user, double amount);
bool withdraw(User& user, double amount);
double checkBalance(const User& user);
bool transfer(User& sender, const string& receiverUsername, double amount);

// File operations
bool saveUser(const User& user);
vector<User> loadUsers();
bool updateUserBalance(const string& username, double newBalance);

#endif