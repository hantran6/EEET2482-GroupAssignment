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
    double creditPoints;
    double buyerRating;
    double sellerRating;

    std::vector<int> sellerRatings;
    std::vector<int> buyerRatings;

public:
    Member(std::string username, std::string password, std::string fullName, std::string phoneNumber,
           std::string email, std::string idType, std::string idNumber, UserRole role);

    // Member-specific methods
    void topUpCredits(AuctionSystem &auctionSystem);
    bool canPlaceBid(double newBidAmount, AuctionSystem &auctionSystem) const;
    void placeBid(int itemId, double bidAmount, AuctionSystem &auctionSystem);
    void addActiveBid(int itemId);
    void removeActiveBid(int itemId);
    bool hasActiveBid(int itemId) const;

    void viewAvailableListings(AuctionSystem &auctionSystem);
    void viewMyListings(AuctionSystem &auctionSystem);
    void createListing(AuctionSystem &auctionSystem);
    void editListing(AuctionSystem &auctionSystem);
    void removeListing(AuctionSystem &auctionSystem);
    void viewProfile() const;

    // Getters
    double getCreditPoints() const;
    double getBuyerRating() const;
    double getSellerRating() const;
    const std::vector<int> &getActiveBids() const;
    const std::vector<int> &getSellerRatings() const { return sellerRatings; }
    const std::vector<int> &getBuyerRatings() const { return buyerRatings; }

    // Setters
    void setCreditPoints(double points);
    void setBuyerRating(double rating);
    void setSellerRating(double rating);
    void setSellerRatings(const std::vector<int> &ratings) { sellerRatings = ratings; }
    void setBuyerRatings(const std::vector<int> &ratings) { buyerRatings = ratings; }

    // Updating profiles
    void updateFullName(const std::string &newFullName, AuctionSystem &auctionSystem);
    void updatePhoneNumber(const std::string &newPhoneNumber, AuctionSystem &auctionSystem);
    void updateEmail(const std::string &newEmail, AuctionSystem &auctionSystem);
    void updatePassword(const std::string &password, AuctionSystem &auctionSystem);

    void addSellerRating(int rating);
    void addBuyerRating(int rating);
};

#endif
