#include "Member.h"
#include "AuctionSystem.h"

#include <iostream>
#include <regex>

Member::Member(std::string username, std::string password, std::string fullName,
               std::string phoneNumber, std::string email, std::string idType,
               std::string idNumber, UserRole role = UserRole::Member)
    : User(username, password, fullName, phoneNumber, email, idType, idNumber, role),
      buyerRating(3.0), sellerRating(3.0) {}

// CRUD items =========================================================================================================================================
void Member::viewMyListings(AuctionSystem &auctionSystem)
{
    // Get the list of items from the AuctionSystem
    const std::vector<Item> &items = auctionSystem.getItems();

    if (items.empty())
    {
        std::cout << "No listings available at the moment.\n";
        return;
    }

    std::cout << "\n========== My Listings ==========\n";

    bool hasListings = false; // Track if the user has any listings

    for (const auto &item : items)
    {
        // Check if the item belongs to the current user
        if (item.getSellerUsername() == this->username) // Compare seller username with current user's username
        {
            hasListings = true;
            // Display the details of the user's item
            std::cout << "Item ID: " << item.getId() << "\n"
                      << "Name: " << item.getName() << "\n"
                      << "Category: " << item.getCategory() << "\n"
                      << "Description: " << item.getDescription() << "\n"
                      << "Starting Bid: " << item.getStartingBid() << " CP\n"
                      << "Current Bid: " << (item.getCurrentBid() > 0 ? item.getCurrentBid() : item.getStartingBid()) << " CP\n"
                      << "Bid Increment: " << item.getBidIncrement() << " CP\n"
                      << "Minimum Buyer Rating: " << item.getMinRating() << "\n"
                      << "Auction Ends At: " << item.getEndDateTime() << "\n"
                      << "-----------------------------------------\n";
        }
    }

    if (!hasListings)
    {
        std::cout << "You have no active listings.\n";
    }
}

void Member::createListing(AuctionSystem &auctionSystem)
{
    std::string name, category, description, endDateTime;
    int startingBid, bidIncrement, minRating;

    std::cin.ignore(); // Clear buffer before reading inputs

    std::cout << "Enter item name: ";
    std::getline(std::cin, name);

    std::cout << "Enter category: ";
    std::getline(std::cin, category);

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    std::cout << "Enter starting bid: ";
    std::cin >> startingBid;
    std::cin.ignore(); // Clear buffer after numeric input

    std::cout << "Enter bid increment: ";
    std::cin >> bidIncrement;
    std::cin.ignore(); // Clear buffer after numeric input

    std::cout << "Enter minimum buyer rating: ";
    std::cin >> minRating;
    std::cin.ignore(); // Clear buffer after numeric input

    // Validate end date & time
    std::regex dateTimeRegex(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
    while (true)
    {
        std::cout << "Enter auction end date & time (YYYY-MM-DD HH:MM:SS): ";
        std::getline(std::cin, endDateTime);

        if (!std::regex_match(endDateTime, dateTimeRegex))
        {
            Utils::showError("Invalid date & time format. Please use YYYY-MM-DD HH:MM:SS.");
            continue;
        }

        // Check if the end date & time is in the past
        std::string currentDateTime = Utils::getCurrentDateTime();
        if (Utils::isDateTimeInPast(endDateTime))
        {
            Utils::showError("Auction end date & time cannot be in the past. Please enter a future date & time.");
        }
        else
        {
            break; // Valid date and time
        }
    }

    // Automatically set the ID and start date & time
    int id = auctionSystem.generateItemId();
    std::string startDateTime = Utils::getCurrentDateTime(); // Fetch the current date and time

    // Create the new item
    Item newItem(id, name, category, description, startingBid, bidIncrement, username, minRating);
    newItem.setStartDateTime(startDateTime); // Automatically set start date & time
    newItem.setEndDateTime(endDateTime);     // Set the user-provided end date & time
    newItem.setHasActiveBids(false);         // No active bids on creation

    // Add the new item to the auction system
    auctionSystem.addItem(newItem);

    Utils::showSuccess("Item listing created successfully.");
}

void Member::editListing(AuctionSystem &auctionSystem)
{
    int itemId;
    std::cout << "Enter item ID to edit: ";
    std::cin >> itemId;
    std::cin.ignore();

    Item *item = auctionSystem.getItemById(itemId);
    if (!item || item->getSellerUsername() != username)
    {
        Utils::showError("Item not found or you are not the seller.");
        return;
    }
    if (item->getHasActiveBids())
    {
        Utils::showError("Cannot edit listing. Active bids exist.");
        return;
    }

    std::string newName, newCategory, newDescription, newEndDateTime;
    int newStartingBid = -1, newBidIncrement = -1, newMinRating = -1;

    std::cout << "\nTo retain the old value, leave the field blank and press Enter.\n";

    std::cout << "Enter new item name (current: " << item->getName() << "): ";
    std::getline(std::cin, newName);
    if (newName.empty())
        newName = item->getName();

    std::cout << "Enter new category (current: " << item->getCategory() << "): ";
    std::getline(std::cin, newCategory);
    if (newCategory.empty())
        newCategory = item->getCategory();

    std::cout << "Enter new description (current: " << item->getDescription() << "): ";
    std::getline(std::cin, newDescription);
    if (newDescription.empty())
        newDescription = item->getDescription();

    std::cout << "Enter new starting bid (current: " << item->getStartingBid() << "): ";
    std::string startingBidInput;
    std::getline(std::cin, startingBidInput);
    if (!startingBidInput.empty())
        newStartingBid = std::stoi(startingBidInput);

    std::cout << "Enter new bid increment (current: " << item->getBidIncrement() << "): ";
    std::string bidIncrementInput;
    std::getline(std::cin, bidIncrementInput);
    if (!bidIncrementInput.empty())
        newBidIncrement = std::stoi(bidIncrementInput);

    std::cout << "Enter new minimum buyer rating (current: " << item->getMinRating() << "): ";
    std::string minRatingInput;
    std::getline(std::cin, minRatingInput);
    if (!minRatingInput.empty())
        newMinRating = std::stoi(minRatingInput);

    // Validate new end date & time
    std::regex dateTimeRegex(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
    while (true)
    {
        std::cout << "Enter new auction end date & time (current: " << item->getEndDateTime() << ", format: YYYY-MM-DD HH:MM:SS): ";
        std::getline(std::cin, newEndDateTime);

        if (newEndDateTime.empty())
        {
            newEndDateTime = item->getEndDateTime(); // Retain old value
            break;
        }

        if (!std::regex_match(newEndDateTime, dateTimeRegex))
        {
            Utils::showError("Invalid date & time format. Please use YYYY-MM-DD HH:MM:SS.");
            continue;
        }

        std::string currentDateTime = Utils::getCurrentDateTime();
        if (Utils::isDateTimeInPast(newEndDateTime))
        {
            Utils::showError("Auction end date & time cannot be in the past. Please enter a future date & time.");
        }
        else
        {
            break; // Valid date and time
        }
    }

    // Update item attributes
    item->setName(newName);
    item->setCategory(newCategory);
    item->setDescription(newDescription);
    item->setStartingBid(newStartingBid > 0 ? newStartingBid : item->getStartingBid());
    item->setBidIncrement(newBidIncrement > 0 ? newBidIncrement : item->getBidIncrement());
    item->setMinRating(newMinRating > 0 ? newMinRating : item->getMinRating());
    item->setEndDateTime(newEndDateTime);

    // Save changes to the database
    auctionSystem.saveItems("./data/items.csv");

    Utils::showSuccess("Item listing updated successfully.");
}

void Member::removeListing(AuctionSystem &auctionSystem)
{
    int itemId;
    std::cout << "Enter item ID to remove: ";
    std::cin >> itemId;
    std::cin.ignore();

    Item *item = auctionSystem.getItemById(itemId);
    if (!item || item->getSellerUsername() != username)
    {
        Utils::showError("Item not found or you are not the seller.");
        return;
    }
    if (item->getHasActiveBids())
    {
        Utils::showError("Cannot remove listing. Active bids exist.");
        return;
    }

    auctionSystem.removeItem(itemId);
    Utils::showSuccess("Item listing removed and database updated successfully.");
}

// Profile Management ==================================================================================================================================
void Member::viewProfile() const
{
    std::cout << "\n========== Your Profile ==========\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Full Name: " << fullName << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Credit Points: " << creditPoints << "\n";
    std::cout << "Buyer Rating: " << buyerRating << "\n";
    std::cout << "Seller Rating: " << sellerRating << "\n";
    std::cout << "==================================\n";
}

void Member::updateFullName(const std::string &newFullName, AuctionSystem &auctionSystem)
{
    fullName = newFullName;
    Utils::showSuccess("Full name updated successfully.");
    auctionSystem.saveUsers("./data/users.csv"); // Save the updated user data
}

void Member::updatePhoneNumber(const std::string &newPhoneNumber, AuctionSystem &auctionSystem)
{
    phoneNumber = newPhoneNumber;
    Utils::showSuccess("Phone number updated successfully.");
    auctionSystem.saveUsers("./data/users.csv"); // Save the updated user data
}

void Member::updateEmail(const std::string &newEmail, AuctionSystem &auctionSystem)
{
    if (Utils::isValidEmail(newEmail)) // Validation here
    {
        email = newEmail;
        Utils::showSuccess("Email updated successfully.");
        auctionSystem.saveUsers("./data/users.csv"); // Save the updated user data
    }
    else
    {
        Utils::showError("Failed to update email. Invalid format.");
    }
}

void Member::updatePassword(const std::string &newPassword, AuctionSystem &auctionSystem)
{
    if (Utils::isValidPassword(newPassword)) // Validation here
    {
        password = newPassword;
        Utils::showSuccess("Password updated successfully.");
        auctionSystem.saveUsers("./data/users.csv"); // Save the updated user data
    }
    else
    {
        Utils::showError("Failed to update password. Invalid format.");
    }
}

// Actions =================================================================================================================================================
void Member::topUpCredits(AuctionSystem &auctionSystem)
{
    double amount;

    std::cout << "Enter the amount to top up: ";
    std::cin >> amount;

    if (amount <= 0)
    {
        Utils::showError("Amount must be greater than 0.");
        return;
    }

    // Update the member's credit balance
    creditPoints += amount;

    auctionSystem.saveUsers("./data/users.csv");
    Utils::showSuccess("Credits successfully topped up!");
    Utils::showInfo("Your new credit balance is: " + std::to_string(creditPoints) + " CP");
}

// Buyers actions =======================================================================================================================================
void Member::viewAvailableListings(AuctionSystem &auctionSystem)
{
    const auto &items = auctionSystem.getItems(); // Retrieve all items from the auction system

    // Check if there are no items available
    if (items.empty())
    {
        std::cout << "\nNo items are currently available for auction.\n";
        return;
    }

    std::cout << "\n========== All Available Listings ==========\n";

    // Get the current date and time
    std::string currentDateTime = Utils::getCurrentDateTime();
    bool hasListings = false; // Track if any listings are displayed

    // Iterate through each item and apply filters
    for (const auto &item : items)
    {
        // Skip items where:
        // 1. The auction end time is in the past
        // 2. The current user's buyer rating is less than the minimum required rating
        // 3. The current user is not the seller
        if (Utils::isDateTimeInPast(item.getEndDateTime()) ||
            (item.getSellerUsername() != username && buyerRating < item.getMinRating()))
        {
            continue;
        }

        hasListings = true;

        // Display the item's details
        std::cout << "Item ID: " << item.getId() << "\n"
                  << "Name: " << item.getName() << "\n"
                  << "Category: " << item.getCategory() << "\n"
                  << "Starting Bid: " << item.getStartingBid() << " CP\n"
                  << "Current Bid: " << (item.getCurrentBid() > 0 ? item.getCurrentBid() : item.getStartingBid()) << " CP\n"
                  << "Auction Ends At: " << item.getEndDateTime() << "\n"
                  << "-----------------------------------------\n";
    }

    // If no listings are available
    if (!hasListings)
    {
        std::cout << "No listings available that match your criteria.\n";
    }
}

const std::vector<int> &Member::getActiveBids() const
{
    return activeBids;
}

void Member::addActiveBid(int itemId)
{
    activeBids.push_back(itemId);
}

void Member::removeActiveBid(int itemId)
{
    auto it = std::find(activeBids.begin(), activeBids.end(), itemId);
    if (it != activeBids.end())
    {
        activeBids.erase(it);
    }
}

// Helper method to check if a member can place a bid
// bool Member::canPlaceBid(double newBidAmount, AuctionSystem &auctionSystem) const
// {
//     double totalActiveBids = 0.0;

//     // Calculate the total of active bids
//     for (int itemId : activeBids)
//     {
//         Item *item = auctionSystem.getItemById(itemId);
//         if (item != nullptr)
//         {
//             totalActiveBids += item->getCurrentBid();
//         }
//     }

//     // Check if the member has enough credit points
//     return (creditPoints >= (totalActiveBids + newBidAmount));
// }

// void Member::placeBid(int itemId, double bidAmount, AuctionSystem &auctionSystem)
// {
//     Item *item = auctionSystem.getItemById(itemId);
//     if (item == nullptr)
//     {
//         Utils::showError("Item not found.");
//         return;
//     }

//     // Check if the new bid is valid (higher than the current bid + bid increment)
//     double minimumRequiredBid = item->getCurrentBid() > 0 ? (item->getCurrentBid() + item->getBidIncrement()) : item->getStartingBid();
//     if (bidAmount < minimumRequiredBid)
//     {
//         Utils::showError("Bid amount is too low. Must be at least the current bid + increment or the starting bid.");
//         return;
//     }

//     // Check if the buyer has enough credit points to cover all active bids
//     if (!canPlaceBid(bidAmount, auctionSystem))
//     {
//         Utils::showError("Insufficient credit points to place this bid.");
//         return;
//     }

//     // Place the bid
//     item->setCurrentBid(bidAmount);
//     item->setHighestBidder(username); // Assuming username identifies the member
//     activeBids.push_back(itemId);

//     Utils::showSuccess("Bid placed successfully!");
// }

// Getter and setters ====================================================================================================================================

// Getter for creditPoints
double Member::getCreditPoints() const
{
    return creditPoints;
}

// Setter for creditPoints
void Member::setCreditPoints(double points)
{
    creditPoints = points;
}

// Getter for buyerRating
double Member::getBuyerRating() const
{
    return buyerRating;
}

// Setter for buyerRating
void Member::setBuyerRating(double rating)
{
    buyerRating = rating;
}

// Getter for sellerRating
double Member::getSellerRating() const
{
    return sellerRating;
}

// Setter for sellerRating
void Member::setSellerRating(double rating)
{
    sellerRating = rating;
}
