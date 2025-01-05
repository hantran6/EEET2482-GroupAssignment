#ifndef SYSTEM_H
#define SYSTEM_H

#include "../users/User.h"
// #include "Member.h"
// #include "Admin.h"
#include "../users/Guest.h"
#include <vector>
#include <string>

class System
{
private:
    vector<User *> users;      // List of registered users (Members and Admins)
    User *loggedInUser;        // Currently logged-in user (nullptr if Guest)
    Guest guest;               // Guest object for browsing as a non-member
    std::string usersDataFile; // File path for storing user data

public:
    System();
    ~System();

    void start();

    // Guests functions
    void browseAsGuest();
    // void registerUser();

    // Member and admin functions
    // void loginUser(UserRole role);
    // void logoutUser();

    // Redirect to corresponding user dashboard
    void displayProjectInfo();
    void displayMainMenu();
    // void displayMemberMenu();
    // void displayAdminMenu();

    // Load and save data
    void loadData();
    void saveData();
};

#endif