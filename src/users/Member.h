#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <vector>
#include <string>

class Member : public User
{
private:
    int creditPoints;                        // Member's credit points balance
    std::vector<std::string> activeListings; // Member's active auction listings
    std::vector<std::string> activeBids;     // Member's active bids

public:
    // Constructor
    Member(const std::string &username, const std::string &password,
           const std::string &fullName, const std::string &phoneNum,
           const std::string &email, const std::string &idType, const std::string &idNum);

    // Member-specific methods
    void addCreditPoints(int amount);
    void createListing(const std::string &listing);
    void placeBid(const std::string &bid);
    void viewListings() const;
    void viewBids() const;

    // Getters
    int getCreditPoints() const;
};

#endif
