#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
    string fullName;
    string phoneNumber;
    string email;
    string idType;  // CitizenID/Passport
    string idNumber;

public:
    User();
    User(const string& username, const string& password, const string& fullName, const string& phoneNumber, 
         const string& email, const string& idType, const string& idNumber);

    // Getters
    string getUsername() const;
    string getFullName() const;
    string getEmail() const;
    string getPhoneNumber() const;
    string getIdType() const;
    string getIdNumber() const;

    // Setters
    void setFullName(const string& fullName);
    void setPhoneNumber(const string& phoneNumber);
    void setEmail(const string& email);
    void setPassword(const string& oldPassword, const string& newPassword);

    // Member Functions
    virtual bool login(const string& username, const string& password);
    virtual void viewProfile() const;
    virtual void updateProfile(const string& fullName, const string& phoneNumber, const string& email);
};

#endif // USER_H
