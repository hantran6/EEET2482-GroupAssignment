#include "System.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
System::System() : userDatabase("../data/users.dat")
{
    users.push_back(new Admin("admin", "Admin@123", "System Admin", "0000000000", "admin@example.com", "CitizenID", "ADMIN001"));

    loadData();
}

// Destructor
System::~System()
{
    saveData(); // Save data on exit

    for (auto user : users)
    {
        delete user; // Free the memory allocated
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
    cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n"
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
    cout << "\n=== Auction Application ===\n"
         << "1. Guest\n"
         << "2. Member\n"
         << "3. Admin\n"
         << "0. Exit\n";
}

// Display the Guest menu
void System::displayGuestMenu()
{
    int choice;
    do
    {
        cout << "\n===== Guest Menu =====\n"
             << "1. Register as a Member\n"
             << "2. Browse as Guest\n"
             << "0. Return to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser();
            return;
        case 2:
            browseAsGuest(); // Call the simplified browseAsGuest function
            break;
        case 0:
            cout << "Returning to Main Menu...\n";
            return; // Exit guest menu
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Display the Member menu
void System::displayMemberMenu()
{
    int choice;
    do
    {
        cout << "\n===== Member Menu =====\n"
             << "1. option 1\n"
             << "2. option 2\n"
             << "0. Return to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Replace with real option" << endl;
            break;
        case 2:
            cout << "Replace with real option" << endl;
            break;
        case 0:
            cout << "Returning to Main Menu...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Display the Admin menu
void System::displayAdminMenu()
{
    int choice;
    do
    {
        cout << "\n===== Admin Menu =====\n"
             << "1. option 1\n"
             << "2. option 2\n"
             << "0. Return to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Replace with real option" << endl;
            break;
        case 2:
            cout << "Replace with real option" << endl;
            break;
        case 0:
            cout << "Returning to Main Menu...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Guest: Browse as guest, display items with limited information
void System::browseAsGuest()
{
    guest.browseItemsLimited();
}

// Guest: Register as Member
void System::registerUser()
{
    string username, password, fullName, phoneNum, email, idType, idNum;

    cout << "\n=== Register New User ===\n";

    // Get and validate username
    cout << "Enter username: ";
    cin >> username;

    // Ensure unique username
    for (const auto user : users)
    {
        if (user->getUsername() == username)
        {
            cout << "Error: Username already exists. Please choose another.\n";
            return;
        }
    }

    // Get and validate password
    do
    {
        cout << "Enter password (must include uppercase, lowercase, number, and special character): ";
        cin >> password;
        if (!User::validatePassword(password))
        {
            cout << "Weak password! Please try again.\n";
        }
    } while (!User::validatePassword(password));

    // Get other details
    cin.ignore(); // Clear input buffer
    cout << "Enter full name: ";
    getline(cin, fullName);
    cout << "Enter phone number: ";
    cin >> phoneNum;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter ID type (e.g., Passport, Citizen ID): ";
    cin >> idType;
    cout << "Enter ID number: ";
    cin >> idNum;

    // Create a new Member user
    User *newUser = new Member(username, password, fullName, phoneNum, email, idType, idNum);

    // Add to in-memory list
    users.push_back(newUser);

    // Save to file
    ostringstream oss;
    oss << username << "," << password << "," << fullName << "," << phoneNum << "," << email << ","
        << idType << "," << idNum << "," << static_cast<int>(UserRole::Member);

    userDatabase.appendLine(oss.str());

    cout << "Account registered successfully! You can now log in as a member.\n";
}

// Admin + Member: Login
void System::loginUser(UserRole role)
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (const auto user : users)
    {
        if (user->getUsername() == username && user->getPassword() == password)
        {
            if (user->getRole() == role)
            {
                loggedInUser = user;
                cout << "Logged in successfully as " << (role == UserRole::Admin ? "Admin" : "Member") << ".\n";
                return;
            }
        }
    }

    cout << "Invalid credentials or role mismatch.\n";
}

void System::logoutUser()
{

    // REPLACE WITH REAL LOGICS

    cout << "Logged out successfully. Goodbye!" << endl;
}

// Load data from the file
void System::loadData()
{
    auto lines = userDatabase.readAllLines();

    for (const auto &line : lines)
    {
        istringstream iss(line);
        string username, password, fullName, phoneNum, email, idType, idNum;
        int role;

        iss >> username >> password >> fullName >> phoneNum >> email >> idType >> idNum >> role;

        if (static_cast<UserRole>(role) == UserRole::Member)
        {
            users.push_back(new Member(username, password, fullName, phoneNum, email, idType, idNum));
        }
        else if (static_cast<UserRole>(role) == UserRole::Admin)
        {
            users.push_back(new Admin(username, password, fullName, phoneNum, email, idType, idNum));
        }
    }

    cout << "User data loaded successfully.\n";
}

// Save data to the file
void System::saveData()
{

    // REPLACE WITH REAL LOGICS

    cout << "Data saved successfully." << endl;
}
