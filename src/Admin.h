#ifndef ADMIN_H
#define ADMIN_H

#include "Member.h"
#include "Item.h" // Assuming you have an Item class
#include <vector>

class Admin : public User
{
public:
    // Constructor
    Admin(std::string username, std::string password, UserRole role);

    // Admin-specific methods
    void viewAllProfiles(const std::vector<User *> &members) const;
};

#endif // ADMIN_H
