#include "User.h"
#include <iostream>
#include <regex>

using namespace std;

// Default Constructor
User::User() : username(""), password(""), fullName(""), phoneNum(""), email(""), idType(""), idNum(""), role(UserRole::Member) {}

// Parameterized Constructor
User::User(const string &username, const string &password, const string &fullName, const string &phoneNum, const string &email, const string &idType, const string &idNum, UserRole role)
    : username(username), password(password), fullName(fullName), phoneNum(phoneNum), email(email), idType(idType), idNum(idNum), role(role) {}

// Destructor
User::~User(){}

// Getters
string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password; 
}

string User::getFullName() const {
    return fullName;
}

string User::getPhoneNum() const {
    return phoneNum;
}

string User::getEmail() const {
    return email;
}

string User::getIdType() const {
    return idType;
}

string User::getIdNum() const {
    return idNum;
}

UserRole User::getRole() const {
    return role;
}

// Display profile
void User::displayProfile() const {
    cout << "Username: " << username << "\n"
         << "Full Name: " << fullName << "\n"
         << "Phone Number: " << phoneNum << "\n"
         << "Email: " << email << "\n"
         << "ID Type: " << idType << "\n"
         << "ID Number: " << idNum << "\n"
         << "Role: " << (role == UserRole::Member ? "Member" : "Admin") << "\n";
}

// Update Profile
void User::updateProfile(){
    // REPLACE WITH REAL LOGIC AND PARAMS


    
    cout << "Profile updated successfully" << endl;
} 


// Validate Password - Ensure strong password
bool User::validatePassword(const string &password) {
    const regex passwordPattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return regex_match(password, passwordPattern);
}