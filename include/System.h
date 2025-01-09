#ifndef SYSTEM_H
#define SYSTEM_H
#include "../database/FileDatabase.h"

#include "../users/User.h"
#include "../users/Member.h"
#include "../users/Admin.h"
#include "../users/Guest.h"
#include <vector>
#include <string>

class System
{
private:
    vector<User *> users; // List of registered users (Members and Admins)
    User *loggedInUser;   // Currently logged-in user (nullptr if Guest)
    Guest guest;          // Guest object for browsing as a non-member
    string usersDataFile; // File path for storing user data
    FileDatabase userDatabase;

public:
    System();
    ~System();

    void start();

    // Redirect to corresponding user dashboard
    void displayProjectInfo();
    void displayMainMenu();
    void displayGuestMenu();
    void displayMemberMenu();
    void displayAdminMenu();

    // Guests functions
    void browseAsGuest();
    void registerUser();

    // Member and admin functions
    void loginUser(UserRole role);
    void logoutUser();

    // Load and save data
    void loadData();
    void saveData();
};

#endif