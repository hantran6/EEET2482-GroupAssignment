#include "Member.h"
#include <iostream>
using namespace std;

// Constructor
Member::Member() : creditPoints(0), sellerRating(3.0), buyerRating(3.0) {}

// Getters
int Member::getCreditPoints() const { return creditPoints; }
float Member::getSellerRating() const { return sellerRating; }
float Member::getBuyerRating() const { return buyerRating; }

// Member Functions
void Member::topUpCredit(int amount, const string& password) {
    if (this->password == password) {
        creditPoints += amount;
        cout << "Successfully topped up " << amount << " CP. Current balance: " << creditPoints << " CP." << endl;
    } else {
        cout << "Password incorrect. Transaction failed." << endl;
    }
}

void Member::addSellerRating(float rating) {
    sellerRating = (sellerRating + rating) / 2;  // Averaging the ratings
}

void Member::addBuyerRating(float rating) {
    buyerRating = (buyerRating + rating) / 2;  // Averaging the ratings
}

float Member::viewOwnAvgRating(bool isSeller) const {
    return isSeller ? sellerRating : buyerRating;
}

void Member::checkCPBalance() const {
    cout << "Credit Points Balance: " << creditPoints << " CP." << endl;
}

// Seller Functions
void Member::createItem(const Item& item) {
    activeListings.push_back(item);
    cout << "Item successfully created!" << endl;
}

void Member::updateItem(int itemId, const Item& updatedItem) {
    cout << "Item successfully updated!" << endl;
}

void Member::removeItem(int itemId) {
    cout << "Item successfully removed!" << endl;
}

// Buyer Functions
vector<Item> Member::searchItems(const string& criteria, const string& category, int minCP, int maxCP) {
    vector<Item> results;
    // Logic to filter items based on criteria
    return results;
}

void Member::viewItemDetails(int itemId) const {
    cout << "Displaying item details..." << endl;
}

void Member::placeBid(int itemId, int bidAmount) {
    if (creditPoints >= bidAmount) {
        creditPoints -= bidAmount;  // Deduct bid amount temporarily
        cout << "Bid of " << bidAmount << " CP placed on item " << itemId << "." << endl;
    } else {
        cout << "Insufficient credit points!" << endl;
    }
}
