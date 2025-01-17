#include "Admin.h"
#include <iostream>

Admin::Admin(std::string username, std::string password, UserRole role)
    : User(username, password, "", "", "", "", "", role) {}

// Admin-specific methods
void Admin::viewAllMembers(const std::vector<User *> &members) const
{
    for (const auto &user : members)
    {
        std::cout << "Username: " << user->getUsername();

        // Check if the user is a Member and display additional details
        if (user->getRole() == UserRole::Member)
        {
            Member *member = dynamic_cast<Member *>(user);
            if (member)
            {
                std::cout << ", Credit Points: " << member->getCreditPoints()
                          << ", Buyer Rating: " << member->getBuyerRating()
                          << ", Seller Rating: " << member->getSellerRating();
            }
        }

        std::cout << "\n";
    }
}

void Admin::viewAllListings(const std::vector<Item> &items) const {
    std::cout << "\n========== All Listings ==========\n";

    if (items.empty()) {
        std::cout << "No items available.\n";
        return;
    }

    for (const auto &item : items) {
        std::cout << "ID: " << item.getId()
                  << ", Name: " << item.getName()
                  << ", Category: " << item.getCategory()
                  << ", Starting Bid: " << item.getStartingBid()
                  << ", Current Bid: " << item.getCurrentBid()
                  << ", Seller: " << item.getSellerUsername()
                  << ", Highest Bidder: " << (item.getHighestBidder().empty() ? "None" : item.getHighestBidder())
                  << ", Status: " << (item.getIsActive() ? "Active" : "Concluded")
                  << "\n";
    }

    std::cout << "==================================\n";
}