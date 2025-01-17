#include "Menu.h"
#include "Utils.h"
#include <iostream>

int main()
{
    AuctionSystem auctionSystem;

    // Load data from the database
    auctionSystem.loadUsers("./data/users.csv");
    auctionSystem.loadItems("./data/items.csv");

    displayWelcomeScreen();

    while (true)
    {
        std::cout << "\n========== User Role Selection Page ==========\n";
        std::cout << "Are you a: \n";
        std::cout << "1. Guest\n";
        std::cout << "2. Member\n";
        std::cout << "3. Admin\n";
        std::cout << "0. Exit\n";

        std::cout << "Enter your choice: ";
        int userType;
        std::cin >> userType;

        switch (userType)
        {
        case 1:
            // Guest Menu
            displayGuestMenu(auctionSystem);
            break;
        case 2:
        {
            // Login before accessing Member Menu
            User *user = auctionSystem.loginMember();
            if (user)
            {
                Member *member = dynamic_cast<Member *>(user);
                if (member)
                {
                    displayMemberMenu(auctionSystem, *member);
                }
            }
            break;
        }
        case 3:
        {
            // Login before accessing Admin Menu
            User *admin = auctionSystem.loginAdmin();
            if (admin)
            {
                Admin *adminUser = dynamic_cast<Admin *>(admin);
                if (adminUser)
                {
                    displayAdminMenu(auctionSystem, *adminUser);
                }
            }
            break;
        }
        case 4:
            // Save all data and exit
            auctionSystem.saveUsers("./data/users.csv");
            auctionSystem.saveItems("./data/items.csv");
            Utils::showInfo("Exiting the application. Goodbye!");
            return 0;
        default:
            Utils::showError("Invalid choice.Please try again.");
            break;
        }
    }
}
