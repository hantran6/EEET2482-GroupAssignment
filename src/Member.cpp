#include "../include/Member.h"
#include "../include/Item.h"   
#include "../include/Bid.h"    
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor
Member::Member() : creditPoints(0), sellerRating(3.0), buyerRating(3.0) {}

// Getters
int Member::getCreditPoints() const {
    return creditPoints;
}

float Member::getSellerRating() const {
    return sellerRating;
}

float Member::getBuyerRating() const {
    return buyerRating;
}

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
    sellerRating = (sellerRating + rating) / 2; 
}

void Member::addBuyerRating(float rating) {
    buyerRating = (buyerRating + rating) / 2; 
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
    cout << "Item \"" << item.getName() << "\" successfully created!" << endl;
}

void Member::updateItem(int itemId, const Item& updatedItem) {
    auto it = find_if(activeListings.begin(), activeListings.end(),
                      [itemId](const Item& item) { return item.getId() == itemId; });

    if (it != activeListings.end()) {
        *it = updatedItem;
        cout << "Item \"" << updatedItem.getName() << "\" successfully updated!" << endl;
    } else {
        cout << "Item with ID " << itemId << " not found in active listings." << endl;
    }
}

void Member::removeItem(int itemId) {
    auto it = remove_if(activeListings.begin(), activeListings.end(),
                        [itemId](const Item& item) { return item.getId() == itemId; });

    if (it != activeListings.end()) {
        activeListings.erase(it, activeListings.end());
        cout << "Item with ID " << itemId << " successfully removed!" << endl;
    } else {
        cout << "Item with ID " << itemId << " not found or cannot be removed." << endl;
    }
}

// Buyer Functions
vector<Item> Member::searchItems(const string& criteria, const string& category, int minCP, int maxCP) {
    vector<Item> results;

    for (const Item& item : activeListings) {
        bool matchesCriteria = item.getName().find(criteria) != string::npos;
        bool matchesCategory = (category.empty() || item.getCategory() == category);
        bool matchesCPRange = (item.getStartingBid() >= minCP && item.getStartingBid() <= maxCP);

        if (matchesCriteria && matchesCategory && matchesCPRange) {
            results.push_back(item);
        }
    }

    return results;
}

void Member::viewItemDetails(int itemId) const {
    auto it = find_if(activeListings.begin(), activeListings.end(),
                      [itemId](const Item& item) { return item.getId() == itemId; });

    if (it != activeListings.end()) {
        cout << "Item Details:" << endl;
        cout << "Name: " << it->getName() << endl;
        cout << "Category: " << it->getCategory() << endl;
        cout << "Current Bid: " << it->getCurrentBid() << " CP" << endl;
        cout << "End Time: " << it->getEndTime() << endl;
    } else {
        cout << "Item with ID " << itemId << " not found." << endl;
    }
}


