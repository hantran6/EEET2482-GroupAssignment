#include "User.h"

User::User(std::string username, std::string password, std::string fullName, std::string phoneNumber,
           std::string email, std::string idType, std::string idNumber, UserRole role)
    : username(username), password(password), fullName(fullName), phoneNumber(phoneNumber),
      email(email), idType(idType), idNumber(idNumber), creditPoints(0), buyerRating(3.0), sellerRating(3.0), role(role) {}

User::~User() {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getEmail() const { return email; }
std::string User::getIdType() const { return idType; }
std::string User::getIdNumber() const { return idNumber; }
UserRole User::getRole() const { return role; }
int User::getCreditPoints() const { return creditPoints; }
double User::getBuyerRating() const { return buyerRating; }
double User::getSellerRating() const { return sellerRating; }

void User::setUsername(std::string &username) { this->username = username; }
void User::setPassword(std::string &password) { this->password = password; }
void User::setBuyerRating(double rating) { buyerRating = rating; }
void User::setSellerRating(double rating) { sellerRating = rating; }

void User::topUpCredits(int amount) { creditPoints += amount; }

bool User::validatePassword(const std::string &pwd) const { return password == pwd; }
