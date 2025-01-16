#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include "Member.h"
#include "Utils.h"
#include "Item.h"
#include <vector>
#include <string>

class AuctionSystem;

class Member : public User
{
private:
    std::vector<int> activeBids; // Track item IDs with active bids
    double buyerRating;
    double sellerRating;

public:
    Member(std::string username, std::string password, std::string fullName, std::string phoneNumber,
           std::string email, std::string idType, std::string idNumber, UserRole(role));

    // Member-specific methods
    void placeBid(int itemId, int bidAmount);
    void viewMyListings(AuctionSystem &auctionSystem);
    void createListing(AuctionSystem &auctionSystem);
    void editListing(AuctionSystem &auctionSystem);
    void removeListing(AuctionSystem &auctionSystem);
    // void rateTransaction(const std::string &role, double rating);

    void viewProfile() const;

    // Getters
    double getBuyerRating() const;
    double getSellerRating() const;
    int getItemById() const;

    // Updating profiles
    void updateFullName(const std::string &newFullName);
    void updatePhoneNumber(const std::string &newPhoneNumber);
    void updateEmail(const std::string &newEmail);
    void updatePassword(const std::string &password);
};

#endif
