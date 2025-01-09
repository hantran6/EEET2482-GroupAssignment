#include "Member.h"
#include <iostream>

using namespace std;

// Constructor
Member::Member(const string &username, const string &password,
               const string &fullName, const string &phoneNum,
               const string &email, const string &idType, const string &idNum)
    : User(username, password, fullName, phoneNum, email, idType, idNum, UserRole::Member),
      creditPoints(0) {}

// Add credit points
void Member::addCreditPoints(int amount) {
    if (amount > 0) {
        creditPoints += amount;
        cout << amount << " credit points added. New balance: " << creditPoints << " CP.\n";
    } else {
        cout << "Invalid amount. Cannot add credit points.\n";
    }
}

// Create a new auction listing
void Member::createListing(const string &listing) {
    activeListings.push_back(listing);
    cout << "Listing added: " << listing << "\n";
}

// Place a bid
void Member::placeBid(const string &bid) {
    activeBids.push_back(bid);
    cout << "Bid placed: " << bid << "\n";
}

// View active listings
void Member::viewListings() const {
    cout << "\n=== Active Listings ===\n";
    for (const auto &listing : activeListings) {
        cout << listing << "\n";
    }
}

// View active bids
void Member::viewBids() const {
    cout << "\n=== Active Bids ===\n";
    for (const auto &bid : activeBids) {
        cout << bid << "\n";
    }
}

// Get current credit points
int Member::getCreditPoints() const {
    return creditPoints;
}
