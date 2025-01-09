#include "User.h"
#include <iostream>
using namespace std;

// Default Constructor
User::User() : username(""), password(""), fullName(""), phoneNumber(""), email(""), idType(""), idNumber("") {}

// Parameterized Constructor
User::User(const string& username, const string& password, const string& fullName, const string& phoneNumber,
           const string& email, const string& idType, const string& idNumber)
    : username(username), password(password), fullName(fullName), phoneNumber(phoneNumber),
      email(email), idType(idType), idNumber(idNumber) {}

// Getters
string User::getUsername() const { return username; }
string User::getFullName() const { return fullName; }
string User::getEmail() const { return email; }
string User::getPhoneNumber() const { return phoneNumber; }
string User::getIdType() const { return idType; }
string User::getIdNumber() const { return idNumber; }

// Setters
void User::setFullName(const string& fullName) { this->fullName = fullName; }
void User::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setEmail(const string& email) { this->email = email; }

void User::setPassword(const string& oldPassword, const string& newPassword) {
    if (password == oldPassword) {
        // Implement password strength validation
        if (newPassword.length() >= 8 && newPassword != "12345" && newPassword != "password") {
            password = newPassword;
            cout << "Password successfully updated." << endl;
        } else {
            cout << "New password is too weak. Use a stronger password." << endl;
        }
    } else {
        cout << "Old password is incorrect!" << endl;
    }
}

// Member Functions
bool User::login(const string& username, const string& password) {
    return this->username == username && this->password == password;
}

void User::viewProfile() const {
    cout << "Username: " << username << endl
         << "Full Name: " << fullName << endl
         << "Phone Number: " << phoneNumber << endl
         << "Email: " << email << endl
         << "ID Type: " << idType << endl
         << "ID Number: " << idNumber << endl;
}

void User::updateProfile(const string& fullName, const string& phoneNumber, const string& email) {
    setFullName(fullName);
    setPhoneNumber(phoneNumber);
    setEmail(email);
    cout << "Profile updated successfully!" << endl;
}
