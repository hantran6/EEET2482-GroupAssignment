#ifndef USER_H
#define USER_H

#include <string>

enum class UserRole
{
    Admin,
    Member
};

class User
{
protected:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    UserRole role;
    int creditPoints;
    double buyerRating;
    double sellerRating;

public:
    User(std::string username, std::string password, std::string fullName, std::string phoneNumber,
         std::string email, std::string idType, std::string idNumber, UserRole role);

    virtual ~User();

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getIdType() const;
    std::string getIdNumber() const;
    UserRole getRole() const;
    int getCreditPoints() const;
    double getBuyerRating() const;
    double getSellerRating() const;

    // Setters
    void setUsername(std::string &username);
    void setPassword(std::string &password);
    void setBuyerRating(double rating);
    void setSellerRating(double rating);

    // Actions
    void topUpCredits(int amount);
    bool validatePassword(const std::string &password) const;
};

#endif