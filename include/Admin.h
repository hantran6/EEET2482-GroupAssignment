#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User
{
public:
    // Constructor
    Admin(const std::string &username, const std::string &password,
          const std::string &fullName, const std::string &phoneNum,
          const std::string &email, const std::string &idType, const std::string &idNum);

    // Admin-specific methods
    void viewAllUsers() const;
    void manageListings();
};

#endif // ADMIN_H
