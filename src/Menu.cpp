#include "Menu.h"

#include <iostream>

// General ===============================================================================================
// Display welcome screen
void displayWelcomeScreen()
{
    std::cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n";
    std::cout << "Semester 3 2024\n";
    std::cout << "AUCTION APPLICATION\n\n";
    std::cout << "Instructor: Dr Ling Huo Chong\n";
    std::cout << "Group: Group 9\n";
    std::cout << "s4103086, Nguyen Viet Ngan Anh\n";
    std::cout << "s4145060, Ly Kieu Anh Hoang\n";
    std::cout << "s3969997, Rybak Polina\n";
    std::cout << "s3963227, Tran Nguyen Ngoc Han\n\n";
}

void saveAndExit(AuctionSystem &auctionSystem)
{
    auctionSystem.saveUsers("./data/users.csv");
    auctionSystem.saveItems("./data/items.csv");
    Utils::showInfo("Exiting the application. Goodbye!");
    std::exit(0);
}

// Guest ================================================================================================
void displayGuestMenu(AuctionSystem &auctionSystem)
{
    bool isRunning = true;

    while (isRunning)
    {
        std::cout << "\n========== Guest Menu ==========\n";
        std::cout << "1. Register an account.\n";
        std::cout << "2. Browse items as a guest.\n";
        std::cout << "3. Back to main menu.\n";
        std::cout << "0. Exit.\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Register a new account
            std::cout << "\n\n========== Register Account ==========\n";
            auctionSystem.registerMember();
            break;
        }
        case 2:
            // Display items for guests to view
            std::cout << "Guest browsing functionality is not yet implemented.\n";
            break;
        case 3:
            isRunning = false;
            break;
        case 0:
            saveAndExit(auctionSystem);
        default:
            Utils::showError("Invalid choice. Please try again.");
            break;
        }
    }
}

// Member ================================================================================================
void displayMemberMenu(AuctionSystem &auctionSystem, Member &member)
{
    int choice;
    do
    {
        std::cout << "\n========== Member Menu ==========\n";
        std::cout << "1. View Profile\n";
        std::cout << "2. Update Profile\n";
        std::cout << "3. Top Up Credit Points\n";

        // As Seller
        std::cout << "4. View Listing\n";
        std::cout << "5. Create Listing\n";
        std::cout << "6. Update Listing\n";
        std::cout << "7. Delete Listing\n";

        // As Buyer
        std::cout << "8. Search for items\n";
        std::cout << "9. View item details\n";
        std::cout << "10. Place a bid";

        std::cout << "11. Back to Main Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            member.viewProfile();
            break;
        case 2:
            displayUpdateProfileMenu(member);
            break;
        case 3:
            // top up credit
            break;
        case 4:
            return;
        case 0:
            saveAndExit(auctionSystem);
        default:
            Utils::showError("Invalid choice.Please try again.");
            break;
        }
    } while (true);
}

void displayUpdateProfileMenu(Member &member)
{
    int choice;
    do
    {
        std::cout << "\n========== Update Profile ==========\n";
        std::cout << "1. Update Full Name\n";
        std::cout << "2. Update Phone Number\n";
        std::cout << "3. Update Email\n";
        std::cout << "4. Update Password\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(); // Ignore leftover newline
        switch (choice)
        {
        case 1:
        {
            std::string newFullName;
            std::cout << "Enter new full name: ";
            std::getline(std::cin, newFullName);
            member.updateFullName(newFullName); // Delegate to Member
            break;
        }
        case 2:
        {
            std::string newPhoneNumber;
            std::cout << "Enter new phone number: ";
            std::getline(std::cin, newPhoneNumber);
            member.updatePhoneNumber(newPhoneNumber); // Delegate to Member
            break;
        }
        case 3:
        {
            std::string newEmail;
            std::cout << "Enter new email: ";
            std::getline(std::cin, newEmail);
            member.updateEmail(newEmail);
            break;
        }
        case 4:
        {
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::getline(std::cin, newPassword);
            member.updatePassword(newPassword);
            break;
        }
        case 0:
            std::cout << "Exiting update profile menu.\n";
            return;
        default:
            Utils::showError("Invalid choice. Please try again.");
        }
    } while (true);
}

// Admin =================================================================================================
void displayAdminMenu(AuctionSystem &auctionSystem, Admin &admin)
{
    int choice;
    do
    {
        std::cout << "\n========== Admin Menu ==========\n";
        std::cout << "1. View All Members\n";
        std::cout << "2. View All Listings\n";
        std::cout << "3. Back to Main Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            admin.viewAllMembers(auctionSystem.getMembers());
            break;
        case 2:
            // Listings logic
            break;
        case 3:
            return; // Return to the main menu
        case 0:
            saveAndExit(auctionSystem);
        default:
            Utils::showError("Invalid choice.Please try again.");
            break;
        }
    } while (true);
}
