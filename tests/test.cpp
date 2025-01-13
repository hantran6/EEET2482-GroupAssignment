#include "../src/system/System.h"
#include "../src/users/Member.h"
#include "../src/users/Admin.h"
#include "../src/users/Guest.h"
#include <iostream>
#include <cassert>

void testGuestBrowsing()
{
    Guest guest;
    std::cout << "\n=== Test: Guest Browsing ===\n";
    guest.browseItemsLimited();
}

void testMemberActions()
{
    Member member("john_doe", "P@ssw0rd", "John Doe", "123456789", "john@example.com", "Passport", "A123456");

    std::cout << "\n=== Test: Member Actions ===\n";
    assert(member.getUsername() == "john_doe");
    assert(member.getPassword() == "P@ssw0rd");

    member.addCreditPoints(100);
    assert(member.getCreditPoints() == 100);

    member.createListing("PlayStation 5");
    member.createListing("Rare Coin Set");
    member.viewListings();

    member.placeBid("PS5 Auction");
    member.viewBids();
}

void testAdminActions()
{
    Admin admin("admin_user", "AdminP@ss", "Admin User", "987654321", "admin@example.com", "CitizenID", "B987654");

    std::cout << "\n=== Test: Admin Actions ===\n";
    assert(admin.getUsername() == "admin_user");
    assert(admin.getPassword() == "AdminP@ss");

    admin.viewAllUsers();
    admin.manageListings();
}

void testSystemRegistrationAndLogin()
{
    System system;

    std::cout << "\n=== Test: User Registration and Login ===\n";

    // Test registration
    // system.registerUser(); // Manually enter details for registration
    system.saveData();     // Ensure new user data is saved to the file

    // Test login as Member
    std::cout << "\nLogin as Member:\n";
    system.loginUser(UserRole::Member);

    // Test login as Admin
    std::cout << "\nLogin as Admin:\n";
    system.loginUser(UserRole::Admin);

    // Test logout
    system.logoutUser();
}

int main()
{
    try
    {
        // Test Guest Browsing
        testGuestBrowsing();

        // Test Member Actions
        testMemberActions();

        // Test Admin Actions
        testAdminActions();

        // Test Registration and Login
        testSystemRegistrationAndLogin();

        std::cout << "\nAll tests completed successfully!\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred.\n";
    }

    return 0;
}
