#include "Menu.h"
#include <limits>
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
            auctionSystem.viewLimitedInfoListing();
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
        std::cout << "4. Seller Actions\n";
        std::cout << "5. Buyer Actions\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            member.viewProfile();
            break;
        case 2:
            displayUpdateProfileMenu(auctionSystem, member);
            break;
        case 3:
            member.topUpCredits(auctionSystem);
            break;
        case 4:
            displaySellerMenu(auctionSystem, member);
            break;
        case 5:
            displayBuyerMenu(auctionSystem, member);
            break;
        case 0:
            saveAndExit(auctionSystem);
            break;
        default:
            Utils::showError("Invalid choice. Please try again.");
            break;
        }
    } while (choice != 0);
}

void displaySellerMenu(AuctionSystem &auctionSystem, Member &member)
{
    int choice;
    do
    {
        std::cout << "\n========== Seller Actions ==========\n";
        std::cout << "1. View My Listings\n";
        std::cout << "2. Create Listing\n";
        std::cout << "3. Update Listing\n";
        std::cout << "4. Delete Listing\n";
        std::cout << "0. Back to Member Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            member.viewMyListings(auctionSystem);
            break;
        case 2:
            member.createListing(auctionSystem);
            break;
        case 3:
            member.editListing(auctionSystem);
            break;
        case 4:
            member.removeListing(auctionSystem);
            break;
        case 0:
            return; // Return to the main member menu
        default:
            Utils::showError("Invalid choice. Please try again.");
            break;
        }
    } while (choice != 0);
}

void displayBuyerMenu(AuctionSystem &auctionSystem, Member &member)
{
    int choice;
    do
    {
        std::cout << "\n========== Buyer Actions ==========\n";
        std::cout << "1. View All Available Listings\n";
        std::cout << "2. Search for Items\n";
        std::cout << "3. View Item Details\n";
        std::cout << "4. Place a Bid\n";
        std::cout << "0. Back to Member Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            member.viewAvailableListings(auctionSystem);
            break;
        case 2:
        {
            std::string name, category;
            double minCredits = 0.0, maxCredits = 0.0;

            std::cin.ignore(); // Clear the input buffer
            std::cout << "Enter item name (leave blank for any): ";
            std::getline(std::cin, name);

            std::cout << "Enter category (leave blank for any): ";
            std::getline(std::cin, category);

            std::cout << "Enter minimum credits (leave 0 for no minimum): ";
            std::cin >> minCredits;

            std::cout << "Enter maximum credits (leave 0 for no maximum): ";
            std::cin >> maxCredits;

            if (maxCredits == 0)
                maxCredits = std::numeric_limits<double>::max(); // No maximum limit if 0

            std::vector<Item> searchResults = auctionSystem.searchItems(name, category, minCredits, maxCredits);
            if (searchResults.empty())
            {
                std::cout << "No items found matching the criteria.\n";
            }
            else
            {
                std::cout << "\n========== Search Results ==========\n";
                for (const auto &item : searchResults)
                {
                    std::cout << "Item ID: " << item.getId() << "\n"
                              << "Name: " << item.getName() << "\n"
                              << "Category: " << item.getCategory() << "\n"
                              << "Starting Bid: " << item.getStartingBid() << " CP\n"
                              << "Auction Ends At: " << item.getEndDateTime() << "\n"
                              << "-----------------------------------------\n";
                }
            }
            break;
        }
        case 3:
        {
            int itemId;
            std::cout << "Enter item ID to view details: ";
            std::cin >> itemId;

            auctionSystem.viewItemDetails(itemId);
            break;
        }
        case 4:
            int itemId;
            double bidAmount;

            std::cout << "Enter the item ID you want to bid on: ";
            std::cin >> itemId;
            std::cout << "Enter your bid amount: ";
            std::cin >> bidAmount;

            auctionSystem.placeBid(itemId, bidAmount, member);
            break;
        case 0:
            return; // Return to the main member menu
        default:
            Utils::showError("Invalid choice. Please try again.");
            break;
        }
    } while (choice != 0);
}

void displayUpdateProfileMenu(AuctionSystem &auctionSystem, Member &member)
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
            member.updateFullName(newFullName, auctionSystem); // Delegate to Member
            break;
        }
        case 2:
        {
            std::string newPhoneNumber;
            std::cout << "Enter new phone number: ";
            std::getline(std::cin, newPhoneNumber);
            member.updatePhoneNumber(newPhoneNumber, auctionSystem); // Delegate to Member
            break;
        }
        case 3:
        {
            std::string newEmail;
            std::cout << "Enter new email: ";
            std::getline(std::cin, newEmail);
            member.updateEmail(newEmail, auctionSystem);
            break;
        }
        case 4:
        {
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::getline(std::cin, newPassword);
            member.updatePassword(newPassword, auctionSystem);
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
