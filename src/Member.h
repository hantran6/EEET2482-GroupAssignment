#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include "Member.h"
#include "Utils.h"
#include "Item.h"
#include "AuctionSystem.h"
#include <vector>
#include <string>

class Member : public User
{
private:
    std::vector<int> activeBids; // Track item IDs with active bids
    //rating that a buyer receives
    double buyerRating;
    //rating that a seller receives
    double sellerRating;

    std::vector<double> buyerRatingList;
    std::vector<double> sellerRatingList;

public:
    Member(std::string username, std::string password, std::string fullName, std::string phoneNumber,
           std::string email, std::string idType, std::string idNumber, UserRole(role));

    // Member-specific methods
    void placeBid(int auctionId, int itemId, int bidAmount);
    // void createListing(AuctionSystem &auctionSystem);
    // void editListing(AuctionSystem &auctionSystem);
    // void removeListing(AuctionSystem &auctionSystem);
    // void rateTransaction(const std::string &role, double rating);


    void viewProfile() const;

    // Getters
    double getBuyerRating() const;
    double getSellerRating() const;

    std::vector<double> getBuyerRatingList() const;
    std::vector<double> getSellerRatingList() const;

    // Updating profiles
    void updateFullName(const std::string &newFullName);
    void updatePhoneNumber(const std::string &newPhoneNumber);
    void updateEmail(const std::string &newEmail);
    void updatePassword(const std::string &password);
};

#endif
