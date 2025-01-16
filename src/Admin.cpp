#include "Admin.h"
#include <iostream>

Admin::Admin(std::string username, std::string password, UserRole role)
    : User(username, password, "", "", "", "", "", role) {}

// Admin-specific methods
void Admin::viewAllProfiles(const std::vector<User *> &members) const
{
    std::cout << "========== All Members ==========\n";
    for (const auto &user : members)
    {
        if (user->getRole() == UserRole::Member)
        {
            std::cout << "Username: " << user->getUsername()
                      << ", Full Name: " << user->getFullName()
                      << ", Email: " << user->getEmail();
        }
    }
    std::cout << "=================================\n";
}

// void Admin::viewAllListings() const
// {
//     std::cout << "Admin viewing all listings..." << std::endl;
//     // Add logic to iterate and display all listings
// }
