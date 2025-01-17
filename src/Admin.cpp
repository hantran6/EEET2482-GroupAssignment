#include "Admin.h"
#include <iostream>

Admin::Admin(std::string username, std::string password, UserRole role)
    : User(username, password, "", "", "", "", "", role) {}

// Admin-specific methods
void Admin::viewAllProfiles(const std::vector<User *> &members) const
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

// void Admin::viewAllListings() const
// {
//     std::cout << "Admin viewing all listings..." << std::endl;
//     // Add logic to iterate and display all listings
// }
