#include "Member.h"
#include <iostream>

Member::Member(std::string username, std::string password, std::string fullName,
               std::string phoneNumber, std::string email, std::string idType,
               std::string idNumber, UserRole role = UserRole::Member)
    : User(username, password, fullName, phoneNumber, email, idType, idNumber, role),
      buyerRating(3.0), sellerRating(3.0) {}

void Member::placeBid(int itemId, int bidAmount)
{
    activeBids.push_back(itemId);
    std::cout << "Bid placed successfully!" << std::endl;
}

void Member::createListing(int itemId)
{
    std::cout << "Listing created successfully for item ID: " << itemId << std::endl;
}

void Member::rateTransaction(const std::string &role, double rating)
{
    if (role == "buyer")
    {
        buyerRating = (buyerRating + rating) / 2.0;
    }
    else if (role == "seller")
    {
        sellerRating = (sellerRating + rating) / 2.0;
    }
}

void Member::viewProfile() const
{
    std::cout << "\n========== Your Profile ==========\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Full Name: " << fullName << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Credit Points: " << creditPoints << "\n";
    std::cout << "Buyer Rating: " << buyerRating << "\n";
    std::cout << "Seller Rating: " << sellerRating << "\n";
    std::cout << "==================================\n";
}

void Member::updateFullName(const std::string &newFullName)
{
    fullName = newFullName;
    Utils::showSuccess("Full name updated successfully.");
}

void Member::updatePhoneNumber(const std::string &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
    Utils::showSuccess("Phone number updated successfully.");
}

void Member::updateEmail(const std::string &newEmail)
{
    if (Utils::isValidEmail(newEmail)) // Validation here
    {
        email = newEmail;
        Utils::showSuccess("Email updated successfully.");
    }
    else
    {
        Utils::showError("Failed to update email. Invalid format.");
    }
}

void Member::updatePassword(const std::string &newPassword)
{
    if (Utils::isValidPassword(newPassword)) // Validation here
    {
        password = newPassword;
        Utils::showSuccess("Password updated successfully.");
    }
    else
    {
        Utils::showError("Failed to update password. Invalid format.");
    }
}

double Member::getBuyerRating() const
{
    return buyerRating;
}

double Member::getSellerRating() const
{
    return sellerRating;
}
