#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <vector>
using namespace std;

class Item;  // Forward Declaration
class Bid;   // Forward Declaration

class Member : public User {
private:
    int creditPoints;
    float sellerRating;
    float buyerRating;
    vector<Bid> activeBids;
    vector<Item> activeListings;

public:
    Member();

    // Getters
    int getCreditPoints() const;
    float getSellerRating() const;
    float getBuyerRating() const;

    // Member Functions
    void topUpCredit(int amount, const string& password);
    void addSellerRating(float rating);
    void addBuyerRating(float rating);
    float viewOwnAvgRating(bool isSeller) const;
    void checkCPBalance() const;

    void createItem(const Item& item);
    void updateItem(int itemId, const Item& updatedItem);
    void removeItem(int itemId);

    vector<Item> searchItems(const string& criteria, const string& category, int minCP, int maxCP);
    void viewItemDetails(int itemId) const;
    void placeBid(int itemId, int bidAmount);
};

#endif // MEMBER_H
