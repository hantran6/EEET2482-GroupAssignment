#include "Admin.h"
#include <iostream>

using namespace std;

// Constructor
Admin::Admin(const string &username, const string &password,
             const string &fullName, const string &phoneNum,
             const string &email, const string &idType, const string &idNum)
    : User(username, password, fullName, phoneNum, email, idType, idNum, UserRole::Admin) {}

// View all users (placeholder - implementation depends on the system's user list structure)
void Admin::viewAllUsers() const
{
    cout << "\n=== All Registered Users ===\n";
    // Iterate through a list of users in the System class to display them.
    cout << "User viewing functionality is not yet implemented.\n";
}

// Manage listings (placeholder - implementation depends on auction listing structure)
void Admin::manageListings()
{
    cout << "\n=== Manage Listings ===\n";
    // Provide admin-specific tools to manage auctions here.
    cout << "Listing management functionality is not yet implemented.\n";
}
