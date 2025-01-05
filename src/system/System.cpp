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
    saveData();                 // Save data on exit

    for (auto user : users)
    {
        delete user;            // Free the memory allocated
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
            displayGuestMenu();
            break;
        case 2:
            // loginUser(UserRole::Member);
            cout << "Member selected: Replace this with login logics!" << endl;
            break;
        case 3:
            cout << "Admin selected: Replace this with login logics!" << endl;
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

// Display Project Details 
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

// Display the Main menu
void System::displayMainMenu()
{
    std::cout << "\n=== Auction Application ===\n"
              << "1. Guest\n"
              << "2. Member\n"
              << "3. Admin\n"
              << "0. Exit\n";
}

// Display the Guest menu
void System::displayGuestMenu() {
    int choice;
    do {
        std::cout << "\n===== Guest Menu =====\n"
                  << "1. Register as a Member\n"
                  << "2. Browse as Guest\n"
                  << "0. Return to Main Menu\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                return;
            case 2:
                browseAsGuest(); // Call the simplified browseAsGuest function
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                return; // Exit guest menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Display the Member menu
void System::displayMemberMenu() {
    int choice;
    do {
        std::cout << "\n===== Member Menu =====\n"
                  << "1. option 1\n"
                  << "2. option 2\n"
                  << "0. Return to Main Menu\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                cout << "Replace with real option" << endl;
                break;
            case 2:
                cout << "Replace with real option" << endl;
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                return; 
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Display the Admin menu
void System::displayAdminMenu() {
    int choice;
    do {
        std::cout << "\n===== Admin Menu =====\n"
                  << "1. option 1\n"
                  << "2. option 2\n"
                  << "0. Return to Main Menu\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                cout << "Replace with real option" << endl;
                break;
            case 2:
                cout << "Replace with real option" << endl;
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                return; 
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Guest: Browse as guest, display items with limited information
void System::browseAsGuest(){
    guest.browseItemsLimited();
}


// Guest: Register as Member
void System::registerUser() {

    // REPLACE WITH REAL LOGICS

    cout << "Account registered successfully" << endl;
}


// Admin + Member: Login
void System::loginUser(UserRole role){
    
    // REPLACE WITH REAL LOGICS

    cout << "Logged in successfully." << endl;
}

void System::logoutUser(){
    
    // REPLACE WITH REAL LOGICS

    cout << "Logged out successfully. Goodbye!" << endl;
}

// Load data from the file
void System::loadData() {

    // REPLACE WITH REAL LOGICS

    cout << "Data Loaded successfully." << endl;
}


// Save data to the file
void System::saveData() {

    // REPLACE WITH REAL LOGICS

    cout << "Data saved successfully." << endl;
}
