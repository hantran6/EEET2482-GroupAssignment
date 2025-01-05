#include "System.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
System::System() : usersDataFile("../../data/users.txt"), loggedInUser(nullptr)
{
    loadData();
}

// Destructor
System::~System()
{
    saveData();

    // Free the memory allocated
    for (auto user : users)
    {
        delete user;
    }
}

void System::start()
{
    displayProjectInfo();
    int choice;
    do
    {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            browseAsGuest();
            break;
        case 2:
            cout << "Member option" << endl;
            // loginUser(UserRole::Member);
            break;
        case 3:
            cout << "Admin option" << endl;
            // loginUser(UserRole::Admin);
            break;
        case 0:
            cout << "Exiting the application. Goodbye" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// Display welcome screen
void System::displayProjectInfo()
{
    std::cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n"
              << "Semester 3 2024\n"
              << "AUCTION APPLICATION\n"
              << "\nInstructor: Dr Ling Huo Chong\n"
              << "Group: Group 9\n"
              << "s4103086, Nguyen Viet Ngan Anh\n"
              << "s4145060, Ly Kieu Anh Hoang\n"
              << "s3969997, Rybak Polina\n"
              << "s3963227, Tran Nguyen Ngoc Han\n";
}

// Display the main menu
void System::displayMainMenu()
{
    std::cout << "\n=== Auction Application ===\n"
              << "1. Guest\n"
              << "2. Member\n"
              << "3. Admin\n"
              << "0. Exit\n";
}

// Guest functionality
void System::browseAsGuest()
{
    guest.browseItemsLimited();
}

// Load data from the file
void System::loadData() {
    std::cout << "Loading data" << std::endl;
    // Implement file reading and user data loading here
}

// Save data to the file
void System::saveData() {
    std::cout << "Saving data" << std::endl;
    // Implement file saving logic here
}
